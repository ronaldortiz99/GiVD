#pragma once

#include "Object.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Model/Modelling/TG/ScaleTG.hh"

class Triangle: public Object{
public:
    Triangle();
    Triangle(vec3 A, vec3 B, vec3 C, float data);
    Triangle(float data);
    virtual ~Triangle() {}
    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;
private:
    vec3 A; //Contiene la x,y,z máxima
    vec3 B; //Contiene la x,y,z mínima
    vec3 C;
    vec3 P;
};

