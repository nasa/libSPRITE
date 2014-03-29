#include "Mutex_ut.h"
#include "Mutex.h"


namespace SRTX
{

    void Mutex_ut::setUp()
    {
    }


    void Mutex_ut::tearDown()
    {
    }


    void Mutex_ut::test_mutex()
    {
        Mutex m;

        /* This test is certainly not exhoustive. We'll need to create multiple
         * threads to give it a real workout.
         */
        CPPUNIT_ASSERT_EQUAL(true, m.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, m.lock());
        CPPUNIT_ASSERT_EQUAL(true, m.unlock());
    }

} // namespace
