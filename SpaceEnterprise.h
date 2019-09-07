#ifndef SPACEENTERPRISE_H
#define SPACEENTERPRISE_H
#include <string>
#include <vector>
#include <fstream>
#include "OpenGlFuncTools.h"
#include "Orbital.h"
#include <ctime>
/**
 * @brief The SpaceEnterprise class- Represent A Space Ship Instanc Inherits From Oribital Class
 */
class SpaceEnterprise : public Orbital
{
    /**
     * @brief verticesPoint-vertices of the spaceship
     */
    std::vector<vector<GLfloat>> verticesPoint;
    /**
     * @brief facePoint-represent the face index of the faces
     */
    std::vector<vector<GLint>> facePoint;
    /**
     * @brief eyesPosition- the position of the world view eye
     */
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
        /**
         * @brief shieldColour- toggle the shiel color
         */
        vector<GLfloat> shieldColour;/**
         * @brief shieldOn-shield flag bool
         */
        bool shieldOn;
        /**
         * @brief readFile-reads the object fle
         * @param fileName-filename string
         */
        void readFile(const std::string& fileName);


};

#endif // SPACEENTERPRISE_H
