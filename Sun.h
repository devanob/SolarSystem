#ifndef SUN_H
#define SUN_H
#include "Orbital.h"
#include "Planet.h"
#include <vector>
///
/// \brief The Sun class
///Sun Class represents the sun in the solar system also control other planets
class Sun : public Orbital
{
public:
    ///
    /// \brief Sun- conturctor for this sun class
    /// \param radius
    /// \param colour
    ///
    Sun(const float& radius, const vector<GLfloat>& colour );
    void setCoronoOn(const bool& value);
    void setOrbitalCircle(const bool& value);
    void draw();
    bool nextFrame();
    void generateConorona();

    void setTipColour(const vector<GLfloat>& value);

    bool getCoronoOn() const;

    float getLengthCorona() const;
    void setLengthCorona(float value);

private:
    std::vector<Planet> solarPLanets; //plants in the solar system
    bool coronoOn; //draw Sun conoron
    bool OrbitalCircle; //draw oribital rings about Sun
    std::vector<vector<GLfloat>> CoronaVector; // the conorno for each vector
    std::vector<vector<GLfloat>> NormalizeCoronaVector;
    GLfloat Scalefactor;// scale factor
    GLfloat currentStep; //current step
    vector<GLfloat> tipColour; // tip colour
    std::vector<GLfloat> Scalefactors;
    float lengthCorona;

};

#endif // SUN_H
