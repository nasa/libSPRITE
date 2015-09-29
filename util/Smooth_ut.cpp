#include <math.h>
#include <stdlib.h>
#include "util/Smooth.h"
#include "util/Smooth_ut.h"

#include "base/XPRINTF.h"

namespace util {

    /* File scope data.
     */
    namespace {
        const unsigned int NELEMS = 11;
        struct test_vector_t {
            double x;
            double y[NELEMS];
            double dy[NELEMS];
        };

        const unsigned int NTVECS = 300;
        test_vector_t test_vec[NTVECS];

        const double DELTA = 1e-6;
    }

    Smooth_ut::Smooth_ut()
    {
        /* Open the file containing the test data.
         */
        const char *fname = "savgoltest.csv";
        FILE *fp = fopen(fname, "r");

        if(NULL == fp) {
            PERROR("fopen");
            exit(1);
        }

        /* Read the header and throw it away.
         */
        const unsigned int BUFFSIZE = 1024;
        char header[BUFFSIZE];

        fscanf(fp, "%s\n", header);

        /* Read in the test vectors.
         */
        for(unsigned int i = 0; i < NTVECS; ++i) {
            fscanf(fp, "%lf", &(test_vec[i].x));

            for(unsigned int j = 0; j < NELEMS; ++j) {
                fscanf(fp, ",%lf", &(test_vec[i].y[j]));
            }

            for(unsigned int j = 0; j < NELEMS; ++j) {
                fscanf(fp, ",%lf", &(test_vec[i].dy[j]));
            }
            fscanf(fp, "\n");
        }
    }

    void Smooth_ut::setUp()
    {
    }

    void Smooth_ut::tearDown()
    {
    }

    static void _test_savgol_cubic(unsigned int nelem)
    {
        Sample_set<double> ss(nelem);

        /* For the first two points, I should get back the original value.
         */
        ss.push(test_vec[0].x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(test_vec[0].x, savgol_cubic(ss), DELTA);
        ss.push(test_vec[1].x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(test_vec[1].x, savgol_cubic(ss), DELTA);

        /* For the third and fourth points, I should get and average of the
         * three most recent points.
         */
        double avg = (test_vec[0].x + test_vec[1].x + test_vec[2].x) / 3.0;
        ss.push(test_vec[2].x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(avg, savgol_cubic(ss), DELTA);
        avg = (test_vec[1].x + test_vec[2].x + test_vec[3].x) / 3.0;
        ss.push(test_vec[3].x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(avg, savgol_cubic(ss), DELTA);

        /* Test cubic/quadratic fitted values against values from the data file.
         */
        double y;
        unsigned int np;
        unsigned int idx;
        for(unsigned int i = 4; i < NTVECS; ++i) {
            ss.push(test_vec[i].x);
            np = ss.npopulated();
            if(np > 23)
                np = 23;
            idx = (np - 1) / 2;
            y = savgol_cubic(ss);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(test_vec[i - idx].y[idx - 2], y,
                                         DELTA);
        }
    }

    static void _test_savgol_cubic_dx(unsigned int nelem)
    {
        Sample_set<double> ss(nelem);

        /* For the first point I should get back 0.
         */
        ss.push(test_vec[0].x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0., savgol_cubic_dx(ss), DELTA);

        /* For the second through fourth points I expect to get back the slope
         * of a line
         * through the first and last points.
         */
        ss.push(test_vec[1].x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL((test_vec[1].x - test_vec[0].x) / 2.,
                                     savgol_cubic_dx(ss), DELTA);

        ss.push(test_vec[2].x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL((test_vec[2].x - test_vec[0].x) / 2.,
                                     savgol_cubic_dx(ss), DELTA);

        ss.push(test_vec[3].x);
        CPPUNIT_ASSERT_DOUBLES_EQUAL((test_vec[3].x - test_vec[0].x) / 2.,
                                     savgol_cubic_dx(ss), DELTA);

        /* For the fifth and subsequent points, the algorithm can computes the
         * derivative using the Savitsky-Golay method.
         * Test cubic/quadratic fitted values against values from the data file.
         */
        double dy;
        unsigned int np;
        unsigned int idx;
        for(unsigned int i = 4; i < NTVECS; ++i) {
            ss.push(test_vec[i].x);
            np = ss.npopulated();
            idx = (np - 1) / 2;
            dy = savgol_cubic_dx(ss);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(test_vec[i - idx].dy[idx - 2], dy,
                                         DELTA);
        }
    }

    void Smooth_ut::test_savgol_cubic()
    {
        for(unsigned int i = 5; i <= 25; i += 2) {
            _test_savgol_cubic(i);
        }
    }

    void Smooth_ut::test_savgol_cubic_dx()
    {
        for(unsigned int i = 5; i <= 25; i += 2) {
            _test_savgol_cubic_dx(i);
        }
    }

} // namespace
