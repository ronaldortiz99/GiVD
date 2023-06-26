#pragma once

#include "Material.hh"

class Metal : public Material
{

public:
    Metal() {};
    Metal(const vec3& color);
    Metal(const vec3& a, const vec3& d, const vec3& s, const float k);
    Metal(const vec3& a, const vec3& d, const vec3& s, const float k, const float o, const vec3& t, const float nu);
    virtual ~Metal();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const;
    virtual vec3 getDiffuse(vec2 uv) const;

};
