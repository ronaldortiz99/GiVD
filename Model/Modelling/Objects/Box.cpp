#include "Box.hh"

Box::Box(){
    min = vec3(-0.1);
    max = vec3(0.1);
}

Box::Box(float data): Object(data){
    min = vec3(-0.1);
    max = vec3(0.1);
}

Box::Box(vec3 max, vec3 min, float data): Object(data){
    Box::max = max;
    Box::min = min;
}

bool Box::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    vec3 orig = raig.getOrigin();
    vec3 dir = raig.getDirection();

    float txmin = (min.x - orig.x)/dir.x;
    float tymin = (min.y - orig.y)/dir.y;
    float tzmin = (min.z - orig.z)/dir.z;

    float txmax = (max.x - orig.x)/dir.x;
    float tymax = (max.y - orig.y)/dir.y;
    float tzmax = (max.z - orig.z)/dir.z;

    float txenter = std::min(txmin,txmax);
    float txexit = std::max(txmin,txmax);

    float tyenter = std::min(tymin,tymax);
    float tyexit = std::max(tymin,tymax);

    float tzenter = std::min(tzmin,tzmax);
    float tzexit = std::max(tzmin,tzmax);

    float tenter = std::max({txenter,tyenter, tzenter});
    float texit = std::min({txexit, tyexit, tzexit});



    if (tenter < texit) {
        if (tenter > tmax || tenter < tmin){
            return false;
        }
        info.t = tenter;
        info.p = raig.pointAtParameter(info.t);

        info.normal = info.p;

        info.normal = vec3(0,0,0);

        if (info.p.x - max.x < FLT_EPSILON){
            info.normal.x = 1.0;
        }
        else if(min.x - info.p.x < FLT_EPSILON){
            info.normal.x = -1.0;
        }
        else if (info.p.y - max.y < FLT_EPSILON){
            info.normal.y = 1.0;
        }
        else if(min.y - info.p.y < FLT_EPSILON){
            info.normal.y = -1.0;
        }
        else if (info.p.z - max.z < FLT_EPSILON){
            info.normal.z = 1.0;
        }
        else if(min.z - info.p.z < FLT_EPSILON){
            info.normal.z = -1.0;
        }
        info.mat_ptr = material.get();
        // TODO Fase 3: Cal calcular les coordenades de textura

        return true;
    }
    return false;
}

void Box::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<TranslateTG>(t)) {
        // Per ara només es fan les translacions
        vec4 c(max, 1.0);
        c = t->getTG() * c;
        max.x = c.x; max.y = c.y; max.z = c.z;
        vec4 d(min, 1.0);
        d = t->getTG() * d;
        min.x = d.x; min.y = d.y; min.z = d.z;
    }
    else if (dynamic_pointer_cast<ScaleTG>(t)){
        vec4 c(max, 1.0);
        c = t->getTG() * c;
        //max.x = c.x;
        max.y = c.y;
        //max.z = c.z;
        vec4 d(min, 1.0);
        d = t->getTG() * d;
        //min.x = d.x;
        min.y = d.y;
        //min.z = d.z;
    }
    //TODO: Cal ampliar-lo per a acceptar Escalats

}

void Box::read (const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("max") && json["max"].isArray()) {
        QJsonArray auxVec = json["max"].toArray();
        max[0] = auxVec[0].toDouble();
        max[1] = auxVec[1].toDouble();
        max[2] = auxVec[2].toDouble();
    }

    if (json.contains("min") && json["min"].isArray()) {
        QJsonArray auxVec = json["min"].toArray();
        min[0] = auxVec[0].toDouble();
        min[1] = auxVec[1].toDouble();
        min[2] = auxVec[2].toDouble();
    }
}

void Box::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(max[0]);auxArray.append(max[1]);auxArray.append(max[2]);
    json["max"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(min[0]);auxArray2.append(min[1]);auxArray2.append(min[2]);
    json["min"] = auxArray2;

}


void Box::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "max:\t" << max[0] << ", "<< max[1] << ", "<< max[2] << "\n";
    QTextStream(stdout) << indent << "min:\t" << min[0] << ", "<< min[1] << ", "<< min[2] << "\n";
}
