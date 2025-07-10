cmake_minimum_required(VERSION 3.10)
project(esel)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-s -Wall -Werror -Wextra")

set(SOURCES
    src/main.c
    src/widgets/textarea.c
)

find_package(Curses REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src/widgets)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
