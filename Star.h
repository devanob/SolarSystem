#ifndef STAR_H
#define STAR_H
#include "Orbital.h"
class Star : Orbital
{
public:
    Star(const vector<GLfloat>& starPostion, const float& size);
    void draw();
    bool nextFrame();
    float size;
    std::vector<vector<GLfloat>>  stars;
    void generatePoints();
};

#endif // STAR_H
