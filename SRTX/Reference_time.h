
#ifndef __SRTX_REFERENCE_TIME_H__
#define __SRTX_REFERENCE_TIME_H__

#include "units/Nanoseconds.h"

namespace SRTX {

    /**
     * Reference time is an incrementing value referenced to a fixed epoch.
     * This time does not map to a real-time clock and need not increment based
     * real time. In a simulation, this can refer to simulation time. In an
     * embedded system, this may be a representation of real-time that is
     * relative to the reference time and is incremented by the application
     * code in a controlled manner.
     */
    class Reference_time {
      public:
        /**
         * There is a single instance of reference time in a given domain.
         * @return A reference to the domain's reference time class.
         */
        static Reference_time &get_instance()
        {
            static Reference_time instance;

            return instance;
        }

        /**
         * Get the domains current reference time.
         * @return Returns the current time value in nanoseconds.
         */
        units::Nanoseconds get_time();

        /**
         * Increment reference time.
         * @param inc Amount of time to increment by in nanoseconds.
         * @return The new reference time.
         */
        units::Nanoseconds increment(units::Nanoseconds inc)
        {
            return m_value = units::Nanoseconds(m_value + inc);
        }

      private:
        /**
         * Constructor.
         * The constructor is made private as part of the singleton pattern.
         */
        Reference_time();

        /**
         * Copy constructor.
         * The copy constructor is made private as part of the singleton
         * pattern.
         */
        Reference_time(const Reference_time &);

        /**
         * Assignment operator.
         * The assignment operator is made private as part of the singleton
         * pattern.
         */
        Reference_time &operator=(const Reference_time &);

        /**
         * The reference time value is stored in nanoseconds.
         */
        units::Nanoseconds m_value;
    };

    /**
     * Retrieve the domains current reference time value.
     * @return The current time value in nanoseconds.
     */
    units::Nanoseconds get_reference_time();

} // namespace

#endif // __SRTX_REFERENCE_TIME_H__
