#ifndef __UNITS_YARDS_UT_H__
#define __UNITS_YARDS_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace units
{
    class Yards_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Yards_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test();

    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Yards_ut);

} // namespace

#endif // __UNITS_YARDS_UT_H__
