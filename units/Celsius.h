/******************************************************************************
 * Copyright (c) 2014 - Daniel L. Heater
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/

#ifndef __UNITS_CELSIUS_H__
#define __UNITS_CELSIUS_H__

namespace units
{

    class Celsius
    {
        public:

            /**
             * Constructor.
             * @param v Number of seconds.
             */
            explicit Celsius(double v = 0.0)
                : m_value(v)
            {
            }


            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }


            /**
             * Overload operator+
             * @param rhs Right hand side of the operation.
             * @return The added value
             */
            Celsius operator+(const Celsius& rhs) const
            {
                return Celsius(m_value + rhs.m_value);
            }


            /**
             * Overload operator-
             * @param rhs Right hand side of the operation.
             * @return The subtracted value.
             */
            Celsius operator-(const Celsius& rhs) const
            {
                return Celsius(m_value - rhs.m_value);
            }


            /**
             * Overload operator+=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value added.
             */
            Celsius& operator+=(const Celsius& rhs)
            {
                m_value += rhs.m_value;

                return *this;
            }


            /**
             * Overload operator-=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value subtracted.
             */
            Celsius& operator-=(const Celsius& rhs)
            {
                m_value -= rhs.m_value;

                return *this;
            }

        private:

            /**
             * Stored number of seconds.
             */
            double m_value;
    };


} // namespace

#endif // __UNITS_CELSIUS_H__
