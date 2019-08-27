#include "SolarSystem.h"

SolarSystem::SolarSystem(const unsigned int &WindowWidth, const unsigned int &WindowHeight)
{
    this->WindowHeight  = WindowHeight;
    this->WindowWidth = WindowWidth;
    vector<GLfloat> colourSun;
    colourSun.x = 0.972;
    colourSun.y = 0.980;
    colourSun.z = 0.556;
    vector<GLfloat> insideSunCorona;
    insideSunCorona.x = 0.976,
    insideSunCorona.y = 0.752;
    insideSunCorona.z =0.282;
    //addPlanets();
    sun = new Sun(4000,colourSun);
    sun->setTipColour(insideSunCorona);
    addPlanets();
    this->setDrawRings(false);
    setUpBoxSolarSystem();
    eyePosition.x =0.0;
    eyePosition.y = this->InnerSolarSystemHeight/2;
    eyePosition.z=  OuterSolarSystemDepth;
    LookAtVector.x = -eyePosition.x;
    LookAtVector.y = -eyePosition.y;
    LookAtVector.z = -eyePosition.z;
    upVector.x = 0.0f;
    upVector.y = 1.0f;
    upVector.z = 0.0f;
    setUpProspective();
    lookAt();
    spaceShip = new SpaceEnterprise("enterprise.txt");
    spaceShip->setEyesPosition(this->eyePosition);
    spaceShip->setEyeOffset(500,eyePosition.y/1.5,OuterSolarSystemDepth/2+800);
    setDrawStars(false);
    generateStars();


}

void SolarSystem::setUpProspective()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WindowWidth, WindowHeight);
    glFrustum(-InnerSolarSystemWidth / 2, InnerSolarSystemWidth / 2, -InnerSolarSystemHeight / 2, InnerSolarSystemHeight / 2,
    OuterSolarSystemDepth/2,  OuterSolarSystemDepth*1.7);
    glMatrixMode(GL_MODELVIEW);
}




void SolarSystem::addPlanets()
{
    float moonOrbit;
    float sizeEarth = 300;
    ///mercury
    Planet* mecury = new Planet(sizeEarth* 0.47,sun->getObjRadius()+sun->getLengthCorona() + 850, 0.0,0.0,0.0,-0.2);
    vector<GLfloat> planetcolour;
    planetcolour.x = 0.654;
    planetcolour.y = 0.650;
    planetcolour.z  =0.674;
    mecury->setColour(planetcolour);
    planets.push_back(mecury);
    ///Venus
    //vector<GLfloat> planetcolour;
    Planet* venus = new Planet(sizeEarth* 0.95,mecury->getOrbitalRadius()+ mecury->getObjRadius() + 250, 0.0,0.0,0.0,0.1);
    planetcolour.x = 0.592;
    planetcolour.y = 0.470;
    planetcolour.z  = 0.494;
    venus->setColour(planetcolour);
    planets.push_back(venus);
    //Earth
    Planet* earth = new Planet(sizeEarth* 1,venus->getOrbitalRadius()+ venus->getObjRadius() + 480, 0.0,0.0,0.0,0.190);
    planetcolour.x = 0.031;
    planetcolour.y = 0.866;
    planetcolour.z  =0.066;
    earth->setColour(planetcolour);
    planets.push_back(earth);
    moonOrbit = earth->addMoons();
    ///Mars
    //vector<GLfloat> planetcolour;
    Planet* mars = new Planet(sizeEarth* 0.53,earth->getOrbitalRadius()+ earth->getObjRadius()+moonOrbit + 900, 0.0,0.0,0.0,0.175);
    planetcolour.x = 1;
    planetcolour.y = 0.141;
    planetcolour.z  =0.580;
    mars->setColour(planetcolour);
    planets.push_back(mars);
    ///Jupiter
    Planet* jupiter = new Planet(sizeEarth* 5,mars->getOrbitalRadius()+ mars->getObjRadius() + sizeEarth* 5, 0.0,0.0,0.0,0.234);
    planetcolour.x = 0.882;
    planetcolour.y = 0.890;
    planetcolour.z  =0.847;
    jupiter->setColour(planetcolour);
    planets.push_back(jupiter);
    float jupiterMoonOrbit =jupiter->addMoons();
    jupiter->setOrbitalRadius(jupiter->getOrbitalRadius()+jupiterMoonOrbit);
    ///Saturn
    Planet* saturn = new Planet(sizeEarth*3,jupiter->getOrbitalRadius()+ jupiter->getObjRadius()+jupiterMoonOrbit + sizeEarth* 3, 0.0,0.0,0.0,-0.200);
    planetcolour.x = 0.901;
    planetcolour.y = 0.290;
    planetcolour.z  =0;
    saturn->setColour(planetcolour);
    planets.push_back(saturn);
    ///Uranus
    Planet* uranus = new Planet(sizeEarth*2,saturn->getOrbitalRadius()+ saturn->getObjRadius() + sizeEarth* 2.5, 0.0,0.0,0.0,-0.300);
    planetcolour.x = 0;
    planetcolour.y = 0.525;
    planetcolour.z  = 0.901;
    uranus->setColour(planetcolour);
    planets.push_back(uranus);
    ///Neptune
    Planet* neptune = new Planet(sizeEarth*2,uranus->getOrbitalRadius()+ uranus->getObjRadius() + sizeEarth* 5, 0.0,0.0,0.0,+0.100);
    planetcolour.x = 0.003;
    planetcolour.y = 0.058;
    planetcolour.z  =0.098;
    neptune->setColour(planetcolour);
    planets.push_back(neptune);
    ///Pluto
    Planet* pluto = new Planet(sizeEarth*0.40,neptune->getOrbitalRadius()+ neptune->getObjRadius() + sizeEarth* 7, 0.0,0.0,0.0,0.070);
    planetcolour.x = 0.976;
    planetcolour.y =  0.486;
    planetcolour.z  =0.325;
    pluto->setColour(planetcolour);
    planets.push_back(pluto);

}

