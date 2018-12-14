//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B3.h"

using namespace std;

// tipos
typedef enum
{
  CUBO,
  PIRAMIDE,
  OBJETO_PLY,
  ROTACION,
  ARTICULADO,
  ESCAVADORA,
  ESFERA
} _tipo_objeto;
_tipo_objeto t_objeto = CUBO;
_modo modo = POINTS;
bool textura_activa = false;
bool escena_material = false;
bool luz1 = true;
// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x, Size_y, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x = 50, Window_y = 50, Window_width = 450, Window_high = 450;

// objetos
_cubo cubo;
_piramide piramide(0.85, 1.3);
_objeto_ply ply;
_rotacion rotacion;
_tanque tanque;
_escavadora escavadora;
_esfera esfera(0.8, 40, 20);
_imagen textura;

float angulo_luz = 30.0;
float lAlfa = 0;
float lx = 1;
float ly = 0;
float lz = 0;
int material_elegido = 0;

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
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -Observer_distance);
  glRotatef(Observer_angle_x, 1, 0, 0);
  glRotatef(Observer_angle_y, 0, 1, 0);
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
  _vertex4f ambiente_obsidiana(0.25375, 2.05, 0.26625, 0.82);
  _vertex4f esp_obsidiana(0.332741, 0.328634, 0.346435, 0.82);

  _vertex4f ambiente_oro(0.24725, 0.2245, 0.0645, 1.0);
  _vertex4f esp_oro(0.797357, 0.723991, 0.208006, 1.0);

  _vertex4f ambiente_esmeralda(0.2215, 0.2745, 0.2215, 0.7);
  _vertex4f esp_esmeralda(0.133, 0.227811, 0.133, 0.35);

  _vertex4f ambiente_amarillo_nampoles(236.0/255, 205.0/255, 106.0/255, 1);
  _vertex4f esp_amarillo_nampoles(0.7, 0.7, 0.04, 1.0);

  _vertex4f ambiente_marfil(1, 1, 220.0/255, 1);
  _vertex4f esp_marfil(1, 1, 220.0/255, 1);

  _vertex4f ambiente_chocolate(104.0/255, 59.0/255,0, 1);
  _vertex4f esp_chocolate(104.0/255, 59.0/255,0, 1);

  float brillo = 10.8;
  _vertex4f materiales[6][2]={
    {ambiente_obsidiana,esp_obsidiana},
    {ambiente_oro,esp_oro},
    {ambiente_esmeralda,esp_esmeralda},   
    {ambiente_amarillo_nampoles,esp_amarillo_nampoles},
    {ambiente_chocolate,esp_chocolate},
    {ambiente_marfil,esp_marfil}
  };
