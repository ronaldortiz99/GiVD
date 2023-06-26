#pragma once

#include "Material.hh"
#include "Texture.hh"

class MaterialTextura : public Material
{
public:
    shared_ptr<Texture> texture;

    MaterialTextura();
    MaterialTextura(const vec3& color);
    MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k);
    MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o, const vec3& t, const float nu);
    virtual ~MaterialTextura();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const ;
    virtual vec3 getDiffuse(vec2 uv) const;

    void setTexture(QString textureFile);
    virtual void read (const QJsonObject &json) override;
};
