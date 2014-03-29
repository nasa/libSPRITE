#ifndef __UNITS_J2010_TIME_UT_H__
#define __UNITS_J2010_TIME_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace units
{
    /**
     * @verify{@req{1389}}
     */
    class J2010_time_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(J2010_time_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test();

    };

    CPPUNIT_TEST_SUITE_REGISTRATION(J2010_time_ut);

} // namespace

#endif // __UNITS_J2010_TIME_UT_H__
