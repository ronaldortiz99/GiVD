#ifndef ROTATETG_HH
#define ROTATETG_HH

#include "TG.hh"

class RotateTG : public TG
{
public:
    float angle;
    glm::vec3 rotation;
    RotateTG(float ang,glm::vec3 rot);
    virtual ~RotateTG();
};

#endif // ROTATETG_HH
