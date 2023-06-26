#include "Triangle.hh"

Triangle::Triangle(){
    A = vec3(0,0,0);
    B = vec3(1,1,1);
    C = vec3(0,2,0);
    P[0] = (A[0] + B[0] + C[0]) / 3;
    P[1] = (A[1] + B[1] + C[1]) / 3;
    P[2] = (A[2] + B[2] + C[2]) / 3;
}

Triangle::Triangle(float data): Object(data){
    A = vec3(0,0,0);
    B = vec3(1,1,1);
    C = vec3(0,2,0);
}

Triangle::Triangle(vec3 A, vec3 B, vec3 C, float data): Object(data){
    Triangle::A = A;
    Triangle::B = B;
    Triangle::C = C;
}

bool Triangle::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    vec3 orig = raig.getOrigin();
    vec3 dir = raig.getDirection();

    vec3 normal = normalize(cross(B - A, C - A));

    double n = dot(dir, normal);
    float d = -dot(A,normal);

    if (abs(n) < FLT_EPSILON) {
        return false;
    }

    float t = -(dot(normal, orig) + d) / dot(dir, normal);
    float scAB, scBC, scCA;

    if(t > tmax || t < tmin) return false;

    vec3 intersect = dir * t + orig;
    scAB = dot(cross(B -A, intersect - A), normal);
    scBC = dot(cross(C -B, intersect - B), normal);
    scCA = dot(cross(A -C, intersect - C), normal);

    if (scAB >= 0 && scBC >= 0 && scCA >= 0) {

        info.t = t;
        info.p = raig.pointAtParameter(info.t);
        info.normal = normal;

        if (n < 0) {
            info.normal = -normal;
        }

        info.mat_ptr = material.get();
        return true;

    }
    return false;



    return false;
}

void Triangle::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<TranslateTG>(t)) {
        // Per ara només es fan les translacions
        vec4 c(P, 1.0);
        vec4 ver1(A, 1.0);
        vec4 ver2(B, 1.0);
        vec4 ver3(C, 1.0);

        c = t->getTG() * c;
        ver1 = t->getTG() * ver1;
        ver2 = t->getTG() * ver2;
        ver3 = t->getTG() * ver3;

        P.x = c.x; P.y = c.y; P.z = c.z;
        A.x = ver1.x; A.y = ver1.y; A.z = ver1.z;
        B.x = ver2.x; B.y = ver2.y; B.z = ver2.z;
        C.x = ver3.x; C.y = ver3.y; C.z = ver3.z;
    }
    else if (dynamic_pointer_cast<ScaleTG>(t)){
        vec4 c(P, 1.0);
        vec4 ver1(A, 1.0);
        vec4 ver2(B, 1.0);
        vec4 ver3(C, 1.0);

        c = t->getTG() * c;
        ver1 = t->getTG() * ver1;
        ver2 = t->getTG() * ver2;
        ver3 = t->getTG() * ver3;

        P.x = c.x; P.y = c.y; P.z = c.z;
        A.x = ver1.x; A.y = ver1.y; A.z = ver1.z;
        B.x = ver2.x; B.y = ver2.y; B.z = ver2.z;
        C.x = ver3.x; C.y = ver3.y; C.z = ver3.z;
    }
    //TODO: Cal ampliar-lo per a acceptar Escalats

}

void Triangle::read (const QJsonObject &json)
{
    Object::read(json);

    if (json.contains("A") && json["A"].isArray()) {
        QJsonArray auxVec = json["A"].toArray();
        A[0] = auxVec[0].toDouble();
        A[1] = auxVec[1].toDouble();
        A[2] = auxVec[2].toDouble();
    }

    if (json.contains("B") && json["B"].isArray()) {
        QJsonArray auxVec = json["B"].toArray();
        B[0] = auxVec[0].toDouble();
        B[1] = auxVec[1].toDouble();
        B[2] = auxVec[2].toDouble();
    }

    if (json.contains("C") && json["C"].isArray()) {
        QJsonArray auxVec = json["C"].toArray();
        C[0] = auxVec[0].toDouble();
        C[1] = auxVec[1].toDouble();
        C[2] = auxVec[2].toDouble();
    }
}

void Triangle::write(QJsonObject &json) const
{
    Object::write(json);

    QJsonArray auxArray;
    auxArray.append(A[0]);auxArray.append(A[1]);auxArray.append(A[2]);
    json["A"] = auxArray;

    auxArray.append(B[0]);auxArray.append(B[1]);auxArray.append(B[2]);
    json["B"] = auxArray;

    auxArray.append(C[0]);auxArray.append(C[1]);auxArray.append(C[2]);
    json["C"] = auxArray;

}


void Triangle::print(int indentation) const
{
    Object::print(indentation);

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "A:\t" << A[0] << ", "<< A[1] << ", "<< A[2] << "\n";
    QTextStream(stdout) << indent << "B:\t" << B[0] << ", "<< B[1] << ", "<< B[2] << "\n";
    QTextStream(stdout) << indent << "C:\t" << C[0] << ", "<< C[1] << ", "<< C[2] << "\n";
}

