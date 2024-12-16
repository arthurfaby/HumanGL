#ifndef HUMAN_HPP
#define HUMAN_HPP
#include <BodyPart.hpp>

class Human
{
public:
    // Constructors
    Human();

    // Destructor
    ~Human();

    // Getters
    [[nodiscard]] BodyPart* getRoot() const;
    [[nodiscard]] BodyPart* getHead() const;
    [[nodiscard]] BodyPart* getTorso() const;
    [[nodiscard]] BodyPart* getRightArm() const;
    [[nodiscard]] BodyPart* getRightLowerArm() const;
    [[nodiscard]] BodyPart* getLeftArm() const;
    [[nodiscard]] BodyPart* getLeftLowerArm() const;
    [[nodiscard]] BodyPart* getRightLeg() const;
    [[nodiscard]] BodyPart* getRightLowerLeg() const;
    [[nodiscard]] BodyPart* getLeftLeg() const;
    [[nodiscard]] BodyPart* getLeftLowerLeg() const;
    void resetTranslations() const;

    // Methods
    void resetMemberRotations() const;
    static void resetRotation(BodyPart* bodyPart);

private:
    // Body parts of the human
    BodyPart* _root = nullptr;
    BodyPart* _head = nullptr;
    BodyPart* _torso = nullptr;
    BodyPart* _rightArm = nullptr;
    BodyPart* _rightLowerArm = nullptr;
    BodyPart* _leftArm = nullptr;
    BodyPart* _leftLowerArm = nullptr;
    BodyPart* _rightLeg = nullptr;
    BodyPart* _rightLowerLeg = nullptr;
    BodyPart* _leftLeg = nullptr;
    BodyPart* _leftLowerLeg = nullptr;

    // Methods
    void _initBodyParts();
    void _initHead() const;
    void _initTorso() const;
    void _initRightArm() const;
    void _initRightLowerArm() const;
    void _initLeftArm() const;
    void _initLeftLowerArm() const;
    void _initRightLeg() const;
    void _initRightLowerLeg() const;
    void _initLeftLeg() const;
    void _initLeftLowerLeg() const;
    void _initRoot();

    void _linkChildren() const;
};

#endif //HUMAN_HPP
