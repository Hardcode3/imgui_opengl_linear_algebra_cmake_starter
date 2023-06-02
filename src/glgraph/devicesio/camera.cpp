#include <camera.h>

Camera::Camera(glm::vec3 position):cameraPosition_(position), yaw_(0.0f), pitch_(0.0f), speed_(2.5f), sensitivity_(1.0f), zoom_(45.0f), cameraFront_(glm::vec3(1.0f, 0.0f, 0.0f))
{
    updateVectors();
}

void Camera::updateDirection(double dx, double dy)
{
    yaw_ += (float)dx;
    pitch_ += (float)dy;
    
    if (pitch_ > 89.0f)
        pitch_ = 89.0f;
    else
        pitch_ = -89.0f;
    
    updateVectors();
}

void Camera::updatePosition(CameraAzimuth azimuth, double dt)
{
    float velocity = (float)dt * speed_;
    
    switch (azimuth) {
        case CameraAzimuth::FOREWARD:
            cameraPosition_ += cameraFront_ * velocity;
            break;
        case CameraAzimuth::BACKWARD:
            cameraPosition_ -= cameraFront_ * velocity;
            break;
        case CameraAzimuth::RIGHT:
            cameraPosition_ += cameraRight_ * velocity;
            break;
        case CameraAzimuth::LEFT:
            cameraPosition_ -= cameraFront_ * velocity;
            break;
        case CameraAzimuth::UP:
            cameraPosition_ += cameraUp_ * velocity;
            break;
        case CameraAzimuth::DOWN:
            cameraPosition_ -= cameraFront_ * velocity;
            break;
            
        default:
            assert(true);
    }
}

void Camera::updateZoom(double dy)
{
    if (zoom_ >= 1.0f && zoom_ <= 45.0f)
        zoom_ -= (float)dy;
    else if (zoom_ < 1.0f)
        zoom_ = 1.0f;
    else
        zoom_ = 45.0f;
}

void Camera::updateVectors()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw_) * cos(glm::radians(pitch_)));
    direction.y = sin(glm::radians(pitch_));
    direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    
    // update camera vectors
    cameraFront_ = glm::normalize(direction);
    cameraRight_ = glm::normalize(glm::cross(cameraFront_, glm::vec3(0.0f, 1.0f, 0.0f)));
    cameraUp_ = glm::normalize(glm::cross(cameraRight_, cameraFront_));
}
