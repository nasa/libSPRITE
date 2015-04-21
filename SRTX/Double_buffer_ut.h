#ifndef __SRTX_DOUBLE_BUFFER_UT_H__
#define __SRTX_DOUBLE_BUFFER_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace SRTX
{
    class Double_buffer_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Double_buffer_ut);

        CPPUNIT_TEST(test_double_buffer);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_double_buffer();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Double_buffer_ut);

} // namespace

#endif // __SRTX_DOUBLE_BUFFER_UT_H__
