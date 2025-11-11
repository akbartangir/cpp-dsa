cmake_minimum_required(VERSION 3.10)
project(cpp-dsa LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------
# Application
# ------------------------
add_executable(cpp-dsa src/main.cpp)
target_include_directories(cpp-dsa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ------------------------
# GoogleTest + Unit tests
# ------------------------
include(FetchContent)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For MSVC shared CRT issues (harmless on non-MSVC)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Build a single test runner that picks up all test files automatically
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp")
add_executable(unit_tests ${TEST_SOURCES})
target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

add_test(NAME unit_tests COMMAND unit_tests)