/* $Id$ */

#ifndef __DEM_DEM_DEFINITIONS_H__
#define __DEM_DEM_DEFINITIONS_H__

#include "base/byteswap.h"


/* Handle byteswaping
 */
#ifdef __BIG_ENDIAN__
#define DEM_SWAP(x) (x)
#else
#define DEM_SWAP(x) byteswap16(x)
#endif


const unsigned int DEM_NUM_BYTES = 1500;
const unsigned int DEM_CRC_SIZE = 4;


#endif /* __DEM_DEM_DEFINITIONS_H__ */
