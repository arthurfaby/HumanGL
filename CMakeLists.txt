# Set the minimum required version of cmake
cmake_minimum_required(VERSION 3.29)

# Store the name of the project in PROJECT_NAME
project(humangl)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Manually specify the source files from directory1
set(SOURCE_FILES
        src/main.cpp
        src/test.cpp
        include/main.hpp
        src/render/Point3.cpp
        src/render/Point3.hpp
)

find_package(SDL2 REQUIRED)



# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# Manually specify the source files from directory1
#set(SOURCE_FILES_1
#    directory1/main.cpp
#    directory1/file1.cpp
#    directory1/file2.cpp
#)
#
# Manually specify the source files from directory2
#set(SOURCE_FILES_2
#    directory2/file3.cpp
#    directory2/file4.cpp
#)