#include "BufferManager.hpp"

#include <algorithm>
#include <Logger.hpp>
#include <GL/glew.h>

float* BufferManager::_vertexBuffer = nullptr;
float* BufferManager::_colorBuffer = nullptr;
unsigned int BufferManager::_verticesBufferSize = 0;
unsigned int BufferManager::_colorsBufferSize = 0;
GLuint BufferManager::_glVertexBuffer = 0;
GLuint BufferManager::_glColorBuffer = 0;
bool BufferManager::_initialized = false;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

[[nodiscard]] float* BufferManager::getVertexBuffer()
{
    return _vertexBuffer;
}

[[nodiscard]] float* BufferManager::getColorBuffer()
{
    return _colorBuffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BufferManager::setVertexBuffer(float* verticesBuffer, unsigned int verticesBufferSize)
{
    delete[] _vertexBuffer;
    _vertexBuffer = new float[verticesBufferSize];
    _verticesBufferSize = verticesBufferSize;
    std::copy_n(verticesBuffer, _verticesBufferSize, _vertexBuffer);
}

void BufferManager::setColorBuffer(float* colorsBuffer, unsigned int colorsBufferSize)
{
    delete[] _colorBuffer;
    _colorBuffer = new float[colorsBufferSize];
    _colorsBufferSize = colorsBufferSize;
    std::copy_n(colorsBuffer, _colorsBufferSize, _colorBuffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BufferManager::init()
{
    Logger::debug("BufferManager::init(): Initializing buffer manager.");
    _initialized = true;
    glGenBuffers(1, &_glVertexBuffer);
    glGenBuffers(1, &_glColorBuffer);
}

void BufferManager::clearBuffers()
{
    delete[] _vertexBuffer;
    delete[] _colorBuffer;
    _vertexBuffer = nullptr;
    _colorBuffer = nullptr;
    Logger::debug("BufferManager::clearBuffers(): Buffers cleared.");
}

void BufferManager::drawBuffers()
{
    if (!_initialized)
    {
        Logger::error("BufferManager::drawBuffers(): Buffer manager not initialized.");
        return;
    }
    // Draw the buffers
    _drawColors();
    _drawVertices();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BufferManager::_drawVertices()
{
    // Generate 1 buffer, put the resulting identifier in vertexBuffer
    glBindBuffer(GL_ARRAY_BUFFER, _glVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<long>(_verticesBufferSize * sizeof(float)),
                 _vertexBuffer,
                 GL_STATIC_DRAW);

    // Draw the vertices
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(_verticesBufferSize) / 3);
    glDisableVertexAttribArray(0);
}

void BufferManager::_drawColors()
{
    // Generate 1 buffer, put the resulting identifier in vertexBuffer
    glBindBuffer(GL_ARRAY_BUFFER, _glColorBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<long>(_colorsBufferSize * sizeof(float)),
                 _colorBuffer,
                 GL_STATIC_DRAW);

    // Draw the vertices
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(_colorsBufferSize) / 3);
    glDisableVertexAttribArray(0);
}