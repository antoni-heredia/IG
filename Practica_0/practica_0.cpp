#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>



void Ejes (int width)
{
    glLineWidth(width); // Tamaño de linea
    glBegin(GL_LINES); //El tipo de objeto qu evamos a pintar, en este caso LINEAS

	   //El eje de x
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-1.0,0.0,0.0);
		glVertex3f(1.0,0.0,0.0);

		//El eje de Y
    	glColor3f(0.0,1.0,0.0);
		glVertex3f(0.0,-1.0,0.0);
		glColor3f(1.0,1.0,0.0); // el ultimo color es el que coje por defecto
		glVertex3f(0.0,1.0,0.0);

	glEnd();


}

// Funciones para visualizar un polígono de distintas formas
void Poligono_Solido (float v[][3], int n)
{
	int i;
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
		for (i=0;i<n;i++) glVertex3f(v[i][0],v[i][1],v[i][2]);
	glEnd();
}

void Poligono_Hueco (float v[][3], int n)
{
	int i;
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
		for (i=0;i<n;i++) glVertex3f(v[i][0],v[i][1],v[i][2]);
	glEnd();
}

void circulo (GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo)
{
	int i;
	if (modo==GL_LINE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (modo==GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	
	glBegin( GL_POLYGON );
	
	for (i=0;i<n;i++)
		glVertex2f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n));
	
	glEnd();
}

float cara_monigote[4][3]={{-0.2,0.0,0.0},{0.2,0.0,0.0},{0.2,0.55,0.0},{-0.2,0.55,0.0}};
float ala_sombrero[4][3] = {{-0.4, 0.55, 0.0},{0.4, 0.55, 0.0}, {0.4, 0.6, 0.0},{-0.4, 0.6, 0.0}};
float sombrero[4][3] = {{-0.22, 0.6, 0.0},{0.22, 0.6, 0.0}, {0.22, 0.8, 0.0},{-0.22, 0.8, 0.0}};
float oreja_izquierda[4][3] ={{-0.27,0.2,0.0},{-0.2,0.2,0.0},{-0.2,0.35,0.0},{-0.27,0.35,0.0}};
float oreja_derecha[4][3] ={{0.2,0.2,0.0},{0.27,0.2,0.0},{0.27,0.35,0.0},{0.2,0.35,0.0}};
float boca[4][3] = {{-0.08,0.05,0.0},{0.08,0.05,0.0},{0.08,0.13,0.0},{-0.08,0.13,0.0}};
float nariz[3][3] = {{-0.07,0.18,0.0},{0.07,0.18,0.0},{0,0.3,0.0}};
void Monigote ()
{

	//pagina web para transformar rgb to glcolor https://openglcolor.mpeters.me/

	// cara
   	glLineWidth(1);
   	glColor3f(1.0,0.8,0.6);
   	Poligono_Solido(cara_monigote,4);
   	Poligono_Solido(oreja_izquierda,4);
	Poligono_Solido(oreja_derecha,4);

	//Nariz
    glColor3f(0.2,0.8,0.0);
	Poligono_Solido(nariz,3);

	//Sombrero
	glColor3f(0.0,0.0,0.0);
	Poligono_Solido(ala_sombrero,4);
	Poligono_Solido(sombrero,4);

	//Ojos
	glColor3f(0.05, 0.27, 0.63);
	circulo(0.05,-0.12,0.39,20,GL_FILL);
	circulo(0.05,0.12,0.39,20,GL_FILL);
	
	//Boca
	glColor3f(0.78, 0.42, 0.11);
   	Poligono_Solido(boca,4);
	circulo(0.04,-0.08,0.09,20,GL_FILL);
	circulo(0.04, 0.08,0.09,20,GL_FILL);

	
	//Contornos
	glColor3f(0.0,0.0,0.);
	Poligono_Hueco(cara_monigote,4);
	Poligono_Hueco(oreja_izquierda,4);
	Poligono_Hueco(oreja_derecha,4);
	Poligono_Hueco(nariz,3);
	circulo(0.05,-0.12,0.39,20,GL_LINE); //contorno de los ojos
	circulo(0.05,0.12,0.39,20,GL_LINE);  //contorno de los ojos


}


static void Init( )
{

   //glShadeModel( GL_FLAT); // GL_FLAT nos pone los poligonos de un solo color
   glShadeModel( GL_SMOOTH); // GL_FLAT nos pone los poligonos de forma suave
}


static void Reshape( int width, int height )
{

    glViewport(0, 0, (GLint)width, (GLint)height); //Transforma segun los valores de la ventana actual

    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0); //para mantener los puntos cartesianos fijos
}

static void Display( )
{

	//Repinta el dibujo cuando vuelve a pasar a primer plano la pantalla

	glClearColor(0.5,0.5,0.5,0.0);
	glClear( GL_COLOR_BUFFER_BIT );



	Ejes(6);
   	Monigote();

   	glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{

  	if (key==27)
    	exit(0);

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 20, 100 );
   glutInitWindowSize(500, 500 );
   glutCreateWindow("Practica 0 IG");


   Init();

   glutReshapeFunc(Reshape); // Para cuando se escale la ventana (desde los bordes)
   glutDisplayFunc(Display); // Para cuando la ventana pase a primer plano
   glutKeyboardFunc(Keyboard); // Cuando se pulse una tecla del teclado

   glutMainLoop( );

   return 0;
}
