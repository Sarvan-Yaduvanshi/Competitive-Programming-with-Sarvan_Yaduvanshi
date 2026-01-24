cmake_minimum_required(VERSION 3.20)
project(Competitive_Programming_with_Sarvan_Yaduvanshi)

# 1. Force C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Find all .cpp files recursively
file(GLOB_RECURSE SOURCES "*.cpp")

# 3. Create a UNIQUE executable for each file
foreach(SOURCE_FILE ${SOURCES})
    # Get the file name
    get_filename_component(RAW_NAME ${SOURCE_FILE} NAME_WE)

    # Clean the name to prevent errors
    string(REGEX REPLACE "[^a-zA-Z0-9_]" "_" TARGET_NAME "${RAW_NAME}")

    # --- THE FIX IS HERE ---
    # Only use ${SOURCE_FILE}. Do NOT add other files here.
    add_executable(${TARGET_NAME} ${SOURCE_FILE}
            practice.cpp)
endforeach()