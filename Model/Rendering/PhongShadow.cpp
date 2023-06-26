#include "PhongShadow.hh"
#include "ShadingStrategy.hh"

vec3 PhongShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight ,vector<shared_ptr<Light>> lights) {
    vec3 color(0,0,0);
    vec3 L(0,0,0), V(0,0,0);
    vec3 R(0,0,0);

    //Vector desde el punto hasta la cámara
    V = normalize(lookFrom - info.p);
    vec3 gloablComp = ambientLight * info.mat_ptr->Ka;
    for (unsigned int i = 0; i< lights.size(); i++) {

        L = normalize(lights[i]->vectorL(info.p));

        //Vector R = 2*N * (N+L) - L
        R = (info.normal+ info.normal)*(info.normal*L)- L;
        float att = lights[i]->attenuation(info.p);
        color +=  info.mat_ptr->Ka * lights[i]->getIa() + att * computeShadow(lights[i], info.p, scene) * (info.mat_ptr->getDiffuse(info.uv)*lights[i]->getId()*
                dot(L,normalize(info.normal)) + info.mat_ptr->Ks*lights[i]->getIs()*pow(dot(V,R), info.mat_ptr->shininess));
    }

    return color+gloablComp;

}
