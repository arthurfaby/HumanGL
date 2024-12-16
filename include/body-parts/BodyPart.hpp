#ifndef BODY_PART_HPP
#define BODY_PART_HPP

#include <stack>
#include <Vector4.hpp>
#include <vector>
#include "BodyPartDefines.hpp"
#include "Matrix4.hpp"

class BodyPart
{
public:
    // Constructors
    BodyPart();

    // Getters
    [[nodiscard]] Matrix4 getMatrixStack() const;
    [[nodiscard]] Matrix4 getTransformationMatrix() const;
    [[nodiscard]] Matrix4 getScaleMatrix() const;

    // Setters
    BodyPart& setColor(float red, float green, float blue);
    BodyPart& setDefaultColor(float red, float green, float blue);
    BodyPart& resetColor();
    BodyPart& setParent(BodyPart* parent);
    BodyPart& setPivotPoint(const Vector4& pivotPoint);
    BodyPart& setXRotation(float angle);
    BodyPart& setYRotation(float angle);
    BodyPart& setZRotation(float angle);
    BodyPart& setTranslateX(float x);
    BodyPart& setTranslateY(float y);
    BodyPart& setTranslateZ(float z);
    BodyPart& setParentRelativeShift(float x, float y, float z);
    BodyPart& setOwnRelativeShift(float x, float y, float z);

    // Methods
    BodyPart& rotateX(float angle);
    BodyPart& rotateY(float angle);
    BodyPart& rotateZ(float angle);
    BodyPart& translate(float x, float y, float z);
    BodyPart& scale(float x, float y, float z);

    BodyPart& addChild(BodyPart* child);
    void applyTransformation();

private:
    /**
    * The number of faces each body part has.
    */
    static int _faceCount;

    /**
    * The number of vertices per face.
    */
    static int _verticesPerFace;

    /**
    * The number of vertices per body parts.
    */
    static int _verticesPerBodyPart;

    /**
    * The relative shift of the body part with respect to its parent.
    */
    float _parentRelativeShiftX = 0;

    /**
    * The relative shift of the body part with respect to its parent.
    */
    float _parentRelativeShiftY = 0;

    /**
    * The relative shift of the body part with respect to its parent.
    */
    float _parentRelativeShiftZ = 0;

    /**
    * The relative shift of the body part with respect to its own pivot point.
    */
    float _ownRelativeShiftX = 0;

    /**
    * The relative shift of the body part with respect to its own pivot point.
    */
    float _ownRelativeShiftY = 0;

    /**
    * The relative shift of the body part with respect to its own pivot point.
    */
    float _ownRelativeShiftZ = 0;

    /**
    * The angle of rotation around the X axis.
    */
    float _angleX = 0;

    /**
    * The angle of rotation around the Y axis.
    */
    float _angleY = 0;

    /**
    * The angle of rotation around the Z axis.
    */
    float _angleZ = 0;

    /**
     * The translate x value.
     */
    float _translateX = 0;

    /**
     * The translate y value.
     */
    float _translateY = 0;

    /**
     * The translate z value.
     */
    float _translateZ = 0;

    /**
    * The red value of the body part's color.
    */
    float _red;

    /**
    * The default red value of the body part's color.
    */
    float _defaultRed = 255;

    /**
    * The green value of the body part's color.
    */
    float _green;

    /**
    * The default green value of the body part's color.
    */
    float _defaultGreen = 255;

    /**
    * The blue value of the body part's color.
    */
    float _blue;

    /**
    * The default blue value of the body part's color.
    */
    float _defaultBlue = 255;

    /**
    * The sum of all rotation matrices that have been applied to the body part.
    */
    Matrix4 _rotationMatrix;

    /**
    * The sum of all translation matrices that have been applied to the body part.
    */
    Matrix4 _translationMatrix;

    /**
    * The sum of all scaling matrices that have been applied to the body part.
    */
    Matrix4 _scaleMatrix;

    /**
    * A list of all the children of the body part.
    */
    std::vector<BodyPart*> _children;

    /**
    * The parent of the body part.
    */
    BodyPart* _parent = nullptr;

    /**
    * The pivot point of the body part.
    */
    Vector4 _pivotPoint;

    /**
    * The matrix stack of the body part.
    */
    std::stack<Matrix4> _matrixStack;

    /**
    * The buffer's index of triangles vertices of the body part.
    */
    unsigned int _trianglesVerticesBufferIndex;

    /**
    * The buffer's index of triangles colors of the body part.
    */
    unsigned int _trianglesColorsBufferIndex;

    /**
    * The buffer of triangles vertices of the body part.
    */
    std::vector<float> _trianglesVerticesBuffer;

    /**
    * The buffer of triangles colors of the body part.
    */
    std::vector<float> _trianglesColorsBuffer;

    // Private getters
    [[nodiscard]] std::vector<float> _getTrianglesVerticesBuffer() const;
    [[nodiscard]] std::vector<float> _getTrianglesColorsBuffer() const;
};

#endif //BODY_PART_HPP