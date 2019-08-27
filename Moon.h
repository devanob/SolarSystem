#ifndef MOON_H
#define MOON_H
#include "Orbital.h"

class Moon : public Orbital
{
public:
    bool nextFrame();
    void draw();
    float angleRotation;
    float currentAngle;
    Moon(const float& objradius, const float& OrbitalRadius,
         const float& xCentre,const float& yCentre, const float& zCentre, const float& rotationsPerSec);
};

#endif // MOON_H
