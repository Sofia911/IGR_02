#include "Particle.h"

std::vector<Vector3f> Particle::getState()
{
    std::vector<Vector3f> f_array; //array declared
    f_array.push_back(x);
    f_array.push_back(v);

    return f_array; //array returned
}

std::vector<Vector3f> Particle::update(float deltaT)
{
    std::vector<Vector3f> s_alt = this->getState();
    std::vector<Vector3f> eval = this->derivEval();
    std::vector<Vector3f> s_neu;
    for (int id = 0; id < 2; id++) { 
        float s_x = s_alt[id].getX() + eval[id].getX() * deltaT;
        float s_y = s_alt[id].getY() + eval[id].getY() * deltaT;
        float s_z = s_alt[id].getZ() + eval[id].getZ() * deltaT;
        s_neu.push_back(Vector3f(s_x, s_y, s_z));
    }
    this->setState(s_neu[0], s_neu[1]);
    return s_neu;
}

void Particle::draw()
{   
    glColor3f(0.0f, 0.0f, 1.0f);
    glPointSize(radius);
    glBegin(GL_POINTS);
    glVertex3f(x.getX(), x.getY(), x.getZ());
    glEnd();
}

std::vector<Vector3f> Particle::derivEval()
{
    f = Vector3f(0.0f, 0.0f, 0.0f); // delete force f
    f = f + Vector3f(0.0f, -9.81f, 0.0f) * m; // add gravitation force
    std::vector<Vector3f> f_array;
    f_array.push_back(v);
    f_array.push_back(f/m);

    return f_array; //array returned
}
