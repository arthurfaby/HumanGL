#include "Human.hpp"
#include "BodyPartDefines.hpp"
#include "HumanDefines.hpp"

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
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @return The root of the human.
  */
BodyPart* Human::getRoot() const
{
    return _root;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Reset the translations of the human body parts.
 */
void Human::resetTranslations() const
{
    if (!_root) return;
    _root->setTranslateX(0);
    _root->setTranslateY(0);
    _root->setTranslateZ(0);
}

/**
  * Reset rotations of the human body parts.
  */
void Human::resetMemberRotations() const
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
    _initRoot();
}

/**
  * Initialize the head of the human.
  */
void Human::_initHead() const
{
    if (!_head) return;
    _head->scale(HEAD_SCALE_X, HEAD_SCALE_Y, HEAD_SCALE_Z);
    _head->setOwnRelativeShift(0, HEAD_SCALE_Y / 2, 0);
    _head->setParentRelativeShift(0, TORSO_SCALE_Y / 2, 0);

    _head->setPivotPoint(Vector4(0.0f, -HEAD_SCALE_Y / 2, 0.0f, 1.0f));

    _head->setColor(HEAD_COLOR);
}

/**
  * Initialize the torso of the human.
  */
void Human::_initTorso() const
{
    if (!_torso) return;
    _torso->scale(TORSO_SCALE_X, TORSO_SCALE_Y, TORSO_SCALE_Z);
    _torso->setColor(TORSO_COLOR);
}

/**
  * Initialize the right arm of the human.
  */
void Human::_initRightArm() const
{
    if (!_rightArm) return;
    _rightArm->scale(RIGHT_ARM_SCALE_X, RIGHT_ARM_SCALE_Y, RIGHT_ARM_SCALE_Z);
    _rightArm->setOwnRelativeShift(-RIGHT_ARM_SCALE_X / 2, RIGHT_ARM_SCALE_Y / 2, 0);
    _rightArm->setParentRelativeShift(-TORSO_SCALE_X / 2, TORSO_SCALE_Y / 2, 0);

    _rightArm->setPivotPoint(Vector4(RIGHT_ARM_SCALE_X / 2, -RIGHT_ARM_SCALE_Y / 2, 0, 1));

    _rightArm->setColor(RIGHT_ARM_COLOR);
}

/**
  * Initialize the right lower arm of the human.
  */
void Human::_initRightLowerArm() const
{
    if (!_rightLowerArm) return;
    _rightLowerArm->scale(RIGHT_LOWER_ARM_SCALE_X, RIGHT_LOWER_ARM_SCALE_Y, RIGHT_LOWER_ARM_SCALE_Z);
    _rightLowerArm->setOwnRelativeShift(-RIGHT_LOWER_ARM_SCALE_X / 2, 0, 0);
    _rightLowerArm->setParentRelativeShift(-RIGHT_ARM_SCALE_X / 2, 0, 0);

    _rightLowerArm->setPivotPoint(Vector4(RIGHT_LOWER_ARM_SCALE_X / 2, 0, 0, 1));
    _rightLowerArm->setColor(RIGHT_LOWER_ARM_COLOR);
}

/**
  * Initialize the left arm of the human.
  */
void Human::_initLeftArm() const
{
    if (!_leftArm) return;
    _leftArm->scale(-LEFT_ARM_SCALE_X, LEFT_ARM_SCALE_Y, LEFT_ARM_SCALE_Z);
    _leftArm->setOwnRelativeShift(LEFT_ARM_SCALE_X / 2, LEFT_ARM_SCALE_Y / 2, 0);
    _leftArm->setParentRelativeShift(TORSO_SCALE_X / 2, TORSO_SCALE_Y / 2, 0);

    _leftArm->setPivotPoint(Vector4(-LEFT_ARM_SCALE_X / 2, -LEFT_ARM_SCALE_Y / 2, 0, 1));

    _leftArm->setColor(LEFT_ARM_COLOR);
}

/**
 * Initialize the left lower arm of the human.
 */
