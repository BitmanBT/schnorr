cmake_minimum_required()
project(schnorr)

set(SOURCES main.cpp src/data_structures.cpp src/schnorr.cpp src/hacker.cpp src/nmath.cpp src/factory.cpp)
set(HEADERS include/console.h include/data_structures.h include/schnorr.h include/hacker.h include/nmath.h include/factory.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)