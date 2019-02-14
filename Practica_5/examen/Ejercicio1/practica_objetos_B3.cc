//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B3.h"
using namespace std;
#if !defined(GLUT_WHEEL_UP)
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#endif
// tipos
typedef enum
{
        CUBO,
        PIRAMIDE,
        OBJETO_PLY,
        ROTACION,
        ARTICULADO,
        ESCAVADORA
} _tipo_objeto;
_tipo_objeto t_objeto = CUBO;
_modo modo = POINTS;
int estadoRaton[3], xc, yc, modo_selec[5], cambio = 0;
struct color
{
        double r;
        double g;
        double b;
};

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;
int vista_multiple = 0;
int Ancho = 450, Alto = 450;
float factor = 1.0;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x, Size_y, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x = 50, Window_y = 50, Window_width = 450, Window_high = 450;
void pick_color(int x, int y);

float primer_giro = 0;
float segundo_giro = 0;

// objetos
_cubo cubo;
color cubo_color;
_cubo cubo1;
color cubo_color1;
_piramide piramide(0.5, 1);
color piramide_color;
color piramide_color1;

_escena5 escena;
_objeto_ply ply;
_rotacion rotacion;
_tanque tanque;
_escavadora escavadora;
// _objeto_ply *ply1;

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
        //  plano_delantero>0  plano_trasero>PlanoDelantero)
        glFrustum(-Size_x, Size_x, -Size_y, Size_y, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

        // posicion del observador

        change_projection();
        glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, -Observer_distance);
        glRotatef(Observer_angle_x, 1, 0, 0);
        glRotatef(Observer_angle_y, 0, 1, 0);
}

void clickRaton(int boton, int estado, int x, int y)
{
        if (boton == GLUT_RIGHT_BUTTON)
        {
                if (estado == GLUT_DOWN)
                {
                        estadoRaton[2] = 1;
                        xc = x;
                        yc = y;
                }
                else
                        estadoRaton[2] = 1;
        }
        if (boton == GLUT_LEFT_BUTTON)
        {
                if (estado == GLUT_DOWN)
                {
                        estadoRaton[2] = 2;
                        xc = x;
                        yc = y;
                        pick_color(xc, yc);
                }
        }
        if (estado == GLUT_UP)
        {
                if (boton == GLUT_WHEEL_UP)
                {
                        Observer_distance *= 1.2;
                }
                else if (boton == GLUT_WHEEL_DOWN)
                {
                        Observer_distance /= 1.2;
                }
                glutPostRedisplay();
        }
}
void getCamara(GLfloat *x, GLfloat *y)
{
        *x = Observer_angle_y;
        *y = Observer_angle_x;
}

/*************************************************************************/

void setCamara(GLfloat x, GLfloat y)
{
        Observer_angle_x = y;
        Observer_angle_y = x;
}

void RatonMovido(int x, int y)
{
        float x0, y0, xn, yn;
        if (estadoRaton[2] == 1)
        {
                getCamara(&x0, &y0);
                yn = y0 - (y - yc);
                xn = x0 + (x - xc);
                setCamara(xn, yn);
                xc = x;
                yc = y;
                glutPostRedisplay();
        }
}

//***************************************************************************
// Funciones para la seleccion
//***************************************************************************

void procesar_color(unsigned char color[3])
{
        int i;
        switch (color[0])
        {
        case 100:
                i = 1;
                if (modo_selec[0] == 0)
                {
                        modo_selec[0] = 1;
                        cambio = 1;
                }
                else
                {
                        modo_selec[0] = 0;
                        cambio = 0;
                }
                break;
        case 110:
                i = 2;
                if (modo_selec[1] == 0)
                {
                        modo_selec[1] = 1;
                        cambio = 1;
                }
                else
                {
                        modo_selec[1] = 0;
                        cambio = 0;
                }
                break;
        case 120:
                i = 3;
                if (modo_selec[2] == 0)
                {
                        modo_selec[2] = 1;
                        cambio = 1;
                }
                else
                {
                        modo_selec[2] = 0;
                        cambio = 0;
                }
                break;

        case 130:
                i = 4;
                if (modo_selec[3] == 0)
                {
                        modo_selec[3] = 1;
                        cambio = 1;
                }
                else
                {
                        modo_selec[3] = 0;
                        cambio = 0;
                }
                break;
        }

        if (cambio == 1)
        {
                switch (i)
                {
                case 1:
                        cubo_color.r = 0.3;
                        cubo_color.g = 0.9;
                        cubo_color.b = 0.3;
                        break;
                case 2:
                        cubo_color1.r = 0.3;
                        cubo_color1.g = 0.9;
                        cubo_color1.b = 0.3;
                        break;
                case 3:
                        piramide_color.r = 0.3;
                        piramide_color.g = 0.9;
                        piramide_color.b = 0.3;
                        break;
                case 4:
                        piramide_color1.r = 0.3;
                        piramide_color1.g = 0.9;
                        piramide_color1.b = 0.3;
                        break;
                }
        }
        if (cambio == 0)
        {
                switch (i)
                {
                case 1:

                        cubo_color.r = 0.9;
                        cubo_color.g = 0.6;
                        cubo_color.b = 0.2;
                        break;
                        ;
                case 2:
                        cubo_color1.r = 0.9;
                        cubo_color1.g = 0.6;
                        cubo_color1.b = 0.2;
                        break;
                case 3:
                        piramide_color.r = 0.9;
                        piramide_color.g = 0.6;
                        piramide_color.b = 0.2;
                        break;
                case 4:
                        piramide_color1.r = 0.9;
                        piramide_color1.g = 0.6;
                        piramide_color1.b = 0.2;
                        break;
                }
        }
}

