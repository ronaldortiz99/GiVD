#include "NormalShadow.hh"
#include "ShadingStrategy.hh"

vec3 NormalShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight ,std::vector<shared_ptr<Light>> lights) {
    vec3 shadow = info.mat_ptr->Ka
            ;
    vec3 color = (info.normal+vec3(1))/2.f;
    for (const shared_ptr<Light> &light: lights) {
        if(computeShadow(light, info.p, scene)){
            shadow = color;
        }
    }
    return shadow;
}