bool SolarSystem::nexFrame()
{
    if (getCameraUp() == true || getCameraDown() == true ||
        getCameraLeft() == true  || getCameraRight() == true||
        getCameraForwards() == true || getCameraBackWards() == true){
        this->lookAt();
        setEnterprisePos();

    }
    if (getDrawStars() == true){
        for(unsigned int i  = 0 ; i < stars.size(); i++ ){
            stars[i]->nextFrame();
        }
    }
    sun->nextFrame();
    spaceShip->nextFrame();
    for (unsigned int planeti = 0 ; planeti < planets.size();  planeti++){
        planets[planeti]->nextFrame();
    }

    return true;

}

void SolarSystem::lookAt()
{     
    setUpProspective();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (getCameraUp() == true){
        eyePosition.y += 10.0;
    }
    if (getCameraDown() == true){
        eyePosition.y -= 10.0;
    }
    if (getCameraLeft() == true){
        eyePosition.x -= 20.0;
    }
    if(getCameraRight() == true){
        eyePosition.x+= 20.0;
    }
    if (getCameraForwards() == true){
        eyePosition.z -= 20.0;
    }
    if (getCameraBackWards() == true){
        eyePosition.z += 20.0;
    }
    gluLookAt(eyePosition.x,
              eyePosition.y,
              eyePosition.z,
              eyePosition.x+LookAtVector.x,
              eyePosition.y+LookAtVector.y,
              eyePosition.z+LookAtVector.z,
              upVector.x,
              upVector.y,
              upVector.z);
}

void SolarSystem::setUpBoxSolarSystem()
{
   GLfloat solarsytemWidthDepth =planets[planets.size() -1 ]->getOrbitalRadius() + planets[planets.size() -1 ]->getObjRadius() +100;
   InnerSolarSystemDepth =solarsytemWidthDepth;
   InnerSolarSystemWidth =solarsytemWidthDepth;
   InnerSolarSystemHeight = InnerSolarSystemWidth*(WindowHeight/(float)WindowWidth);
   OuterSolarSystemDepth =InnerSolarSystemDepth*2;
   OuterSolarSystemHeight =InnerSolarSystemHeight*2;
   OuterSolarSystemWidth = InnerSolarSystemWidth*2;


}

