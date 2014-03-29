// $Id$

#ifndef __DEM_DEM_TIMESTAMP_H__
#define __DEM_DEM_TIMESTAMP_H__

#include <assert.h>
#include <string.h>
#include "DEM/DEM_definitions.h"
#include "units/Nanoseconds.h"

namespace DEM
{

    class DEM_timestamp
    {
        public:

            /* One would expect us to initialize the DEM_timestamp to zero in
             * the constructor, however, because it is included in the DEM
             * header which is part of a union that defines a DEM, this is not
             * permitted by the compiler.
             */
#if 0
            /**
             * Construct a DEM timestamp using Nanoseconds.
             */
            DEM_timestamp() :
                m_seconds_msw(0),
                m_seconds_lsw(0),
                m_milliseconds(0)
        {
        }
#endif

            /**
             * Return the number of seconds in the timestamp
             */
            uint32_t get_seconds() const
            {
                return (DEM_SWAP(m_seconds_msw) << 16) |
                    DEM_SWAP(m_seconds_lsw);
            }

            /**
             * Set the number of seconds in the timestamp.
             */
            void set_seconds(uint32_t seconds)
            {
                m_seconds_msw = DEM_SWAP(seconds >> 16);
                m_seconds_lsw = DEM_SWAP(seconds & 0xffff);
            }

            /**
             * Return the number of milliseconds in the timestamp.
             */
            uint16_t get_milliseconds() const
            {
                return DEM_SWAP(m_milliseconds) >> 6;
            }

#if (__GNUC__ >= 4) && (__GNUC_MINOR__ > 1)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif
            /**
             * Set the number of milliseconds in the timestamp.
             * @param  milliseconds number of milliseconds to set to.
             * @warning It is illegal to set the milliseconds value to greater
             * than 999.
             */
            void set_milliseconds(uint16_t milliseconds)
            {
                assert(milliseconds <= 999);
                /* I know that I may be using an uninitialized m_milliseconds.
                 * I cannot initialize it in a constructor (see comment #if 0
                 * comment around the constructor). variable here. So this is
                 * where I am initializing the variable instead. GNU compiler
                 * version 4.2 and up let me selective suppress this warning.
                 * Earlier version do not.
                 */
                m_milliseconds = DEM_SWAP((DEM_SWAP(m_milliseconds) & ~0xFFC0) |
                        milliseconds << 6);
            }
#if (__GNUC__ >= 4) && (__GNUC_MINOR__ > 1)
#pragma GCC diagnostic pop
#endif

            /**
             * Get time value.
             */
            double get_time() const
            {
                return get_seconds() + get_milliseconds() / 1000.0;
            }

            /**
             * Test for equality.
             * @param ts right hand side operator.
             * @return true if the DEM timestamps are identical,
             * otherwise, false.
             */
            bool operator==(const DEM_timestamp& ts) const
            {
                return (get_seconds() == ts.get_seconds()) &&
                    (get_milliseconds() == ts.get_milliseconds());
            }


            /**
             * Test for inequality.
             * @param ts right hand side operator.
             * @return false if the DEM timestamps are identical,
             * otherwise, true.
             */
            bool operator!=(const DEM_timestamp ts) const
            {
                return !(*this == ts);
            }


            /**
             * Assign the timestamp a new value.
             * @param n Value to assign the timestamp to in nanoseconds.
             * @return The updated timestamp value.
             */
            DEM_timestamp& operator=(const units::Nanoseconds& n)
            {
                this->set_seconds(n / units::SEC);
                this->set_milliseconds((n % units::SEC) / units::MSEC);
                return *this;
            }

        private:
            uint16_t m_seconds_msw;
            uint16_t m_seconds_lsw;
            uint16_t m_milliseconds;
    } __attribute__ ((packed));

} // namespace

#endif // __DEM_DEM_TIMESTAMP_H__
