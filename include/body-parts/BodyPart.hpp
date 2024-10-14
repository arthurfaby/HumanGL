#ifndef BODY_PART_HPP
#define BODY_PART_HPP

#include <Vector4.hpp>
#include <vector>

class BodyPart
{
public:
  // Constructor
  BodyPart() = delete;
  explicit BodyPart(const Vector4& position);
  BodyPart(const BodyPart& other) = delete;

  // Destructor
  virtual ~BodyPart() = default;

  // Getters
  [[nodiscard]] Vector4 getPosition() const;
  [[nodiscard]] Vector4 getDir() const;
  [[nodiscard]] std::vector<BodyPart*> getChildren() const;

  // Setters
  void setPosition(const Vector4& position);
  void setDir(const Vector4& dir);

  // Operator overloads
  BodyPart& operator=(const BodyPart& other) = delete;

  // Methods
  void addChild(BodyPart* child);
  void removeChild(const BodyPart* child);

protected:
  /**
    * The lines vertices of the body part.
    */
  std::vector<float> _linesVertices;

  /**
    * The lines colors of the body part.
    */
  std::vector<float> _linesColors;

  /**
    * The triangles vertices of the body part.
    */
  std::vector<float> _trianglesVertices;

  /**
    * The triangles colors of the body part.
    */
  std::vector<float> _trianglesColors;

  /**
    * The start index of the lines vertices buffer.
    */
  unsigned int _startLinesVerticesBufferStartIndex = 0;

  /**
    * The start index of the lines colors buffer.
    */
  unsigned int _startLinesColorBufferStartIndex = 0;

  /**
    * The start index of the triangles vertices buffer.
    */
  unsigned int _startTrianglesVerticesBufferStartIndex = 0;

  /**
    * The start index of the triangles colors buffer.
    */
  unsigned int _startTrianglesColorBufferStartIndex = 0;

  /**
    * The children of the body part.
    */
  std::vector<BodyPart*> _children;

  /**
    * The parent of the body part.
    */
  BodyPart* _parent = nullptr;

  /**
    * The position of the body part.
    */
  Vector4 _position;

  /**
    * The direction of the body part.
    */
  Vector4 _dir;

  // Methods
  void _updateVertices(bool modifyBuffer = true);
};

#endif //BODY_PART_HPP