void draw_objects()
{
  switch (t_objeto)
  {
  case CUBO:
    cubo.ambiente_difusa = materiales[5][0];
    cubo.especular = materiales[5][1];
    cubo.brillo = brillo;
    cubo.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
    break;
  case PIRAMIDE:
    piramide.ambiente_difusa = materiales[5][0];
    piramide.especular = esp_esmeralda;
    piramide.brillo = brillo;
    piramide.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
    break;
  case OBJETO_PLY:
    ply.ambiente_difusa = materiales[5][0];
    ply.especular = materiales[5][1];
    ply.brillo = brillo;

    //ply.ambiente_difusa = _vertex4f(0.5,0.5,0.5,1.0);
    //ply.especular = _vertex4f(0.5,0.5,0.5,1.0);
    ply.brillo = 120;
    ply.draw(modo, 1.0, 0.6, 0.0, 0.0, 1.0, 0.3, 2);
    break;
  case ROTACION:
    rotacion.ambiente_difusa = materiales[5][0];
    rotacion.especular = materiales[5][1];
    rotacion.brillo = brillo;
    rotacion.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
    break;
  case ARTICULADO:
    tanque.ambiente_difusa = materiales[5][0];
    tanque.especular = materiales[5][1];
    tanque.brillo = brillo;
    tanque.draw(modo, 0.5, 0.7, 0.2, 0.3, 0.6, 0.3, 2);
    break;
  case ESCAVADORA:
    escavadora.ambiente_difusa = materiales[5][0];
    escavadora.especular = materiales[5][1];
    escavadora.brillo = brillo;
    escavadora.draw(modo, 0.5, 0.7, 0.2, 0.3, 0.6, 0.3, 2);
    break;

  case ESFERA:
    esfera.ambiente_difusa = materiales[5][0];
    esfera.especular = materiales[5][1];
    esfera.brillo = brillo;
    esfera.draw(modo, 0.5, 0.7, 0.2, 0.3, 0.6, 0.3, 2);
    break;
  }
}
void luces(float alfa)
{
  GLfloat light_position[4] = {0, 20, 0, 1},
          light1_position[4] = {0, 20, 0, 1},
          lightl_ambient[4] = {0.1, 0.0, 0.0, 1},
          lightl_intensity[4] = {1.0, 0.4, 0.4, 1};

  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT1, GL_AMBIENT, lightl_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightl_intensity);
  glLightfv(GL_LIGHT1, GL_SPECULAR, lightl_intensity);

  glPushMatrix();
  glRotatef(alfa, 0, 1, 0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glPopMatrix();
};

void draw_Luz1()
{
  GLfloat ambiente[] = {0.02, 0, 0, 1.0};
  GLfloat luz_posicion[] = {0, 0, 0.0, 1.0};

  GLfloat difusa[] = {0.8, 0, 0, 1.0};
  GLfloat especular[] = {0.8, 0, 0, 1.0};
  GLfloat direccion[] = {-1,1,1};
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT2);

  glEnable(GL_LIGHT1);
   

  glPushMatrix();
  glLightfv(GL_LIGHT1, GL_AMBIENT, (GLfloat *)&ambiente);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat *)&difusa);
  glLightfv(GL_LIGHT1, GL_SPECULAR, (GLfloat *)&especular);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, (GLfloat *)&direccion);


  glPopMatrix();
}
void draw_Luz2()
{
  GLfloat luz_posicion[] = {8.0, 8.0, 0.0, 1.0};
  GLfloat ambiente[] = {0.05, 0.2, 0.02, 1.0};
  GLfloat difusa[] = {0.6, 0.5, 0.1, 1.0};
  GLfloat especular[] = {0.6, 0.5, 0.1, 1.0};

  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);

  glEnable(GL_LIGHT2);

  glPushMatrix();
  glRotatef(lAlfa, lx, ly, lz);
  glLightfv(GL_LIGHT2, GL_AMBIENT, (GLfloat *)&ambiente);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, (GLfloat *)&difusa);
  glLightfv(GL_LIGHT2, GL_SPECULAR, (GLfloat *)&especular);
  glLightfv(GL_LIGHT2, GL_POSITION, (GLfloat *)&luz_posicion);
  glPopMatrix();
}

void draw_luzBlanca()
{
  GLfloat luz_posicion[] = {200.0, 200.0, 200.0, 1.0};
  GLfloat ambiente[] = {0.2, 0.2, 0.2, 0.2};
  GLfloat difusa[] = {0.7, 0.7, 0.7, 0.7};
  GLfloat especular[] = {0.7, 0.7, 0.7, 0.7};

  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  glPushMatrix();
  glRotatef(lAlfa, lx, ly, lz);
  glLightfv(GL_LIGHT2, GL_AMBIENT, (GLfloat *)&ambiente);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, (GLfloat *)&difusa);
  glLightfv(GL_LIGHT2, GL_SPECULAR, (GLfloat *)&especular);
  glLightfv(GL_LIGHT2, GL_POSITION, (GLfloat *)&luz_posicion);
  glPopMatrix();
}
//**************************************************************************
//
//***************************************************************************

