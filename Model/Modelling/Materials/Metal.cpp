#include "Metal.hh"

Metal::Metal(const vec3& color): Material()
{
    Ks = color;
}

Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k, const float o, const vec3& t, const float nu):
    Material(a, d, s, k, o, t, nu) {
}
Metal::~Metal()
{
}

bool Metal::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    float fuzz = 0;
    vec3 reflection = glm::reflect(r_in.getDirection(), rec.normal) ;
    r_out =  Ray(rec.p, reflection  + fuzz* Hitable::RandomInSphere());
    color = Ks;
    return true;
}

vec3 Metal::getDiffuse(vec2 uv) const {
    return Kd;

}
