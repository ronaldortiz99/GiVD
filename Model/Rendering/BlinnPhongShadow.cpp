#include "BlinnPhongShadow.hh"
#include "ShadingStrategy.hh"
#include "Controller.hh"


vec3 BlinnPhongShadow::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom, vec3 ambientLight, vector<shared_ptr<Light>> lights){
    //L - Vector desde el foco de luz al punto a iluminar
    //V - Vector desde la cámara al punto a iluminar
    //H - Vector resultado de la operación entre L y V
    vec3 L(0,0,0), V(0,0,0), H(0,0,0);
    V = normalize(lookFrom - info.p);

    //Calculo de la componente global (Iglobal*Ka)
    vec3 gloablComp = ambientLight * info.mat_ptr->Ka;
    //Atenuación de la luz (1/(a+bd+cd²))
    float att;
    float cosLN, cosNH;
    //Calculo del sumatorio (att + Id*Kd*cos(L,N)+Ks*Is*cos(N,H)+Ia*Ka)
    vec3 sumatorio(0,0,0);
    for(const shared_ptr<Light>&light: lights){
        //Atenuación hasta p
        att = light->attenuation(info.p);
        //Calculo de la L
        L = normalize(light->vectorL(info.p));
        //Calculo de la H = (L+V)/|L+V|
        H=normalize(L+V);
        //Producto entre los vectores y comprovacion de que no sean negativos (si son negativos entonces estamos fuera del alcance de la luz)
        cosLN = std::max(dot(L,normalize(info.normal)), 0.0f);
        cosNH = std::max(dot(normalize(info.normal),H),0.0f);
        sumatorio += light->getIa()*info.mat_ptr->Ka;
        //sumatorio += computeShadow(light, info.p, scene) * att * (light->getId()*info.mat_ptr->Kd * cosLN + light->getIs()*info.mat_ptr->Ks*pow(cosNH,info.mat_ptr->shininess)) + light->getIa()*info.mat_ptr->Ka;
        sumatorio += att * computeShadow(light, info.p, scene) * (light->getId()*info.mat_ptr->getDiffuse(info.uv) * cosLN + light->getIs()*info.mat_ptr->Ks*pow(cosNH,info.mat_ptr->shininess));
    }
    return gloablComp + sumatorio;
}

