#include "PhongShading.hh"

vec3 PhongShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight ,vector<shared_ptr<Light>> lights) {
    vec3 color = vec3(0);
    vec3 L, V;
    vec3 R(0,0,0);

    //Vector desde el punto hasta la cámara
    V = normalize(lookFrom - info.p);
    vec3 gloablComp = ambientLight * info.mat_ptr->Ka;
    for (unsigned int i = 0; i< lights.size(); i++) {

        L = normalize(lights[i]->vectorL(info.p));

        //Vector R = 2*N * (N+L) - L
        R = (info.normal+ info.normal)*(info.normal*L)- L;
        float att = lights[i]->attenuation(info.p);
        color +=  info.mat_ptr->Ka * lights[i]->getIa() +  att * (info.mat_ptr->getDiffuse(info.uv)*lights[i]->getId()* dot(normalize(info.normal),L) + info.mat_ptr->Ks*lights[i]->getIs()*pow(dot(V,R), info.mat_ptr->shininess));
    }

    return gloablComp + color;
}
