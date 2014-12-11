#ifndef __COORD_ECI_UT_H__
#define __COORD_ECI_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace coord
{
    class ECI_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(ECI_ut);

        CPPUNIT_TEST(test_position_constructor);
        CPPUNIT_TEST(test_position_vector_constructor);
        CPPUNIT_TEST(test_toECEF);

        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test_position_constructor();
        void test_position_vector_constructor();
        void test_toECEF();

    };

    CPPUNIT_TEST_SUITE_REGISTRATION(ECI_ut);

} // namespace

#endif // __COORD_ECI_UT_H__
