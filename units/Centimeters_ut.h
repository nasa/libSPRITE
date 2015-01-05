#ifndef __UNITS_CENTIMETERS_UT_H__
#define __UNITS_CENTIMETERS_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace units
{
    class Centimeters_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Centimeters_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test();

    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Centimeters_ut);

} // namespace

#endif // __UNITS_CENTIMETERS_UT_H__
