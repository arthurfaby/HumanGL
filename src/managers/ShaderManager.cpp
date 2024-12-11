#include "ShaderManager.hpp"
#include <fstream>
#include <Logger.hpp>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include "ShaderException.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Load and compile the shaders (Vertex and Fragment).
 * Attach the shaders to a program.
 * Use the program.
 * Detach and delete the shaders.
 *
 * @return The ID of the shader program (0 if an error occurred)
 */
GLuint ShaderManager::init()
{
    const GLuint vertexShader = _compileShader(VERTEX_SHADER_SOURCE_PATH, GL_VERTEX_SHADER);
    const GLuint fragmentShader = _compileShader(FRAGMENT_SHADER_SOURCE_PATH, GL_FRAGMENT_SHADER);
    const GLuint geometryShader = _compileShader(GEOMETRY_SHADER_SOURCE_PATH, GL_GEOMETRY_SHADER);

    // Create a shader program
    const GLuint programId = glCreateProgram();
    if (programId == 0)
    {
        Logger::warning("ShaderManager::init(): Shader program creation failed.");
        return 0;
    }

    // Attach the shaders to the program
    if (vertexShader != 0)
    {
        glAttachShader(programId, vertexShader);
    }
    if (fragmentShader != 0)
    {
        glAttachShader(programId, fragmentShader);
    }
    if (geometryShader != 0)
    {
        glAttachShader(programId, geometryShader);
    }
    glLinkProgram(programId);

    // Check for linking errors
    GLint status;
    glGetProgramiv(programId, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(programId, maxLength, &maxLength, &errorLog[0]);

        Logger::error("ShaderManager::init(): Program linking failed: %s",
                      errorLog.data());
    }
    glDetachShader(programId, vertexShader);
    glDetachShader(programId, fragmentShader);
    glDetachShader(programId, geometryShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
    glUseProgram(programId);
    glUniform2f(glGetUniformLocation(programId, "screenSize"), 1000.0f, 700.0f);
    return programId;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Compile the shader from the given file.
 *
 * @param fileName The name of the file to compile the shader from
 * @param shaderId The ID of the shader to compile
 *
 * @return The compiled shader (0 if an error occurred)
 */
GLuint ShaderManager::_compileShader(const std::string& fileName, const GLenum shaderId)
{
    Logger::debug("ShaderManager::compileShader(): Compiling shader %s...", fileName.c_str());
    // Load shader source from file
    const char* shaderSource = nullptr;
    try
    {
        shaderSource = _loadShader(fileName);
    } catch (const std::exception& e)
    {
        Logger::warning("ShaderManager::compileShader(): %s. Compilation aborted.", e.what());
        return 0;
    }
    // Compile shader
    GLuint shader = glCreateShader(shaderId);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    GLint isCompiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        Logger::warning("ShaderManager::compileShader(): Shader %s compilation failed: %s",
                        fileName.c_str(),
                        errorLog.data());
        glDeleteShader(shader);
    }
    else
    {
        Logger::debug("ShaderManager::compileShader(): Shader %s compiled.", fileName.c_str());
    }

    // Clean up
    delete[] shaderSource;
    return shader;
}

/**
 * Load the shader source from the given file.
 *
 * @param fileName The name of the file to load the shader source from
 *
 * @return The shader source as a string
 */
const char* ShaderManager::_loadShader(const std::string& fileName)
{
    Logger::debug("ShaderManager::loadShader(): Loading shader source from file %s...", fileName.c_str());
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        throw ShaderException("Could not open file " + fileName);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    if (file.fail())
    {
        throw ShaderException("Could not read file " + fileName);
    }

    file.close();

    // Dynamically allocate memory for the shader source
    std::string content = buffer.str();
    char* result = new char[content.size() + 1];
    std::copy(content.begin(), content.end(), result);
    result[content.size()] = '\0';

    Logger::debug("ShaderManager::loadShader(): Shader source loaded from file %s.", fileName.c_str());
    return result;
}