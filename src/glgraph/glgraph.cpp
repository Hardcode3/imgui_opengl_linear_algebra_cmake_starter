#include <glgraph.h>

void glGraphBase::drawPoint(Vertex v, float size)
{
    glPointSize(size);
    glBegin(GL_POINTS);
    glColor4f(v.r, v.g, v.b, v.a);
    glVertex3f(v.x, v.y, v.z);
    glEnd();
}

void glGraphBase::drawSegment(Vertex v1, Vertex v2, float width)
{
    assert(width >= 0);
    
    glLineWidth(width);
    glBegin(GL_LINES);
    glColor4f(v1.r, v1.g, v1.b, v1.a);
    glVertex3f(v1.x, v1.y, v1.z);
    glColor4f(v2.r, v2.g, v2.b, v2.a);
    glVertex3f(v2.x, v2.y, v2.z);
    glEnd();
}

void glGraphBase::drawTriangle(Vertex v1, Vertex v2, Vertex v3)
{
    glBegin(GL_TRIANGLES);
    glColor4f(v1.r, v1.g, v1.b, v1.a);
    glVertex3f(v1.x, v1.y, v1.z);
    glColor4f(v2.r, v2.g, v2.b, v2.a);
    glVertex3f(v2.x, v2.y, v2.z);
    glColor4f(v3.r, v3.g, v3.b, v3.a);
    glVertex3f(v3.x, v3.y, v3.z);
    glEnd();
}

void glGraphBase::drawGrid(float width, float height, float gridStep, float gridThickness)
{
    assert(gridStep >= 0);
    assert(gridThickness >= 0);
    
    //draw horizontal lines
    for(float i=-height; i<height; i+=gridStep){
        Vertex v1 = {-width, i, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        Vertex v2 = {width, i, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        drawSegment(v1, v2, gridThickness);
    }
    // draw vertical lines
    for(float i=-width; i<width; i+=gridStep){
        Vertex v1 = {i, -height, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        Vertex v2 = {i, height, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        drawSegment(v1, v2, gridThickness);
    }
}

void glGraphBase::scatterPlot2D(const Data* data, int nbPoints, float pointSize, float axSize, float gridStep, float gridThickness)
{
    assert(axSize >= 0);
    assert(nbPoints >= 0);
    assert(pointSize >= 0);
    assert(gridStep >= 0);
    assert(gridThickness >= 0);
    
    // draw the x and y axes
    Vertex v1 = {-10.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    Vertex v2 = {10.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    drawSegment(v1, v2, 1.0f);
    v1.x = 0.0f;
    v1.y = -1.0f;
    v2.x = 0.0f;
    v2.y = 1.0f;
    drawSegment(v1, v2, 1.0f);
    
    // draw the data point
    for (int i = 0; i<nbPoints; i++)
    {
        float x = data[i].x;
        float y = data[i].y;
        Vertex v = {x, y, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f};
        drawPoint(v, 8.0f);
    }
    
    // draw grid
    drawGrid(5.0f, 1.0f, gridStep, gridThickness);
}

void glGraphBase::linePlot2D(const Data* data, int nbPoints, float segmentWidth)
{
    assert(nbPoints >= 0);
    assert(segmentWidth >= 0);
    
    for (int i = 0; i < nbPoints; i++)
    {
        float x1 = data[i].x;
        float y1 = data[i].y;
        float x2 = data[i+i].x;
        float y2 = data[i+1].y;
        Vertex v1 = {x1, y1, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f};
        Vertex v2 = {x2, y2, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f};
        drawSegment(v1, v2, segmentWidth);
    }
}


int glGraphBase::drawPointDemo(bool antiAliasing)
{
    // initialize glfw and create glfw object
    GLFWwindow* Window;
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }
    Window = glfwCreateWindow(640, (int)(480/2), "Drawing points of increasing size", NULL, NULL);
    if(!Window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(Window);
    
    // for anti aliasing and smoothing
    if(antiAliasing)
    {
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
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
        
        // draw points of increasing sizes here
        float pointSize = 5.0f;
        for (float x = 0.0f; x <= 1.0f; x+= 0.2f, pointSize += 5)
        {
            glGraphBase::Vertex v = {x, 0.0f , 0.0f , 1.0f , 1.0f , 1.0f , 1.0f };
            glGraphBase::drawPoint(v, pointSize);
        }
        
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

int glGraphBase::drawTriangleDemo(bool antiAliasing)
{
    // initialize glfw and create glfw object
    GLFWwindow* Window;
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }
    Window = glfwCreateWindow(640, (int)(480), "Drawing points of increasing size", NULL, NULL);
    if(!Window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(Window);
    
    // for anti aliasing and smoothing
    if(antiAliasing)
    {
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    // define a loop terminating when the loop is closed
    while (!glfwWindowShouldClose(Window)) {
        float ratio;
        int width, height;
        
        glfwGetFramebufferSize(Window, &width, &height);
        ratio = (float) width / (float)height;
        
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        //Orthographic Projection
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        drawGrid(5.0f, 1.0f, 0.05f, 1.0f);
        
        //define the vertices and colors of the line segments
        Vertex v1 = {0.0f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f};
        Vertex v2 = {-1.0f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 0.6f};
        Vertex v3 = {1.0f, -0.8f, 0.0f, 0.0f, 0.0f, 1.0f, 0.6f};
        
        // draw the triangle
        drawTriangle(v1, v2, v3);
        
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    
    // terminate glfw and close the window
    glfwDestroyWindow(Window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}

int glGraphBase::drawLineDemo(bool antiAliasing)
{
    // initialize glfw and create glfw object
    GLFWwindow* Window;
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }
    Window = glfwCreateWindow(640*2, (int)(480), "Drawing points of increasing size", NULL, NULL);
    if(!Window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(Window);
    
    // for anti aliasing and smoothing
    if(antiAliasing)
    {
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    // define a loop terminating when the loop is closed
    while (!glfwWindowShouldClose(Window)) {
        float ratio;
        int width, height;
        
        glfwGetFramebufferSize(Window, &width, &height);
        ratio = (float) width / (float)height;
        
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        //Orthographic Projection
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        drawGrid(5.0f, 1.0f, 0.05f, 1.0f);
        
        //define the vertices and colors of the line segments
        Vertex v1 = {-5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.7f};
        Vertex v2 = {5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.7f};
        Vertex v3 = {0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.7f};
        Vertex v4 = {0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.7f};
        
        //draw the line segments
        drawSegment(v1, v2, 10.0f);
        drawSegment(v3, v4, 10.0f);
        
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    
    // terminate glfw and close the window
    glfwDestroyWindow(Window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
