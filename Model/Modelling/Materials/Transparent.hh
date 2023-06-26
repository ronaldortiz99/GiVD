#pragma once

#include "Material.hh"

class Transparent : public Material
{

public:
    Transparent() {};
    Transparent(const vec3& color);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o, const vec3& t, const float nu);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o, const vec3& t, const float nu, const float dmax);
    virtual ~Transparent();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const;
    virtual vec3 getDiffuse(vec2 uv) const;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    float dmax;
};
