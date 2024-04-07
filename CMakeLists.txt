cmake_minimum_required(VERSION 3.13)

project(CrackingCoding)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

include(CTest)
include(GoogleTest)
include(PackageAddTest)

add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest")

include_directories("include")

file(GLOB files "src/**/*.cpp")
foreach(file ${files})
  get_filename_component(exec_name ${file} NAME_WE)
  package_add_test(${exec_name} ${file})
endforeach()
