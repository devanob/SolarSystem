#ifndef MOON_H
#define MOON_H
#include "Orbital.h"

/**
 * @brief The Moon class- Represents A Moon Object In Solar System
 */
class Moon : public Orbital
{
public:
    /*
     Returns A Flag Bool If the Next Page Should Be Rendered
     */
    bool nextFrame();
    /**
     * @brief draw
     */
    void draw();
    float angleRotation;
    float currentAngle;
    Moon(const float& objradius, const float& OrbitalRadius,
         const float& xCentre,const float& yCentre, const float& zCentre, const float& rotationsPerSec);
};

#endif // MOON_H
