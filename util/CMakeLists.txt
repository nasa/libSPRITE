# Build the library.
add_library(SPRITE_util
    Serial_buffer.cpp
    Smooth.cpp
    )

# Installation rules.
install(TARGETS SPRITE_util
    EXPORT libSPRITE-targets
    ARCHIVE DESTINATION lib/SPRITE)
install(FILES
    Linked_list.h
    Sample_set.h
    Serial_buffer.h
    Smooth.h
    DESTINATION include/SPRITE/util)

# Build unit tests.
if(CMAKE_BUILD_TYPE MATCHES Test)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_TEST}")
    add_executable(run_test_util ../test_harness.cpp
        Linked_list_ut.cpp
        Sample_set_ut.cpp
        Serial_buffer_ut.cpp
        Smooth_ut.cpp
        )
    target_link_libraries(run_test_util SPRITE_util cppunit)
    file(COPY savgoltest.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
