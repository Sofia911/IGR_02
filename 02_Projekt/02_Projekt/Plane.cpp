#include "Plane.h"

bool Plane::hit(Vector3f pos)
{
    const float EPSILON = 0.2f;
    Vector3f AB, AC, AP;
    AB = B - A; 
    AC = C - A;
    AP = pos - A;

    normal = AB.cross_product(AC).normalize();

    // calculate dot product: AP * (AB x AC)
    float dotProduct = AP.dot_product(normal);

    // check if point is on plane
    if (abs(dotProduct) <= EPSILON) { 
        float p_x = pos.getX();
        float p_y = pos.getY();
        float p_z = pos.getZ();
        if (p_x < A.getX() || p_x > B.getX()) 
            return false;
        if (p_y < D.getY() || p_y > A.getY())
            return false;
        if (p_z < A.getZ() || p_z > D.getZ())
            return false;
        return true;
    }
    else {
        return false;
    }
}

void Plane::draw()
{
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(A.getX(), A.getY(), A.getZ());
    glVertex3f(B.getX(), B.getY(), B.getZ());
    glVertex3f(C.getX(), C.getY(), C.getZ());
    glVertex3f(D.getX(), D.getY(), D.getZ());
    glEnd();
}