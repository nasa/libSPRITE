/******************************************************************************
 * Copyright (c) 2013 - Daniel L. Heater
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

#include "util/Sample_set.h"
#include "util/Sample_set_ut.h"


namespace util
{

    void Sample_set_ut::setUp()
    {
    }


    void Sample_set_ut::tearDown()
    {
    }


    void Sample_set_ut::test_int()
    {
        const unsigned int NELEM = 5;
        Sample_set<int> ss(NELEM);

        CPPUNIT_ASSERT_EQUAL(NELEM, ss.nelem());
        CPPUNIT_ASSERT_EQUAL(0u, ss.npopulated());

        ss.push(1);
        CPPUNIT_ASSERT_EQUAL(1u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(1, ss(1));

        ss.push(2);
        CPPUNIT_ASSERT_EQUAL(2u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(2, ss(1));
        CPPUNIT_ASSERT_EQUAL(1, ss(2));

        ss.push(3);
        CPPUNIT_ASSERT_EQUAL(3u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(3, ss(1));
        CPPUNIT_ASSERT_EQUAL(2, ss(2));
        CPPUNIT_ASSERT_EQUAL(1, ss(3));
        CPPUNIT_ASSERT_EQUAL(false, ss.is_full());

        ss.push(4);
        ss.push(5);
        CPPUNIT_ASSERT_EQUAL(true, ss.is_full());
        ss.push(6);
        CPPUNIT_ASSERT_EQUAL(true, ss.is_full());
        CPPUNIT_ASSERT_EQUAL(NELEM, ss.npopulated());

        CPPUNIT_ASSERT_EQUAL(6, ss(1));
        CPPUNIT_ASSERT_EQUAL(5, ss(2));
        CPPUNIT_ASSERT_EQUAL(4, ss(3));
        CPPUNIT_ASSERT_EQUAL(3, ss(4));
        CPPUNIT_ASSERT_EQUAL(2, ss(5));
    }


    void Sample_set_ut::test_double()
    {
        const unsigned int NELEM = 5;
        Sample_set<double> ss(NELEM);

        CPPUNIT_ASSERT_EQUAL(NELEM, ss.nelem());
        CPPUNIT_ASSERT_EQUAL(0u, ss.npopulated());

        ss.push(1.);
        CPPUNIT_ASSERT_EQUAL(1u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(1., ss(1));

        ss.push(2.);
        CPPUNIT_ASSERT_EQUAL(2u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(2., ss(1));
        CPPUNIT_ASSERT_EQUAL(1., ss(2));

        ss.push(3.);
        CPPUNIT_ASSERT_EQUAL(3u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(3., ss(1));
        CPPUNIT_ASSERT_EQUAL(2., ss(2));
        CPPUNIT_ASSERT_EQUAL(1., ss(3));
        CPPUNIT_ASSERT_EQUAL(false, ss.is_full());

        ss.push(4.);
        ss.push(5.);
        CPPUNIT_ASSERT_EQUAL(true, ss.is_full());
        ss.push(6.);
        CPPUNIT_ASSERT_EQUAL(true, ss.is_full());
        CPPUNIT_ASSERT_EQUAL(NELEM, ss.npopulated());

        CPPUNIT_ASSERT_EQUAL(6., ss(1));
        CPPUNIT_ASSERT_EQUAL(5., ss(2));
        CPPUNIT_ASSERT_EQUAL(4., ss(3));
        CPPUNIT_ASSERT_EQUAL(3., ss(4));
        CPPUNIT_ASSERT_EQUAL(2., ss(5));
    }

} // namespace
