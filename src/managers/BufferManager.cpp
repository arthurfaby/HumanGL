#include "BufferManager.hpp"
#include <algorithm>
#include <Logger.hpp>
#include <GL/glew.h>

bool BufferManager::_initialized = false;

std::vector<float> BufferManager::_trianglesVerticesBuffer = {};
std::vector<float> BufferManager::_trianglesColorsBuffer = {};
std::vector<float> BufferManager::_linesVerticesBuffer = {};
std::vector<float> BufferManager::_linesColorsBuffer = {};

GLuint BufferManager::_glTrianglesVerticesBuffer = 0;
GLuint BufferManager::_glTrianglesColorsBuffer = 0;
GLuint BufferManager::_glLinesVerticesBuffer = 0;
GLuint BufferManager::_glLinesColorsBuffer = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Initialize the buffer manager.\n
 * Create the 4 OpenGL buffers (triangles vertices, triangles colors, lines vertices, lines colors).
 */
void BufferManager::init()
{
    Logger::debug("BufferManager::init(): Initializing buffer manager.");

    // Init VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    _initialized = true;
    glGenBuffers(1, &_glTrianglesVerticesBuffer);
    glGenBuffers(1, &_glTrianglesColorsBuffer);
    glGenBuffers(1, &_glLinesVerticesBuffer);
    glGenBuffers(1, &_glLinesColorsBuffer);
}

/**
 * Draw all the buffers.\n
 * Draw the lines and the triangles with their colors.\n
 * Don't draw if the buffer manager is not initialized.
 */
void BufferManager::drawAll()
{
    if (!_initialized)
    {
        Logger::error("BufferManager::drawBuffers(): Buffer manager not initialized.");
        return;
    }
    // Draw the buffers
    drawLines();
    drawTriangles();
}

/**
 * Add vertices to the triangles vertices buffer.
 *
 * @param trianglesVertices Triangles vertices to add
 *
 * @return Start index of the added triangles vertices
 */
unsigned int BufferManager::addTrianglesVertices(const std::vector<float>& trianglesVertices)
{
    const unsigned int startIndex = _trianglesVerticesBuffer.size();
    _trianglesVerticesBuffer.insert(_trianglesVerticesBuffer.end(), trianglesVertices.begin(), trianglesVertices.end());
    return startIndex;
}

/**
 * Add colors to the triangles colors buffer.
 *
 * @param trianglesColors Colors to add
 *
 * @return Start index of the added colors
 */
unsigned int BufferManager::addTrianglesColors(const std::vector<float>& trianglesColors)
{
    const unsigned int startIndex = _trianglesColorsBuffer.size();
    _trianglesColorsBuffer.insert(_trianglesColorsBuffer.end(), trianglesColors.begin(), trianglesColors.end());
    return startIndex;
}

/**
 * Add vertices to the lines vertices buffer.
 *
 * @param linesVertices Lines vertices to add
 *
 * @return Start index of the added lines vertices
 */
unsigned int BufferManager::addLinesVertices(const std::vector<float>& linesVertices)
{
    const unsigned int startIndex = _linesVerticesBuffer.size();
    _linesVerticesBuffer.insert(_linesVerticesBuffer.end(), linesVertices.begin(), linesVertices.end());
    return startIndex;
}

/**
 * Add colors to the lines colors buffer.
 *
 * @param linesColors Colors to add
 *
 * @return Start index of the added colors
 */
unsigned int BufferManager::addLinesColors(const std::vector<float>& linesColors)
{
    const unsigned int startIndex = _linesColorsBuffer.size();
    _linesColorsBuffer.insert(_linesColorsBuffer.end(), linesColors.begin(), linesColors.end());
    return startIndex;
}

/**
 * Modify vertices in the triangles vertices buffer.
 *
 * @param startIndex Start index of the triangles vertices to modify
 * @param trianglesVertices Triangles vertices that will overwrite the existing ones
 *
 * @return Start index of the modified triangles vertices
 */
unsigned int BufferManager::modifyTrianglesVertices(const unsigned int startIndex,
                                                    const std::vector<float>& trianglesVertices)
{
    if (startIndex + trianglesVertices.size() > _trianglesVerticesBuffer.size())
    {
        // Erase existing vertices and add new ones
        _trianglesVerticesBuffer.erase(_trianglesVerticesBuffer.begin() + startIndex, _trianglesVerticesBuffer.end());
        const unsigned int newStartIndex = _trianglesVerticesBuffer.size();
        _trianglesVerticesBuffer.insert(_trianglesVerticesBuffer.end(),
                                        trianglesVertices.begin(),
                                        trianglesVertices.end());
        return newStartIndex;
    }
    std::ranges::copy(trianglesVertices, _trianglesVerticesBuffer.begin() + startIndex);
    return startIndex;
}

/**
 * Modify colors in the triangles colors buffer.
 *
 * @param startIndex Start index of the colors to modify
 * @param trianglesColors Colors that will overwrite the existing ones
 *
 * @return Start index of the modified triangles colors
 */
