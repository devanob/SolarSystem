#include "Moon.h"
#include <iostream>
bool Moon::nextFrame()
{

    currentAngle += angleRotation;
    if (currentAngle > 360){
        currentAngle = 0.0;
    }
    setNeedsRedraw(true);
    return true;

}

void Moon::draw()
{
    if(needsRedraw == true ){
        preDrawSetup();///starting drawing
        glTranslated(getCentreAbout().x,getCentreAbout().y, getCentreAbout().z);
        glRotated(currentAngle,0.0, 1.0, 0.0);
        glTranslated(getOrbitalRadius(), 0.0,0.0);
        glColor3f(getColour().x, getColour().y, getColour().z);
        glutSolidSphere(getObjRadius(), 50,50);
        postDrawDeSetup();///stop drawing
        setNeedsRedraw(false);
    }



}

Moon::Moon(const float &objradius, const float &OrbitalRadius, const float &xCentre, const float &yCentre, const float &zCentre, const float &rotationsPerSec)
    : Orbital(objradius,OrbitalRadius)
{
    vector<GLfloat> colour;
    colour.x = 1.0;
    colour.y =1.0;
    colour.z =  1.0;
    this->setColour(colour);
    this->setActualPosition(0,0,0);
    this->setCentreAbout(xCentre,yCentre,zCentre);
    this->angleRotation = (rotationsPerSec * 360) / 30.0;
    currentAngle = 0.0;
    setNeedsRedraw(true);

}
