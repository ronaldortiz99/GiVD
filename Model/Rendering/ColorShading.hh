#pragma once

#include "ShadingStrategy.hh"

class ColorShading: public ShadingStrategy
{
public:
    ColorShading() {};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight ,std::vector<shared_ptr<Light>> lights) override;
    ~ColorShading(){};
};

