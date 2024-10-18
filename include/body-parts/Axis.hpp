// Axis.hpp
#pragma once
#include <vector>
#include "Matrix4.hpp"

class Axis
{
public:
    Axis();
    void translate(float x, float y, float z);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void addChild(Axis* child);
    [[nodiscard]] Matrix4 getTransformationMatrix() const;
    void draw();
    void setPivotPoint(const Vector4& pivotPoint);

private:
    Matrix4 _translationMatrix;
    Matrix4 _rotationMatrix;
    std::vector<Axis*> _children;

    Vector4 _pivotPoint;

    unsigned int _linesVerticesBufferIndex;
    unsigned int _linesColorsBufferIndex;
    std::vector<float> _linesVerticesBuffer;
    std::vector<float> _linesColorsBuffer;
    unsigned int _trianglesVerticesBufferIndex;
    unsigned int _trianglesColorsBufferIndex;
    std::vector<float> _trianglesVerticesBuffer;
    std::vector<float> _trianglesColorsBuffer;
};