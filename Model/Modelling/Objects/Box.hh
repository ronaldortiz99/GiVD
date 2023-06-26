#pragma once

#include "Object.hh"
#include "Model/Modelling/Animation.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Model/Modelling/TG/ScaleTG.hh"
#include "Model/Modelling/TG/RotateTG.hh"

class Box: public Object{
public:
    Box();
    Box(vec3 max, vec3 min, float data);
    Box(float data);
    virtual ~Box() {}
    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;
private:
    vec3 max; //Contiene la x,y,z máxima
    vec3 min; //Contiene la x,y,z mínima
};