void pick_color(int x, int y)
{
        GLint viewport[4];
        unsigned char pixel[3];

        glGetIntegerv(GL_VIEWPORT, viewport);
        glReadBuffer(GL_BACK);
        glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (GLubyte *)&pixel[0]);
        printf(" valor x %d, valor y %d, color %d, %d, %d \n", x, y, pixel[0], pixel[1], pixel[2]);

        procesar_color(pixel);
        glutPostRedisplay();
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

        glDisable(GL_LIGHTING);
        glLineWidth(2);
        glBegin(GL_LINES);
        // eje X, color rojo
        glColor3f(1, 0, 0);
        glVertex3f(-AXIS_SIZE, 0, 0);
        glVertex3f(AXIS_SIZE, 0, 0);
        // eje Y, color verde
        glColor3f(0, 1, 0);
        glVertex3f(0, -AXIS_SIZE, 0);
        glVertex3f(0, AXIS_SIZE, 0);
        // eje Z, color azul
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, -AXIS_SIZE);
        glVertex3f(0, 0, AXIS_SIZE);
        glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

        piramide.draw(EDGES, 0, 0, 1, 0.0, 0.0, 0.0, 1);
        piramide.draw(SOLID, piramide_color1.r, piramide_color1.g, piramide_color1.b, 0.0, 0.0, 0.0, 1);
}
void draw_objects_seleccion()
{

        piramide.draw_seleccion_color(130, 130, 130);
}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{
        clean_window();

        if (vista_multiple == 0)
        {

                change_observer();
                draw_axis();
                glutSwapBuffers();
                draw_objects();
                glutSwapBuffers();
                clean_window();
                change_observer();
                draw_objects_seleccion();
        }
        else
        {       
                
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
                glFrustum(-Window_width, Window_width, Window_high,
                         Window_high, Front_plane, Back_plane);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                gluLookAt(4, 0, 4,
                          -1, 0, 0,
                          0.1, -1, 0.0);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                draw_axis();
                draw_objects();

                glutSwapBuffers();
        }
        glFlush();
}
//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************
void change_window_size(int Ancho1, int Alto1)
{
        change_projection();
        Ancho = Ancho1;
        Alto = Alto1;
        draw();
}

