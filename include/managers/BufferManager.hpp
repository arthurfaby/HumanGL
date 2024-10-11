#ifndef BUFFER_MANAGER_HPP
#define BUFFER_MANAGER_HPP
#include <vector>
#include <GL/glew.h>

class BufferManager
{
public:
 // Constructors
 BufferManager() = delete;

 // Destructor
 ~BufferManager() = delete;

 // Methods
 static void init();
 static void drawAll();
 static void drawTriangles();
 static void drawLines();

 static unsigned int addTrianglesVertices(const std::vector<float>& trianglesVertices);
 static unsigned int addTrianglesColors(const std::vector<float>& trianglesColors);
 static unsigned int addLinesVertices(const std::vector<float>& linesVertices);
 static unsigned int addLinesColors(const std::vector<float>& linesColors);

 static void modifyTrianglesVertices(unsigned int startIndex, const std::vector<float>& trianglesVertices);
 static void modifyTrianglesColors(unsigned int startIndex, const std::vector<float>& trianglesColors);
 static void modifyLinesVertices(unsigned int startIndex, const std::vector<float>& linesVertices);
 static void modifyLinesColors(unsigned int startIndex, const std::vector<float>& linesColors);

private:
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
};

#endif //BUFFER_MANAGER_HPP
