#pragma once

#include "ShadingStrategy.hh"

class PhongShading : public ShadingStrategy
{
public:
    PhongShading(){};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight, vector<shared_ptr<Light>> lights) override;
    ~PhongShading() {};
};

