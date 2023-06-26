#include "NormalShading.hh"

vec3 NormalShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight ,std::vector<shared_ptr<Light>> lights) {
    return (info.normal+vec3(1))/2.0f;
}
