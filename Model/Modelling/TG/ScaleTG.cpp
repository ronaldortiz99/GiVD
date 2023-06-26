#include "ScaleTG.hh"

ScaleTG::ScaleTG(glm::vec3 scal): scaled(scal)
{
    matTG = glm::scale(glm::mat4(1.0f), scaled);
}

ScaleTG::~ScaleTG(){

}
