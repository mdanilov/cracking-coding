cmake_minimum_required(VERSION 3.10)
project(CrackingCoding)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

enable_testing()
include(GoogleTest)
include(PackageAddTest)

add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest")

file(GLOB files "src/**/*.cpp")
foreach(file ${files})
  get_filename_component(exec_name ${file} NAME_WE)
  package_add_test(${exec_name} ${file})
endforeach()
