
cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0042 NEW)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror ${CMAKE_CXX_FLAGS} -flto")


include(GenerateExportHeader)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_library(foo
  libfoo.c
)

set_target_properties(foo PROPERTIES DEFINE_SYMBOL FOO_EXPORTS)
if (BUILD_SHARED_LIBS)
  add_compiler_export_flags(FOO_EXPORT_FLAGS)
  set_target_properties(foo PROPERTIES COMPILE_FLAGS ${FOO_EXPORT_FLAGS})
  set_target_properties(foo PROPERTIES LINK_FLAGS ${FOO_EXPORT_FLAGS})
endif()

generate_export_header(foo
  EXPORT_FILE_NAME libfoo_export.h
  EXPORT_MACRO_NAME LIBFOO_API
  STATIC_DEFINE LIBFOO_STATIC
)

macro(example ex)
  add_executable(example${ex} example${ex}.cpp)
  target_link_libraries(example${ex} foo)
  if (NOT BUILD_SHARED_LIBS)
    set_target_properties(example${ex} PROPERTIES COMPILE_DEFINITIONS LIBFOO_STATIC)
  endif()
endmacro()

example(1)
example(2)
example(3)
example(4)
example(5)
example(6)
