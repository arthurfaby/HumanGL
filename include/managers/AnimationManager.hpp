#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include <Animation.hpp>
#include <Human.hpp>

enum AnimationType
{
    STAYING_PUT = 0,
    WALKING = 1,
    JUMPING = 2
};

class AnimationManager
{
public:
    // Constructor
    AnimationManager() = delete;

    // Destructor
    ~AnimationManager() = delete;

    // Methods
    static void init(Human* human);
    static void update();
    static void select(int index);
    static void clean();

private:
    /**
     * The different animations that are managed by the AnimationManager.
     */
    static std::vector<Animation*> _animations;

    /**
     * The currently selected animation.
     */
    static Animation* _selectedAnimation;

    // Methods
    static void _generateAndAddStayingPutKeyframes(Human* human);
    static void _generateAndAddWalkingKeyframes(Human* human);
    static void _generateAndAddJumpingKeyframes(Human* human);
};

#endif //ANIMATION_MANAGER_HPP