unsigned int BufferManager::modifyTrianglesColors(const unsigned int startIndex,
                                                  const std::vector<float>& trianglesColors)
{
    if (startIndex + trianglesColors.size() > _trianglesColorsBuffer.size())
    {
        // Erase existing colors and add new ones
        _trianglesColorsBuffer.erase(_trianglesColorsBuffer.begin() + startIndex, _trianglesColorsBuffer.end());
        const unsigned int newStartIndex = _trianglesColorsBuffer.size();
        _trianglesColorsBuffer.insert(_trianglesColorsBuffer.end(), trianglesColors.begin(), trianglesColors.end());
        return newStartIndex;
    }

    std::ranges::copy(trianglesColors, _trianglesColorsBuffer.begin() + startIndex);
    return startIndex;
}

/**
 * Modify vertices in the lines buffer.
 *
 * @param startIndex Start index of the lines vertices to modify
 * @param linesVertices Lines vertices that will overwrite the existing ones
 *
 * @return Start index of the modified lines vertices
 */
unsigned int BufferManager::modifyLinesVertices(const unsigned int startIndex, const std::vector<float>& linesVertices)
{
    if (startIndex + linesVertices.size() > _linesVerticesBuffer.size())
    {
        // Erase existing vertices and add new ones
        _linesVerticesBuffer.erase(_linesVerticesBuffer.begin() + startIndex, _linesVerticesBuffer.end());
        const unsigned int newStartIndex = _linesVerticesBuffer.size();
        _linesVerticesBuffer.insert(_linesVerticesBuffer.end(), linesVertices.begin(), linesVertices.end());
        return newStartIndex;
    }
    std::ranges::copy(linesVertices, _linesVerticesBuffer.begin() + startIndex);
    return startIndex;
}

/**
 * Modify colors in the lines colors buffer.
 *
 * @param startIndex Start index of the colors to modify
 * @param linesColors Colors that will overwrite the existing ones
 *
 * @return Start index of the modified lines colors
 */
unsigned int BufferManager::modifyLinesColors(const unsigned int startIndex, const std::vector<float>& linesColors)
{
    if (startIndex + linesColors.size() > _linesColorsBuffer.size())
    {
        // Erase existing colors and add new ones
        _linesColorsBuffer.erase(_linesColorsBuffer.begin() + startIndex, _linesColorsBuffer.end());
        const unsigned int newStartIndex = _linesColorsBuffer.size();
        _linesColorsBuffer.insert(_linesColorsBuffer.end(), linesColors.begin(), linesColors.end());
        return newStartIndex;
    }
    std::ranges::copy(linesColors, _linesColorsBuffer.begin() + startIndex);
    return startIndex;
}

/**
 * Draw the triangles.\n
 * 1. Bind the triangles vertices buffer.\n
 * 2. Enable the vertex attribute array with index 0 for vertices.\n
 * 3. Configure the vertex attribute array with index 0 for vertices.\n
 * 4. Bind the triangles colors buffer.\n
 * 5. Enable the vertex attribute array with index 1 for colors.\n
 * 6. Configure the vertex attribute array with index 1 for colors.\n
 * 7. Calculate the total length of the vertices and colors buffers.\n
 * 8. Draw the triangles.\n
 * 9. Disable the vertex attribute arrays with index 0 and 1.
 */
void BufferManager::drawTriangles()
{
    glBindBuffer(GL_ARRAY_BUFFER, _glTrianglesVerticesBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<long>(_trianglesVerticesBuffer.size() * sizeof(float)),
                 _trianglesVerticesBuffer.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, _glTrianglesColorsBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<long>(_trianglesColorsBuffer.size() * sizeof(float)),
                 _trianglesColorsBuffer.data(),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    const int totalLength = static_cast<int>(_trianglesVerticesBuffer.size() / 3
                                             + _trianglesColorsBuffer.size() / 3);

    glDrawArrays(GL_TRIANGLES, 0, totalLength);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

/**
 * Draw the lines.\n
 * 1. Bind the lines vertices buffer.\n
 * 2. Enable the vertex attribute array with index 0 for vertices.\n
 * 3. Configure the vertex attribute array with index 0 for vertices.\n
 * 4. Bind the lines colors buffer.\n
 * 5. Enable the vertex attribute array with index 1 for colors.\n
 * 6. Configure the vertex attribute array with index 1 for colors.\n
 * 7. Calculate the total length of the vertices and colors buffers.\n
 * 8. Draw the lines.\n
 * 9. Disable the vertex attribute arrays with index 0 and 1.
 */
void BufferManager::drawLines()
{
    glBindBuffer(GL_ARRAY_BUFFER, _glLinesVerticesBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<long>(_linesVerticesBuffer.size() * sizeof(float)),
                 _linesVerticesBuffer.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, _glLinesColorsBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<long>(_linesColorsBuffer.size() * sizeof(float)),
                 _linesColorsBuffer.data(),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    const int totalLength = static_cast<int>(_linesVerticesBuffer.size() / 2
                                             + _linesColorsBuffer.size() / 2);

    glDrawArrays(GL_LINES, 0, totalLength);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

