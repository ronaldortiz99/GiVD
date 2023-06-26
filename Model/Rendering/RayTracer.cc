#include "RayTracer.hh"


RayTracer::RayTracer(QImage *i):
    image(i) {

    setup = Controller::getInstance()->getSetUp();
    scene = Controller::getInstance()->getScene();
    depth = 0;
}

void RayTracer::addDepth(){
    this->depth++;
}
int RayTracer::getDepth(){
    return depth;
}
void RayTracer::run() {

    init();
    auto camera = setup->getCamera();
    int  width = camera->viewportX;
    int  height = camera->viewportY;
    int numSamples = setup->getSamples();

    for (int y = height-1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;  // Progrés del càlcul
        for (int x = 0; x < width; x++) {
            float u, v;
            vec3 colorSum(0,0,0);
            //TODO FASE 2: mostrejar més rajos per pixel segons el valor de "samples"
            for (int i = 0; i < numSamples; i++){
                u = (float(x) + glm::linearRand(0.0f, 1.0f)) / float(width);
                v = (float(height -y) + glm::linearRand(0.0f, 1.0f)) / float(height);
                 Ray r = camera->getRay(u, v);

                // Sumar els colors resultants
                colorSum += RayPixel(r);

            }
            vec3 color = colorSum / float(numSamples);
            color = clamp(color,0,1);

            // TODO FASE 2: Gamma correction
            color = sqrt(color);
            color *= 255;
            setPixel(x, y, color);
            this->depth = 0;

        }
    }
}


void RayTracer::setPixel(int x, int y, vec3 color) {

    if (color.r < 0) color.r = 0.0;
    if (color.g < 0) color.g = 0.0;
    if (color.b < 0) color.b = 0.0;

    if (color.r > 255) color.r = 255;
    if (color.g > 255) color.g = 255;
    if (color.b > 255) color.b  = 255;


    image->setPixelColor(x, y, QColor(color.r, color.g, color.b));

}

/* Mètode RayPixel
** TODO: Cal modificar la funcio RayPixel es la funcio recursiva del RayTracing. Cal retocar-lo per:
** FASE 0 per a fer el degradat del fons
** FASES 0 i 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte (via color, depth o normal)
** FASE 2 per incloure els shading més realistes (Blinn-Phong  i ombres)
** FASE 2 per a tractar reflexions i transparències
**
*/

// Funcio recursiva que calcula el color.
vec3 RayTracer::RayPixel(Ray &ray) {

    vec3 color;
    vec3 colorsec = vec3(0);
    vec3 unit_direction;
    HitInfo info;
    Ray rayout;
    vec3 ray2 = normalize(ray.getDirection());

    if (scene->hit(ray,0.001f,numeric_limits<float>::infinity(),info)) {
        shared_ptr<ShadingStrategy> shade = setup->getShadingStrategy();
        if (shade!=nullptr){
            color = shade->shading(scene,info,ray.getOrigin(),setup->getGlobalLight(), setup->getLights());
            if(setup->getReflections()){
                if(MaterialFactory::getInstance().getIndexType(info.mat_ptr) == MaterialFactory::TRANSPARENT){
                    color *= (1.0f - info.mat_ptr->Kt);
                }
                if(getDepth() <= setup->getMAXDEPTH()){
                    addDepth();
                    if(info.mat_ptr->scatter(ray, info, colorsec, rayout)){
                        color += colorsec*RayPixel(rayout);
                    }
                }
            }
        }else{
            color = info.mat_ptr->Ka;
        }
    } else {
        if (setup->getBackground()){
            float t = 0.5f*(ray2.y+1);
            color = setup->getTopBackground() *  t + setup->getDownBackground() * (1- t);
        }
        else{
            color = vec3(0.0,0.0,0.0);
        }

    }

    return color;
}


void RayTracer::init() {
    auto s = setup->getShadingStrategy();
    auto s_out = ShadingFactory::getInstance().switchShading(s, setup->getShadows());
    if (s_out!=nullptr) setup->setShadingStrategy(s_out);
}

