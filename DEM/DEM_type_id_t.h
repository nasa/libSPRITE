// $Id$

#ifndef __DEM_DEM_TYPE_ID_T_H__
#define __DEM_DEM_TYPE_ID_T_H__

namespace DEM
{
    /**
     * DEM types.
     */
    enum DEM_type_id_t
    {
    	DEM_TYPE_INVALID = 0,
    	DEM_TYPE_COMMAND = 1,
    	DEM_TYPE_TELEMETRY = 2,
    	DEM_TYPE_SYNC = 3,
    	DEM_TYPE_TIME_DIFF = 4,
    	DEM_TYPE_BDT = 5,
    	DEM_TYPE_HEARTBEAT = 6
    };

} // namespace

#endif // __DEM_DEM_TYPE_ID_T_H__
