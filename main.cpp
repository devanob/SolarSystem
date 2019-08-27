#include <iostream>
#include "SolarSystem.h"
using namespace std;

int main(int argc, char ** argv)
{
    SolarSystem solarSystem(argc, argv, 500, 500);//intialize the program
    solarSystem.executeProgram();//start up the endloop
}
