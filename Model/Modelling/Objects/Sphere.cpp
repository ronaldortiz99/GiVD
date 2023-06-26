#include "Sphere.hh"

Sphere::Sphere() {
    center=vec3(0.0,0.0,0.0);
    radius = 1.0;
}

Sphere::Sphere(vec3 cen, float r, float data) :Object(data) {
    center = cen;
    radius = r;
}

Sphere::Sphere(float data) :Object(data) {
    center = vec3(0,0,0);
    radius = 1.0f;
}

bool Sphere::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    vec3 oc = raig.getOrigin() - center;
    float a = dot(raig.getDirection(), raig.getDirection());
    float b = dot(oc, raig.getDirection());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < tmax && temp > tmin) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material.get();
            float u = 0.5 + (atan2(info.p.z, info.p.x) / (2 * M_PI));
            float v = 0.5 - (asin(info.p.y) / M_PI);
            info.uv = vec2(u,v);

            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tmax && temp > tmin) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material.get();
            float u = 0.5 + (atan2(info.p.z, info.p.x) / (2 * M_PI));
            float v = 0.5 - (asin(info.p.y) / M_PI);
            info.uv = vec2(u,v);

            return true;
        }
    }
    return false;
}


void Sphere::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<TranslateTG>(t)) {
        // Per ara només es fan les translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
    else if(dynamic_pointer_cast<ScaleTG>(t)) {
        vec3 point = vec3(center.x+radius,center.y+radius,center.z+radius);
        vec4 c(radius,0,0,1.0);
        c = t->getTG() * c;
        radius = c.x;
    }
    //TODO: Cal ampliar-lo per a acceptar Escalats

}

void Sphere::read (const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("radius") && json["radius"].isDouble()) {
        radius = json["radius"].toDouble();
    }
    if (json.contains("center") && json["center"].isArray()) {
        QJsonArray auxVec = json["center"].toArray();
        center[0] = auxVec[0].toDouble();
        center[1] = auxVec[1].toDouble();
        center[2] = auxVec[2].toDouble();
    }
}


//! [1]
void Sphere::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(center[0]);auxArray.append(center[1]);auxArray.append(center[2]);
    json["center"] = auxArray;

    json["radius"] = radius;
}
//! [1]

void Sphere::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "center:\t" << center[0] << ", "<< center[1] << ", "<< center[2] << "\n";
    QTextStream(stdout) << indent << "radius:\t" << radius<< "\n";
}

