project(fusionfs-fuse)

cmake_minimum_required(VERSION 2.8)
INCLUDE (CheckIncludeFiles)

set(FUSIONFS_VERSION_MAJOR 0)
set(FUSIONFS_VERSION_MINOR 1)
set(FUSIONFS_VERSION_PATCH 0)
set(FUSIONFS_VERSION_STRING ${FUSIONFS_VERSION_MAJOR}.${FUSIONFS_VERSION_MINOR}.${FUSIONFS_VERSION_PATCH})
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -pipe")
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -pipe -ggdb")

# Select flags.
SET(CMAKE_C_FLAGS "-pipe -W -Wall -DFORTIFY_SOURCE=2")
SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_C_FLAGS_RELEASE "-O2")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g -DDEBUG")

add_definitions(-D_FILE_OFFSET_BITS=64)

#add_subdirectory(redis3m)

set(CPPSRCS cppwrapper.cpp fusionfs.cpp rpc.cpp gen-cpp/rpc_types.cpp
gen-cpp/rpc_constants.cpp gen-cpp/RPC.cpp)
set(CSRCS fusion.c)
add_executable(fusionfs ${CSRCS} ${CPPSRCS})
target_link_libraries(fusionfs fuse pthread rt redis3m thrift)

INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/fusionfs DESTINATION bin)
