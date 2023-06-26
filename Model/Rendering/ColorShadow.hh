#pragma once

#include "ShadingStrategy.hh"

class ColorShadow : public ShadingStrategy
{
public:
    ColorShadow(){};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight ,std::vector<shared_ptr<Light>> lights) override;
    ~ColorShadow() {};
};

