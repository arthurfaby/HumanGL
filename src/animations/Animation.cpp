#include "Animation.hpp"

#include <utility>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Initializes the Animation.
 */
Animation::Animation() : _startTime(std::chrono::high_resolution_clock::now())
{
}

Animation::Keyframe::Keyframe(const float time, const std::function<void(double)>& newAction)
{
    timestamp = time;
    action = newAction;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Resets the animation to the beginning.
 */
void Animation::resetAnimation()
{
    _startTime = std::chrono::high_resolution_clock::now();
}

/**
 * Adds a keyframe to the animation.
 *
 * @param time - The timestamp of the keyframe in seconds.
 * @param action - The action to perform at this keyframe.
 */
void Animation::addKeyframe(const float time, const std::function<void(double)>& action)
{
    _keyframes.push_back({time, action});
    std::sort(_keyframes.begin(),
              _keyframes.end(),
              [](const Keyframe& a, const Keyframe& b)
              {
                  return a.timestamp < b.timestamp;
              });
}

/**
 * Updates the animation.<br>
 * This method should be called every frame to update the animation.
 */
void Animation::update()
{
    if (_keyframes.empty()) return;

    const auto now = std::chrono::high_resolution_clock::now();
    float elapsed = std::chrono::duration<float>(now - _startTime).count();

    // Adjust elapsed time for looping
    if (const float totalDuration = _keyframes.back().timestamp; totalDuration > 0.0f)
    {
        elapsed = std::fmod(elapsed, totalDuration);
    }

    // Find the two keyframes for interpolation
    Keyframe* prevKeyframe = nullptr;
    Keyframe* nextKeyframe = nullptr;

    for (size_t i = 0; i < _keyframes.size(); ++i)
    {
        if (_keyframes[i].timestamp > elapsed)
        {
            nextKeyframe = &_keyframes[i];
            if (i > 0)
            {
                prevKeyframe = &_keyframes[i - 1];
            }
            break;
        }
    }

    if (prevKeyframe && nextKeyframe)
    {
        // Interpolate between prevKeyframe and nextKeyframe
        const float range = nextKeyframe->timestamp - prevKeyframe->timestamp;
        float factor = (elapsed - prevKeyframe->timestamp) / range;

        // Clamp factor between 0 and 1
        factor = std::clamp(factor, 0.0f, 1.0f);

        // Trigger the interpolation action
        prevKeyframe->action(factor);
    }
    else if (!nextKeyframe && !_keyframes.empty())
    {
        // If we've passed the last keyframe, snap to the last keyframe action
        _keyframes.back().action(1.0f);
    }
}