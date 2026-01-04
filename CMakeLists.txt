cmake_minimum_required(VERSION 3.16)

project(ConnectorNetwork LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to build the example
option(BUILD_EXAMPLE "Build the example executable" ON)

# Define an INTERFACE library for use as a submodule
add_library(connector_network INTERFACE)

# Add source files (consumers will compile these)
target_sources(connector_network INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/wss/WssWorker.cpp
)

# Include directory for headers
target_include_directories(connector_network INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/wss
)

# Build example if requested
if(BUILD_EXAMPLE)
    find_package(Boost REQUIRED)
    find_package(OpenSSL REQUIRED)

    if(NOT Boost_FOUND)
        message(FATAL_ERROR "Boost not found! Install with: brew install boost")
    endif()

    if(NOT OpenSSL_FOUND)
        message(FATAL_ERROR "OpenSSL not found! Install with: brew install openssl")
    endif()

    add_executable(connector_example example/main.cpp)

    target_link_libraries(connector_example PRIVATE
        connector_network
        ${Boost_LIBRARIES}
        OpenSSL::SSL
        OpenSSL::Crypto
    )

    target_include_directories(connector_example PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
    )
endif()
