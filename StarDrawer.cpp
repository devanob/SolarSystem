#include "StarDrawer.h"
#include <iostream>

void StarDrawer::generate5Points()
{
    this->points_star.resize(10*3);
    double angle_i = 360.0/5;
    double angle = 90.00;
    vector<GLdouble>* vec= (vector<GLdouble>*)points_star.data();
    for (unsigned int i = 0; i < 10; i+=2){
        vec[i].x =this->size_float*std::cos(angle*degreeToRads);
        vec[i].y = this->size_float*std::sin(angle*degreeToRads);
        vec[i].z = 0.0;
        angle -= angle_i;
    }
    vector <GLfloat> intermediatePoint;
        for(unsigned int i = 1 ; i < 10; i+=2){
            intermediatePoint.x = (vec[(i-1)%10].x + vec[(i+1)%10] .x) /2.0;
            intermediatePoint.y = (vec[(i-1)%10].y + vec[(i+1)%10] .y) /2.0;
            intermediatePoint.x/=2.0;
            intermediatePoint.y/=2.0;
            vec[i].x = intermediatePoint.x;
            vec[i].y = intermediatePoint.y;
            vec[i].z = 0.0;
        }

}

bool StarDrawer::getMakeTwinkle() const
{
    return makeTwinkle;
}

void StarDrawer::setMakeTwinkle(bool value)
{
    makeTwinkle = value;
}
void StarDrawer::makeMakeRotate(const bool &rotate)
{
    this->rotateStart = rotate;
    angleofRotattion = 0.0;
}

bool StarDrawer::nextFrame()
{
    if (rand() % 100 < 50){
        colour.x = rand()  / (float) RAND_MAX;
        colour.y = rand()  / (float) RAND_MAX;
        colour.z = rand()  / (float) RAND_MAX;
    }
    else {
        colour.x = 1;
        colour.y = 1;
        colour.z = 1;

    }
	
    this->currentStep += this->incrementStep;
    bool reachAnimationEnd = false;
    if (currentStep >= 1.0){
        this->resetBig(); // must be reset to the big Star  probagation
    }
    else if (currentStep<= 0.0){ //the circle has finished it full cycle
        this->resetSmall();
        reachAnimationEnd = true;

    }
    setNeedsRedraw(true);
    return reachAnimationEnd;
}

void StarDrawer::resetBig()
{
    this->currentStep = 1.0;
    this->incrementStep = -1*std::abs(incrementStep);

}

void StarDrawer::resetSmall()
{
    this->currentStep = 0.0;
    this->incrementStep = std::abs(incrementStep);

}

StarDrawer::StarDrawer(const float size_diameter, unsigned int steps,
                       const float&angle_step, const vector<GLfloat> &position)
{
    this->setMakeTwinkle(false);
    this->setActualPosition(position.x,position.y,position.z);
    this->size_float = size_diameter;
    this->animation_step = steps;
    this->incrementStep = 1.0 / (float) steps;
    this->currentStep = 1.0;
    this->generate5Points();
    this->points_render.resize(10*3);
    //srand(time(NULL));
    colour.x =1.0;
    colour.y =1.0;
    colour.z =1.0;
    this->incrementAngle = angle_step;
    this->setNeedsRedraw(true);
    this->rotateStart = false;
    glimmer = false;
    dontGlimmer= true;
    frames = 0;

}



void StarDrawer::draw()
{
    if (needsRedraw == true){
        preDrawSetup();
        vector<GLdouble>* vec;
        if(getMakeTwinkle() == true){
            vec = (vector<GLdouble>*)points_render.data();
        }
        else{

            vec = (vector<GLdouble>*)points_star.data();
        }

        if (this->rotateStart == true){
            glRotated(currentStep,0,1,0);
        }
        glTranslated(actualPosition.x,
                     actualPosition.y,
                     actualPosition.z);
        glBegin(GL_TRIANGLE_FAN);
        glVertex3d(0.0,0.0,0.0);
        glColor4f(colour.x,colour.y,colour.z,
                  ((rand()% 100) < 20) ? currentStep : 1.0);
        for (unsigned int i = 0 ; i <= 10 ; i++){
            glVertex3dv((GLdouble*)&vec[i%10]);
        }
        glEnd();
        postDrawDeSetup();
        setNeedsRedraw(false);
    }

}
