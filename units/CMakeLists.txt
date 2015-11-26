# Build the library
add_library(SPRITE_units STATIC
    Days.cpp
    Degrees.cpp
    Kilometers.cpp
    Meters.cpp
    Millimeters.cpp
    Nanoseconds.cpp
    Radians.cpp
    Seconds.cpp
    )

# Installation rules.
install(TARGETS SPRITE_units
    EXPORT libsprite-targets
    ARCHIVE DESTINATION lib/SPRITE)
install(FILES
    Celsius.h
    Days.h
    Degrees.h
    GPS_time.h
    Grams.h
    Kilometers.h
    Liters.h
    Meters.h
    Meterspersecond.h
    Meterspersecondpersecond.h
    Millimeters.h
    Nanoseconds.h
    Pascal.h
    Radians.h
    Radianspersecond.h
    Seconds.h
    Tesla.h
    DESTINATION include/SPRITE/units)

# Build unit tests.
if(CMAKE_BUILD_TYPE MATCHES Test)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_TEST}")
    add_executable(run_test_units ../test_harness.cpp
        Celsius_ut.cpp
        Degrees_ut.cpp
        GPS_time_ut.cpp
        Kilometers_ut.cpp
        Liters_ut.cpp
        Meterspersecondpersecond_ut.cpp
        Meterspersecond_ut.cpp
        Meters_ut.cpp
        Millimeters_ut.cpp
        Nanoseconds_ut.cpp
        Pascal_ut.cpp
        Radians_ut.cpp
        Seconds_ut.cpp
        )
    target_link_libraries(run_test_units SPRITE_units cppunit)
endif()
