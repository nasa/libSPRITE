#ifndef __SRTX_RUNTIME_ATTRIBUTES_H__
#define __SRTX_RUNTIME_ATTRIBUTES_H__

#include "units/Nanoseconds.h"

namespace SRTX {

    /**
     * This struct stores attributes that decribe the runtime behavior of a
     * SRTX rategroup.
     */
    struct Runtime_attributes {
        Runtime_attributes()
            : num_overruns(0)
            , max_runtime(0)
            , last_runtime(0)
        {
        }

        uint32_t num_overruns;
        units::Nanoseconds max_runtime;
        units::Nanoseconds last_runtime;
    };

    /**
     * Define a symbol table database type to store runtime attributes in.
     */
    typedef Symbol_db<Runtime_attributes> Runtime_attributes_db;

    const char *const runtime_attr_symbol_prefix = "Rategroup_";
    const char *const minor_frame_runtime_attr_symbol_name =
        "Minor Frame RT atttibutes";

} // namepsace

#endif // __SRTX_RUNTIME_ATTRIBUTES_H__
