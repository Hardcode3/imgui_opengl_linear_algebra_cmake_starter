#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// from https://opengl.developpez.com/tutoriels/opengl-tutorial/3-matrices/
int main()
{
    glm::mat4 myMatrix;
    glm::vec4 myVector;
    glm::vec4 transformedVector = myMatrix * myVector;

    return 0;
}
