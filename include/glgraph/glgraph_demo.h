#pragma once

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <assert.h>


namespace glGraphBase {

typedef struct
{
    // for the position
    float x, y, z;
    
    // for the color and alpha channel
    float r, g, b, a;
} Vertex;

typedef struct
{
    float x, y, z;
} Data;

// draw a point
void drawPoint(Vertex v, float size);

// draw a segment
void drawSegment(Vertex v1, Vertex v2, float width);

// draw a triangle
void drawTriangle(Vertex v1, Vertex v2, Vertex v3);

// draw a grid
void drawGrid(float width, float height, float gridStep, float gridThickness);

void scatterPlot2D(const Data* data, int nbPoints, float pointSize = 8.0f, float axSize = 1.0f, float gridStep = 0.1f, float gridThickness = 0.1f);

void linePlot2D(const Data* data, int nbPoints, float segmentWidth = 4.0f);

int drawPointDemo(bool antiAliasing);
int drawLineDemo(bool antiAliasing);
int drawTriangleDemo(bool antiAliasing);
}

