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

#ifndef __UTIL_SAMPLE_SET_UT_H__
#define __UTIL_SAMPLE_SET_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace util
{

    class Sample_set_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Sample_set_ut);

        CPPUNIT_TEST(test_int);
        CPPUNIT_TEST(test_double);

        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test_int();
        void test_double();

    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Sample_set_ut);

} //namespace

#endif // __UTIL_SAMPLE_SET_UT_H__
