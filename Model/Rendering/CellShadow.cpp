#include "CellShadow.hh"
#include "ShadingStrategy.hh"

vec3 CellShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight, vector<shared_ptr<Light>> lights){
    vec3 I = vec3(0);
    vec3 N = info.normal;
    vec3 V = normalize(lookFrom-info.p);
    for (int i = 0; i < lights.size(); i++){
        vec3 color;
        vec3 L = lights[i]->vectorL(info.p);
        vec3 H = (L+V)/length(L+V);
        H = normalize(H);
        float rimDot = (1 - dot(V,N)) > 0.75 ? 1 : 0;
        vec3 colD = info.mat_ptr->Kd*lights[i]->getId();
        float intensity = dot(L,N);
        if (intensity > 0.95)
            color = vec3(1.0)*colD;
        else if (intensity > 0.5)
            color = vec3(0.6)*colD;
        else if (intensity > 0.25)
            color = vec3(0.3)*colD;
        else
            color = vec3(0.1);
        color += lights[i]->getIa()*info.mat_ptr->Ka +  computeShadow(lights[i], info.p, scene)  * vec3(1.0)*colD*info.mat_ptr->Ks*rimDot*dot(N,L);
        I += color;

    }
    return I;
}
