#pragma once

#include <QtWidgets>
#include "Controller.hh"

class Builder : public QObject {
    Q_OBJECT

public:
    Builder(){};

public slots:
    void newSphere();
    void newBox();
    void newTriangle();
    void newMesh();

    void newSimulatedScene();
    void newVirtualScene();
    void newDataScene();
    void loadSettings();
    void activaColorShading();
    void activaDepthShader();
    void activaNormalShader();
  
    void activaCell_Shading();
    void activaPhongShader();
    void activaBlinn_Phong();
signals:
     void settingsChanged();
};

