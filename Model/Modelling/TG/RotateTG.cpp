#include "RotateTG.hh"

RotateTG::RotateTG(float ang,glm::vec3 rot): angle(ang), rotation(rot)
{
    matTG = glm::rotate(glm::mat4(1.0f),angle,rotation);
}

RotateTG::~RotateTG(){

}
