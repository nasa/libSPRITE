#ifndef __MATH_EULER_H__
#define __MATH_EULER_H__

#include "units/Radians.h"

namespace math {

    /**
     * Forward declaration of class.
     */
    class DCM;
    class Quaternion;

    class Euler {
      public:
        /**
         * Default constructor.
         */
        Euler()
            : m_roll(0)
            , m_pitch(0)
            , m_yaw(0)
        {
        }

        /**
         * Constructor. Initializes values using radians.
         */
        Euler(units::Radians roll, units::Radians pitch, units::Radians yaw)
            : m_roll(roll)
            , m_pitch(pitch)
            , m_yaw(yaw)
        {
        }

        /**
         * Construct euler angles from a quaternion.
         */
        Euler(const Quaternion q);

        /**
         * Get the value of roll.
         * @return Radians roll.
         */
        units::Radians get_roll() const
        {
            return m_roll;
        }

        /**
         * Set the value of roll.
         * @param roll Roll in radians.
         */
        void set_roll(units::Radians roll)
        {
            m_roll = roll;
        }

        /**
         * Get the value of pitch.
         * @return Radians pitch.
         */
        units::Radians get_pitch() const
        {
            return m_pitch;
        }

        /**
         * Set the value of pitch.
         * @param pitch Pitch in radians.
         */
        void set_pitch(units::Radians pitch)
        {
            m_pitch = pitch;
        }

        /**
         * Get the value of yaw.
         * @return Radians yaw.
         */
        units::Radians get_yaw() const
        {
            return m_yaw;
        }

        /**
         * Set the value of yaw.
         * @param yaw Yaw in radians.
         */
        void set_yaw(units::Radians yaw)
        {
            m_yaw = yaw;
        }

        /**
         * Convert euler angles to a direction cosine matrix.
         * @return the equivalent direction cosine matrix.
         */
        DCM toDCM() const;

        /**
         * Convert euler angles to a quaternion.
         * @return The equivalent quaternion.
         */
        Quaternion toQuaternion() const;

      private:
        units::Radians m_roll;
        units::Radians m_pitch;
        units::Radians m_yaw;
    };

} // namespace

#endif // __MATH_EULER_H__
