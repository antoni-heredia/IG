//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE = 5000;
typedef enum
{
    POINTS,
    EDGES,
    SOLID_CHESS,
    SOLID
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
    void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

    vector<_vertex3i> caras;
};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo : public _triangulos3D
{
  public:
    _cubo(float tam = 0.5);
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
    void parametros(vector<_vertex3f> perfil1, int num1, int tapas);

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



//*************************************************************************
// clase objetoCunia
//*************************************************************************

class _objetoCunia : public _triangulos3D
{
  public:
    _objetoCunia(float tam = 0.5);
};

//*************************************************************************
// clase objetoCunia
//*************************************************************************

class _objetoPeonza : public _triangulos3D
{
  public:
    _objetoPeonza();
    void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
    void crearPerfil();

};

//*************************************************************************
// clase objetoCunia
//*************************************************************************

class _objetoMartillo : public _triangulos3D
{
  public:
    _objetoMartillo();
    void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

    float giro_cubo;
    float giro_martillo;
  
  protected:
    _cubo cubo;
    _rotacion cilindro;

};