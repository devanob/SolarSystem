#include "Sun.h"
#include "random"
#include "time.h"
#include <iostream>

Sun::Sun(const float &radius, const vector<GLfloat> &colour) : Orbital(radius,0.0)
{

    ///
    this->setActualPosition(0,0,0);
    this->setCentreAbout(0,0,0);
    this->setColour(colour);
    this->setOrbitalCircle(false);
    this->setCoronoOn(false);
    this->lengthCorona = 500;
    srand(time(NULL));
    this->generateConorona();

}

void Sun::setCoronoOn(const bool& value)
{
    coronoOn = value;
}

void Sun::setOrbitalCircle(const bool &value)
{
    OrbitalCircle = value;
}

void Sun::draw()
{
    if (needsRedraw == true){
        preDrawSetup();
        glLineWidth(100.0f);
        glColor4f(this->colour.x, this->colour.y, this->colour.z,1.0);
        glutSolidSphere(getObjRadius(),90,90);
        if (getCoronoOn() == true){
            glBegin(GL_LINES);
            for (unsigned int i = 0; i < CoronaVector.size() ; i++){
                glColor4f(colour.x, colour.y, colour.z,1.0);
                glVertex3f(getObjRadius()*NormalizeCoronaVector[i].x,
                           getObjRadius()*NormalizeCoronaVector[i].y,
                           0.0);
                glColor4f(tipColour.x, tipColour.y, tipColour.z,0.0);
                glVertex3f(CoronaVector[i].x+getObjRadius()*NormalizeCoronaVector[i].x,
                           CoronaVector[i].y+getObjRadius()*NormalizeCoronaVector[i].y,
                           0.0);
            }
            glEnd();
       }
       postDrawDeSetup();
       setNeedsRedraw(false);
    }
}

bool Sun::nextFrame()
{

    float scaledLength;
    for (unsigned int i = 0 ; i < NormalizeCoronaVector.size(); i++)
    {
        scaledLength = (rand() / (float) RAND_MAX)* lengthCorona ;
        CoronaVector[i].x = scaledLength*this->NormalizeCoronaVector[i].x;
        CoronaVector[i].y = scaledLength*this->NormalizeCoronaVector[i].y;
        CoronaVector[i].z = 0.0;
    }
    setNeedsRedraw(true);
    return true;
}

void Sun::generateConorona()
{
    vector<GLfloat> vecCorona;
    for (float angle = 0 ; angle <= 360 ; angle++){
        vecCorona.x = std::cos(degreeToRads*angle);
        vecCorona.y = std::sin(degreeToRads*angle);
        vecCorona.z = 0.0;
        this->NormalizeCoronaVector.push_back(vecCorona);
    }
    this->CoronaVector.resize(NormalizeCoronaVector.size());
}

void Sun::setTipColour(const vector<GLfloat> &value)
{
    tipColour.x = value.x;
    tipColour.y = value.y;
    tipColour.z = value.z;
}

bool Sun::getCoronoOn() const
{
    return coronoOn;
}

float Sun::getLengthCorona() const
{
    return lengthCorona;
}

void Sun::setLengthCorona(float value)
{
    lengthCorona = value;
}
