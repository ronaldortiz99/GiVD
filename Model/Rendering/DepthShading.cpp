#include "DepthShading.hh"

vec3 DepthShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight ,std::vector<shared_ptr<Light>> lights) {

    vec3 normpos = (info.p-scene->pmin)/(scene->pmax-scene->pmin);
    vec3 d = lookFrom - normpos;
    float dist = sqrt(d.x*d.x+d.y*d.y+d.z*d.z)/3;
    return vec3(dist);
}
