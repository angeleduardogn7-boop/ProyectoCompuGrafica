#include <GL/freeglut.h>
#include <iostream>

// Para usar stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Variables globales para quadrics (útiles para cilindros/esferas en maquinaria)
GLUquadricObj* p;

void luzYMaterial() {
    // Configuracion de luz ambiental (como un sol general)
    GLfloat luz_ambiente[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // Luz gris suave
    GLfloat luz_difusa[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Luz blanca fuerte
    GLfloat posicion_luz[] = { 0.0f, 100.0f, 0.0f, 1.0f }; // Desde arriba

    glEnable(GL_LIGHTING);   // Habilitar iluminacion
    glEnable(GL_LIGHT0);     // Habilitar la fuente de luz 0

    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_POSITION, posicion_luz);

    // Habilitar que los materiales sigan los colores de glColor
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void inicializar() {
    glClearColor(0.7f, 0.7f, 0.7f, 0.0f); // Fondo gris claro
    glEnable(GL_DEPTH_TEST);              // Activar buffer de profundidad

    p = gluNewQuadric();
    gluQuadricDrawStyle(p, GLU_FILL);
}

void redimensionar(int w, int h) {
    // Evitar division por cero
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    // Configurar Viewport
    glViewport(0, 0, w, h);

    // Configurar Proyeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 500.0); // Campo de vision de 45 grados

    glMatrixMode(GL_MODELVIEW);
}

void graficar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Configuración de la Cámara
    // gluLookAt(ojoX, ojoY, ojoZ, centroX, centroY, centroZ, arribaX, arribaY, arribaZ)
    gluLookAt(20.0, 20.0, 50.0,  // Posicion de la camara
        0.0, 5.0, 0.0,    // Hacia donde mira
        0.0, 1.0, 0.0);   // Vector hacia arriba (Eje Y)

    // --- AQUÍ SE DIBUJARÁN LOS MODELOS (Raul y Mathias R.) ---
    // Ejemplo: Un suelo simple
    glBegin(GL_LINES);
    for (int i = -50; i <= 50; i += 5) {
        glVertex3f((float)i, 0, -50); glVertex3f((float)i, 0, 50);
        glVertex3f(-50, 0, (float)i); glVertex3f(50, 0, (float)i);
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Configuracion de ventana solicitada
    glutInitWindowSize(1600, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simulacion de Maquinaria");

    inicializar();
    luzYMaterial();

    // Registro de funciones
    glutDisplayFunc(graficar);
    glutReshapeFunc(redimensionar);
    glutIdleFunc(graficar); 

    glutMainLoop();

    return 0;
}