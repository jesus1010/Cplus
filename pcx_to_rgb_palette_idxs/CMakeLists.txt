#>>GENERAL
cmake_minimum_required(VERSION 3.0.2)
project(pcx_to_rgb_palette_idxs CXX)


#SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
#SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")
#SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
#SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")
#SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
#SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")

#set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build)
#set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
#set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
#set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
#set(CMAKE_BUILD_DIRECTORY ${dir})
#set(CMAKE_BINARY_DIR  ${targets})
set(EXECUTABLE_OUTPUT_PATH "target")
#set(EXECUTABLE_OUTPUT_PATH_DEBUG "debug/target")
#set(EXECUTABLE_OUTPUT_PATH_RELEASE "release/target")
set(LIBRARY_OUTPUT_PATH "lib")
#set(LIBRARY_OUTPUT_PATH_DEBUG "debug/lib")
#set(LIBRARY_OUTPUT_PATH_RELEASE "release/lib")
#set(CMAKE_CACHEFILE_DIR ${dir})

include_directories(src/layer0 src/layer1 src/layer2)

set(CMAKE_CXX_COMPILER "g++")
#set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-security")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-aliasing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-include-dirs")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=5")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-conversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wbad-function-cast")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-prototypes") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

set(CMAKE_DEBUG_POSTFIX d)

IF(CMAKE_BUILD_TYPE MATCHES debug)
  message("Debug build.")
  add_definitions(-DDML=1)
  add_definitions(-DDEBUG_OUTPUT=1)

ELSEIF(CMAKE_BUILD_TYPE MATCHES release)
  message("Release build.")
ELSE()
  message("Some other build type.")
ENDIF()

#>>

#>>LIBS 
#lib layer0
file(GLOB LAYER0_SRC "src/layer0/*.cpp")

#lib layer1
file(GLOB LAYER1_SRC "src/layer1/*.cpp")

#lib layer2
file(GLOB LAYER2_SRC "src/layer2/*.cpp")

add_library(layer0 STATIC ${LAYER0_SRC})
add_library(layer1 STATIC ${LAYER1_SRC})
add_library(layer2 STATIC ${LAYER2_SRC})
#<<

#>>TESTS
#test Pcx_file_RGB_palette_idxs_seq_br_test
add_executable(Pcx_file_RGB_palette_idxs_seq_br_test "src/tests/Pcx_file_RGB_palette_idxs_seq_br_test.cpp")
set_target_properties(Pcx_file_RGB_palette_idxs_seq_br_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

#WARNING!! order is important
target_link_libraries(Pcx_file_RGB_palette_idxs_seq_br_test layer2 stdc++)
target_link_libraries(Pcx_file_RGB_palette_idxs_seq_br_test layer1 stdc++)
target_link_libraries(Pcx_file_RGB_palette_idxs_seq_br_test layer0 stdc++)
#<<