# CMakeLists.txt for txblibs
#
# cmake -G "Ninja Multi-Config" -S source -B build
# cmake --build build --config Release or Debug or RelWithDebInfo ...
#
# this builds the unit tests for the libraries. to generate the
# release includes use Makefile in the root directory to run
# buildhdr which bundles up the xx.h and xx.c files into txbxx.h
# for client use.

cmake_minimum_required(VERSION 3.5)

project(
  MAZES
  VERSION 0.0.0.1
  DESCRIPTION "just working through a textbook"
  HOMEPAGE_URL "https://github.com/BlameTroi/mazes_for_programmers"
  LANGUAGES C
)

set(
  CMAKE_C_COMPILER "clang"
)
add_compile_options(
  -Wall
  --pedantic-errors
  -Werror
  -std=c18
)

if(CMAKE_CONFIG_TYPE MATCHES "Debug")
  add_compile_options(
    -g3
    -fsanitize=address
  )
  add_link_options(
    -fsanitize=address
  )
elseif(CMAKE_CONFIG_TYPE MATCHES "RelWithDebInfo")
  add_compile_options(
    -g3
  )
endif()

add_executable(binary_tree_demo "binary_tree_demo.c"
  "binary_tree.c"
  "cell.c" "cell.h"
  "grid.c" "grid.h")

add_executable(sidewinder_demo "sidewinder_demo.c"
  "sidewinder.c"
  "cell.c" "cell.h"
  "grid.c" "grid.h")

target_include_directories(binary_tree_demo PUBLIC "~/.local/include")
target_include_directories(sidewinder_demo PUBLIC "~/.local/include")
