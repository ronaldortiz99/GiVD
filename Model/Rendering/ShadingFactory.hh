#pragma once

#include "ShadingFactory.hh"
#include "DepthShading.hh"
#include "NormalShading.hh"
#include "ColorShading.hh"
#include "ColorShadow.hh"
#include "CellShading.hh"
#include "PhongShading.hh"
#include "BlinnPhongShading.hh"
#include "BlinnPhongShadow.hh"
#include "PhongShadow.hh"
#include "CellShadow.hh"
#include "NormalShadow.hh"
#include "DepthShadow.hh"

class ShadingFactory
{
public:
    ShadingFactory() {};
    typedef enum  SHADING_TYPES{
        COLOR,
        COLORSHADOW,
        NORMAL,
        NORMALSHADOW,
        DEPTH,
        DEPTHSHADOW,
        PHONG,
        PHONGSHADOW,
        CELL,
        CELLSHADOW,
        BLINNPHONG,
        BLINNPHONGSHADOW
    } SHADING_TYPES;

    static ShadingFactory& getInstance() {
        static ShadingFactory instance;
        return instance;
    }

    shared_ptr<ShadingStrategy>   createShading(SHADING_TYPES t);
    SHADING_TYPES                 getShadingType(QString s);
    QString                       getNameType(SHADING_TYPES t);
    ShadingFactory::SHADING_TYPES getIndexType(shared_ptr<ShadingStrategy> m);
    shared_ptr<ShadingStrategy>   switchShading(shared_ptr<ShadingStrategy> m, bool shadow);
};

