# Set the minimum required version of cmake
cmake_minimum_required(VERSION 3.29)

# Store the name of the project in PROJECT_NAME
project(humangl)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Contain all cpp files within src/
set(SOURCE_FILES
        src/main.cpp
)

# Contain all cpp files within src/render
set(RENDER_SOURCE_FILES
        src/render/Color.cpp
        src/render/Point2.cpp
        src/render/Point3.cpp
        src/render/Renderer.cpp
)

# Contain all cpp files within src/utils
set(UTILS_SOURCE_FILES
        src/utils/Logger.cpp
)

# Contain all source files
set(ALL_SOURCE_FILES
        ${SOURCE_FILES}
        ${RENDER_SOURCE_FILES}
        ${UTILS_SOURCE_FILES}
)

find_package(SDL2 REQUIRED)

# Add an executable target
add_executable(${PROJECT_NAME} ${ALL_SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
        PRIVATE ${SDL2_INCLUDE_DIRS}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/render
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})