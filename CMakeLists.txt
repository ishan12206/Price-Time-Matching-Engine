cmake_minimum_required(VERSION 3.16)

project(
    price_time_matching_engine
    VERSION 1.0
    LANGUAGES CXX
)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings (important signal for recruiters)
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Define executable
add_executable(matching_engine
    main.cpp
    src/order_book.cpp
    src/matching_engine.cpp
)

# Tell compiler where headers live
target_include_directories(matching_engine
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

