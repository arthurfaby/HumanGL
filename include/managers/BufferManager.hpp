#ifndef BUFFER_MANAGER_HPP
#define BUFFER_MANAGER_HPP

#include <vector>
#include <GL/glew.h>

enum ManipulableBuffer
{
 TRIANGLES_VERTICES,
 TRIANGLES_COLORS,
 LINES_VERTICES,
 LINES_COLORS
};

class BufferManager
{
public:
 // Constructors
 BufferManager() = delete;

 // Destructor
 ~BufferManager() = delete;

 // Methods
 static void init();
 static void clean();
 static void drawAll();
 static void drawTriangles();
 static void drawLines();

 static unsigned int add(ManipulableBuffer bufferToManipulate, const std::vector<float>& data);
 static unsigned int modify(ManipulableBuffer bufferToManipulate,
                            unsigned int startIndex,
                            const std::vector<float>& data);

private:
 /**
 * The vertex array ID.
 */
 static GLuint _vertexArrayID;

 /**
  * Whether the buffer manager has been initialized.
  */
 static bool _initialized;

 /**
  * The buffer for the triangles.
  */
 static std::vector<float> _trianglesVerticesBuffer;

 /**
  * The buffer for the triangles colors.
  */
 static std::vector<float> _trianglesColorsBuffer;

 /**
  * The buffer for the lines.
  */
 static std::vector<float> _linesVerticesBuffer;

 /**
  * The buffer for the lines colors.
  */
 static std::vector<float> _linesColorsBuffer;

 /**
  * The OpenGL triangles buffer.
  */
 static GLuint _glTrianglesVerticesBuffer;

 /**
  * The OpenGL triangles colors buffer.
  */
 static GLuint _glTrianglesColorsBuffer;

 /**
  * The OpenGL lines buffer.
  */
 static GLuint _glLinesVerticesBuffer;

 /**
  * The OpenGL lines buffer.
  */
 static GLuint _glLinesColorsBuffer;

 // Methods
 static std::vector<float>* _getBuffer(ManipulableBuffer bufferToGet);
};

#endif //BUFFER_MANAGER_HPP
