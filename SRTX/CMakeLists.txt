# Build the library.
add_library(SPRITE_SRTX
    Base_double_buffer.cpp
    Base_ring_buffer.cpp
    Buffer.cpp
    Container.cpp
    Data_router.cpp
    End_of_frame.cpp
    Mutex.cpp
    Reference_time.cpp
    RTC.cpp
    Scheduler.cpp
    Syncpoint.cpp
    Task.cpp
    )

# Installation rules.
install(TARGETS SPRITE_SRTX
    EXPORT libSPRITE-targets
    ARCHIVE DESTINATION lib/SPRITE)
install(FILES
    Base_double_buffer.h
    Base_ring_buffer.h
    Buffer.h
    Container.h
    Data_router.h
    Double_buffer.h
    End_of_frame.h
    Message_db.h
    Message.h
    Mutex.h
    Publication.h
    Reference_time.h
    Ring_buffer.h
    RTC.h
    Runtime_attributes.h
    Scheduler.h
    Scheduler_types.h
    Subscription.h
    Symbol_db.h
    Symbol.h
    Symbol_table.h
    Syncpoint.h
    Task.h
    Task_properties.h
    DESTINATION include/SPRITE/SRTX)

# Build unit tests.
if(CMAKE_BUILD_TYPE MATCHES Test)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_TEST}")
    add_executable(run_test_SRTX ../test_harness.cpp
        Double_buffer_ut.cpp
        Ring_buffer_ut.cpp
        Mutex_ut.cpp
        Symbol_table_ut.cpp
        Task_properties_ut.cpp
        RTC_ut.cpp
        Scheduler_ut.cpp
        Message_ut.cpp
        External_trigger_ut.cpp
        )
    target_link_libraries(run_test_SRTX SPRITE_SRTX cppunit pthread rt)
endif()