void draw(void)
{

  clean_window();
  change_observer();
  if(!escena_material)
    if(luz1)
      draw_Luz1();
    else
      draw_Luz2();
  if (textura_activa){
    textura.draw_piramide();
    glTranslatef(0, 0.75,0);
    glScalef(0.7, 1 , 0.7);
    textura.draw_piramide();
  }else if( escena_material){
    draw_luzBlanca();
    glTranslatef(-0.75, 0,0);
    esfera.ambiente_difusa = materiales[4][0];
    esfera.especular = materiales[4][1];
    esfera.brillo = brillo;
    esfera.draw(modo, 0.5, 0.7, 0.2, 0.3, 0.6, 0.3, 2);

    esfera.ambiente_difusa = materiales[5][0];
    esfera.especular = materiales[5][1];
    esfera.brillo = brillo;
    glTranslatef(1.5, 0,0);
    esfera.draw(modo, 0.5, 0.7, 0.2, 0.3, 0.6, 0.3, 2);
    glTranslatef(-0.75, 0,0);

  }else
    draw_objects();

  draw_axis();
  glutSwapBuffers();
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
  float Aspect_ratio;

  Aspect_ratio = (float)Alto1 / (float)Ancho1;
  Size_y = Size_x * Aspect_ratio;
  change_projection();
  glViewport(0, 0, Ancho1, Alto1);
  glutPostRedisplay();
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
  string archivo;
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
  case '5':
    modo = SOLID_ILLUMINATED_FLAT;
    material_elegido++;
    break;
  case '6':
    modo = SOLID_ILLUMINATED_GOURAUD;
    luz1 = false;
    material_elegido++;
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
  case 'T':
    t_objeto = ESFERA;
    break;
  case '7':
    textura_activa = !textura_activa;
    textura.Load("./abeto.jpg");
    break;
  case '8':
    modo = SOLID_ILLUMINATED_GOURAUD;
    escena_material = !escena_material;
    break;
  case '9':
    modo = SOLID_ILLUMINATED_GOURAUD;
    luz1 = true;
  case 'H':
    lAlfa = fmod(lAlfa + 5, 360.0);
    lz = 1;
    lx = ly = 0;
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
    Observer_angle_x--;
    break;
  case GLUT_KEY_DOWN:
    Observer_angle_x++;
    break;
  case GLUT_KEY_PAGE_UP:
    Observer_distance *= 1.2;
    break;
  case GLUT_KEY_PAGE_DOWN:
    Observer_distance /= 1.2;
    break;
  case GLUT_KEY_F1:
    tanque.giro_tubo += 1;
    escavadora.giro_cazo += 1;
    if (tanque.giro_tubo > tanque.giro_tubo_max)
      tanque.giro_tubo = tanque.giro_tubo_max;
    break;
  case GLUT_KEY_F2:
    tanque.giro_tubo -= 1;
    escavadora.giro_cazo -= 1;
    if (tanque.giro_tubo < tanque.giro_tubo_min)
      tanque.giro_tubo = tanque.giro_tubo_min;
    break;
    break;
  case GLUT_KEY_F3:
    tanque.giro_torreta += 5;
    escavadora.giro_base += 5;
    break;
  case GLUT_KEY_F4:
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
  case GLUT_KEY_F10:
    lAlfa = fmod(lAlfa + 5, 360.0);
    lx = 1;
    ly = lz = 0;
    break;
  case GLUT_KEY_F11:
    lAlfa = fmod(lAlfa + 5, 360.0);
    ly = 1;
    lx = lz = 0;
    break;
  case GLUT_KEY_F12:
    lAlfa = fmod(lAlfa + 5, 360.0);
    lz = 1;
    lx = ly = 0;
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
  Size_x = 0.5;
  Size_y = 0.5;
  Front_plane = 1;
  Back_plane = 1000;

  // se incia la posicion del observador, en el eje z
  Observer_distance = 4 * Front_plane;
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

  // funcion de inicialización
  initialize();

  // inicio del bucle de eventos
  glutMainLoop();

  textura.libera();

  return 0;
}
