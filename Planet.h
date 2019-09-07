#ifndef PLANET_H
#define PLANET_H
#include "Orbital.h"
#include "Moon.h"
#include <vector>
/**
 * @brief The Planet class- Planet Class That Represent A Planet Model
 */
class Planet : public Orbital
{
public:
    /**
     * @brief Planet- Contructor
     * @param objradius - radius of the planet
     * @param OrbitalRadius
     * @param xCentre - the planet x coordinate
     * @param yCentre- the planet y coordinate
     * @param zCentre - the planet z coordinate
     * @param rotationsPerSec - the  rotation speed of the planet about the sun
     */
    Planet(const float& objradius, const float& OrbitalRadius,
    const float& xCentre,const float& yCentre, const float& zCentre, const float& rotationsPerSec);
    //add a random moon the planet
    float addMoons();
    //draw the moons
    void drawMoons();
    //overide base method to render the next frame
    bool nextFrame();
    //handles the draw of the planet
    void draw();
    //get a flag whehter the moons children should be drawned
    bool getDrawMoonOrbital() const;
     //set a flag whehter the moons children should be drawned
    /**
     * @brief setDrawMoonOrbital
     * @param value- bool value
     */
    void setDrawMoonOrbital(bool value);

private:
    /*
    * @brief drawCircle-helper method for drawing moon child instances
    */
    void drawCircle();
    bool drawMoonOrbital;
    float angleRotation;
    float currentAngle;
    /**
     * @brief moons-list of children moon
     */
    std::vector<Moon*> moons;

};

#endif // PLANET_H
