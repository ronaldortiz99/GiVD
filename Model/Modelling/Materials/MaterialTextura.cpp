#include "MaterialTextura.hh"

MaterialTextura::MaterialTextura()
{

}
MaterialTextura::MaterialTextura(const vec3& color): Material()
{
    Kd = color;
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o, const vec3& t, const float nu):
    Material(a, d, s, k, o, t, nu) {
}
MaterialTextura::~MaterialTextura()
{
}

bool MaterialTextura::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    return false;
}

vec3 MaterialTextura::getDiffuse(vec2 uv) const {
    return texture->getColorPixel(uv);
}

void MaterialTextura::setTexture(QString textureFile){
    texture = make_shared<Texture>(textureFile);
}

void MaterialTextura::read(const QJsonObject &json) {
    if (json.contains("ka") && json["ka"].isArray()) {
        QJsonArray auxVec = json["ka"].toArray();
        Ka[0] = auxVec[0].toDouble();
        Ka[1] = auxVec[1].toDouble();
        Ka[2] = auxVec[2].toDouble();
    }
    if (json.contains("kd") && json["kd"].isArray()) {
        QJsonArray auxVec = json["kd"].toArray();
        Kd[0] = auxVec[0].toDouble();
        Kd[1] = auxVec[1].toDouble();
        Kd[2] = auxVec[2].toDouble();
    }
    if (json.contains("ks") && json["ks"].isArray()) {
        QJsonArray auxVec = json["ks"].toArray();
        Ks[0] = auxVec[0].toDouble();
        Ks[1] = auxVec[1].toDouble();
        Ks[2] = auxVec[2].toDouble();
    }
    if (json.contains("shininess") && json["shininess"].isDouble())
        shininess = json["shininess"].toDouble();

    if (json.contains("textureFile") && json["textureFile"].isString()){
        QString textureFile = json["textureFile"].toString();
        texture = make_shared<Texture>(textureFile);
    }
}
