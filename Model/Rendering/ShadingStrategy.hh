#pragma once

#include "Model/Modelling/Scene.hh"
#include "Model/Modelling/Lights/Light.hh"
#include "Model/Modelling/Lights/LightFactory.hh"
#include "Model/Modelling/Materials/MaterialFactory.hh"


class ShadingStrategy {
 public:
    // TODO: Fase 2: Canviar el mètode per passar les llums per calcular el shading
    virtual vec3 shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight, std::vector<shared_ptr<Light>> lights){
        return vec3(1.0, 0.0, 0.0);
    };

    // FASE 2: Calcula si el punt "point" és a l'ombra segons si el flag està activat o no
    float computeShadow(shared_ptr<Light> light, vec3 point, shared_ptr<Scene> scene);
    float getShadowFxTransp(shared_ptr<Light> light,Ray &raig, shared_ptr<Scene> scene, HitInfo& info,  float shadow_fx);

    virtual ~ShadingStrategy() {};
};
