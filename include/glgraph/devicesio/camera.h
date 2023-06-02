#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraAzimuth { NONE = 0, FOREWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Camera
{
public:
    glm::vec3 cameraPosition_;
    
    // three camera vectors defining the main directions associated to the camera
    glm::vec3 cameraFront_;
    glm::vec3 cameraUp_;
    glm::vec3 cameraRight_;
    
    float yaw_, pitch_;
    
    float speed_, sensitivity_, zoom_;
    
    Camera(glm::vec3 position = glm::vec3(0.0f));
    
    void updateDirection(double dx, double dy);
    void updatePosition(CameraAzimuth azimuth, double dt);
    void updateZoom(double dy);
    
    glm::mat4 getViewMatrix() {return glm::lookAt(cameraPosition_, cameraPosition_ + cameraFront_, cameraUp_);}
    float getZoom() {return zoom_;}
    
private:
    void updateVectors();
};

#endif
