# CMakeLists.txt for for chapter 2 of mazes for programmers
#
# cmake -G "Ninja Multi-Config" -S source -B build
# cmake --build build --config Release or Debug or RelWithDebInfo ...
#
# i'm not sure how best to lay out a project such as this. the
# use of common 'classes' makes it tempting to have a single
# copy in a common directory but work in later chapters could
# break earlier chapters.
#
# for my single header libraries, i am using a directory in
# common and then a link to pull that into each chapter's code
# directory.
#
# cmake files and classes carried forward will be copied to
# the next chapter and edited as needed. diffs will provide
# one way to explore the changes.

cmake_minimum_required(VERSION 3.5)

project(
  MAZES
  VERSION 0.0.0.2
  DESCRIPTION "just working through a textbook"
  HOMEPAGE_URL "https://github.com/BlameTroi/mazes_for_programmers"
  LANGUAGES C
)

# standard c compilation

set(CMAKE_C_COMPILER "clang")

set(MY_RELEASE_OPTIONS "-Wall -Werror -pedantic-errors -std=c18")
set(MY_RELWITHDEBINFO_OPTIONS "-Wall -Werror -pedantic-errors -std=c18 -g")
set(MY_DEBUG_OPTIONS "-Wall -Werror -pedantic-errors -std=c18 -g -fsanitize=address")
set(MY_DEBUG_LINK_OPTIONS "-fsanitize=address")

# the executables

add_executable(binary_tree_demo
  "${CMAKE_CURRENT_SOURCE_DIR}/src/binary_tree_demo.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/binary_tree.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/genlibs.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/cell.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/grid.c")
target_include_directories(binary_tree_demo PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/inc"
 "${CMAKE_CURRENT_SOURCE_DIR}/txblibs")
target_link_options(binary_tree_demo PUBLIC "$<$<CONFIG:DEBUG>:SHELL:${MY_DEBUG_LINK_OPTIONS}>")
target_compile_options(binary_tree_demo PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:SHELL:${MY_REL_DEB_OPTIONS}>")
target_compile_options(binary_tree_demo PUBLIC "$<$<CONFIG:DEBUG>:SHELL:${MY_DEBUG_OPTIONS}>")
target_compile_options(binary_tree_demo PUBLIC "$<$<CONFIG:RELEASE>:SHELL:${MY_RELEASE_OPTIONS}>")


add_executable(sidewinder_demo
  "${CMAKE_CURRENT_SOURCE_DIR}/src/sidewinder_demo.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/sidewinder.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/genlibs.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/cell.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/grid.c")
target_include_directories(sidewinder_demo PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/inc"
  "${CMAKE_CURRENT_SOURCE_DIR}/txblibs")
target_link_options(binary_tree_demo PUBLIC "$<$<CONFIG:DEBUG>:SHELL:${MY_DEBUG_LINK_OPTIONS}>")
target_compile_options(binary_tree_demo PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:SHELL:${MY_REL_DEB_OPTIONS}>")
target_compile_options(binary_tree_demo PUBLIC "$<$<CONFIG:DEBUG>:SHELL:${MY_DEBUG_OPTIONS}>")
target_compile_options(binary_tree_demo PUBLIC "$<$<CONFIG:RELEASE>:SHELL:${MY_RELEASE_OPTIONS}>")

# CMakeLists.txt ends here
