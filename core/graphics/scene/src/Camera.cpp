#include <Camera.h>

#include <Utils.h>
#include <Vec2.h>
#include <Vec3.h>
#include <Mat4.h>
#include <Uniform.h>

// Camera
Camera::Camera(const math::Vec3& lookFrom, const math::Vec3& lookAt, const math::Vec3& up)
: lookFrom(lookFrom), lookAt(lookAt), up(up), view({"view", math::Mat4::view(lookFrom, lookAt, up)}) {};

void Camera::setUniforms(GLuint programId)
{
    view.setMatrix(math::Mat4::view(lookFrom, lookAt, up));
    view.set(programId);
}

// FirstPersonCamera
FirstPersonCamera::FirstPersonCamera(const math::Vec3& lookFrom, const math::Vec3& up, math::Degrees yaw, math::Degrees pitch) : yaw(yaw), pitch(pitch),
forward
({
    cosf(math::toRadians(pitch)) * cosf(math::toRadians(yaw)),
    sinf(math::toRadians(pitch)),
    cosf(math::toRadians(pitch)) * sinf(math::toRadians(-yaw))
}),
Camera(
    lookFrom, 
    lookFrom + math::Vec3
    {
        cosf(math::toRadians(pitch)) * cosf(math::toRadians(yaw)),
        sinf(math::toRadians(pitch)),
        cosf(math::toRadians(pitch)) * sinf(math::toRadians(-yaw))
    },
    up
) {}

void FirstPersonCamera::deltaPositionCallback(double deltatime, const std::vector<Input::Mouse::PositionEvent>& deltaPositionEvents)
{
    using namespace Input::Mouse;

    static const float moveSpeed = 50.0f;

    for(auto& deltaPositionEvent : deltaPositionEvents)
    {
        // Update yaw and pitch based on input
        yaw.degrees -= deltaPositionEvent.position.elements[0] * moveSpeed;
        pitch.degrees += deltaPositionEvent.position.elements[1] * moveSpeed;
    }

    // Limit yaw to 360 degrees to limit floating point errors with big values.
    yaw.degrees = std::fmod(yaw, 360.0f);

    // Limit pitch to a 180 degreee arch.
    if(pitch > 89.99f)
        pitch.degrees = 89.99f;
    if(pitch < -89.99f)
        pitch.degrees = -89.99f;

    // Update forward vector
    forward =
    {
        cosf(math::toRadians(pitch)) * cosf(math::toRadians(yaw)),
        sinf(math::toRadians(pitch)),
        cosf(math::toRadians(pitch)) * sinf(math::toRadians(-yaw))
    };

    // Update lookAt vector
    lookAt = lookFrom + forward;
}

void FirstPersonCamera::keyCallback(double deltatime, const std::vector<Input::Keyboard::KeyEvent>& keyEvents)
{
    using namespace Input::Keyboard;

    static const float moveSpeed = 10.0f; // Per second

    // Make a frameMoveSpeed based on frame render time, to make input independent of FPS
    const float frameMoveSpeed = moveSpeed * (float)deltatime;

    // Limit WASD movement to horizontal plane by using a horizontal forward vector
    math::Vec3 horizontalForward = forward;
    horizontalForward.elements[1] = 0.0f;
    horizontalForward = horizontalForward.normalize();

    for(auto& keyEvent : keyEvents)
    {
        if(keyEvent.action == Action::HOLD)
        {
            switch(keyEvent.key)
            {
            case Key::S:
                lookFrom -= horizontalForward * frameMoveSpeed;
                break;
            case Key::W:
                lookFrom += horizontalForward * frameMoveSpeed;
                break;
            case Key::A:
                lookFrom -= horizontalForward.cross(up) * frameMoveSpeed;
                break;        
            case Key::D:
                lookFrom += horizontalForward.cross(up) * frameMoveSpeed;
                break;
            case Key::SPACE:
                lookFrom.elements[1] += frameMoveSpeed;                
                break;
            case Key::LEFT_SHIFT:
                lookFrom.elements[1] -= frameMoveSpeed;                
                break;
            }
        }
    }

    // Update lookAt so its always relative to lookFrom
    lookAt = lookFrom + forward;
}