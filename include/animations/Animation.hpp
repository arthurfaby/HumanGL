#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <vector>

class Animation
{
    class Keyframe
    {
    public:
        // Constructors
        Keyframe() = default;
        Keyframe(float time, std::function<void(double)> action);

        // Destructor
        ~Keyframe() = default;

        /**
        * The timestamp of the keyframe in seconds.
        */
        float timestamp = 0;

        /**
        * The action to perform at this keyframe.
        *
        * @param double - The factor component that represents the interpolation between keyframes.
        */
        std::function<void(double)> action;
    };

public:
    // Constructor
    Animation();

    // Destructor
    ~Animation() = default;

    // Methods
    void resetAnimation();
    void addKeyframe(float time, const std::function<void(double)>& action);
    void update();

private:
    /**
    * The start time of the animation.
    */
    std::chrono::high_resolution_clock::time_point _startTime;

    /**
    * The keyframes of the animation.
    */
    std::vector<Keyframe> _keyframes;
};

#endif // ANIMATION_HPP