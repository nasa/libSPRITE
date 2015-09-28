#include "base/assertion.h"
#include "units/Meters.h"
#include "util/Smooth.h"
#include "base/XPRINTF.h"

namespace util {

    template <typename T> T savgol_cubic(Sample_set<T> &points)
    {
        const int coeff[13][13] = {
            { 1 },    // For 1 or 2 points, just return the original value.
            { 1, 1 }, // For 3 or 4 sample points, we just average.
            { 17, 12, -3 },
            { 7, 6, 3, -2 },
            { 59, 54, 39, 14, -21 },
            { 89, 84, 69, 44, 9, -36 },
            { 25, 24, 21, 16, 9, 0, -11 },
            { 167, 162, 147, 122, 87, 42, -13, -78 },
            { 43, 42, 39, 34, 27, 18, 7, -6, -21 },
            { 269, 264, 249, 224, 189, 144, 89, 24, -51, -136 },
            { 329, 324, 309, 284, 249, 204, 149, 84, 9, -76, -171 },
            { 79, 78, 75, 70, 63, 54, 43, 30, 15, -2, -21, -42 },
            { 467, 462, 447, 422, 387, 343, 287, 222, 147, 62, -33, -138, -253 }
        };
        const int h[] = { 1,    3,   35,   21,   231, 429, 143,
                          1105, 323, 2261, 3059, 805, 5175 };

        int np = points.npopulated();

        /* We must use an odd number of points. If we are given an even number,
         * reduces the sample set by one.
         */
        if(0 == (np % 2)) {
            --np;
        }

        /* The maximum number of points we can filter on is 25.
         * Actually, I cannot verify 25 entries. The coefficients in the table
         * are correct according to multiple sources, but the results do not
         * match those from R so we'll only allow up to 23 for the time being.
         */
        if(np > 23) {
            np = 23;
        }

        int idx = (np - 1) / 2;
        double sum(0);

        /* Sum the sample values from -i to i
         */
        for(int i = -idx; i <= idx; ++i, --np) {
            DPRINTF("coeff [%d][%d] = %d\n", idx, i, coeff[idx][abs(i)]);
            DPRINTF("i(%d) point(%d)\n", i, np);
            sum += static_cast<double>(coeff[idx][abs(i)] * points(np));
        }

        /* Divide by the correct constant to provide the new estimate.
         */
        // return sum / static_cast<T>(h[idx]);
        return static_cast<T>(sum / h[idx]);
    }

    template <typename T> double savgol_cubic_dx(Sample_set<T> &points)
    {
        const int h[] = { 0,   0,   10,  28,  60,   110, 182,
                          280, 408, 570, 770, 1012, 1300 };

        int np = points.npopulated();

        /* Handle the special case of 1 or fewer points.
         */
        if(np <= 1) {
            return 0;
        }

        /* If we have two points, the the derivative is the slope of the line
         * through those points.
         */
        if(np < 5) {
            return (points(1) - points(np)) / 2.;
        }

        /* We must use an odd number of points. If we are given an even number,
         * reduces the sample set by one.
         */
        if(0 == (np % 2)) {
            --np;
        }

        /* The maximum number of points we can filter on is 25.
         */
        if(np > 25) {
            np = 25;
        }

        int idx = (np - 1) / 2;
        double sum(0.);

        /* Sum the sample values from -i to i
         */
        for(int i = -idx; i <= idx; ++i, --np) {
            sum += i * points(np);
        }

        /* Divide by the correct constant to provide the new estimate.
         */
        return sum / static_cast<double>(h[idx]);
    }

    /* We have to create an instantiation for the template code to be created.
     * Otherwise we will get link errors.
     */
    template double savgol_cubic<double>(Sample_set<double> &points);
    template units::Meters
    savgol_cubic<units::Meters>(Sample_set<units::Meters> &points);
    template double savgol_cubic_dx<double>(Sample_set<double> &points);
    template double
    savgol_cubic_dx<units::Meters>(Sample_set<units::Meters> &points);

} // namespace
