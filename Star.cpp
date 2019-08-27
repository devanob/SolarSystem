#include "Star.h"

Star::Star(const vector<GLfloat> &starPostion, const float& size)
{
    setActualPosition(starPostion.x,starPostion.y,starPostion.z);
    this->size = size;
    generatePoints();
    colour.x =1.0;
    colour.y =1.0;
    colour.z =1.0;


}

void Star::draw()
{

    if(needsRedraw == true){
        preDrawSetup();
        glColor3f(colour.x,colour.y,colour.z);
        glTranslated(actualPosition.x,actualPosition.y,actualPosition.z);
        glBegin(GL_LINES);
        for (unsigned int i  = 0; i< stars.size(); i++){
            glVertex3f(0,0,0);
            glVertex3f(stars[i].x,stars[i].y,stars[i].z);
        }
        glEnd();
        setNeedsRedraw(false);
        postDrawDeSetup();
    }


}

bool Star::nextFrame()
{
    setNeedsRedraw(true);
}

void Star::generatePoints()
{
    vector<GLfloat> starPoint;
    for (int i  = 45; i <= 360 ; i+=120){
        starPoint.x = size * std::cos(i*degreeToRads);
        starPoint.y = size * std::sin(i*degreeToRads);
        starPoint.z = 0.0;
        stars.push_back(starPoint);
    }
    //std::cout << stars.size() << std::endl;
}
