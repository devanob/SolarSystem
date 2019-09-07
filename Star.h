#ifndef STAR_H
#define STAR_H
#include "Orbital.h"
/**
 * @brief The Star class- represent the star handlier class DOP
 */
class Star : Orbital
{
public:
    /**
     * @brief Star - constructor
     * @param starPostion - position of the star
     * @param size - size of the stars
     */
    Star(const vector<GLfloat>& starPostion, const float& size);
    /**
     * @brief draw- handles draw the opengl object
     */
    void draw();
    /**
     * @brief nextFrame - returns of the next frame should be rendered
     * @return
     */
    bool nextFrame();
    /**
     * @brief size-size of the star
     */
    float size;
    /**
     * @brief stars
     */
    std::vector<vector<GLfloat>>  stars;

    void generatePoints();
};

#endif // STAR_H
