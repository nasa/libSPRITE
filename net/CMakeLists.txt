# Build the library.
add_library(SPRITE_net
    Socket.cpp
    UDP_client.cpp
    UDP_connection.cpp
    UDP_server.cpp
    )

# Installation rules.
install(TARGETS SPRITE_net
    EXPORT libSPRITE-targets
    ARCHIVE DESTINATION lib/SPRITE)
install(FILES
    Socket.h
    UDP_client.h
    UDP_connection.h
    UDP_server.h
    DESTINATION include/SPRITE/net)

# Build unit tests.
if(CMAKE_BUILD_TYPE MATCHES Test)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_TEST}")
    add_executable(run_test_net ../test_harness.cpp
        UDP_server_ut.cpp
        UDP_client_ut.cpp
        UDP_ut.cpp
        )
    target_link_libraries(run_test_net SPRITE_net cppunit)
    file(COPY udpecho.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
