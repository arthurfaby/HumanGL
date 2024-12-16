#include "Human.hpp"
#include "BodyPartDefines.hpp"
#include "HumanDefines.hpp"

std::map<std::array<int, 3>, BodyPart*> Human::_colorToBodyPartMap;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * Constructor of the Human class.
  */
Human::Human()
{
    _head = new BodyPart();
    _torso = new BodyPart();
    _rightArm = new BodyPart();
    _rightLowerArm = new BodyPart();
    _leftArm = new BodyPart();
    _leftLowerArm = new BodyPart();
    _rightLeg = new BodyPart();
    _rightLowerLeg = new BodyPart();
    _leftLeg = new BodyPart();
    _leftLowerLeg = new BodyPart();

    _rightShoe = new BodyPart();
    _leftShoe = new BodyPart();

    _hatBrim = new BodyPart();
    _hatBrimGreenBand = new BodyPart();
    _hatBrimRedBand = new BodyPart();
    _hatBrimYellowBand = new BodyPart();

    _hatCrown = new BodyPart();

    _initBodyParts();
    _linkChildren();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * Destructor
  */
Human::~Human()
{
    delete _head;
    delete _torso;
    delete _rightArm;
    delete _rightLowerArm;
    delete _leftArm;
    delete _leftLowerArm;
    delete _rightLeg;
    delete _rightLowerLeg;
    delete _leftLeg;
    delete _leftLowerLeg;

    delete _rightShoe;
    delete _leftShoe;

    delete _hatBrim;
    delete _hatBrimGreenBand;
    delete _hatBrimRedBand;
    delete _hatBrimYellowBand;

    delete _hatCrown;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @return The root of the human.
  */
std::map<std::array<int, 3>, BodyPart*> Human::getColorToBodyPartMap()
{
    return _colorToBodyPartMap;
}

/**
  * @return The root of the human.
  */
BodyPart* Human::getRoot() const
{
    return _root;
}

/**
  * @return The targeted body part of the human.
  */
BodyPart* Human::getTarget() const
{
    return _target;
}

/**
  * @return The head of the human.
  */
BodyPart* Human::getHead() const
{
    return _head;
}

/**
  * @return The torso of the human.
  */
BodyPart* Human::getTorso() const
{
    return _torso;
}

/**
  * @return The right arm of the human.
  */
BodyPart* Human::getRightArm() const
{
    return _rightArm;
}

/**
  * @return The right lower arm of the human.
  */
BodyPart* Human::getRightLowerArm() const
{
    return _rightLowerArm;
}

/**
  * @return The left arm of the human.
  */
BodyPart* Human::getLeftArm() const
{
    return _leftArm;
}

/**
  * @return The left lower arm of the human.
  */
BodyPart* Human::getLeftLowerArm() const
{
    return _leftLowerArm;
}

/**
  * @return The right leg of the human.
  */
BodyPart* Human::getRightLeg() const
{
    return _rightLeg;
}

/**
  * @return The right lower leg of the human.
  */
BodyPart* Human::getRightLowerLeg() const
{
    return _rightLowerLeg;
}

/**
  * @return The left leg of the human.
  */
BodyPart* Human::getLeftLeg() const
{
    return _leftLeg;
}

/**
  * @return The left lower leg of the human.
  */
BodyPart* Human::getLeftLowerLeg() const
{
    return _leftLowerLeg;
}

/**
  * @return The right shoe of the human.
  */
BodyPart* Human::getRightShoe() const
{
    return _rightShoe;
}

/**
  * @return The left shoe of the human.
  */
BodyPart* Human::getLeftShoe() const
{
    return _leftShoe;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setter
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Human::setTarget(BodyPart* target)
{
    _target = target;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Human::addToColorToBodyPartMap(const std::array<int, 3> colors, BodyPart* bodyPart)
{
    _colorToBodyPartMap[colors] = bodyPart;
}

/**
 * Reset the translations of the human body parts.
 */
void Human::resetMembersTranslations() const
{
    if (!_root) return;
    _root->setTranslateX(0);
    _root->setTranslateY(0);
    _root->setTranslateZ(0);
}

/**
 * Reset the scaling of the human body parts.
 */
void Human::resetMembersScaling() const
{
    if (!_root) return;
    _root->setTranslateX(0);
    _root->setTranslateY(0);
    _root->setTranslateZ(0);
}

/**
  * Reset rotations of the human body parts.
  */
void Human::resetMembersRotations() const
{
    resetRotation(_head);
    resetRotation(_rightArm);
    resetRotation(_rightLowerArm);
    resetRotation(_leftArm);
    resetRotation(_leftLowerArm);
    resetRotation(_rightLeg);
    resetRotation(_rightLowerLeg);
    resetRotation(_leftLeg);
    resetRotation(_leftLowerLeg);
    resetRotation(_rightShoe);
    resetRotation(_leftShoe);
}

/**
 *  Reset the rotation of a body part.
 *
 * @param bodyPart The body part to reset the rotation.
 */
void Human::resetRotation(BodyPart* bodyPart)
{
    if (!bodyPart) return;
    bodyPart->setXRotation(0);
    bodyPart->setYRotation(0);
    bodyPart->setZRotation(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * Initialize the body parts of the human.
  */
void Human::_initBodyParts()
{
    _initHead();
    _initTorso();
    _initRightArm();
    _initRightLowerArm();
    _initLeftArm();
    _initLeftLowerArm();
    _initRightLeg();
    _initRightLowerLeg();
    _initLeftLeg();
    _initLeftLowerLeg();

    _initRightShoe();
    _initLeftShoe();

    _initHatBrim();
    _initHatBrimGreenBand();
    _initHatBrimRedBand();
    _initHatBrimYellowBand();

    _initHatCrown();

    _initRoot();
    _initTarget();
}

/**
  * Initialize the head of the human.
  */
void Human::_initHead() const
{
    _head->scale(HEAD_SCALE_X, HEAD_SCALE_Y, HEAD_SCALE_Z);
    _head->setOwnRelativeShift(0, HEAD_SCALE_Y / 2, 0);
    _head->setParentRelativeShift(0, TORSO_SCALE_Y / 2, 0);

    _head->setPivotPoint(Vector4(0.0f, -HEAD_SCALE_Y / 2, 0.0f, 1.0f));

    _head->setDefaultColor(HEAD_COLOR);
    _colorToBodyPartMap[{HEAD_COLOR}] = _head;
}

/**
  * Initialize the torso of the human.
  */
void Human::_initTorso() const
{
    _torso->scale(TORSO_SCALE_X, TORSO_SCALE_Y, TORSO_SCALE_Z);
    _torso->setDefaultColor(TORSO_COLOR);
    _colorToBodyPartMap[{TORSO_COLOR}] = _torso;
}

/**
  * Initialize the right arm of the human.
  */
void Human::_initRightArm() const
{
    _rightArm->scale(RIGHT_ARM_SCALE_X, RIGHT_ARM_SCALE_Y, RIGHT_ARM_SCALE_Z);
    _rightArm->setOwnRelativeShift(-RIGHT_ARM_SCALE_X / 2, RIGHT_ARM_SCALE_Y / 2, 0);
    _rightArm->setParentRelativeShift(-TORSO_SCALE_X / 2, TORSO_SCALE_Y / 2, 0);

    _rightArm->setPivotPoint(Vector4(RIGHT_ARM_SCALE_X / 2, -RIGHT_ARM_SCALE_Y / 2, 0, 1));

    _rightArm->setDefaultColor(RIGHT_ARM_COLOR);
    _colorToBodyPartMap[{RIGHT_ARM_COLOR}] = _rightArm;
}

/**
  * Initialize the right lower arm of the human.
  */
void Human::_initRightLowerArm() const
{
    _rightLowerArm->scale(RIGHT_LOWER_ARM_SCALE_X, RIGHT_LOWER_ARM_SCALE_Y, RIGHT_LOWER_ARM_SCALE_Z);
    _rightLowerArm->setOwnRelativeShift(-RIGHT_LOWER_ARM_SCALE_X / 2, 0, 0);
    _rightLowerArm->setParentRelativeShift(-RIGHT_ARM_SCALE_X / 2, 0, 0);

    _rightLowerArm->setPivotPoint(Vector4(RIGHT_LOWER_ARM_SCALE_X / 2, 0, 0, 1));
    _rightLowerArm->setDefaultColor(RIGHT_LOWER_ARM_COLOR);
    _colorToBodyPartMap[{RIGHT_LOWER_ARM_COLOR}] = _rightLowerArm;
}

/**
  * Initialize the left arm of the human.
  */
void Human::_initLeftArm() const
{
    _leftArm->scale(-LEFT_ARM_SCALE_X, LEFT_ARM_SCALE_Y, LEFT_ARM_SCALE_Z);
    _leftArm->setOwnRelativeShift(LEFT_ARM_SCALE_X / 2, LEFT_ARM_SCALE_Y / 2, 0);
    _leftArm->setParentRelativeShift(TORSO_SCALE_X / 2, TORSO_SCALE_Y / 2, 0);

    _leftArm->setPivotPoint(Vector4(-LEFT_ARM_SCALE_X / 2, -LEFT_ARM_SCALE_Y / 2, 0, 1));

    _leftArm->setDefaultColor(LEFT_ARM_COLOR);
    _colorToBodyPartMap[{LEFT_ARM_COLOR}] = _leftArm;
}

/**
 * Initialize the left lower arm of the human.
 */
void Human::_initLeftLowerArm() const
{
    _leftLowerArm->scale(-LEFT_LOWER_ARM_SCALE_X, LEFT_LOWER_ARM_SCALE_Y, LEFT_LOWER_ARM_SCALE_Z);
    _leftLowerArm->setOwnRelativeShift(LEFT_LOWER_ARM_SCALE_X / 2, 0, 0);
    _leftLowerArm->setParentRelativeShift(LEFT_ARM_SCALE_X / 2, 0, 0);

    _leftLowerArm->setPivotPoint(Vector4(-LEFT_LOWER_ARM_SCALE_X / 2, 0, 0, 1));
    _leftLowerArm->setDefaultColor(LEFT_LOWER_ARM_COLOR);
    _colorToBodyPartMap[{LEFT_LOWER_ARM_COLOR}] = _leftLowerArm;
}

/**
 * Initialize the right leg of the human.
 */
void Human::_initRightLeg() const
{
    _rightLeg->scale(RIGHT_LEG_SCALE_X, RIGHT_LEG_SCALE_Y, RIGHT_LEG_SCALE_Z);
    _rightLeg->setOwnRelativeShift(0, -RIGHT_LEG_SCALE_Y / 2, 0);
    _rightLeg->setParentRelativeShift(-TORSO_SCALE_X / 2, -TORSO_SCALE_Y / 2, 0);

    _rightLeg->setPivotPoint(Vector4(0, RIGHT_LEG_SCALE_Y / 2, 0, 1));

    _rightLeg->setDefaultColor(RIGHT_LEG_COLOR);
    _colorToBodyPartMap[{RIGHT_LEG_COLOR}] = _rightLeg;
}

/**
 * Initialize the right lower leg of the human.
 */
void Human::_initRightLowerLeg() const
{
    _rightLowerLeg->scale(RIGHT_LOWER_LEG_SCALE_X, RIGHT_LOWER_LEG_SCALE_Y, RIGHT_LOWER_LEG_SCALE_Z);
    _rightLowerLeg->setOwnRelativeShift(0, -RIGHT_LOWER_LEG_SCALE_Y / 2, 0);
    _rightLowerLeg->setParentRelativeShift(0, -RIGHT_LEG_SCALE_Y / 2, 0);

    _rightLowerLeg->setPivotPoint(Vector4(0, RIGHT_LOWER_LEG_SCALE_Y / 2, 0, 1));

    _rightLowerLeg->setDefaultColor(RIGHT_LOWER_LEG_COLOR);
    _colorToBodyPartMap[{RIGHT_LOWER_LEG_COLOR}] = _rightLowerLeg;
}

/**
 * Initialize the left leg of the human.
 */
void Human::_initLeftLeg() const
{
    _leftLeg->scale(LEFT_LEG_SCALE_X, LEFT_LEG_SCALE_Y, LEFT_LEG_SCALE_Z);
    _leftLeg->setOwnRelativeShift(0, -LEFT_LEG_SCALE_Y / 2, 0);
    _leftLeg->setParentRelativeShift(TORSO_SCALE_X / 2, -TORSO_SCALE_Y / 2, 0);

    _leftLeg->setPivotPoint(Vector4(0, LEFT_LEG_SCALE_Y / 2, 0, 1));

    _leftLeg->setDefaultColor(LEFT_LEG_COLOR);
    _colorToBodyPartMap[{LEFT_LEG_COLOR}] = _leftLeg;
}

/**
 * Initialize the left lower leg of the human.
 */
void Human::_initLeftLowerLeg() const
{
    _leftLowerLeg->scale(LEFT_LOWER_LEG_SCALE_X, LEFT_LOWER_LEG_SCALE_Y, LEFT_LOWER_LEG_SCALE_Z);
    _leftLowerLeg->setOwnRelativeShift(0, -LEFT_LOWER_LEG_SCALE_Y / 2, 0);
    _leftLowerLeg->setParentRelativeShift(0, -LEFT_LEG_SCALE_Y / 2, 0);

    _leftLowerLeg->setPivotPoint(Vector4(0, LEFT_LOWER_LEG_SCALE_Y / 2, 0, 1));

    _leftLowerLeg->setDefaultColor(LEFT_LOWER_LEG_COLOR);
    _colorToBodyPartMap[{LEFT_LOWER_LEG_COLOR}] = _leftLowerLeg;
}

/**
 * Initialize the right shoe of the human.
 */
void Human::_initRightShoe() const
{
    _rightShoe->scale(RIGHT_SHOE_SCALE_X, RIGHT_SHOE_SCALE_Y, RIGHT_SHOE_SCALE_Z);
    _rightShoe->setOwnRelativeShift(0, -RIGHT_SHOE_SCALE_Y / 2, -RIGHT_SHOE_SCALE_Z / 2);
    _rightShoe->setParentRelativeShift(0, -RIGHT_LOWER_LEG_SCALE_Y / 2, RIGHT_LOWER_LEG_SCALE_Z / 2);

    _rightShoe->setPivotPoint(Vector4(0, RIGHT_SHOE_SCALE_Y / 2, RIGHT_SHOE_SCALE_Z / 2, 1));

    _rightShoe->setDefaultColor(RIGHT_SHOE_COLOR);
    _colorToBodyPartMap[{RIGHT_SHOE_COLOR}] = _rightShoe;
}

/**
 * Initialize the left shoe of the human.
 */
void Human::_initLeftShoe() const
{
    _leftShoe->scale(LEFT_SHOE_SCALE_X, LEFT_SHOE_SCALE_Y, LEFT_SHOE_SCALE_Z);
    _leftShoe->setOwnRelativeShift(0, -LEFT_SHOE_SCALE_Y / 2, -LEFT_SHOE_SCALE_Z / 2);
    _leftShoe->setParentRelativeShift(0, -LEFT_LOWER_LEG_SCALE_Y / 2, LEFT_LOWER_LEG_SCALE_Z / 2);

    _leftShoe->setPivotPoint(Vector4(0, LEFT_SHOE_SCALE_Y / 2, LEFT_SHOE_SCALE_Z / 2, 1));

    _leftShoe->setDefaultColor(LEFT_SHOE_COLOR);
    _colorToBodyPartMap[{LEFT_SHOE_COLOR}] = _leftShoe;
}

/**
 * Initialize the brim of the hat.
 */
void Human::_initHatBrim() const
{
    _hatBrim->scale(HAT_BRIM_SCALE_X, HAT_BRIM_SCALE_Y, HAT_BRIM_SCALE_Z);
    _hatBrim->setOwnRelativeShift(0, HAT_BRIM_SCALE_Y / 2, 0);
    _hatBrim->setParentRelativeShift(0, HEAD_SCALE_Y / 2, 0);

    _hatBrim->setPivotPoint(Vector4(0.0f, -HAT_BRIM_SCALE_Y / 2, 0.0f, 1.0f));

    _hatBrim->setDefaultColor(HAT_BRIM_COLOR);
    _colorToBodyPartMap[{HAT_BRIM_COLOR}] = _hatBrim;
}

/**
 * Initialize the green band of the hat's brim.
 */
void Human::_initHatBrimGreenBand() const
{
    _hatBrimGreenBand->scale(HAT_BRIM_GREEN_SCALE_X, HAT_BRIM_GREEN_SCALE_Y, HAT_BRIM_GREEN_SCALE_Z);
    _hatBrimGreenBand->setOwnRelativeShift(0, HAT_BRIM_GREEN_SCALE_Y / 2, 0);
    _hatBrimGreenBand->setParentRelativeShift(0, HAT_BRIM_SCALE_Y / 2, 0);

    _hatBrimGreenBand->setPivotPoint(Vector4(0.0f, -HAT_BRIM_GREEN_SCALE_Y / 2, 0.0f, 1.0f));

    _hatBrimGreenBand->setDefaultColor(HAT_GREEN_BAND_COLOR);
    _colorToBodyPartMap[{HAT_GREEN_BAND_COLOR}] = _hatBrimGreenBand;
}

/**
 * Initialize the red band of the hat's brim.
 */
void Human::_initHatBrimRedBand() const
{
    _hatBrimRedBand->scale(HAT_BRIM_RED_SCALE_X, HAT_BRIM_RED_SCALE_Y, HAT_BRIM_RED_SCALE_Z);
    _hatBrimRedBand->setOwnRelativeShift(0, HAT_BRIM_RED_SCALE_Y / 2, 0);
    _hatBrimRedBand->setParentRelativeShift(0, HAT_BRIM_GREEN_SCALE_Y / 2, 0);

    _hatBrimRedBand->setPivotPoint(Vector4(0.0f, -HAT_BRIM_RED_SCALE_Y / 2, 0.0f, 1.0f));

    _hatBrimRedBand->setDefaultColor(HAT_RED_BAND_COLOR);
    _colorToBodyPartMap[{HAT_RED_BAND_COLOR}] = _hatBrimRedBand;
}

/**
 * Initialize the yellow band of the hat's brim.
 */
void Human::_initHatBrimYellowBand() const
{
    _hatBrimYellowBand->scale(HAT_BRIM_YELLOW_SCALE_X, HAT_BRIM_YELLOW_SCALE_Y, HAT_BRIM_YELLOW_SCALE_Z);
    _hatBrimYellowBand->setOwnRelativeShift(0, HAT_BRIM_YELLOW_SCALE_Y / 2, 0);
    _hatBrimYellowBand->setParentRelativeShift(0, HAT_BRIM_GREEN_SCALE_Y / 2, 0);

    _hatBrimYellowBand->setPivotPoint(Vector4(0.0f, -HAT_BRIM_YELLOW_SCALE_Y / 2, 0.0f, 1.0f));

    _hatBrimYellowBand->setDefaultColor(HAT_YELLOW_BAND_COLOR);
    _colorToBodyPartMap[{HAT_YELLOW_BAND_COLOR}] = _hatBrimYellowBand;
}

/**
 * Initialize the crown of the hat.
 */
void Human::_initHatCrown() const
{
    _hatCrown->scale(HAT_CROWN_SCALE_X, HAT_CROWN_SCALE_Y, HAT_CROWN_SCALE_Z);
    _hatCrown->setOwnRelativeShift(0, HAT_CROWN_SCALE_Y / 2, 0);
    _hatCrown->setParentRelativeShift(0, HAT_BRIM_YELLOW_SCALE_Y / 2, 0);

    _hatCrown->setPivotPoint(Vector4(0.0f, -HAT_CROWN_SCALE_Y / 2, 0.0f, 1.0f));

    _hatCrown->setDefaultColor(HAT_CROWN_COLOR);
    _colorToBodyPartMap[{HAT_CROWN_COLOR}] = _hatCrown;
}

/**
 * Initialize the root of the human.
 */
void Human::_initRoot()
{
    _root = _torso;
}

/**
 * Initialize the targeted body part of the human.
 */
void Human::_initTarget()
{
    _target = _torso;
}

/**
 * Link the children of the body parts.
 */
void Human::_linkChildren() const
{
    _torso->addChild(_head);
    _torso->addChild(_rightArm);
    _torso->addChild(_leftArm);
    _torso->addChild(_rightLeg);
    _torso->addChild(_leftLeg);

    _rightArm->addChild(_rightLowerArm);
    _leftArm->addChild(_leftLowerArm);
    _rightLeg->addChild(_rightLowerLeg);
    _leftLeg->addChild(_leftLowerLeg);

    _rightLowerLeg->addChild(_rightShoe);
    _leftLowerLeg->addChild(_leftShoe);

    _head->addChild(_hatBrim);

    _hatBrim->addChild(_hatBrimGreenBand);
    _hatBrimGreenBand->addChild(_hatBrimRedBand);
    _hatBrimRedBand->addChild(_hatBrimYellowBand);
    _hatBrimYellowBand->addChild(_hatCrown);
}