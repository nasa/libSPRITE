#ifndef __DEM_DEM_HEADER_H__
#define __DEM_DEM_HEADER_H__

#include "DEM_origin_code_t.h"
#include "DEM_operation_code_t.h"
#include "DEM_timestamp.h"
#include "DEM_type_id_t.h"
#include "DEM_system_id_t.h"


namespace DEM
{
    class DEM_header
    {
        public:
            /**
             * Return the DEM size.
             */
            uint16_t get_size() const
            {
                return DEM_SWAP(m_size);
            }

            /**
             * Set the DEM size.
             */
            void set_size(uint16_t size)
            {
                m_size = DEM_SWAP(size);
            }

            /**
             * Return the version number.
             */
            unsigned int get_version_number() const
            {
                return (0xE0 & m_upper_flags) >> 5;
            }

            /**
             * Set the version number.
             */
            void set_version_number(unsigned int version)
            {
                assert(version <= 7);
                m_upper_flags = (m_upper_flags & ~0xE0) | (version << 5);
            }

            /**
             * Is the CRC present?
             */
            bool crc_is_present() const
            {
                return (m_upper_flags & 0x10) != 0;
            }

            /**
             * Set the CRC present bit.
             */
            void set_crc_present()
            {
                m_upper_flags |= 0x10;
            }

            /**
             * Clear the CRC present bit.
             */
            void clear_crc_present()
            {
                m_upper_flags &= ~0x10;
            }

            /**
             * Is the sequence counter present?
             */
            bool sequence_counter_is_present() const
            {
                return (m_lower_flags & 0x80) != 0;
            }

            /**
             * Set the sequence counter present bit.
             */
            void set_sequence_counter_present()
            {
                m_lower_flags |= 0x80;
            }

            /**
             * Clear the sequence counter present bit.
             */
            void clear_sequence_counter_present()
            {
                m_lower_flags &= ~0x80;
            }

            /**
             * Is the secondary header present?
             */
            bool secondary_header_is_present() const
            {
                return (m_lower_flags & 0x40) != 0;
            }

            /**
             * Set the secondary header present bit.
             */
            void set_secondary_header_present()
            {
                m_lower_flags |= 0x40;
            }

            /**
             * Clear the secondary header present bit.
             */
            void clear_secondary_header_present()
            {
                m_lower_flags &= ~0x40;
            }

            /**
             * Return the origin code.
             */
            DEM_origin_code_t get_origin_code() const
            {
                return static_cast<DEM_origin_code_t>
                    ((m_lower_flags & 0x38) >> 3);
            }

            /**
             * Set the origin code.
             */
            void set_origin_code(DEM_origin_code_t origin_code)
            {
                m_lower_flags = (m_lower_flags & ~0x38) | (origin_code << 3);
            }

            /**
             * Return the operation code.
             */
            DEM_operation_code_t get_operation_code() const
            {
                return static_cast<DEM_operation_code_t>(m_lower_flags & 0x07);
            }

            /**
             * Set the operation code.
             */
            void set_operation_code(DEM_operation_code_t operation_code)
            {
                m_lower_flags = (m_lower_flags & ~0x07) | operation_code;
            }

            /**
             * Return the system id.
             */
            DEM_system_id_t get_system_id() const
            {
                return static_cast<DEM_system_id_t>
                    (DEM_SWAP(m_sysid_typeid) >> 5);
            }

            /**
             * Set the system id.
             */
            void set_system_id(DEM_system_id_t system_id)
            {
                m_sysid_typeid = DEM_SWAP((DEM_SWAP(m_sysid_typeid) & ~0xFFE0) |
                        system_id << 5);
            }

            /**
             * Return the type id.
             */
            DEM_type_id_t get_type_id() const
            {
                return static_cast<DEM_type_id_t>
                    (DEM_SWAP(m_sysid_typeid) & 0x07);
            }

            /**
             * Set the type id.
             */
            void set_type_id(DEM_type_id_t type_id)
            {
                m_sysid_typeid = DEM_SWAP((DEM_SWAP(m_sysid_typeid) & ~0x001F) |
                        type_id);
            }

            /**
             * Return the DEM content id.
             */
            uint16_t get_content_id() const
            {
                return DEM_SWAP(m_content_id);
            }

            /**
             * Set the DEM content id.
             */
            void set_content_id(uint16_t content_id)
            {
                m_content_id = DEM_SWAP(content_id);
            }

            /**
             * Return a reference to the DEM timestamp.
             */
            DEM_timestamp& get_timestamp()
            {
                return m_timestamp;
            }

            /**
             * Set the DEM timestamp.
             */
            void set_timestamp(DEM_timestamp& timestamp)
            {
                m_timestamp = timestamp;
            }

            /**
             * Return the source system id.
             */
            DEM_system_id_t get_source_system_id() const
            {
                return static_cast<DEM_system_id_t>
                    (DEM_SWAP(m_system_subsystem) >> 5);
            }

            /**
             * Set the source system id.
             */
            void set_source_system_id(DEM_system_id_t system_id)
            {
                m_system_subsystem = DEM_SWAP((DEM_SWAP(m_system_subsystem) &
                            ~0xFFE0) | system_id << 5);
            }

            /**
             * Return the source subsystem id.
             */
            unsigned int get_source_subsystem_id() const
            {
                return (DEM_SWAP(m_system_subsystem) & 0x1F);
            }

            /**
             * Set the source subsystem id.
             */
            void set_source_subsystem_id(unsigned int subsystem_id)
            {
                assert(subsystem_id <= 0x1F);
                m_system_subsystem = DEM_SWAP((DEM_SWAP(m_system_subsystem) &
                            ~0x001F) | subsystem_id);
            }

            /**
             * Get the source system and subsystem
             */
            uint16_t get_source_system_subsystem() const
            {
                return DEM_SWAP(m_system_subsystem);
            }

            /**
             * Return the DEM sequence counter.
             */
            uint16_t get_sequence_count() const
            {
                return (sequence_counter_is_present()) ?
                    DEM_SWAP(m_sequence_count) : 0;
            }

            /**
             * Set the DEM sequence count.
             */
            void set_sequence_count(uint16_t sequence_count)
            {
                if(sequence_counter_is_present())
                {
                    m_sequence_count = DEM_SWAP(sequence_count);
                }
            }

        private:
            /**
             * DEM size
             */
            uint16_t m_size;
            /**
             * Version: 3 | CRC flag: 1 | Content Map ID Size: 3
             */
            uint8_t m_upper_flags;
            /**
             * Sequence Counter Present: 1 | Secondary Header Present: 1 |
             * Origin Code:3 | Operation Code:3
             */
            uint8_t m_lower_flags;
            /**
             * System ID:11 | Type ID:5
             */
            uint16_t m_sysid_typeid;
            /**
             * DEM content id
             */
            uint16_t m_content_id;
            /**
             * DEM timestamp
             */
            DEM_timestamp m_timestamp;
            /**
             * Source System:11 | Source Subsystem:5
             */
            uint16_t m_system_subsystem;
            /**
             * Sequence counter
             * The sequence counters presence is determined by the sequence
             * counter present flag.
             */
            uint16_t m_sequence_count;

    } __attribute__ ((packed));

} // namespace


#endif // __DEM_DEM_HEADER_H__
