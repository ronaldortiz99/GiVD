#include "Model/Rendering/ShadingStrategy.hh"

float ShadingStrategy::computeShadow(shared_ptr<Light> light, vec3 point, shared_ptr<Scene> scene){
    HitInfo info;

    Ray raig(point, light->vectorL(point), 0.01f, light->distanceToLight(point));
    float shadow_fx = 1.0;
    if(scene->hit(raig, 0.0001, light->distanceToLight(point), info)){

        //Mientras interseccione con un Material Transparent se queda en el bucle
        while(MaterialFactory::getInstance().getIndexType(info.mat_ptr) == MaterialFactory::TRANSPARENT){
            /*//Paso Material a Transparente para obtener dmax
            Transparent * t = static_cast<Transparent*>(info.mat_ptr);
            //Como no tengo  dmax uso este valor de prueba
            float fah =  1/t->dmax;
            //Punto inicial de intersección con el objeto transparente
            vec3 iniP =  info.p;
            //Doy por hecho que la luz estará fuera del objeto transparente y que no hay ningun objeto  dentro del mismo
            scene->hit(raig, info.t + 0.0001, light->distanceToLight(info.p), info);
            //Calculo la distancia entre punto inicial y final de intersección con el objeto
            float dist = distance(iniP,info.p);
            //Compruebo que shadow factor no sea igual a 0
            if(shadow_fx < FLT_EPSILON)
                return 0.0;
            //Aumento shadow factor
            shadow_fx -= fah * dist;
            // Si no hay ninguna otra  intersección devuelvo shadow factor
            if(!scene->hit(raig, info.t + 0.0001, light->distanceToLight(info.p), info))
                return shadow_fx;*/
            shadow_fx =  1 - getShadowFxTransp(light,raig,scene,info,0);
            if(shadow_fx < FLT_EPSILON)
                return 0.0;
            //Compruebo si se intersecciona con otro objeto
            if(!scene->hit(raig, info.t + 0.0001, light->distanceToLight(info.p), info))
                return shadow_fx;
        }

        return 0.0f;
    }

    return 1.0f;
}
//Metodo para calcular de forma recursiva el factor de atenuación de las sombras para un objeto transparennte, controlando  si tiene objetos internos
float ShadingStrategy::getShadowFxTransp(shared_ptr<Light> light,Ray &raig, shared_ptr<Scene> scene, HitInfo& info,  float shadow_fx){
    HitInfo infoTmp = info;
    //Devuelve  Shadow Factor = 1 si el rayo de entrada interseca un objeto no transpare o este factor es menor que epsilon.
    if (MaterialFactory::getInstance().getIndexType(info.mat_ptr) != MaterialFactory::TRANSPARENT || abs(1-shadow_fx) < FLT_EPSILON) {
        return 1;
    } else{
        Transparent * t = static_cast<Transparent*>(info.mat_ptr);
        if(scene->hit(raig, info.t + 0.0001, light->distanceToLight(info.p), info)){
            //Si el rayo atraviesa el objeto con el que interseca
            if (info.mat_ptr  == infoTmp.mat_ptr){
                float d = distance(infoTmp.p,info.p);
                return (1/t->dmax) * d;
            }
            else{
                //Calculo la distancia entre la intersección  del rayo con el objeto y el objeto interior
                float d = distance(infoTmp.p,info.p);

                //Obtengo el Shadow Factor del objeto interior
                shadow_fx += getShadowFxTransp(light,raig,scene,info,shadow_fx);

                vec3 p = info.p;
                //Si hay otra intersección
                if(scene->hit(raig, info.t + 0.0001, light->distanceToLight(info.p), info)){
                    //Añado la distancia entre la intersección  del rayo con el objeto interior y el siguiente objeto interior o final del objeto
                    d += distance(p,info.p);
                    //Mientras el rayo no atraviese el objeto
                    while (info.mat_ptr  != infoTmp.mat_ptr){
                        //Obtengo el Shadow Factor del objeto interior
                        shadow_fx += getShadowFxTransp(light,raig,scene,info,shadow_fx);
                        if (abs(1-shadow_fx) < FLT_EPSILON) {
                            return 1;
                        }
                        HitInfo newInfo = info;
                        if(!scene->hit(raig, newInfo.t + 0.0001, light->distanceToLight(newInfo.p), newInfo)){
                            return shadow_fx  += (1/t->dmax) * d;
                        }
                        //Añado la distancia entre la intersección  del rayo con el objeto interior y el siguiente objeto interior o final del objeto//Añado la distancia entre la intersección  del rayo con el objeto interior y el siguiente objeto interior o final del objeto
                        d += distance(newInfo.p,info.p);
                        newInfo = info;
                    }
                    shadow_fx  += (1/t->dmax) * d;
                }
            }
        }
    }
    return shadow_fx;
}
