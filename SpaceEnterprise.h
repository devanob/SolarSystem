#ifndef SPACEENTERPRISE_H
#define SPACEENTERPRISE_H
#include <string>
#include <vector>
#include <fstream>
#include "OpenGlFuncTools.h"
#include "Orbital.h"
#include <ctime>
class SpaceEnterprise : public Orbital
{
    std::vector<vector<GLfloat>> verticesPoint;
    std::vector<vector<GLint>> facePoint;
    vector<GLfloat> eyesPosition;
    vector<GLfloat> eyeOffset;
    public:
        int frames;
        bool glimmer;
        bool dontGlimmer;
        std::clock_t time;
        SpaceEnterprise(const std::string & fileName);
        bool nextFrame();
        void draw();
        bool getShieldOn() const;
        void setShieldOn(bool value);

        vector<GLfloat> getEyeOffset() const;
        void setEyeOffset(const float& eyexOff, const float& eyeyOff
                          , const float& eyezOff);

        vector<GLfloat> getEyesPosition() const;
        bool setEyesPosition(const vector<GLfloat> &value);

private:
        vector<GLfloat> shieldColour;
        bool shieldOn;
        void readFile(const std::string& fileName);


};

#endif // SPACEENTERPRISE_H
