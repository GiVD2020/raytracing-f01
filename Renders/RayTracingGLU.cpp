#include "RayTracingGLU.h"


RayTracing *rIntern;

RayTracingGLU::RayTracingGLU()
{
    rIntern = this;
    f_render = &RenderingSceneGLU;
}

RayTracingGLU::~RayTracingGLU() {
}

void RayTracingGLU::startRendering(int argc, char **argv) {
    //inicialitza OpenGL
    glutInit(&argc, argv);
    //Define la mida de la window GL especificada per la mida del viewport
    glutInitWindowSize(cam->viewportX, cam->viewportY);

    //Creacio de la window per pintar amb GL
    glutCreateWindow("RayTracer");
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    //Posa la funcio Render per a que la window GL cridi quan es refresca
    glutDisplayFunc(f_render);
    // Inicia el main loop per a poder refrescar l'escena
    glutMainLoop();

}
void RayTracingGLU::initRender(string nomFitxer) {

    // Les seguents linieas permeten visualitzar en una finestra GLU el output
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Netejar la finestra OpenGL
    glBegin(GL_POINTS);	//S'activa el mode GL_POINTS. En aquest mode
                        // cada vertex especificat és un punt.
                        //Reference https://en.wikibooks.org/wiki/OpenGL_Programming/GLStart/Tut3 si us interessa.


}

void RayTracingGLU::setPixelColor(vec3 col, int x, int y) {
    // Aquestes línies permeten visualitzar en el buffer de la finestra GLU, el color associat al píxel corresponent
    float pixelX =  2*((x+0.5f)/cam->viewportX)-1;
    float pixelY = 2*((y+0.5f)/cam->viewportY)-1;

    glColor3f(col[0], col[1], col[2]);
    glVertex3f(pixelX, pixelY, 0.0f);
}

void RayTracingGLU::exitRender() {
    glEnd();
    glFlush();
}

void RenderingSceneGLU() {
    rIntern->renderingScene();
}
