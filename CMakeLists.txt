cmake_minimum_required(VERSION 3.10)
project(esel)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-s")

find_package(Curses REQUIRED)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND upx ${PROJECT_NAME}
    COMMENT "Compressing binary using upx"
)
