
#ifndef __UNITS_PASCAL_UT_H__
#define __UNITS_PASCAL_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Pascal_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Pascal_ut);

        /**
         * @verifies{units-12.2}
         * @verifies{units-12.3}
         * @verifies{units-12.5}
         */
        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Pascal_ut);

} // namespace

#endif // __UNITS_PASCAL_UT_H__
