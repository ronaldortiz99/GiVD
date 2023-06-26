#include "FittedPlane.hh"
FittedPlane::FittedPlane(){
    pmin = vec2(-1,-1);
    pmax = vec2(1,1);
    normal = vec3(0,1,0);
    point = vec3(0,0.5,0);
}

FittedPlane::FittedPlane(float data): Object(data){
    pmin = vec2(-1,-1);
    pmax = vec2(1,1);
    normal = vec3(0,1,0);
    point = vec3(0,0.5,0);
}

FittedPlane::FittedPlane(vec2 max, vec2 min, vec3 point, vec3 normal, float data): Object(data){
    pmin = min;
    pmax = max;
    FittedPlane::point = point;
    FittedPlane::normal = normal;
}
bool FittedPlane::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    if(abs(dot(raig.getDirection(), normal))<DBL_EPSILON){
        return false;
    }
    float d = -normal[0]*point[0] - normal[1]*point[1] - normal[2]*point[2];
    vec3 rp = raig.getOrigin();
    vec3 vp = raig.getDirection();
    float temp =  -normal[0]*rp[0] - normal[1]*rp[1] - normal[2]*rp[2] - d;

    temp/= normal[0]*vp[0] + normal[1]*vp[1] + normal[2]*vp[2];

    if (temp > tmax || temp < tmin) {
            return false;
    }

    vec3 point = raig.pointAtParameter(temp);
    if (point.x > pmax.x || point.x < pmin.x || point.z > pmax.y ||    point.z < pmin.y){
        return false;
    }

    info.t = temp;
    info.p = raig.pointAtParameter(info.t);
    info.normal = normal;
    info.mat_ptr = material.get();
    float u = (info.p.x - pmin.x)/(pmax.x-pmin.x);
    float v = (pmax.y - info.p.z)/(pmax.y-pmin.y);
    info.uv = vec2(u,v);

    return true;
}

void FittedPlane::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {

        // Nomes movem el punt de pas
        vec4 newp(this->point, 1.0);
        newp = t->getTG() * newp;
        this->point.x = newp.x;
        this->point.y = newp.y;
        this->point.z = newp.z;
    }
}

void FittedPlane::read (const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("normal") && json["normal"].isArray()) {
        QJsonArray auxVec = json["normal"].toArray();
        normal[0] = auxVec[0].toDouble();
        normal[1] = auxVec[1].toDouble();
        normal[2] = auxVec[2].toDouble();
    }

    if (json.contains("point") && json["point"].isArray()) {
        QJsonArray auxVec = json["point"].toArray();
        point[0] = auxVec[0].toDouble();
        point[1] = auxVec[1].toDouble();
        point[2] = auxVec[2].toDouble();
    }

    if (json.contains("pmin") && json["pmin"].isArray()) {
        QJsonArray auxVec = json["pmin"].toArray();
        pmin[0] = auxVec[0].toDouble();
        pmin[1] = auxVec[1].toDouble();
    }

    if (json.contains("pmax") && json["pmax"].isArray()) {
        QJsonArray auxVec = json["pmax"].toArray();
        pmax[0] = auxVec[0].toDouble();
        pmax[1] = auxVec[1].toDouble();
    }
}


//! [1]
void FittedPlane::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(normal[0]);auxArray.append(normal[1]);auxArray.append(normal[2]);
    json["normal"] = auxArray;

    QJsonArray auxArray2;
    auxArray2.append(point[0]);auxArray2.append(point[1]);auxArray2.append(point[2]);
    json["point"] = auxArray2;

    QJsonArray auxArray3;
    auxArray3.append(pmin[0]);auxArray3.append(pmin[1]);
    json["pmin"] = auxArray3;

    QJsonArray auxArray4;
    auxArray4.append(pmax[0]);auxArray4.append(pmax[1]);
    json["pmax"] = auxArray4;
}
//! [1]

void FittedPlane::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "pmin:\t" << pmin[0] << ", "<< pmin[1] << "\n";
    QTextStream(stdout) << indent << "pmax:\t" << pmax[0] << ", "<< pmax[1] << "\n";
    QTextStream(stdout) << indent << "point:\t" << point[0] << ", "<< point[1] << ", "<< point[2] << "\n";
    QTextStream(stdout) << indent << "normal:\t" << normal[0] << ", "<< normal[1] << ", "<< normal[2] << "\n";

}
