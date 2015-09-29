#ifndef __UTIL_SMOOTH_H__
#define __UTIL_SMOOTH_H__

#include "util/Sample_set.h"

namespace util {

    /**
     * Compute a Savitzky-Golay smoothed value of the set of data points
     * provided. The points represent a window and the SV is a form of average
     * that makes a least-squares fit to the data. In this case we use a cubic
     * polynomial fit.
     * @param points Set of points to be smoothed.
     * @return Estimated value at the center of the window.
     * @satisfies{util-3.1}
     */
    template <typename T> T savgol_cubic(Sample_set<T> &points);

    /**
     * Compute a Savitzky-Golay first derivative of the set of data points
     * provided. The points represent a window and the SV is a form of average
     * that makes a least-squares fit to the data. In this case we use a cubic
     * polynomial fit.
     * @param points Set of points to be smoothed.
     * @return Estimated derivative at the center of the window.
     * @satisfies{util-4.1}
     */
    template <typename T> double savgol_cubic_dx(Sample_set<T> &points);

} // namespace

#endif // __UTIL_SMOOTH_H__
