/******************************************************************************
 * Copyright (c) 2013-2014 - Daniel L. Heater
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/

#ifndef __UTIL_SMOOTH_H__
#define __UTIL_SMOOTH_H__

#include "util/Sample_set.h"

namespace util
{

    /**
     * Compute a Savitzky-Golay smoothed value of the set of data points
     * provided. The points represent a window and the SV is a form of average
     * that makes a least-squares fit to the data. In this case we use a cubic
     * polynomial fit.
     * @param points Set of points to be smoothed.
     * @return Estimated value at the center of the window.
     */
    template<typename T>
    T savgol_cubic(Sample_set<T>& points);


    /**
     * Compute a Savitzky-Golay first derivative of the set of data points
     * provided. The points represent a window and the SV is a form of average
     * that makes a least-squares fit to the data. In this case we use a cubic
     * polynomial fit.
     * @param points Set of points to be smoothed.
     * @return Estimated derivative at the center of the window.
     */
    template<typename T>
    double savgol_cubic_dx(Sample_set<T>& points);

} // namespace

#endif // __UTIL_SMOOTH_H__
