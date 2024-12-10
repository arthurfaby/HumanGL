#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include <string>
#include <GL/glew.h>

#define VERTEX_SHADER_SOURCE_PATH "../src/shaders/vertexShader.vert"
#define FRAGMENT_SHADER_SOURCE_PATH "../src/shaders/fragShader.frag"
#define GEOMETRY_SHADER_SOURCE_PATH "../src/shaders/geometryShader.geom"

class ShaderManager
{
public:
    // Constructors
    ShaderManager() = delete;
    ShaderManager(const ShaderManager&) = delete;

    // Destructor
    ~ShaderManager() = delete;

    // Operator overloads
    ShaderManager& operator=(const ShaderManager&) = delete;

    // Methods
    static GLuint init();

private:
    // Private methods
    static GLuint _compileShader(const std::string& fileName, GLenum shaderId);
    static const char* _loadShader(const std::string& fileName);
};

#endif //SHADER_MANAGER_HPP
