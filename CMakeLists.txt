cmake_minimum_required(VERSION 3.20)

# --- Project ---
project(RaylibGame LANGUAGES C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type (for single-config generators)
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the build type: Debug, Release, RelWithDebInfo, MinSizeRel." FORCE)
endif()

# Output dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- raylib ---
set(RAYLIB_VERSION 5.5 CACHE STRING "Raylib version to use")
find_package(raylib ${RAYLIB_VERSION} QUIET)

if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.zip
  )
  FetchContent_MakeAvailable(raylib)
endif()

# --- Sources & target ---
# Build every .cpp under src/
file(GLOB SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

# Headers can live in src/ or include/
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Warnings
if (MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# When debugging from VS/IDE, run from the exe folder (assets will be next to it)
set_target_properties(${PROJECT_NAME}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

# --- Assets handling (best option = copy on build) ---
# Optionally allow a dev symlink (Windows needs Developer Mode / admin)
option(USE_ASSET_SYMLINK "Create a symlink to assets instead of copying (dev only)" OFF)

if (USE_ASSET_SYMLINK)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Creating symlink to assets/")
else()
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Copying assets/ next to the executable")
endif()

# --- Install (for releases) ---
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION assets)

# Optional: clean helper
add_custom_target(distclean
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}"
  COMMENT "Removing build directory: ${CMAKE_BINARY_DIR}"
)
