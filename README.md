# cpp-dsa

Data Structures and Algorithms in C++

## Overview

This repo contains C++ implementations of common data structures and algorithms.

- Build system: CMake
- Tests: GoogleTest
- Layout: data structures in `ds/`, sources in `src/`, tests in `tests/`

## Prerequisites

- CMake 3.10+
- A C++20 compiler (g++/clang++)
- Build toolchain Ninja or Make

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

All test files under `tests/*.cpp` are compiled into a single test runner (`unit_tests`).

Run the full suite:

```bash
ctest --test-dir build --output-on-failure
```

Run the test binary directly (useful for filtering):

```bash
./build/unit_tests --gtest_filter="LinkedListTest.*"
```

## Add a new data structure/algorithm

1) Create a file in `ds/` or `al`, e.g. `ds/stack.h`.
2) Write implementations.

The project builds a reusable library from everything in `src/` (except `src/main.cpp`), so your new code is automatically compiled for both the app and the tests.

## Add a new test

1) Create a file under `tests/`, e.g. `tests/test_stack.cpp`.
2) Write test cases:

```cpp
#include <gtest/gtest.h>
#include "../ds/stack.h"

TEST(StackTest, PushPop) {
	Stack s;
	s.push(1);
	s.push(2);
	EXPECT_EQ(s.pop(), 2);
	EXPECT_EQ(s.pop(), 1);
}
```

3) Rebuild and run tests:

```bash
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## Project structure

```
ds/             # Data structures
al/             # Algorithms
src/            # Playground
tests/          # Test cases
CMakeLists.txt  # Build config
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
