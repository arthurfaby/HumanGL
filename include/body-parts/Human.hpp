#ifndef HUMAN_HPP
#define HUMAN_HPP
#include <BodyPart.hpp>
#include <map>

class Human
{
public:
    // Constructors
    Human();

    // Destructor
    ~Human();

    // Getters
    [[nodiscard]] static std::map<std::array<int, 3>, BodyPart*> getColorToBodyPartMap() ;
    [[nodiscard]] BodyPart* getRoot() const;
    [[nodiscard]] BodyPart* getTarget() const;
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

    // Setter
    void setTarget(BodyPart* target);

    // Methods
    static void addToColorToBodyPartMap(std::array<int, 3> colors, BodyPart* bodyPart);
    void resetMembersRotations() const;
    void resetMembersTranslations() const;
    void resetMembersScaling() const;
    static void resetRotation(BodyPart* bodyPart);

private:
    // Body parts of the human
    BodyPart* _root = nullptr;
    BodyPart* _target = nullptr;
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
    void _initTarget();

    void _linkChildren() const;

    static std::map<std::array<int, 3>, BodyPart*> _colorToBodyPartMap;
};

#endif //HUMAN_HPP
