#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <stdio.h>
#include <stdlib.h>

int helloWorld()
{
    
    // initialize glfw and create glfw object
    GLFWwindow* Window;
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }
    Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!Window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(Window);
    
    // define a loop terminating when the loop is closed
    while (!glfwWindowShouldClose(Window)) {
        // set up the viewport
        float ratio;
        int width, height;
        
        // get height and width of the window and put it in variables
        glfwGetFramebufferSize(Window, &width, &height);
        // define the ratio from width and height
        ratio = (float)width / (float)height;
        
        // create the viewport in the window
        glViewport(0, 0, width, height);
        
        // clear the window
        glClear(GL_COLOR_BUFFER_BIT);
        
        // set up the camera matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // draw a rotating triangle with different colors for each vertex
        glRotatef((float)glfwGetTime() * 50.0f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
        
        // swap front and back buffers to update the screen
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    
    // terminate glfw and close the window
    glfwDestroyWindow(Window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}

int main()
{
    helloWorld();
    return 0;
}
