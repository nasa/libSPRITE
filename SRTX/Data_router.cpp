#include <string.h>
#include "base/XPRINTF.h"
#include "SRTX/Data_router.h"
#include "util/Linked_list.h"

namespace SRTX {

    /* These are data elements that we will transfer from source to destination
     * on a periodic basis.
     */
    struct Transfer_item {
        Transfer_item(Base_double_buffer &s, Base_double_buffer &d,
                      unsigned int n, units::Nanoseconds p)
            : source(s)
            , dest(d)
            , nbytes(n)
            , period(p)
            , last_update_count(0)
        {
        }

        Base_double_buffer &source;
        Base_double_buffer &dest;
        unsigned int nbytes;
        const units::Nanoseconds period;
        unsigned int last_update_count;
    };
    typedef util::Linked_list<Transfer_item *> Transfer_list;

    /* These are subscription request that are waiting to be matched up with a
     * publication.
     */
    struct Orphan_item {
        Orphan_item(const char *n, units::Nanoseconds p, Base_double_buffer &b)
            : name(n)
            , period(p)
            , buffer(b)
        {
        }

        const char *name;
        units::Nanoseconds period;
        Base_double_buffer &buffer;
    };
    typedef util::Linked_list<Orphan_item *> Orphan_list;

    /* Internal implementation dependent stuff. See PIMPL pattern.
     */
    struct Data_router_impl {
        /**
         * Constructor.
         */
        Data_router_impl()
            : transfer()
            , orphan()
        {
        }

        /* A linked list of data items that need to be moved at a specific
         * period.
         */
        Transfer_list transfer;

        /* A linked list of orphaned subscriptions.
         */
        Orphan_list orphan;
    };

    Data_router::Data_router() : m_impl(new Data_router_impl)
    {
    }

    Data_router::~Data_router()
    {
        delete m_impl;
    }

    bool Data_router::register_transfer(Base_double_buffer &source,
                                        Base_double_buffer &dest,
                                        unsigned int nbytes,
                                        units::Nanoseconds period)
    {
        m_impl->transfer.add_back(
            new Transfer_item(source, dest, nbytes, period));

        return true;
    }

    void Data_router::register_orphan(const char *name,
                                      units::Nanoseconds period,
                                      Base_double_buffer &buffer)
    {
        m_impl->orphan.add_back(new Orphan_item(name, period, buffer));
    }

    void Data_router::adopt_orphans(const char *name,
                                    Base_double_buffer &buffer,
                                    unsigned int nbytes,
                                    units::Nanoseconds period)
    {
        Orphan_list &list = m_impl->orphan;
        Orphan_list::Node *n = list.head();

        DPRINTF("%s: Looking for orphans\n", name);
        while(n) {
            /* If name matches the orphan, tie this publisher to the orphaned
             * subscribers buffer.
             */
            if(0 == strcmp(name, n->data->name)) {
                DPRINTF("Adopting %s%lld\n", n->data->name,
                        int64_t(n->data->period));

                /* If the orphan runs with the same period as the publisher
                 * then they already point to the same symbol table entry,
                 * otherwise, we have to schedule data to be transfered from
                 * one rategoup to the other.
                 */
                if(period != n->data->period) {
                    DPRINTF("Registering transfer for for topic %s from %lld "
                            "nanosecond process to %lld nanoseconds\n",
                            name, int64_t(period), int64_t(n->data->period));
                    units::Nanoseconds slower_period =
                        (period > n->data->period) ? period : n->data->period;
                    this->register_transfer(buffer, n->data->buffer, nbytes,
                                            slower_period);
                }

                /* Now that that orphan has been adopted, we can take it off
                 * the list.
                 */
                Orphan_list::Node *tmp = n;
                n = n->next();
                list.delete_node(tmp);
            } else {
                n = n->next();
            }
        }
    }

    void Data_router::do_transfers(const units::Nanoseconds &ref_time)
    {
        Transfer_list &list = m_impl->transfer;
        Transfer_list::Node *n = list.head();

        while(n) {
            /* If the transfer was registered to take place with a period that
             * begins on this frame boundary, then do the transfer.
             */
            if(0 == (ref_time % n->data->period)) {
                /* We only do the transfer if the publication time has changed.
                 * Otherwise, were wasting our time and we could trigger a
                 * blocking_get() call when there really is no new data.
                 */
                const unsigned int current_update_count =
                    n->data->source.get_update_count();
                if(n->data->last_update_count != current_update_count) {
                    DPRINTF("Transferring %lld period data\n",
                            int64_t(n->data->period));
                    n->data->last_update_count = current_update_count;
                    if(false ==
                       copy(n->data->dest, n->data->source, n->data->nbytes)) {
                        EPRINTF("Error performing data copy\n");
                    }
                }
            }

            n = n->next();
        }
    }

} // namespace
