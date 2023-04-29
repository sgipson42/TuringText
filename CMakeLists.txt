cmake_minimum_required(VERSION 3.0)
project(TuringText)

set(BUILD_TESTING OFF)

# Include CPM.cmake
include(CPM.cmake)

# Add nlohmann_json as a dependency
CPMAddPackage(
        NAME nlohmann_json
        GITHUB_REPOSITORY nlohmann/json
        VERSION 3.9.1
)

CPMAddPackage(
        NAME Boost
        VERSION 1.81.0
        GITHUB_REPOSITORY "boostorg/boost"
        GIT_TAG "boost-1.81.0"
)

CPMAddPackage(
        NAME cpr
        VERSION  1.10.0
        GITHUB_REPOSITORY "libcpr/cpr"
        GIT_TAG "0817715923c9705e68994eb52ef9df3f6845beba"
)

# Find all source files in the current directory
file(GLOB SOURCES *.cpp)

# Add the executable target
add_executable(TuringText ${SOURCES} TwilioClient.cpp TwilioClient.h TwilioServer.cpp TwilioServer.h main.cpp)

# Find all header files in the current directory
file(GLOB HEADERS *.h)
file(GLOB HEADERS *.hpp)

# Add the header files to the target
target_sources(TuringText PRIVATE ${HEADERS})

# Link the cpr library
target_link_libraries(TuringText PRIVATE cpr::cpr)

# Link the nlohmann_json library
target_link_libraries(TuringText PRIVATE nlohmann_json::nlohmann_json)

# Link Boost libraries to your executable
target_link_libraries(TuringText PRIVATE Boost::asio Boost::property_tree Boost::beast)

