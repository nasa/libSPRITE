# Build the library.
add_library(SPRITE_math
    DCM.cpp
    Euler.cpp
    Matrix3.cpp
    Quaternion.cpp
    trig.cpp
    Vec3.cpp
    )

# Installation rules.
install(TARGETS SPRITE_math
    EXPORT libSPRITE-targets
    ARCHIVE DESTINATION lib/SPRITE)
install(FILES
    DCM.h
    Euler.h
    Matrix3.h
    MTRand.h
    Quaternion.h
    trig.h
    Vec3.h
    DESTINATION include/SPRITE/math)

# Build unit tests.
if(CMAKE_BUILD_TYPE MATCHES Test)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_TEST}")
    add_executable(run_test_math ../test_harness.cpp
        DCM_ut.cpp
        Euler_ut.cpp
        Matrix3_ut.cpp
        Quaternion_ut.cpp
        trig_ut.cpp
        Vec3_ut.cpp
        )
    target_link_libraries(run_test_math SPRITE_math SPRITE_units cppunit)
endif()
