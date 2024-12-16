#include "AnimationManager.hpp"

std::vector<Animation*> AnimationManager::_animations;
Animation* AnimationManager::_selectedAnimation = nullptr;

/**
 * Initialize the AnimationManager.
 *
 * @param human Human to animate
 */
void AnimationManager::init(Human* human)
{
    _generateAndAddStayingPutKeyframes(human);
    _generateAndAddWalkingKeyframes(human);
    _generateAndAddJumpingKeyframes(human);
    _generateAndAddSnowAngelKeyframes(human);
    _selectedAnimation = _animations[0];
}

/**
 * Update the selected animation.
 */
void AnimationManager::update()
{
    if (_selectedAnimation == nullptr)
    {
        return;
    }
    _selectedAnimation->update();
}

/**
 * Select an animation
 *
 * @param index Index of new selected animation
 */
void AnimationManager::select(const int index)
{
    if (index == NO_ANIMATION)
    {
        _selectedAnimation = nullptr;
        return;
    }
    if (index > _animations.size() - 1)
    {
        return;
    }
    _selectedAnimation = _animations[index];
    if (_selectedAnimation)
    {
        _selectedAnimation->resetAnimation();
    }
}

/**
 * Clean up the AnimationManager.
 */
void AnimationManager::clean()
{
    for (auto animation: _animations)
    {
        delete animation;
    }
    _animations.clear();
}

/**
 * Generate keyframes for the staying put animation.
 *
 * @param human Human to animate
 */
void AnimationManager::_generateAndAddStayingPutKeyframes(Human* human)
{
    auto* stayingPutAnimation = new Animation();
    stayingPutAnimation->addKeyframe(0.0f,
                                     [human](const double factor)
                                     {
                                         const auto angle = 0.0f + factor * M_PI / 64;
                                         human->resetMembersTranslations();
                                         human->resetMembersRotations();
                                         human->getRightArm()->setXRotation(angle)
                                                 .setZRotation(M_PI / 2 - M_PI / 50);
                                         human->getLeftArm()->setXRotation(-angle)
                                                 .setZRotation(-M_PI / 2 + M_PI / 50);
                                     });

    stayingPutAnimation->addKeyframe(1.0f,
                                     [human](const double factor)
                                     {
                                         const auto angle = M_PI / 64 - 2 * factor * M_PI / 64;
                                         human->getRightArm()->setXRotation(angle);
                                         human->getLeftArm()->setXRotation(-angle);
                                     });
    stayingPutAnimation->addKeyframe(3.0f,
                                     [human](const double factor)
                                     {
                                         const auto angle = -M_PI / 64 + factor * M_PI / 64;
                                         human->getRightArm()->setXRotation(angle);
                                         human->getLeftArm()->setXRotation(-angle);
                                     });
    stayingPutAnimation->addKeyframe(4.0f,
                                     [](const double)
                                     {
                                     });
    _animations.push_back(stayingPutAnimation);
}

/**
 * Generate keyframes for the jumping animation.
 *
 * @param human Human to animate
 */
void AnimationManager::_generateAndAddJumpingKeyframes(Human* human)
{
    auto* jumpingAnimation = new Animation();
    jumpingAnimation->addKeyframe(0.0f,
                                  [human](const float factor)
                                  {
                                      human->resetMembersRotations();
                                      human->resetMembersTranslations();
                                      human->getRightLeg()->setXRotation(factor * M_PI / 4);
                                      human->getLeftLeg()->setXRotation(factor * M_PI / 4);

                                      human->getRightLowerLeg()->setXRotation(factor * -M_PI / 2);
                                      human->getLeftLowerLeg()->setXRotation(factor * -M_PI / 2);

                                      human->getRightShoe()->setXRotation(factor * M_PI / 4);
                                      human->getLeftShoe()->setXRotation(factor * M_PI / 4);

                                      human->getRightArm()->setYRotation(-M_PI / 2)
                                              .setZRotation(3 * M_PI / 8);
                                      human->getRightLowerArm()->setZRotation(-3 * M_PI / 8);

                                      human->getLeftArm()->setYRotation(M_PI / 2)
                                              .setZRotation(-3 * M_PI / 8);
                                      human->getLeftLowerArm()->setZRotation(3 * M_PI / 8);

                                      human->getRoot()->setTranslateY(factor * -0.17f);
                                  });
    jumpingAnimation->addKeyframe(0.5f,
                                  [human](const float factor)
                                  {
                                      human->getRightLeg()->setXRotation(M_PI / 4 - factor * M_PI / 4);
                                      human->getLeftLeg()->setXRotation(M_PI / 4 - factor * M_PI / 4);

                                      human->getRightLowerLeg()->setXRotation(-M_PI / 2 + factor * M_PI / 2);
                                      human->getLeftLowerLeg()->setXRotation(-M_PI / 2 + factor * M_PI / 2);

                                      human->getRightShoe()->setXRotation(M_PI / 4 - factor * M_PI / 2);
                                      human->getLeftShoe()->setXRotation(M_PI / 4 - factor * M_PI / 2);

                                      human->getRightArm()->setZRotation(3 * M_PI / 8 - factor * 6 * M_PI / 8);
                                      human->getRightLowerArm()->setZRotation(-3 * M_PI / 8 + factor * 3 * M_PI / 8);

                                      human->getLeftArm()->setZRotation(-3 * M_PI / 8 + factor * 6 * M_PI / 8);
                                      human->getLeftLowerArm()->setZRotation(3 * M_PI / 8 - factor * 3 * M_PI / 8);

                                      human->getRoot()->setTranslateY(-0.17 + factor * 0.3);
                                  });
    jumpingAnimation->addKeyframe(0.75f,
                                  [human](const float factor)
                                  {
                                      human->getRoot()->setTranslateY(0.13f + factor * 0.3f);
                                  });
    jumpingAnimation->addKeyframe(1.0f,
                                  [human](const float factor)
                                  {
                                      human->getRoot()->setTranslateY(0.43f - factor * 0.43f);

                                      human->getRightArm()->setZRotation(-3 * M_PI / 8 + factor * 6 * M_PI / 8);
                                      human->getRightLowerArm()->setZRotation(factor * -3 * M_PI / 8);

                                      human->getLeftArm()->setZRotation(3 * M_PI / 8 - factor * 6 * M_PI / 8);
                                      human->getLeftLowerArm()->setZRotation(factor * 3 * M_PI / 8);

                                      human->getRightShoe()->setXRotation(-M_PI / 4 + factor * M_PI / 4);
                                      human->getLeftShoe()->setXRotation(-M_PI / 4 + factor * M_PI / 4);
                                  });
    jumpingAnimation->addKeyframe(1.5f,
                                  [human](const double factor)
                                  {
                                  });
    _animations.push_back(jumpingAnimation);
}

