#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include <string>
#include <GL/glew.h>

#define GEOMETRY_SHADER_SOURCE_PATH "../src/shaders/geometryShader.geom"
#define VERTEX_SHADER_SOURCE_PATH "../src/shaders/vertexShader.glsl"
#define FRAGMENT_SHADER_SOURCE_PATH "../src/shaders/fragmentShader.glsl"

class ShaderManager
{
public:
    // Constructors
    ShaderManager() = delete;
    ShaderManager(const ShaderManager&) = delete;

    // Destructor
    ~ShaderManager() = delete;

    // Getters
    static GLuint getProgramId();

    // Operator overloads
    ShaderManager& operator=(const ShaderManager&) = delete;

    // Methods
    static GLuint init();

private:
    /**
    * The program object to which shader objects are attached.
    */
    static GLuint _programId;

    // Private methods
    static GLuint _compileShader(const std::string& fileName, GLenum shaderId);
    static const char* _loadShader(const std::string& fileName);
};

#endif //SHADER_MANAGER_HPP
