cmake_minimum_required(VERSION 3.16)
project(graphs LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Fetch Boost::Asio
set(BOOST_INCLUDE_LIBRARIES asio thread filesystem)
set(BOOST_ENABLE_CMAKE ON)
include (FetchContent)
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.7z
    USES_TERMINAL_DOWNLOAD TRUE
    DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(Boost)

include_directories(include)
add_subdirectory(src)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_SOURCE_DIR}/bin)