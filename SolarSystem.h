#ifndef SolarSystem_H
#define SolarSystem_H
#include <GL/glew.h>
#include "Sun.h"
#include <iostream>
#include <ctime>
#include "SpaceEnterprise.h"
#include "StarDrawer.h"
///
/// \brief The SolarSystem class
///This is Graphics Handlier For this Render System
/// This Class handles the intialization of the glutLoop Functions
/// Handles The Drawing Of Menue And Shape Animation Class
class SolarSystem
{
public:
    static SolarSystem* thisInstance;
    //static SolarSystem* thisInstance;
    void  ChangeView(const unsigned int& viewOrientation);
    void addPlanets();
    bool nexFrame();
    vector<GLfloat> eyePosition; // the point where the eyes is located
    vector<GLfloat> LookAtVector; // the  vector for the lookatCentre
    vector<GLfloat> upVector; // the up vector <Perependicular>
    ////
    float InnerSolarSystemWidth; //the size of the inner Solar System width
    float InnerSolarSystemHeight; //the size of the innner Solar System height
    float InnerSolarSystemDepth; //the size of the innerSolar System depth
    ///
    float OuterSolarSystemWidth; //the size of the outer Solar System width
    float OuterSolarSystemHeight; //the size of the outer Solar System height
    float OuterSolarSystemDepth; //the size of the outer Solar System depth
    void lookAt();
    void setUpBoxSolarSystem();
    void generateStars();
    ///
    /// \brief thisInstance
    ///The inner instance of this class contain non- static method that deal
    /// with the menue and AnimationHandlier unlike the outer version fo theis class
    /// without a allocated instance non-static members are avaible

    ///
    /// \brief menu
    ///This handles the interaction with the menue
    Sun* sun;
    std::vector<Planet*> planets;
    SpaceEnterprise* spaceShip;
    std::vector<StarDrawer*> stars;
    bool drawStars;
    bool setEnterprisePos();

    ////
    /// \brief shapeAnim Handles The Animations Of The steps
    ///
    //ShapeAnimationHandiler* shapeAnim;
    ///
    /// \brief WindowWidth
    ///The Current Size Of Real World window for resizing(Width)
    unsigned int WindowWidth;
    ///
    /// \brief WindowHeight The Current Size Of Real World window for resizing(Height)
    ///
    unsigned int WindowHeight;
    ////
    /// \brief SolarSystem - Intializing the Outer Class of this class
    /// \param argc - the command line argument
    /// \param argv - the command line argument
    /// \param WindowWidth - the Width Of the Window
    /// \param WindowHeight - the Height Of the Window
    ///
    SolarSystem(int argc, char **argv, const unsigned int& WindowWidth,
    const unsigned int& WindowHeight );
    ///
    /// \brief SolarSystem-Handles Intiaization Of The Inner This Instance Class
    /// \param WindowWidth - The Width Of the Window
    /// \param WindowHeight - The Height Of The Window
    ///
    SolarSystem(const unsigned int &WindowWidth, const unsigned int &WindowHeight);
    ///Handles Mouse Control OF the Menue/IS Wrapper To MouseControl
    /// ///
    ///  button is the buton pressed
    /// x is the coordinates of the mouse when it is press in pixel coorindinates
    ///
    /// \brief mouseControl - The inner this instance of this class than control the Pixel Cooridinates
    ///  /// \param button - the button pressed
    /// \param state - the state of the button pressed
    /// \param x - x Pixel Coorinates
    /// \param y -  y Pixel Cooridinates
    ///
    void setUpProspective();
    void KeyboardFunc(const unsigned char& key,
                             const int& x, const int& y);
    static void wrapperKeyboardFunc(unsigned char key,
                             const int x, const int y);
    ///
    /// \brief WarpDraw Warps Around the Draw Function of draw function
    ///
    static void WarpDraw();
     void draw();
     ///
     /// \brief setup - Sets Up the glut System for interaction
     /// \param argc - command line arguments
     /// \param argv - command line arguments
     /// \param width - the width of the window
     /// \param height - the height of the window
     ///
    void setup(int argc, char **argv, const int& width, const int& height);
    ///
    /// \brief WrapResize - Wraps Around the Resize method
    /// \param width -the width of the window
    /// \param height- the height of the window
    ///
    static void WrapResize(int width,int height);
    ///
    /// \brief resize- redraw the current screen when the window is resize
    ///\param width -the width of the window
    /// \param height- the height of the window
    ///
    void resize(const int& width, const int& height);
    ///
    /// \brief executeProgram
    ///executes the glutMainLoop
    void executeProgram();
    ///Wrappe Idle Funciton
    static void WarapperIdleFunc();
    ///
    /// \brief WrapperAnimate - Wrapper For the Animate Function
    /// \param i
    ///
    static void WrapperAnimate(int i);
    ///
    /// \brief animate- Animates both The menue and animation of this program
    /// set at a rate of ~30 frames per second
    /// \param i - unused parametre
    static void WrapperspecialFunc(int key, int x, int y);
    static void WrapperFuncUp(int key, int x, int y);
    void specialFunc(const int& key, const int& x, const int& y);
    void specialFuncUp(const int& key, const int& x, const int& y);
    ///
    bool cameraForwards;
    bool cameraBackWards;
    bool cameraLeft;
    bool cameraRight;
    bool cameraUp;
    bool cameraDown;

    void animate(const unsigned& i );
    bool drawRings;
    void drawOrbitRings();
    ~SolarSystem();
    void setDrawRings(bool value);
    bool getDrawRings() const;

    bool getCameraForwards() const;
    void setCameraForwards(bool value);
    bool getCameraBackWards() const;
    void setCameraBackWards(bool value);
    bool getCameraLeft() const;
    void setCameraLeft(bool value);
    bool getCameraRight() const;
    void setCameraRight(bool value);
    bool getCameraUp() const;
    void setCameraUp(bool value);
    bool getCameraDown() const;
    void setCameraDown(bool value);
    bool getDrawStars() const;
    void setDrawStars(bool value);
};


#endif // SolarSystem_H