void SolarSystem::generateStars()
{
    unsigned int numStar =  250;
    float starSize;
    float angleStep;
    float shrinkStep;
    vector<GLfloat> pointVector;
    for (unsigned int i  = 0; i < numStar ; i++){
         starSize = rand() % 5;
         angleStep = rand()  % 30;
         shrinkStep = (rand() / (float) RAND_MAX) *30 +1;
         pointVector.x = generateNumber(-OuterSolarSystemWidth/ 2,OuterSolarSystemWidth/2 );

         pointVector.y = generateNumber(-OuterSolarSystemHeight/ 2,OuterSolarSystemHeight/2 );

         pointVector.z= generateNumber(-OuterSolarSystemDepth/2, OuterSolarSystemDepth/2);

         stars.push_back(new StarDrawer(90.0,shrinkStep,angleStep,pointVector));
    }
}

bool SolarSystem::getDrawStars() const
{
    return drawStars;
}

void SolarSystem::setDrawStars(bool value)
{
    drawStars = value;
}

bool SolarSystem::setEnterprisePos()
{
    return this->spaceShip->setEyesPosition(this->eyePosition);

}

SolarSystem::SolarSystem(int argc, char **argv, const unsigned int &WindowWidth, const unsigned int &WindowHeight)
{

    if (thisInstance == nullptr){ // if no inner class is created
        setup(argc,argv, WindowWidth,WindowHeight);
        thisInstance = new SolarSystem(WindowWidth,WindowHeight);
    }
    else {
        delete thisInstance; // if a new class is created when already created this is clas is crated
        setup(argc,argv, WindowWidth,WindowHeight);
        thisInstance = new SolarSystem(WindowWidth,WindowHeight);
    }
}

void SolarSystem::KeyboardFunc(const unsigned char & key,
                                        const int& x, const int& y)
{
    if (key == 'c'){
        sun->setCoronoOn(!sun->getCoronoOn());
    }
    else if (key == 'r'){
        setDrawRings(!getDrawRings());
    }
    else if (key == 'k'){
        spaceShip->setShieldOn(!spaceShip->getShieldOn());

    }
    else if (key == 's'){
        this->setDrawStars(!getDrawStars());
        std::cout << "Stars: "<< getDrawStars() << std::endl;
    }


}

void SolarSystem::wrapperKeyboardFunc(unsigned char key, const int x, const int y)
{
    thisInstance->KeyboardFunc(key,x,y);
}


void SolarSystem::WarpDraw()
{
    thisInstance->draw();
}

void SolarSystem::draw()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    spaceShip->draw();
    this->drawOrbitRings();
    for (unsigned int planeti = 0 ; planeti < planets.size();  planeti++){
        planets[planeti]->draw();
    }
    sun->draw();
    if (getDrawStars() == true){
        for(unsigned int i  = 0 ; i < stars.size(); i++ ){
            stars[i]->draw();
        }
    }
    glutSwapBuffers();

}

void SolarSystem::setup(int argc, char **argv, const int &width, const int &height)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4,3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
//  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Final Project:Solar System");
    //Init glew
    glewExperimental = GL_TRUE;
    glewInit();
    glutDisplayFunc(SolarSystem::WarpDraw);
    glutKeyboardFunc(SolarSystem::wrapperKeyboardFunc);
    glutReshapeFunc(SolarSystem::WrapResize);
    glutSpecialFunc(SolarSystem::WrapperspecialFunc);
    glutSpecialUpFunc(SolarSystem::WrapperFuncUp);
    glutTimerFunc(5, WrapperAnimate, 1);
    glEnable(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable( GL_POLYGON_SMOOTH ) ;
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST ) ;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glClearColor(0.0, 0.0, 0.0, 0.0);



}

void SolarSystem::WrapResize(int width, int height)
{
    thisInstance ->resize(width,height);
}

void SolarSystem::resize(const int &width, const int &height)
{
    this->WindowWidth = width;
    this->WindowHeight = height;
    setUpBoxSolarSystem();
    setUpProspective();
    this->sun->nextFrame();
    for (unsigned int planeti = 0 ; planeti < planets.size();  planeti++){
        this->planets[planeti]->nextFrame();
    }
    glutPostRedisplay();

}

void SolarSystem::executeProgram()
{
    glutMainLoop();
}

void SolarSystem::WarapperIdleFunc()
{

}

void SolarSystem::WrapperAnimate(int i)
{
    thisInstance->animate(i);
}

