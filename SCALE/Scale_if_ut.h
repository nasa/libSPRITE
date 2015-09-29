#ifndef __SCALE_SCALE_IF_UT_H__
#define __SCALE_SCALE_IF_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace SCALE {
    /**
     * Provide tests for SCALE.
     */
    class Scale_if_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Scale_if_ut);

        CPPUNIT_TEST(test_task_properties);
        CPPUNIT_TEST(test_scheduler);
        CPPUNIT_TEST(test_nesting);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_task_properties();
        void test_scheduler();
        void test_nesting();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Scale_if_ut);

} // namespace

#endif // __SCALE_SCALE_IF_UT_H__