/**
 * Generate keyframes for the walking animation.
 *
 * @param human Human to animate
 */
void AnimationManager::_generateAndAddWalkingKeyframes(Human* human)
{
    auto* walkingAnimation = new Animation();
    walkingAnimation->addKeyframe(0.0f,
                                  [human](const double factor)
                                  {
                                      const auto angle = static_cast<float>(factor * M_PI / 8);
                                      human->resetMembersRotations();
                                      human->resetMembersTranslations();
                                      human->getRightLeg()->setXRotation(angle);
                                      human->getLeftLeg()->setXRotation(-angle);

                                      human->getRightLowerLeg()->setXRotation(-angle / 2);
                                      human->getLeftLowerLeg()->setXRotation(angle / 2);

                                      human->getRightArm()->setZRotation(M_PI / 2 - M_PI / 50)
                                              .setXRotation(-angle);
                                      human->getLeftArm()->setZRotation(-M_PI / 2 + M_PI / 50)
                                              .setXRotation(angle);

                                      human->getRightLowerArm()->setXRotation(-angle);
                                      human->getLeftLowerArm()->setXRotation(angle);

                                      human->getHead()->setYRotation(factor * M_PI / 16);
                                  });

    walkingAnimation->addKeyframe(0.5f,
                                  [human](const double factor)
                                  {
                                      const auto angle = static_cast<float>(M_PI / 8 - 2 * factor * M_PI / 8);
                                      human->getRightLeg()->setXRotation(angle);
                                      human->getLeftLeg()->setXRotation(-angle);

                                      human->getRightLowerLeg()->setXRotation(-angle / 2);
                                      human->getLeftLowerLeg()->setXRotation(angle / 2);

                                      human->getRightArm()->setXRotation(-angle);
                                      human->getLeftArm()->setXRotation(angle);

                                      human->getRightLowerArm()->setXRotation(-angle);
                                      human->getLeftLowerArm()->setXRotation(angle);

                                      human->getHead()->setYRotation(M_PI / 16 - 2 * factor * M_PI / 16);
                                  });

    walkingAnimation->addKeyframe(1.5f,
                                  [human](const double factor)
                                  {
                                      const auto angle = static_cast<float>(-M_PI / 8 + factor * M_PI / 8);
                                      human->getRightLeg()->setXRotation(angle);
                                      human->getLeftLeg()->setXRotation(-angle);

                                      human->getRightLowerLeg()->setXRotation(-angle / 2);
                                      human->getLeftLowerLeg()->setXRotation(angle / 2);

                                      human->getRightArm()->setXRotation(-angle);
                                      human->getLeftArm()->setXRotation(angle);

                                      human->getRightLowerArm()->setXRotation(-angle);
                                      human->getLeftLowerArm()->setXRotation(angle);

                                      human->getHead()->setYRotation(-M_PI / 16 + factor * M_PI / 16);
                                  });

    walkingAnimation->addKeyframe(2.0f,
                                  [](const double)
                                  {
                                  });
    _animations.push_back(walkingAnimation);
}

/**
 * Generate keyframes for the jumping animation.
 *
 * @param human Human to animate
 */
