#include "DepthShadow.hh"

vec3 DepthShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight ,std::vector<shared_ptr<Light>> lights) {
    vec3 normpos = (info.p-scene->pmin)/(scene->pmax-scene->pmin);
    vec3 d = lookFrom - normpos;
    float dist = sqrt(d.x*d.x+d.y*d.y+d.z*d.z)/3;
    vec3 color = vec3(dist);
    vec3 shadow = info.mat_ptr->Ka;
    for (const shared_ptr<Light> &light: lights) {
        if(computeShadow(light, info.p, scene)){
            shadow = color;
        }
    };
    return shadow;
}
