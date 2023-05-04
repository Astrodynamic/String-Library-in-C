cmake_minimum_required(VERSION 3.10)
project(GrepUtility VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(
  ${CMAKE_SOURCE_DIR}/model
)

set(HEADERS
  ${CMAKE_SOURCE_DIR}/model/grep_utility.h
)

set(SOURCES
  ${CMAKE_SOURCE_DIR}/model/grep_utility.c
)

set(BUILD_FILES
  ${HEADERS}
  ${SOURCES}
  ${CMAKE_SOURCE_DIR}/main.c
)

add_executable(${PROJECT_NAME}
  ${BUILD_FILES}
)

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE
  -Wall
  -Werror
  -Wextra
  -Wpedantic
  -fsanitize=address
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  -fsanitize=address
)

# Add cppcheck
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
  message(STATUS "cppcheck found: ${CPPCHECK}")
  list(
    APPEND CPPCHECK_ARGS
    "--enable=all"
    "--inconclusive"
    "--quiet"
    "--std=c11"
    "--suppress=missingIncludeSystem"
    "--suppress=unusedFunction"
    "--suppress=missingInclude"
    "--suppress=unusedStructMember"
    "--suppress=variableScope"
  )
  add_custom_target(
    cppcheck
    COMMAND ${CPPCHECK} ${CPPCHECK_ARGS} ${BUILD_FILES}
  )
else()
  message(STATUS "cppcheck not found")
endif()

# Add clang-format
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
  message(STATUS "clang-format found: ${CLANG_FORMAT}")
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT} -i -style=Google ${BUILD_FILES}
  )
else()
  message(STATUS "clang-format not found")
endif()