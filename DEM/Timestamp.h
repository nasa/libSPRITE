// $Id$

#ifndef __DEM_TIMESTAMP_H__
#define __DEM_TIMESTAMP_H__

#include "DEM_timestamp.h"

namespace DEM
{
    /**
     * This class is defined to permit the DEM_timestamp to have a constructor.
     * A constructor cannot be placed directly in the DEM_timestamp class
     * because this class is utilmately the member of a union and members of
     * unions may not have constructors.
     */
    class Timestamp : public DEM_timestamp
    {

        public:
            Timestamp(uint32_t seconds = 0, uint16_t milliseconds = 0)
            {
                set_seconds(seconds);
                set_milliseconds(milliseconds);
            }

    };

} // namespace

#endif // __DEM_TIMESTAMP_H__
