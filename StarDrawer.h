#ifndef STARDRAWER_H
#define STARDRAWER_H
#include "GL/freeglut.h"
#include <vector>
#include "OpenGlFuncTools.h"
#include <cmath>
#include<ctime>
#include "Orbital.h"
/**
 * @brief The StarDrawer class
 */
class StarDrawer:public Orbital
{
    private: 
        int frames;
        bool glimmer;
        bool dontGlimmer;
        bool rotateStart;
        double angleofRotattion;
        std::vector<GLfloat> colorStar;
        std::vector<GLdouble> points_star; //full star points
        std::vector<GLdouble> points_render; //points to render
        float size_float; //size of the star
        unsigned int animation_step; // betwee 0,1
        float currentStep;
        float incrementStep;
        // the number of steps for animation
        //more steps smother animatio
        void generate5Points();
        //void reset();// reset the star to its original frame
        float incrementAngle;
        bool makeTwinkle;
    public:
        void makeMakeRotate(const bool &rotate);
        bool nextFrame();// returns true then 0 frame has been reached
        void resetBig();// reset the star to its original frame (Big)
        void resetSmall();// reset the star to its original frame (Small)
        StarDrawer(const float size_diameter, unsigned int steps, const float&angle_step
                   ,const vector<GLfloat>& position);
        void draw(); // draw the
        //void reset(); //reset the animation to default;
        //void nextAnimation(); //generates the next for vertixes for the animation

        bool getMakeTwinkle() const;
        void setMakeTwinkle(bool value);
};

#endif // STARDRAWER_H
