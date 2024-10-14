#ifndef BODY_PART_HPP
#define BODY_PART_HPP

#include <Matrix4.hpp>
#include <Vector4.hpp>
#include <vector>

class BodyPart
{
public:
  // Constructor
  BodyPart() = delete;
  explicit BodyPart(const Vector4& position, const Vector4& offset);
  BodyPart(const BodyPart& other) = delete;

  // Destructor
  virtual ~BodyPart() = default;

  // Getters
  [[nodiscard]] Vector4 getOffset() const;
  [[nodiscard]] Vector4 getPosition() const;
  [[nodiscard]] Vector4 getDir() const;
  [[nodiscard]] BodyPart* getParent() const;
  [[nodiscard]] std::vector<BodyPart*> getChildren() const;

  // Setters
  void setOffset(const Vector4& offset);
  void setPosition(const Vector4& position);
  void setDir(const Vector4& dir);
  void setParent(BodyPart* parent);

  // Operator overloads
  BodyPart& operator=(const BodyPart& other) = delete;

  // Methods
  void addChild(BodyPart* child);
  void removeChild(BodyPart* child);
  void updateVertices();
  [[nodiscard]] Matrix4 getRotationMatrix() const;

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
  unsigned int _startLinesVerticesBufferStartIndex{};

  /**
    * The start index of the lines colors buffer.
    */
  unsigned int _startLinesColorBufferStartIndex{};

  /**
    * The start index of the triangles vertices buffer.
    */
  unsigned int _startTrianglesVerticesBufferStartIndex{};

  /**
    * The start index of the triangles colors buffer.
    */
  unsigned int _startTrianglesColorBufferStartIndex{};

  /**
    * The children of the body part.
    */
  std::vector<BodyPart*> _children;

  /**
    * The parent of the body part.
    */
  BodyPart* _parent = nullptr;

  /**
    * The offset of the body part compare to its parent.
    */
  Vector4 _offset;

  /**
    * The position of the body part.
    */
  Vector4 _position;

  /**
    * The direction of the body part.
    */
  Vector4 _dir;
};

#endif //BODY_PART_HPP
