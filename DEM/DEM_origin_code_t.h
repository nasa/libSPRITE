#ifndef __DEM_DEM_ORIGIN_CODE_T_H__
#define __DEM_DEM_ORIGIN_CODE_T_H__

namespace DEM
{
    enum DEM_origin_code_t
    {
        DEM_ORIGIN_LIVE = 0,
        DEM_ORIGIN_REPLAY = 1,
        DEM_ORIGIN_TEST = 2,
        DEM_ORIGIN_SIMULATION = 3
    };

} // namespace

#endif // __DEM_DEM_ORIGIN_CODE_T_H__