void AnimationManager::_generateAndAddJumpingKeyframes(Human* human)
{
    auto* jumpingAnimation = new Animation();
    jumpingAnimation->addKeyframe(0.0f,
                                  [human](const float factor)
                                  {
                                      human->resetMembersRotations();
                                      human->resetMembersTranslations();
                                      human->getRightLeg()->setXRotation(factor * M_PI / 4);
                                      human->getLeftLeg()->setXRotation(factor * M_PI / 4);

                                      human->getRightLowerLeg()->setXRotation(factor * -M_PI / 2);
                                      human->getLeftLowerLeg()->setXRotation(factor * -M_PI / 2);

                                      human->getRightArm()->setYRotation(-M_PI / 2)
                                              .setZRotation(3 * M_PI / 8);
                                      human->getRightLowerArm()->setZRotation(-3 * M_PI / 8);

                                      human->getLeftArm()->setYRotation(M_PI / 2)
                                              .setZRotation(-3 * M_PI / 8);
                                      human->getLeftLowerArm()->setZRotation(3 * M_PI / 8);

                                      human->getRoot()->setTranslateY(factor * -0.17f);
                                  });
    jumpingAnimation->addKeyframe(0.5f,
                                  [human](const float factor)
                                  {
                                      human->getRightLeg()->setXRotation(M_PI / 4 - factor * M_PI / 4);
                                      human->getLeftLeg()->setXRotation(M_PI / 4 - factor * M_PI / 4);

                                      human->getRightLowerLeg()->setXRotation(-M_PI / 2 + factor * M_PI / 2);
                                      human->getLeftLowerLeg()->setXRotation(-M_PI / 2 + factor * M_PI / 2);

                                      human->getRightArm()->setZRotation(3 * M_PI / 8 - factor * 6 * M_PI / 8);
                                      human->getRightLowerArm()->setZRotation(-3 * M_PI / 8 + factor * 3 * M_PI / 8);

                                      human->getLeftArm()->setZRotation(-3 * M_PI / 8 + factor * 6 * M_PI / 8);
                                      human->getLeftLowerArm()->setZRotation(3 * M_PI / 8 - factor * 3 * M_PI / 8);

                                      human->getRoot()->setTranslateY(-0.17 + factor * 0.3);
                                  });
    jumpingAnimation->addKeyframe(0.75f,
                                  [human](const float factor)
                                  {
                                      human->getRoot()->setTranslateY(0.13f + factor * 0.3f);
                                  });
    jumpingAnimation->addKeyframe(1.0f,
                                  [human](const float factor)
                                  {
                                      human->getRoot()->setTranslateY(0.43f - factor * 0.43f);

                                      human->getRightArm()->setZRotation(-3 * M_PI / 8 + factor * 6 * M_PI / 8);
                                      human->getRightLowerArm()->setZRotation(factor * -3 * M_PI / 8);

                                      human->getLeftArm()->setZRotation(3 * M_PI / 8 - factor * 6 * M_PI / 8);
                                      human->getLeftLowerArm()->setZRotation(factor * 3 * M_PI / 8);
                                  });
    jumpingAnimation->addKeyframe(1.5f,
                                  [](const double)
                                  {
                                  });
    _animations.push_back(jumpingAnimation);
}

/**
 * Generate keyframes for the snow angel animation.
 *
 * @param human Human to animate
 */
void AnimationManager::_generateAndAddSnowAngelKeyframes(Human* human)
{
    auto* snowAngelAnimation = new Animation();
    snowAngelAnimation->addKeyframe(0.0f,
                                    [human](const float factor)
                                    {
                                        human->resetMembersRotations();
                                        human->resetMembersTranslations();

                                        human->getRightArm()->setZRotation(M_PI / 3 - factor * 2 * M_PI / 3);
                                        human->getRightLowerArm()->setZRotation(M_PI / 3 - factor * 2 * M_PI / 3);

                                        human->getLeftArm()->setZRotation(-M_PI / 3 + factor * 2 * M_PI / 3);
                                        human->getLeftLowerArm()->setZRotation(-M_PI / 3 + factor * 2 * M_PI / 3);

                                        human->getRightLeg()->setZRotation(-M_PI / 6 + factor * M_PI / 6);
                                        human->getLeftLeg()->setZRotation(M_PI / 6 - factor * M_PI / 6);
                                    });
    snowAngelAnimation->addKeyframe(0.5f,
                                    [human](const float factor)
                                    {
                                        human->getRightArm()->setZRotation(-M_PI / 3 + 2 * factor * M_PI / 3);
                                        human->getRightLowerArm()->setZRotation(-M_PI / 3 + 2 * factor * M_PI / 3);

                                        human->getLeftArm()->setZRotation(M_PI / 3 - factor * 2 * M_PI / 3);
                                        human->getLeftLowerArm()->setZRotation(M_PI / 3 - factor * 2 * M_PI / 3);

                                        human->getRightLeg()->setZRotation(factor * -M_PI / 6);
                                        human->getLeftLeg()->setZRotation(factor * M_PI / 6);
                                    });
    snowAngelAnimation->addKeyframe(1.0f,
                                    [](const float)
                                    {
                                    });
    _animations.push_back(snowAngelAnimation);
}

