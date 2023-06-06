#include "main.h"

const float PI = 3.14159;

float radius = 30.0f;
float phi = 0.0f;
float theta = 0.0f;
float deltaTheta, deltaPhi, deltaRadius;

const int num_particles = 3;
float deltaT = 0.02f;

Vector3f camCenter(0.0f, 0.0f, 0.0f); 
Plane plane0(Vector3f(-10.0f, 10.6f, -3.0f), Vector3f(10.0f, 10.6f, -3.0f), Vector3f(10.0f, 10.0f, 0.0f), Vector3f(-10.0f, 10.0f, 0.0f));
Plane plane1(Vector3f(-10.0f, 10.0f, 0.0f), Vector3f(10.0f, 10.0f, 0.0f), Vector3f(10.0f, 1.0f, 10.0f), Vector3f(-10.0f, 1.0f, 10.0f));
Plane plane2(Vector3f(-10.0f, 1.0f, 10.0f), Vector3f(10.0f, 1.0f, 10.0f), Vector3f(10.0f, 0.5f, 13.0f), Vector3f(-10.0f, 0.5f, 13.0f));
ParticleSystem pSys;

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); // Reset the model-view matrix
    gluPerspective(60.0, 4.0 / 3.0, 1, 100); //60: Oeffnungswinkel, w/h: Seitenverhaeltnis, 1.0:near, 100.0:far

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 

    // change theta, phi or radius if keyboard is pressed
    if (deltaTheta) { theta += deltaTheta * PI / 180.0f; } 
    if (deltaPhi) { phi += deltaPhi * PI / 180.0f; }
    if (deltaRadius) { radius += deltaRadius; } 

    // calculate new camera direction 
    float camDirX = camCenter.getX() + radius * cos(phi) * sin(theta); 
    float camDirY = camCenter.getY() + radius * sin(phi);
    float camDirZ = camCenter.getZ() + radius * cos(phi) * cos(theta);

    gluLookAt(camDirX, camDirY, camDirZ, // camera looking at 
              camCenter.getX(), camCenter.getY(), camCenter.getZ(), // position of the camera
              0.0f, 1.0f, 0.0f); // vector looking upwards
   
    // Draw planes
    plane0.draw();
    plane1.draw();
    plane2.draw();
   
    pSys.generateParticle(num_particles); // fill vector particleBuffer
    
    for (int i = 0; i < pSys.getSize(); i++) { // for every particle in particleBuffer
        Particle p = pSys.getParticle(i);
        vector<Vector3f> s_neu = p.update(deltaT); // calculate new state
        p.setState(s_neu[0], s_neu[1]);

        // check if particle hits a plane
        if (plane0.hit(s_neu[0])) {
            Vector3f s_v = s_neu[1] - (plane0.getNormal() * s_neu[1].dot_product(plane0.getNormal()) * 2.0f); // calculate new velocity
            p.setState(s_neu[0], s_v); // set new state
        }
        else if (plane1.hit(s_neu[0])) {
            Vector3f s_v = s_neu[1] - (plane1.getNormal() * s_neu[1].dot_product(plane1.getNormal()) * 2.0f);
            p.setState(s_neu[0], s_v);
        }
        else if (plane2.hit(s_neu[0])) {
            Vector3f s_v = s_neu[1] - (plane2.getNormal() * s_neu[1].dot_product(plane2.getNormal()) * 2.0f);
            p.setState(s_neu[0], s_v);
        }
        pSys.particleHit(i, p); // check if particle hits another particle
        p.draw(); // draw particle
        pSys.setParticle(i, p); // set particle in particleBuffer
        pSys.deleteParticle(i, p, Vector3f(10.0f, 0.5f, 13.0f), Vector3f(-10.0f, 0.5f, 13.0f)); // delete particle if its postion is behind plane2
    }
    glutSwapBuffers();
    //glFlush();// Flush drawing command buffer to make drawing happen as soon as possible
}

void pressKey(int key, int xx, int yy) {

    switch (key) {
    case GLUT_KEY_UP: deltaPhi = -1.0f; break;
    case GLUT_KEY_DOWN: deltaPhi = 1.0f; break;
    case GLUT_KEY_LEFT: deltaTheta = 1.0f; break;
    case GLUT_KEY_RIGHT: deltaTheta = -1.0f; break;
    case GLUT_KEY_F1: deltaRadius = 1.0f; break;
    case GLUT_KEY_F2: deltaRadius = -1.0f; break;
    }
}

void releaseKey(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP: deltaPhi = 0.0f; break;
    case GLUT_KEY_DOWN: deltaPhi = 0.0f; break;
    case GLUT_KEY_LEFT: deltaTheta = 0.0f; break;
    case GLUT_KEY_RIGHT: deltaTheta = 0.0f; break;
    case GLUT_KEY_F1: deltaRadius = 0.0f; break;
    case GLUT_KEY_F2: deltaRadius = 0.0f; break;
    }
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // sets the initial display mode
    glutInitWindowPosition(80, 80); 
    glutInitWindowSize(800, 600);
    glutCreateWindow("Particle System");
  
    glutDisplayFunc(display);
    glutSpecialFunc(pressKey); // sets the special keyboard callback for the current window
    glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
    glutSpecialUpFunc(releaseKey); // call releaseKey() when key is released
    glutIdleFunc(display);    
    
    glEnable(GL_DEPTH_TEST);  // Enable depth testing for z-component
    glutMainLoop();

    return 0;


}