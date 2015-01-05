#ifndef __DEM_DEM_SYSTEM_ID_T_H__
#define __DEM_DEM_SYSTEM_ID_T_H__

namespace DEM
{
    /**
     * Define the system type per the Constellation registry.
     * @todo Define the per actual values from the Cx registry.
     */
    enum DEM_system_id_t
    {
        DEM_SYSTEM_ID_ARES = 1,
        DEM_SYSTEM_ID_GS = 2
    };

} // namespace

#endif // __DEM_DEM_SYSTEM_ID_T_H__
