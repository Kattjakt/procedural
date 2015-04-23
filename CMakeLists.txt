cmake_minimum_required(VERSION 2.8)
project (Procedural)

set(OGRE_INCLUDE_DIR "/usr/include/" CACHE FILEPATH "")
set(OGRE_LIB_DIR "/usr/lib/" CACHE FILEPATH "")

set(BOOST_INCLUDE_DIR "/usr/include/boost/" CACHE FILEPATH "") 
set(BOOST_LIB_DIR "/usr/lib/" CACHE FILEPATH "")

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_DEBUG_POSTFIX "_d")

file(GLOB INCS "src/*.h")
file(GLOB CPPS "src/*.cpp")

set(LIBS optimized OgreMain optimized OgreOverlay optimized OIS) # release libs
set(LIBS_D debug OgreMain_d debug OgreOverlay_d debug OIS_d) # debug libs 

include_directories("${OGRE_INCLUDE_DIR}" "${OGRE_INCLUDE_DIR}/OIS" "${OGRE_INCLUDE_DIR}/OGRE" "${BOOST_INCLUDE_DIR}")
link_directories("${OGRE_LIB_DIR}" "${OGRE_LIB_DIR}/Debug" "${OGRE_LIB_DIR}/Release" "${BOOST_LIB_DIR}")

add_executable(Procedural ${CPPS} ${INCS})
set_target_properties(Procedural PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(Procedural ${LIBS} ${LIBS_D})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})