//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1, int x, int y)
{
        switch (toupper(Tecla1))
        {
        case 'Q':
                exit(0);
        case '1':
                modo = POINTS;
                break;
        case '2':
                modo = EDGES;
                break;
        case '3':
                modo = SOLID;
                break;
        case '4':
                modo = SOLID_CHESS;
                break;
        case 'P':
                t_objeto = PIRAMIDE;
                break;
        case 'C':
                t_objeto = CUBO;
                break;
        case 'O':
                t_objeto = OBJETO_PLY;
                break;
        case 'R':
                t_objeto = ROTACION;
                break;
        case 'A':
                t_objeto = ARTICULADO;
                break;
        case 'E':
                t_objeto = ESCAVADORA;
                break;
        }
        glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1, int x, int y)
{

        switch (Tecla1)
        {
        case GLUT_KEY_LEFT:
                Observer_angle_y--;
                break;
        case GLUT_KEY_RIGHT:
                Observer_angle_y++;
                break;
        case GLUT_KEY_UP:
                Observer_angle_x++;
                break;
        case GLUT_KEY_DOWN:
                Observer_angle_x--;
                break;
        case GLUT_KEY_PAGE_UP:
                Observer_distance *= 1.2;
                break;
        case GLUT_KEY_PAGE_DOWN:
                Observer_distance /= 1.2;
                break;
        case GLUT_KEY_F1:
                vista_multiple = 1;
                break;
        case GLUT_KEY_F2:
                vista_multiple = 0;
                break;
        case GLUT_KEY_F3:
                primer_giro++;
                tanque.giro_torreta += 5;
                escavadora.giro_base += 5;
                break;
        case GLUT_KEY_F4:
                primer_giro--;
                tanque.giro_torreta -= 5;
                escavadora.giro_base -= 5;
                break;
        case GLUT_KEY_F5:
                escavadora.giro_primer_brazo += 1;
                break;
        case GLUT_KEY_F6:
                escavadora.giro_primer_brazo -= 1;
                break;
        case GLUT_KEY_F7:
                escavadora.giro_segundo_brazo += 1;
                break;
        case GLUT_KEY_F8:
                escavadora.giro_segundo_brazo -= 1;
                break;
        }
        glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
        // se inicalizan la ventana y los planos de corte
        Window_width = .5;
        Window_high = .5;

        // se inicalizan la ventana y los planos de corte
        Size_x = 0.5;
        Size_y = 0.5;
        Front_plane = 1;
        Back_plane = 1000;
        cubo_color.r = 0.9;
        cubo_color.g = 0.6;
        cubo_color.b = 0.2;
        cubo_color1.r = 0.9;
        cubo_color1.g = 0.6;
        cubo_color1.b = 0.2;
        piramide_color.r = 0.9;
        piramide_color.g = 0.6;
        piramide_color.b = 0.2;
        piramide_color1.r = 0.9;
        piramide_color1.g = 0.6;
        piramide_color1.b = 0.2;
        // se incia la posicion del observador, en el eje z
        Observer_distance = 3 * Front_plane;
        Observer_angle_x = 0;
        Observer_angle_y = 0;

        // se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
        // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
        glClearColor(1, 1, 1, 1);

        // se habilita el z-bufer
        glEnable(GL_DEPTH_TEST);
        change_projection();
        glViewport(0, 0, Window_width, Window_high);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

        // creación del objeto ply

        ply.parametros(argv[1]);

        // perfil

        vector<_vertex3f> perfil2;
        _vertex3f aux;
        aux.x = 1.0;
        aux.y = -1.4;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 1.0;
        aux.y = -1.1;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.5;
        aux.y = -0.7;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.4;
        aux.y = -0.4;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.4;
        aux.y = 0.5;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.5;
        aux.y = 0.6;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.3;
        aux.y = 0.6;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.5;
        aux.y = 0.8;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.55;
        aux.y = 1.0;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.5;
        aux.y = 1.2;
        aux.z = 0.0;
        perfil2.push_back(aux);
        aux.x = 0.3;
        aux.y = 1.4;
        aux.z = 0.0;
        perfil2.push_back(aux);
        rotacion.parametros(perfil2, 6, 1);

        // se llama a la inicialización de glut
        glutInit(&argc, argv);

        // se indica las caracteristicas que se desean para la visualización con OpenGL
        // Las posibilidades son:
        // GLUT_SIMPLE -> memoria de imagen simple
        // GLUT_DOUBLE -> memoria de imagen doble
        // GLUT_INDEX -> memoria de imagen con color indizado
        // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
        // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
        // GLUT_DEPTH -> memoria de profundidad o z-bufer
        // GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

        // posicion de la esquina inferior izquierdad de la ventana
        glutInitWindowPosition(Window_x, Window_y);

        // tamaño de la ventana (ancho y alto)
        glutInitWindowSize(Window_width, Window_high);

        // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
        // al bucle de eventos)
        glutCreateWindow("PRACTICA - 2");

        // asignación de la funcion llamada "dibujar" al evento de dibujo
        glutDisplayFunc(draw);
        // asignación de la funcion llamada "change_window_size" al evento correspondiente
        glutReshapeFunc(change_window_size);
        // asignación de la funcion llamada "normal_key" al evento correspondiente
        glutKeyboardFunc(normal_key);
        // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
        glutSpecialFunc(special_key);
        // eventos ratón
        glutMouseFunc(clickRaton);
        glutMotionFunc(RatonMovido);

        // funcion de inicialización
        initialize();

        // inicio del bucle de eventos
        glutMainLoop();
        return 0;
}
