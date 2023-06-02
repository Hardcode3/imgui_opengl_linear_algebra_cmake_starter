#include <glgraph.h>

// foreward declaration
int testPointDrawingWithoutAntiAliasing();
int testPointDrawingWithAntiAliasing();
int testLineDrawingWithoutAntiAlisaing();
int testLineDrawingWithAntiAlisaing();
int testTriangleDrawingWithAntiAliasing();

int main()
{
    return 0;
}

int testPointDrawingWithoutAntiAlisaing()
{
    return glGraphBase::drawPointDemo(true);
}

int testPointDrawingWithAntiAliasing()
{
    return glGraphBase::drawPointDemo(false);
}

int testLineDrawingWithoutAntiAlisaing()
{
    return glGraphBase::drawLineDemo(false);
}

int testLineDrawingWithAntiAlisaing()
{
    return glGraphBase::drawLineDemo(true);
}

int testTriangleDrawingWithAntiAliasing()
{
    return glGraphBase::drawTriangleDemo(true);
}


