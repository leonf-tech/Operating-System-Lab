cmake_minimum_required(VERSION 3.0.0)
project(operating-system-lab VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)



file(GLOB src_files ${CMAKE_SOURCE_DIR}/src/*.cpp)
# message("测试")
message(${src_files})

add_executable( ${CMAKE_PROJECT_NAME}  )

target_sources(${CMAKE_PROJECT_NAME}  PRIVATE ${src_files})

 
target_include_directories(${CMAKE_PROJECT_NAME}  PRIVATE  ${CMAKE_SOURCE_DIR}/src/include )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