void SolarSystem::WrapperspecialFunc(int key, int x, int y)
{
    thisInstance->specialFunc(key,x,y);
}

void SolarSystem::WrapperFuncUp(int key, int x, int y)
{
    thisInstance->specialFuncUp(key,x,y);
}

void SolarSystem::specialFunc(const int &key, const int &x, const int &y)
{
     if (key == GLUT_KEY_UP)
        this->setCameraUp(true);
    else if (key == GLUT_KEY_DOWN)
        this->setCameraDown(true);
    else if(key == GLUT_KEY_LEFT)
        this->setCameraLeft(true);
    else if (key == GLUT_KEY_RIGHT)
        this->setCameraRight(true);
    else if (key == GLUT_KEY_PAGE_UP)
         this->setCameraForwards(true);
    else if (key == GLUT_KEY_PAGE_DOWN)
         this->setCameraBackWards(true);


}

void SolarSystem::specialFuncUp(const int &key, const int &x, const int &y)
{
    if (key == GLUT_KEY_UP)
       this->setCameraUp(false);
    if (key == GLUT_KEY_DOWN)
        this->setCameraDown(false);
    if(key == GLUT_KEY_LEFT)
        this->setCameraLeft(false);
    if(key == GLUT_KEY_RIGHT)
        this->setCameraRight(false);
    else if (key == GLUT_KEY_PAGE_UP)
         this->setCameraForwards(false);
    else if (key == GLUT_KEY_PAGE_DOWN)
         this->setCameraBackWards(false);
}

bool SolarSystem::getCameraDown() const
{
    return cameraDown;
}

void SolarSystem::setCameraDown(bool value)
{
    cameraDown = value;
}

bool SolarSystem::getCameraUp() const
{
    return cameraUp;
}

void SolarSystem::setCameraUp(bool value)
{
    cameraUp = value;
}

bool SolarSystem::getCameraRight() const
{
    return cameraRight;
}

void SolarSystem::setCameraRight(bool value)
{
    cameraRight = value;
}

bool SolarSystem::getCameraLeft() const
{
    return cameraLeft;
}

void SolarSystem::setCameraLeft(bool value)
{
    cameraLeft = value;
}

bool SolarSystem::getCameraBackWards() const
{
    return cameraBackWards;
}

void SolarSystem::setCameraBackWards(bool value)
{
    cameraBackWards = value;
}

bool SolarSystem::getCameraForwards() const
{
    return cameraForwards;
}

void SolarSystem::setCameraForwards(bool value)
{
    cameraForwards = value;
}

void SolarSystem::animate(const unsigned &i)
{
    //if there is animation to play
    this->nexFrame();
    glutTimerFunc(26,WrapperAnimate,i);
        glutPostRedisplay();//render the next frame of the animation

}

bool SolarSystem::getDrawRings() const
{
    return drawRings;
}

void SolarSystem::setDrawRings(bool value)
{
    drawRings = value;
    for (unsigned int i = 0 ; i < planets.size(); i++){
        planets[i]->setDrawMoonOrbital(value);
    }
}

void SolarSystem::drawOrbitRings()
{
    glLineWidth(1);
    if(getDrawRings() == true){
        vector<GLfloat> ringCircle;
        for(unsigned int planeti = 0; planeti < planets.size() ; planeti++){
            glColor3f(1.0,1.0,1.0);
            glBegin(GL_LINE_LOOP);
            for (unsigned int angle = 0 ; angle <=360 ; angle+=3 ){
                ringCircle.x = planets[planeti]->getOrbitalRadius() * std::cos(degreeToRads*angle);
                ringCircle.z = planets[planeti]->getOrbitalRadius() * std::sin(degreeToRads*angle);
                ringCircle.y=  0.0;
                glVertex4f(ringCircle.x,ringCircle.y,ringCircle.z,1.0);
            }
            glEnd();
        }

    }

}

SolarSystem::~SolarSystem()
{
    if (sun != nullptr){ // if the class decontructing is the main class
          //delete menu;
          //delete shapeAnim;
          //menu = NULL;//delete the menue
          //shapeAnim = NULL; //delte the star
    }
    else {
        delete thisInstance;
        thisInstance = nullptr;

    }


}
 SolarSystem* SolarSystem::thisInstance =nullptr;
