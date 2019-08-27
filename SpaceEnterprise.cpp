#include "SpaceEnterprise.h"
#include <iostream>
vector<GLfloat> SpaceEnterprise::getEyeOffset() const
{
    return eyeOffset;
}

void SpaceEnterprise::setEyeOffset(const float &eyexoff, const float &eyeyOff, const float &eyezOff)
{
    this->eyeOffset.x = eyexoff;
    this->eyeOffset.y = eyeyOff;
    this->eyeOffset.z = eyezOff;

}



vector<GLfloat> SpaceEnterprise::getEyesPosition() const
{
    return eyesPosition;
}

bool SpaceEnterprise::setEyesPosition(const vector<GLfloat> &value)
{
    eyesPosition = value;
    return true;
}

SpaceEnterprise::SpaceEnterprise(const std::string &fileName)
{
    readFile(fileName);
    this->setShieldOn(false);
    glimmer = false;
    dontGlimmer= true;
    frames = 0;

}


bool SpaceEnterprise::nextFrame()
{
    frames++;
    if(dontGlimmer == true && frames < 60){
        colour.x = 1.0;
        colour.y = 1.0;
        colour.z = 1.0;
    }
    if(dontGlimmer == true && frames > 60){
        dontGlimmer = false;
        glimmer = true;
        frames =0;
    }
    if (glimmer == true && frames  == 0){
        if ((rand() % 100) < 30){
            glimmer = true;
            dontGlimmer = false;
            frames = 0;
            colour.x = rand() / (float) RAND_MAX;
            colour.y = rand() / (float) RAND_MAX;
            colour.z = rand() / (float) RAND_MAX;

        }
        else {
            dontGlimmer = true;
            glimmer = false;
            frames = 0;
        }

    }
    if(glimmer == true && frames>= 60){
        glimmer = false;
        dontGlimmer = true;
    }
    setNeedsRedraw(true);
    return true;
}

void SpaceEnterprise::draw()
{
    if(needsRedraw == true){
        preDrawSetup();
        glTranslated(eyesPosition.x-eyeOffset.x,eyesPosition.y - eyeOffset.y,eyesPosition.z - eyeOffset.z);
        glScaled(2000,2000,2000);
        GLfloat enColourMax = 1989.0;
        GLfloat enColour = 0;
        glBegin(GL_TRIANGLES);
        for (unsigned int i = 0 ; i < facePoint.size() ; i++){
            enColour = ((float)i)/ enColourMax;
                glColor3f(enColour,enColour,enColour);
                glVertex3f(verticesPoint[facePoint[i].x -1 ].x ,verticesPoint[facePoint[i].x -1 ].y,verticesPoint[facePoint[i].x -1].z);
                glVertex3f(verticesPoint[facePoint[i].y -1].x,verticesPoint[facePoint[i].y -1 ].y,verticesPoint[facePoint[i].y -1 ].z );
                glVertex3f(verticesPoint[facePoint[i].z -1 ].x ,verticesPoint[facePoint[i].z -1 ].y,verticesPoint[facePoint[i].z -1].z );

        }
        glEnd();
        postDrawDeSetup();
        if (getShieldOn()== true){
            preDrawSetup();
            glLineWidth(1);
            preDrawSetup();
            glTranslated(eyesPosition.x-eyeOffset.x,eyesPosition.y - eyeOffset.y,eyesPosition.z - eyeOffset.z);
            glRotated(-15,1,0,0);
            glRotated(8,0,1,0);
            glScaled(900,900,1800);
            glColor4f(colour.x,
                      colour.y,
                      colour.z,
                      0.1);
            glutWireSphere(1,15,50);
            postDrawDeSetup();
        }

        setNeedsRedraw(false);

    }
}

bool SpaceEnterprise::getShieldOn() const
{
    return shieldOn;
}

void SpaceEnterprise::setShieldOn(bool value)
{
    shieldOn = value;
}

void SpaceEnterprise::readFile(const std::string &fileName)
{
    std::ifstream file(fileName, std::ios::in);
    char vOrf;
    vector<GLfloat> pointvertice;
    vector<GLint> pointfaces;
    if(file.fail()){
        throw std::runtime_error("Erorr Opening: "+fileName);
    }
    while(!file.eof()){
        file >> vOrf;
        if (vOrf == 'v'){
            file >> pointvertice.x;
            file >> pointvertice.y;
            file >> pointvertice.z;
            this->verticesPoint.push_back(pointvertice);
        }
        else if (vOrf == 'f'){
           file >> pointfaces.x;
           file >> pointfaces.y;
           file >> pointfaces.z;
          this->facePoint.push_back(pointfaces);
        }
    }

    file.close();
}