void Human::_initLeftLowerArm() const
{
    if (!_leftLowerArm) return;
    _leftLowerArm->scale(-LEFT_LOWER_ARM_SCALE_X, LEFT_LOWER_ARM_SCALE_Y, LEFT_LOWER_ARM_SCALE_Z);
    _leftLowerArm->setOwnRelativeShift(LEFT_LOWER_ARM_SCALE_X / 2, 0, 0);
    _leftLowerArm->setParentRelativeShift(LEFT_ARM_SCALE_X / 2, 0, 0);

    _leftLowerArm->setPivotPoint(Vector4(-LEFT_LOWER_ARM_SCALE_X / 2, 0, 0, 1));
    _leftLowerArm->setColor(LEFT_LOWER_ARM_COLOR);
}

/**
 * Initialize the right leg of the human.
 */
void Human::_initRightLeg() const
{
    if (!_rightLeg) return;
    _rightLeg->scale(RIGHT_LEG_SCALE_X, RIGHT_LEG_SCALE_Y, RIGHT_LEG_SCALE_Z);
    _rightLeg->setOwnRelativeShift(0, -RIGHT_LEG_SCALE_Y / 2, 0);
    _rightLeg->setParentRelativeShift(-TORSO_SCALE_X / 2, -TORSO_SCALE_Y / 2, 0);

    _rightLeg->setPivotPoint(Vector4(0, RIGHT_LEG_SCALE_Y / 2, 0, 1));

    _rightLeg->setColor(RIGHT_LEG_COLOR);
}

/**
 * Initialize the right lower leg of the human.
 */
void Human::_initRightLowerLeg() const
{
    if (!_rightLowerLeg) return;
    _rightLowerLeg->scale(RIGHT_LOWER_LEG_SCALE_X, RIGHT_LOWER_LEG_SCALE_Y, RIGHT_LOWER_LEG_SCALE_Z);
    _rightLowerLeg->setOwnRelativeShift(0, -RIGHT_LOWER_LEG_SCALE_Y / 2, 0);
    _rightLowerLeg->setParentRelativeShift(0, -RIGHT_LEG_SCALE_Y / 2, 0);

    _rightLowerLeg->setPivotPoint(Vector4(0, RIGHT_LOWER_LEG_SCALE_Y / 2, 0, 1));

    _rightLowerLeg->setColor(RIGHT_LOWER_LEG_COLOR);
}

/**
 * Initialize the left leg of the human.
 */
void Human::_initLeftLeg() const
{
    if (!_leftLeg) return;
    _leftLeg->scale(LEFT_LEG_SCALE_X, LEFT_LEG_SCALE_Y, LEFT_LEG_SCALE_Z);
    _leftLeg->setOwnRelativeShift(0, -LEFT_LEG_SCALE_Y / 2, 0);
    _leftLeg->setParentRelativeShift(TORSO_SCALE_X / 2, -TORSO_SCALE_Y / 2, 0);

    _leftLeg->setPivotPoint(Vector4(0, LEFT_LEG_SCALE_Y / 2, 0, 1));

    _leftLeg->setColor(LEFT_LEG_COLOR);
}

/**
 * Initialize the left lower leg of the human.
 */
void Human::_initLeftLowerLeg() const
{
    if (!_leftLowerLeg) return;
    _leftLowerLeg->scale(LEFT_LOWER_LEG_SCALE_X, LEFT_LOWER_LEG_SCALE_Y, LEFT_LOWER_LEG_SCALE_Z);
    _leftLowerLeg->setOwnRelativeShift(0, -LEFT_LOWER_LEG_SCALE_Y / 2, 0);
    _leftLowerLeg->setParentRelativeShift(0, -LEFT_LEG_SCALE_Y / 2, 0);

    _leftLowerLeg->setPivotPoint(Vector4(0, LEFT_LOWER_LEG_SCALE_Y / 2, 0, 1));

    _leftLowerLeg->setColor(LEFT_LOWER_LEG_COLOR);
}

/**
 * Initialize the root of the human.
 */
void Human::_initRoot()
{
    _root = _torso;
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
}

