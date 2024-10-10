#ifndef BODY_PART_HPP
#define BODY_PART_HPP

#include <Vector4.hpp>
#include <vector>

class BodyPart
{
public:
    // Constructor
    BodyPart() = delete;
    BodyPart(const BodyPart& other) = delete;

    // Destructor
    ~BodyPart() = delete;

    // Getters
    [[nodiscard]] Vector4 getPosition() const;
    [[nodiscard]] std::vector<BodyPart> getChildren() const;

    // Setters
    void setPosition(const Vector4& position);

    // Operator overloads
    BodyPart& operator=(const BodyPart& other) = delete;

    // Methods
    void draw() const;
    void addChild(const BodyPart& child);
    void removeChild(const BodyPart& child);

private:
    /**
      * The children of the body part.
      */
    std::vector<BodyPart> _children;

    /**
      * The position of the body part.
      */
    Vector4 _position;
};

#endif //BODY_PART_HPP
