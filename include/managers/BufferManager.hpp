#ifndef BUFFER_MANAGER_HPP
#define BUFFER_MANAGER_HPP
#include <GL/glew.h>

class BufferManager
{
public:
 // Constructors
 BufferManager() = delete;

 // Destructor
 ~BufferManager() = delete;

 // Getters
 [[nodiscard]] static float* getVertexBuffer();
 [[nodiscard]] static float* getColorBuffer();

 // Setters
 static void setVertexBuffer(float* verticesBuffer, unsigned int verticesBufferSize);
 static void setColorBuffer(float* colorsBuffer, unsigned int colorsBufferSize);

 // Methods
 static void init();
 static void clearBuffers();
 static void drawBuffers();

private:
 /**
  * The OpenGL vertex buffer.
  */
 static GLuint _glVertexBuffer;

 /**
  * The OpenGL color buffer.
  */
 static GLuint _glColorBuffer;

 /**
  * Whether the buffer manager has been initialized.
  */
 static bool _initialized;

 /**
  * The buffer for the vertices.
  */
 static float* _vertexBuffer;

 /**
  * The buffer for the colors.
  */
 static float* _colorBuffer;

 /**
  * The size of the vertices buffer.
  */
 static unsigned int _verticesBufferSize;

 /**
  * The size of the colors buffer.
  */
 static unsigned int _colorsBufferSize;

 // Private methods
 static void _drawVertices();
 static void _drawColors();
};

#endif //BUFFER_MANAGER_HPP
