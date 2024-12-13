#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <vector>

using TimePoint = std::chrono::high_resolution_clock::time_point;

class Animation
{
    class Keyframe
    {
    public:
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

    // Methods
    void resetAnimation();
    void addKeyframe(float time, const std::function<void(double)>& action);
    void update();

private:
    /**
    * The start time of the animation.
    */
    TimePoint _startTime;

    /**
    * The keyframes of the animation.
    */
    std::vector<Keyframe> _keyframes;
};

#endif // ANIMATION_HPP