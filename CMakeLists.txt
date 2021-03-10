cmake_minimum_required(VERSION 3.16)
project(openai VERSION 1.0 DESCRIPTION "C wrapper for the OpenAI API")

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES src/*.c)

include_directories(include)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} curl)

install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

# Testing
enable_testing()
add_subdirectory(test)
add_test(NAME main COMMAND tests)

# Pandoc
include(cmake/Modules/PandocMan.cmake)
set (CMAKE_INSTALL_FULL_MANDIR "/usr/local/man/")
add_pandoc_man("${CMAKE_CURRENT_SOURCE_DIR}/doc/${PROJECT_NAME}.1.md")