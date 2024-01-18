message(STATUS "Build Start CMakeLists.txt")

#필요 CMake 최소 버전 명시
cmake_minimum_required(VERSION 3.0.0)

#프로젝트 설정
project(Project_ST 
        VERSION 0.1.0 
        LANGUAGES C CXX)

set( CMAKE_VERBOSE_MAKEFILE true )

include(CTest)
enable_testing()


#컴파일 옵션 추가
add_compile_options(/std:c++latest /experimental:module /W4 )
#헤더 디렉토리 추가 (컴파일러 옵션 -I)
include_directories(${PROJECT_SOURCE_DIR}) 

set(SRC_FILES 
    main.cpp
    st/test/datetime_test.cpp)

#빌드 대상 바이너리 추가
add_executable(Project_ST 
                ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

message(STATUS "Build End CMakeLists.txt")
