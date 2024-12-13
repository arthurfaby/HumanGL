#include "Human.hpp"
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
    _head->setHeight(0.1f);
    _head->setWidth(0.1f);
    _head->setDepth(0.1f);
    _head->setPivotPoint(Vector4(0.0f, -0.05f, 0.0f, 1.0f));
    _head->translate(0.0f, 0.25f, 0.0f);
    _head->setColor(HEAD_COLOR);
}

/**
  * Initialize the torso of the human.
  */
void Human::_initTorso() const
{
    if (!_torso) return;
    _torso->setHeight(0.4f);
    _torso->setWidth(0.2f);
    _torso->setDepth(0.1f);
    _torso->setColor(TORSO_COLOR);
}

/**
  * Initialize the right arm of the human.
  */
void Human::_initRightArm() const
{
    if (!_rightArm) return;
    _rightArm->setHeight(0.04f);
    _rightArm->setDepth(0.04f);
    _rightArm->translate(-0.2f, 0.13f, 0.0f);
    _rightArm->setPivotPoint(Vector4(0.08f, 0, 0, 1));
    _rightArm->setColor(RIGHT_ARM_COLOR);
}

/**
  * Initialize the right lower arm of the human.
  */
void Human::_initRightLowerArm() const
{
    if (!_rightLowerArm) return;
    _rightLowerArm->setHeight(0.025f);
    _rightLowerArm->setDepth(0.025);
    _rightLowerArm->setPivotPoint(Vector4(0.10f, 0, 0, 1));
    _rightLowerArm->translate(-0.2f, 0, 0);
    _rightLowerArm->setColor(RIGHT_LOWER_ARM_COLOR);
}

/**
  * Initialize the left arm of the human.
  */
void Human::_initLeftArm() const
{
    if (!_leftArm) return;
    _leftArm->setHeight(0.05f);
    _leftArm->setDepth(0.05f);
    _leftArm->setPivotPoint(Vector4(-0.08f, 0, 0, 1));
    _leftArm->translate(0.2f, 0.13f, 0.0f);
    _leftArm->setColor(LEFT_ARM_COLOR);
}

/**
 * Initialize the left lower arm of the human.
 */
void Human::_initLeftLowerArm() const
{
    if (!_leftLowerArm) return;
    _leftLowerArm->setHeight(0.035f);
    _leftLowerArm->setDepth(0.035f);
    _leftLowerArm->setPivotPoint(Vector4(-0.10f, 0, 0, 1));
    _leftLowerArm->translate(0.2f, 0, 0);
    _leftLowerArm->setColor(LEFT_LOWER_ARM_COLOR);
}

/**
 * Initialize the right leg of the human.
 */
void Human::_initRightLeg() const
{
    if (!_rightLeg) return;
    _rightLeg->setHeight(0.2f);
    _rightLeg->setWidth(0.05f);
    _rightLeg->setDepth(0.05f);
    _rightLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    _rightLeg->translate(-0.05f, -0.3f, 0.0f);
    _rightLeg->setColor(LEFT_LEG_COLOR);
}

/**
 * Initialize the right lower leg of the human.
 */
void Human::_initRightLowerLeg() const
{
    if (!_rightLowerLeg) return;
    _rightLowerLeg->setHeight(0.2f);
    _rightLowerLeg->setWidth(0.035f);
    _rightLowerLeg->setDepth(0.035f);
    _rightLowerLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    _rightLowerLeg->translate(0.0f, -0.2f, 0.0f);
    _rightLowerLeg->setColor(LEFT_LOWER_LEG_COLOR);
}

/**
 * Initialize the left leg of the human.
 */
void Human::_initLeftLeg() const
{
    if (!_leftLeg) return;
    _leftLeg->setHeight(0.2f);
    _leftLeg->setWidth(0.05f);
    _leftLeg->setDepth(0.05f);
    _leftLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    _leftLeg->translate(0.05f, -0.3f, 0.0f);
    _leftLeg->setColor(LEFT_LEG_COLOR);
}

/**
 * Initialize the left lower leg of the human.
 */
void Human::_initLeftLowerLeg() const
{
    if (!_leftLowerLeg) return;
    _leftLowerLeg->setHeight(0.2f);
    _leftLowerLeg->setWidth(0.035f);
    _leftLowerLeg->setDepth(0.035f);
    _leftLowerLeg->setPivotPoint(Vector4(0, 0.1f, 0, 1));
    _leftLowerLeg->translate(0.0f, -0.2f, 0.0f);
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

