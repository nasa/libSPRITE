// $Id$

#ifndef __DEM_DEM_OPERATION_CODE_T_H__
#define __DEM_DEM_OPERATION_CODE_T_H__

namespace DEM
{
    /**
     * DEM operation code.
     */
    enum DEM_operation_code_t
    {
        DEM_OPERATION_MSG_RQ = 0,
        DEM_OPERATION_MSG = 1,
        DEM_OPERATION_MSG_W_RSP_RQ = 2,
        DEM_OPERATION_MSG_RSP = 3,
        DEM_OPERATION_CMAP_RQ = 4,
        DEM_OPERATION_CMAP_RPT = 5
    };

} // namespace

#endif // __DEM_DEM_OPERATION_CODE_T_H__
