# Set the minimum required version of cmake
cmake_minimum_required(VERSION 3.29)

# Store the name of the project in PROJECT_NAME
project(humangl)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(LIBS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs)


# Contain all cpp files within src/animations
set(ANIMATIONS_SOURCE_FILES
        src/animations/Animation.cpp
)

# Contain all cpp files within src/body-parts
set(BODY_PARTS_SOURCE_FILES
        src/body-parts/BodyPart.cpp
        src/body-parts/Human.cpp
)


# Contain all cpp files within src/camera
set(CAMERA_SOURCE_FILES
        src/camera/Camera.cpp
)

# Contain all cpp files within src/managers
set(MANAGERS_SOURCE_FILES
        src/managers/AnimationManager.cpp
        src/managers/BufferManager.cpp
        src/managers/ShaderManager.cpp
)

# Contain all cpp files within src/maths
set(MATHS_SOURCE_FILES
        src/maths/vectors/Vector4.cpp
        src/maths/matrices/Matrix4.cpp
)

# Contain all cpp files within src/
set(SOURCE_FILES
        src/main.cpp
        src/keybindings.cpp
)

# Contain all cpp files within src/utils
set(UTILS_SOURCE_FILES
        src/utils/Logger.cpp
)

# Contain all source files
set(ALL_SOURCE_FILES
        ${ANIMATIONS_SOURCE_FILES}
        ${BODY_PARTS_SOURCE_FILES}
        ${CAMERA_SOURCE_FILES}
        ${MANAGERS_SOURCE_FILES}
        ${MATHS_SOURCE_FILES}
        ${UTILS_SOURCE_FILES}
        ${SOURCE_FILES}
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)


# Add an executable target
add_executable(${PROJECT_NAME} ${ALL_SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/animations
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/body-parts
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/camera
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/defines
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/exceptions
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/managers
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/maths/matrices
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/maths/vectors
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
)

target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw GLEW)