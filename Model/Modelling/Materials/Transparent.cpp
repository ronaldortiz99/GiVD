#include "Transparent.hh"

Transparent::Transparent(const vec3& color): Material()
{
    Ks = color;
    dmax = 10;
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
    dmax = 10;
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o, const vec3& t, const float nu):
    Material(a, d, s, k, o, t, nu) {
    this->dmax  = 10;
}

Transparent::Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o, const vec3& t, const float nu, const float dmax):
    Material(a, d, s, k, o, t, nu) {
    this->dmax  = dmax;
}
Transparent::~Transparent()
{
}

bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    vec3 normal;
    float ni_over_nt;

    //Rayo sigue el camino Material->Vacío
    if (dot(r_in.getDirection(), rec.normal) > 0){
        normal = -rec.normal;
        ni_over_nt = rec.mat_ptr->nut / 1.0;
    }

    //Rayo sigue el camino Vacío->Material
    else {
        normal = rec.normal;
        ni_over_nt = 1.0 / rec.mat_ptr->nut;
    }

    vec3 transmision = glm::refract(r_in.getDirection(),normal,ni_over_nt);

    //Angle superior a l'angle límit (reflexió total interna)
    if (length(transmision) < 0.001){
        transmision = glm::reflect(r_in.getDirection(), rec.normal);
        color = Ks;
    } else{
        color = Kt;
    }
    r_out = Ray(rec.p+0.01f*(transmision), transmision);
    return true;
}

vec3 Transparent::getDiffuse(vec2 uv) const {
    return Kd;

}

void Transparent::read (const QJsonObject &json)
{
    Material::read(json);

    if (json.contains("dmax") && json["dmax"].isDouble()) {
        dmax = json["dmax"].toDouble();
    }
}

//! [1]
void Transparent::write(QJsonObject &json) const
{
    Material::write(json);
    json["dmax"] = dmax;
}
//! [1]

void Transparent::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "Ka:\t" << Ka[0] << ", "<< Ka[1] << ", "<< Ka[2] << "\n";
    QTextStream(stdout) << indent << "Kd:\t" << Kd[0] << ", "<< Kd[1] << ", "<< Kd[2] << "\n";
    QTextStream(stdout) << indent << "Ks:\t" << Ks[0] << ", "<< Ks[1] << ", "<< Ks[2] << "\n";
    QTextStream(stdout) << indent << "Kt:\t" << Kt[0] << ", "<< Kt[1] << ", "<< Kt[2] << "\n";
    QTextStream(stdout) << indent << "shininess:\t" << shininess<< "\n";
    QTextStream(stdout) << indent << "opacity:\t" << opacity<< "\n";
    QTextStream(stdout) << indent << "nut:\t" << nut<< "\n";
    QTextStream(stdout) << indent << "dmax:\t" << dmax<< "\n";
}
