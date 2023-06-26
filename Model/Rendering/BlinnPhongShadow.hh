#pragma once

#include "Model/Modelling/Scene.hh"
#include "Model/Rendering/ShadingStrategy.hh"
#include "Model/Modelling/Lights/Light.hh"


class BlinnPhongShadow: public ShadingStrategy
{
public:
    BlinnPhongShadow() {};
    vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight, vector<shared_ptr<Light>> lights) override;
    ~BlinnPhongShadow(){};
};
