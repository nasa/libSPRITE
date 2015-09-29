#ifndef __SRTX_MESSAGE_H__
#define __SRTX_MESSAGE_H__

#include "units/Nanoseconds.h"

namespace SRTX {
    /**
     * This is a strongly typed message that is communicated through the
     * pub/sub system.
     * @param T The type of data carried by the message.
     */
    template <typename T> class Message {
      public:
        /**
         * Constructor.
         */
        Message()
            : content()
            , m_time_of_publication(-1)
            , m_publication_period(-1)
        {
        }

        /**
         * Destructor.
         */
        virtual ~Message()
        {
        }

        /**
         * Get the time of the most recent time of message update.
         * @return The time of the most recent publication in
         * Nanoseconds. A value of -1 indicates an error.
         */
        units::Nanoseconds get_publication_time() const
        {
            return m_time_of_publication;
        }

        /**
         * The data portion of the message.
         */
        T content;

        /**
         * Time when the message was last published.
         */
        units::Nanoseconds m_time_of_publication;

      protected:
        /**
         * Rate at which the publication is expected to be updated.
         */
        units::Nanoseconds m_publication_period;
    };

} // namespace

#endif // __SRTX_MESSAGE_H__
