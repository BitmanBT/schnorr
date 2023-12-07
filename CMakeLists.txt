cmake_minimum_required()
project(schnorr)

set(SOURCES main.cpp src/schnorr.cpp src/hacker.cpp src/nmath.cpp)
set(HEADERS include/data_structures.h include/schnorr.h include/hacker.h include/nmath.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)