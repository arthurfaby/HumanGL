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

GLuint BufferManager::_vertexArrayID = -1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Initialize the buffer manager.<br>
 * Create the 4 OpenGL buffers (triangles vertices, triangles colors, lines vertices, lines colors).
 */
void BufferManager::init()
{
    Logger::debug("BufferManager::init(): Initializing buffer manager.");

    // Init VAO
    glGenVertexArrays(1, &_vertexArrayID);
    glBindVertexArray(_vertexArrayID);

    _initialized = true;
    glGenBuffers(1, &_glTrianglesVerticesBuffer);
    glGenBuffers(1, &_glTrianglesColorsBuffer);
    glGenBuffers(1, &_glLinesVerticesBuffer);
    glGenBuffers(1, &_glLinesColorsBuffer);
}

void BufferManager::clean()
{
    glDeleteVertexArrays(1, &_vertexArrayID);
    glDeleteBuffers(1, &_glTrianglesVerticesBuffer);
    glDeleteBuffers(1, &_glTrianglesColorsBuffer);
    glDeleteBuffers(1, &_glLinesVerticesBuffer);
    glDeleteBuffers(1, &_glLinesColorsBuffer);
}

/**
 * Draw all the buffers.<br>
 * Draw the lines and the triangles with their colors.<br>
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
 * Add data to the buffer that is being manipulated.
 *
 * @param bufferToManipulate The buffer to manipulate
 * @param data The data to add
 *
 * @return the start index of the data in the buffer (or -1 if the buffer is invalid)
 */
unsigned int BufferManager::add(const ManipulableBuffer bufferToManipulate, const std::vector<float>& data)
{
    std::vector<float>* buffer = _getBuffer(bufferToManipulate);
    if (buffer == nullptr)
    {
        return -1;
    }
    const unsigned int startIndex = buffer->size();
    buffer->insert(buffer->end(), data.begin(), data.end());

    return startIndex;
}

/**
 * Modify the data in the buffer that is being manipulated.
 *
 * @param bufferToManipulate The buffer to manipulate
 * @param startIndex The start index of the data to modify
 * @param data The data to add
 *
 * @return the start index of the data in the buffer (or -1 if the buffer is invalid)
 */
unsigned int BufferManager::modify(const ManipulableBuffer bufferToManipulate,
                                   const unsigned int startIndex,
                                   const std::vector<float>& data)
{
    std::vector<float>* buffer = _getBuffer(bufferToManipulate);
    if (buffer == nullptr)
    {
        return -1;
    }
    if (startIndex + data.size() > buffer->size())
    {
        // Erase existing data and add new one
        buffer->erase(buffer->begin() + startIndex, buffer->end());
        const unsigned int newStartIndex = buffer->size();
        buffer->insert(buffer->end(), data.begin(), data.end());

        return newStartIndex;
    }
    std::ranges::copy(data, buffer->begin() + startIndex);

    return startIndex;
}

/**
 * Draw the triangles.<br>
 * 1. Bind the triangles vertices buffer.<br>
 * 2. Enable the vertex attribute array with index 0 for vertices.<br>
 * 3. Configure the vertex attribute array with index 0 for vertices.<br>
 * 4. Bind the triangles colors buffer.<br>
 * 5. Enable the vertex attribute array with index 1 for colors.<br>
 * 6. Configure the vertex attribute array with index 1 for colors.<br>
 * 7. Calculate the total length of the vertices and colors buffers.<br>
 * 8. Draw the triangles.<br>
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
 * Draw the lines.<br>
 * 1. Bind the lines vertices buffer.<br>
 * 2. Enable the vertex attribute array with index 0 for vertices.<br>
 * 3. Configure the vertex attribute array with index 0 for vertices.<br>
 * 4. Bind the lines colors buffer.<br>
 * 5. Enable the vertex attribute array with index 1 for colors.<br>
 * 6. Configure the vertex attribute array with index 1 for colors.<br>
 * 7. Calculate the total length of the vertices and colors buffers.<br>
 * 8. Draw the lines.<br>
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

std::vector<float>* BufferManager::_getBuffer(const ManipulableBuffer bufferToGet)
{
    switch (bufferToGet)
    {
        case TRIANGLES_VERTICES:
            return &_trianglesVerticesBuffer;
        case TRIANGLES_COLORS:
            return &_trianglesColorsBuffer;
        case LINES_VERTICES:
            return &_linesVerticesBuffer;
        case LINES_COLORS:
            return &_linesColorsBuffer;
        default:
            //TODO: Throw ?
            Logger::error("BufferManager::add(): Invalid buffer type.");
            return nullptr;
    }
}