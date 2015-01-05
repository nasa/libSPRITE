#ifndef __DEM_DEM_H__
#define __DEM_DEM_H__

#include "DEM_header.h"

namespace DEM
{
    union DEM
    {
        /**
         * Return the size of the header.
         */
        unsigned int get_header_size() const
        {
            return sizeof(DEM_header) -
                ((header.sequence_counter_is_present()) ? 0 : 2);
        }

        /**
         * Return the size of the payload in number of bytes.
         */
        unsigned int get_payload_size() const
        {
            return header.get_size() - get_header_size() - DEM_CRC_SIZE;
        }

        /**
         * Return a pointer to the payload as an array of bytes.
         */
        uint8_t* get_payload_pointer()
        {
            return &(byte[get_header_size()]);
        }

        /**
         * Return the CRC offset in number of bytes from the start of the DEM.
         */
        unsigned int get_crc_offset() const
        {
            return header.get_size() - DEM_CRC_SIZE;
        }

        /**
         * Calculate and return the CRC value.
         */
        uint32_t calculate_crc() const;

        /**
         * Return the CRC value.
         */
        uint32_t get_crc() const;

        /**
         * Set the CRC value.
         */
        void set_crc(uint32_t crc);

        /**
         * Return true if the DEM CRC is valid or the CRC present flag is not
         * set in the header.
         */
        bool crc_is_valid() const
        {
            return header.crc_is_present() ? get_crc() == calculate_crc() :
                true;
        }

        /**
         * Compute and store the updated CRC value.
         */
        void update_crc()
        {
            set_crc(calculate_crc());
        }

        /**
         * DEM header attribute.
         * The header starts at the beginning of the DEM.
         */
        DEM_header header;

        /**
         * Representation of the DEM as an array of bytes.
         */
        uint8_t byte[DEM_NUM_BYTES];

    } __attribute__ ((packed));

} // namespace

#endif // __DEM_DEM_H__
