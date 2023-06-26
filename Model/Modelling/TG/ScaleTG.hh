#ifndef SCALETG_HH
#define SCALETG_HH

#include "TG.hh"

class ScaleTG : public TG
{
public:
    glm::vec3 scaled;
    ScaleTG(glm::vec3 scal);
    virtual ~ScaleTG();
};

#endif // SCALETG_HH
