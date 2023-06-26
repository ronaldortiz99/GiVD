#include "ColorShading.hh"


vec3 ColorShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight, std::vector<shared_ptr<Light>> lights){
    return info.mat_ptr->getDiffuse(info.uv);
}

