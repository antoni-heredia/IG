//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"
#include "CImg.h"
using namespace std;
using namespace cimg_library;

const float AXIS_SIZE = 5000;
typedef enum
{
  POINTS,
  EDGES,
  SOLID_CHESS,
  SOLID,
  SOLID_ILLUMINATED_FLAT,
  SOLID_ILLUMINATED_GOURAUD
} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:
  _puntos3D();
  void draw_puntos(float r, float g, float b, int grosor);

  vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D : public _puntos3D
{
public:
  _triangulos3D();
  void draw_aristas(float r, float g, float b, int grosor);
  void draw_solido(float r, float g, float b);
  void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
  void draw_iluminacion_plana();
  void draw_iluminacion_suave();

  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  void calcular_normales_caras();
  void calcular_normales_vertices();

  vector<_vertex3i> caras;

  vector<_vertex3f> normales_caras;
  vector<_vertex3f> normales_vertices;

  bool b_normales_caras;
  bool b_normales_vertices;

  _vertex4f ambiente_difusa; //coeficientes ambiente y difuso
  _vertex4f especular;       //coeficiente especular
  float brillo;
};
class _imagen : public _triangulos3D
{
private:
  // IDENTIFICADOR DE TEXTURA
  GLuint textura_id;

public:
  _imagen();
  void Load(const char path[]);
  void draw();
  void draw_portatil();
  void draw_skybox();
  void draw_piramide();
  void libera();
};
//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo : public _triangulos3D
{
public:
  _imagen *textura;
  _cubo(float tam = 0.5);
  void SetTextura(_imagen &i);
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide : public _triangulos3D
{
public:
  _piramide(float tam = 0.5, float al = 0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply : public _triangulos3D
{
public:
  _objeto_ply();

  int parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion : public _triangulos3D
{
public:
  _rotacion();
  _imagen *textura;
  void parametros(vector<_vertex3f> perfil1, int num1, int tapas);
  void SetTextura(_imagen &i);

  vector<_vertex3f> perfil;
  int num;
};

//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis : public _triangulos3D
{
public:
  _chasis();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float altura;

protected:
  _rotacion rodamiento;
  _cubo base;
};

//************************************************************************

class _torreta : public _triangulos3D
{
public:
  _torreta();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float altura;
  float anchura;

protected:
  _cubo base;
  _piramide parte_trasera;
};

//************************************************************************

class _tubo : public _triangulos3D
{
public:
  _tubo();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
  _rotacion tubo_abierto; // caña del cañón
};

//************************************************************************
class _tanque : public _triangulos3D
{
public:
  _tanque();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float giro_tubo;
  float giro_torreta;

  float giro_tubo_min;
  float giro_tubo_max;

protected:
  _chasis chasis;
  _torreta torreta;
  _tubo tubo;
};
/**********************************Objeto escavadora********************************************************/
class _base_escavadora : public _triangulos3D
{
public:
  _base_escavadora();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float altura_base;
  float largo_base;
  float ancho_base;
  float altura_rodamiento;

protected:
  _cubo base;
  _rotacion rueda;
  _rotacion rodamiento;
};

class _brazo : public _triangulos3D
{
public:
  _brazo();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
  float giro_segundo_brazo;
  float giro_cazo;

  float largo_brazo;
  float ancho_brazo;
  float alto_brazo;

  float largo_cazo;
  float ancho_cazo;
  float alto_cazo;

protected:
  _cubo tramo_brazo;
};

class _escavadora : public _triangulos3D
{
public:
  _escavadora();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  float giro_base;
  float giro_primer_brazo;
  float giro_segundo_brazo;
  float giro_cazo;
  float pos_pies;

  float altura_motor;
  float altura_cabina;

protected:
  _base_escavadora base;
  _cubo motor;
  _cubo cabina;
  _brazo brazo;
};

//************************************************************************
// clase objeto cono
//************************************************************************

class _esfera : public _triangulos3D
{
private:
  vector<_vertex3f> perfil;
  int longitud;
  int latitud;
  float radio;
  void crearPerfil();
  _imagen *textura;

public:
  _esfera(float radio, int longitud, int latitud);
  void parametros();
  void SetTextura(_imagen &i);
};
