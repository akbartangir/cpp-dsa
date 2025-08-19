# cpp-dsa

Data Structures and Algorithms in C++

## Overview

This repo contains C++ implementations of common data structures and algorithms.

- Build system: CMake (C++17)
- Tests: GoogleTest (auto-downloaded with CMake)
- Simple layout: headers in `include/`, sources in `src/`, tests in `tests/`

## Prerequisites

- CMake 3.10+
- A C++17 compiler (g++/clang++)
- Build toolchain (Ninja or Make; CMake will pick one available)

## Build

```bash
cmake -S . -B build
cmake --build build -j
```

## Run the app

```bash
./build/cpp-dsa
```

## Run tests (GoogleTest)

All test files under `tests/*.cpp` are compiled into a single test runner (`unit_tests`). No CMake edits are needed when adding new test files.

Run the full suite:

```bash
ctest --test-dir build --output-on-failure
```

Run the test binary directly (useful for filtering):

```bash
./build/unit_tests --gtest_filter="LinkedListTest.*"
```

## Add a new data structure/algorithm

1) Create a header in `include/`, e.g. `include/stack.h`.
2) Implement it in `src/…`, e.g. `src/data_structures/stack.cpp`.

The project builds a reusable library from everything in `src/` (except `src/main.cpp`), so your new code is automatically compiled for both the app and the tests.

## Add a new test

1) Create a file under `tests/`, e.g. `tests/test_stack.cpp`.
2) Write GoogleTest cases:

```cpp
#include <gtest/gtest.h>
#include "../include/stack.h"

TEST(StackTest, PushPop) {
	Stack s;
	s.push(1);
	s.push(2);
	EXPECT_EQ(s.pop(), 2);
	EXPECT_EQ(s.pop(), 1);
}
```

3) Rebuild and run tests (no CMake changes required):

```bash
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## Project structure

```
include/              # Public headers
src/                  # Implementations (main in src/main.cpp)
tests/                # GoogleTest sources (auto-discovered)
CMakeLists.txt        # Build config (downloads GoogleTest)
build/                # Out-of-source build directory
```

## Tips

- Use `--gtest_filter` to run a subset of tests.
- If you rename/move many files, a fresh configure can help:

```bash
rm -rf build && cmake -S . -B build && cmake --build build -j
```

## Troubleshooting

- First configure takes a moment because CMake downloads GoogleTest.
- A warning about DOWNLOAD_EXTRACT_TIMESTAMP from FetchContent is safe to ignore.
