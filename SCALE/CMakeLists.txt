# Find Lua and set paths to Lua
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
set(LIBS ${LIBS} ${LUA_LIBRARIES})

# Build the library.
add_library(SPRITE_SCALE
    Nest.cpp
    Scale_if.cpp
    Test_task.cpp
    )

# Installation rules.
install(TARGETS SPRITE_SCALE
    EXPORT libSPRITE-targets
    ARCHIVE DESTINATION lib/SPRITE)
install(FILES
    Container.h
    LuaWrapper.h
    luawrapper.hpp
    luawrapperutil.hpp
    Nest.h
    Nest_lua.h
    Scale_if.h
    Scheduler.h
    Task.h
    Task_properties.h
    Test_task_ext.h
    Test_task.h
    DESTINATION include/SPRITE/SCALE)

install(FILES
    scheduler.lua
    DESTINATION lib/SPRITE)

# Build unit tests.
if(CMAKE_BUILD_TYPE MATCHES Test)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_TEST}")
    add_executable(run_test_SCALE ../test_harness.cpp
        Scale_if_ut.cpp
        )
    target_link_libraries(run_test_SCALE SPRITE_SCALE SPRITE_SRTX SPRITE_units
        cppunit lua pthread rt)
    file(COPY lunatest.lua DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY scheduler.lua DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY domath.lua DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY Nest_ut.lua DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY Scheduler_ut.lua DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY Task_properties_ut.lua DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
