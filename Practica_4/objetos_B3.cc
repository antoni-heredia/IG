//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B3.h"

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
	//**** usando vertex_array ****
	glPointSize(grosor);
	glColor3f(r, g, b);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glDrawArrays(GL_POINTS, 0, vertices.size());
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
	//**** usando vertex_array ****
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(grosor);
	glColor3f(r, g, b);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glDrawElements(GL_TRIANGLES, caras.size() * 3, GL_UNSIGNED_INT, &caras[0]);

	/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	int i;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < caras.size(); i++)
	{
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < caras.size(); i++)
	{
		if (i % 2 == 0)
			glColor3f(r1, g1, b1);
		else
			glColor3f(r2, g2, b2);
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

void _triangulos3D::calcular_normales_caras()
{
	normales_caras.resize(caras.size());
	for (int i = 0; i < normales_caras.size(); ++i)
	{
		_vertex3f v1 = vertices[caras[i]._1] - vertices[caras[i]._0];
		_vertex3f v2 = vertices[caras[i]._2] - vertices[caras[i]._1];
		_vertex3f normal = v1.cross_product(v2);

		float modulo = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

		// Normalizacion
		normales_caras[i] = _vertex3f(normal.x / modulo, normal.y / modulo, normal.z / modulo);
	}
}

void _triangulos3D::calcular_normales_vertices()
{
	if (normales_caras.size() != caras.size())
		calcular_normales_caras();

	normales_vertices.resize(vertices.size());

	// Calculas la sumatoria de las normales de las caras
	for (int i = 0; i < caras.size(); ++i)
	{
		normales_vertices[caras[i]._0].x += normales_caras[i].x;
		normales_vertices[caras[i]._0].y += normales_caras[i].y;
		normales_vertices[caras[i]._0].z += normales_caras[i].z;

		normales_vertices[caras[i]._1].x += normales_caras[i].x;
		normales_vertices[caras[i]._1].y += normales_caras[i].y;
		normales_vertices[caras[i]._1].z += normales_caras[i].z;

		normales_vertices[caras[i]._2].x += normales_caras[i].x;
		normales_vertices[caras[i]._2].y += normales_caras[i].y;
		normales_vertices[caras[i]._2].z += normales_caras[i].z;
	}

	// Normaliza el vector
	for (int i = 0; i < normales_vertices.size(); ++i)
	{
		int mod = sqrt(normales_vertices[i].x * normales_vertices[i].x +
					   normales_vertices[i].y * normales_vertices[i].y +
					   normales_vertices[i].z * normales_vertices[i].z);

		normales_vertices[i] = _vertex3f(normales_vertices[i].x / mod,
										 normales_vertices[i].y / mod,
										 normales_vertices[i].z / mod);
	}
}

void _triangulos3D::draw_iluminacion_plana()
{
	if (normales_caras.size() != caras.size())
		calcular_normales_caras();

	glEnable(GL_LIGHTING);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *)&ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++)
	{
		glNormal3fv((GLfloat *)&normales_caras[i]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();

	glDisable(GL_LIGHTING);
}

void _triangulos3D::draw_iluminacion_suave()
{
	if (normales_vertices.size() != vertices.size())
		calcular_normales_vertices();

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *)&ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++)
	{
		glNormal3fv((GLfloat *)&normales_vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glNormal3fv((GLfloat *)&normales_vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glNormal3fv((GLfloat *)&normales_vertices[caras[i]._2]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();

	glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	switch (modo)
	{
	case POINTS:
		draw_puntos(r1, g1, b1, grosor);
		break;
	case EDGES:
		draw_aristas(r1, g1, b1, grosor);
		break;
	case SOLID_CHESS:
		draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);
		break;
	case SOLID:
		draw_solido(r1, g1, b1);
		break;
	case SOLID_ILLUMINATED_FLAT:
		draw_iluminacion_plana();
		break;
	case SOLID_ILLUMINATED_GOURAUD:
		draw_iluminacion_suave();
		using namespace cimg_library;

		break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
	//vertices
	vertices.resize(8);
	vertices[0].x = -tam;
	vertices[0].y = -tam;
	vertices[0].z = tam;
	vertices[1].x = tam;
	vertices[1].y = -tam;
	vertices[1].z = tam;
	vertices[2].x = tam;
	vertices[2].y = tam;
	vertices[2].z = tam;
	vertices[3].x = -tam;
	vertices[3].y = tam;
	vertices[3].z = tam;
	vertices[4].x = -tam;
	vertices[4].y = -tam;
	vertices[4].z = -tam;
	vertices[5].x = tam;
	vertices[5].y = -tam;
	vertices[5].z = -tam;
	vertices[6].x = tam;
	vertices[6].y = tam;
	vertices[6].z = -tam;
	vertices[7].x = -tam;
	vertices[7].y = tam;
	vertices[7].z = -tam;

	// triangulos
	caras.resize(12);
	caras[0]._0 = 0;
	caras[0]._1 = 1;
	caras[0]._2 = 3;
	caras[1]._0 = 3;
	caras[1]._1 = 1;
	caras[1]._2 = 2;
	caras[2]._0 = 1;
	caras[2]._1 = 5;
	caras[2]._2 = 2;
	caras[3]._0 = 5;
	caras[3]._1 = 6;
	caras[3]._2 = 2;
	caras[4]._0 = 5;
	caras[4]._1 = 4;
	caras[4]._2 = 6;
	caras[5]._0 = 4;
	caras[5]._1 = 7;
	caras[5]._2 = 6;
	caras[6]._0 = 0;
	caras[6]._1 = 7;
	caras[6]._2 = 4;
	caras[7]._0 = 0;
	caras[7]._1 = 3;
	caras[7]._2 = 7;
	caras[8]._0 = 3;
	caras[8]._1 = 2;
	caras[8]._2 = 7;
	caras[9]._0 = 2;
	caras[9]._1 = 6;
	caras[9]._2 = 7;
	caras[10]._0 = 0;
	caras[10]._1 = 1;
	caras[10]._2 = 4;
	caras[11]._0 = 1;
	caras[11]._1 = 5;
	caras[11]._2 = 4;
}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

	//vertices
	vertices.resize(5);
	vertices[0].x = -tam;
	vertices[0].y = 0;
	vertices[0].z = tam;
	vertices[1].x = tam;
	vertices[1].y = 0;
	vertices[1].z = tam;
	vertices[2].x = tam;
	vertices[2].y = 0;
	vertices[2].z = -tam;
	vertices[3].x = -tam;
	vertices[3].y = 0;
	vertices[3].z = -tam;
	vertices[4].x = 0;
	vertices[4].y = al;
	vertices[4].z = 0;

	caras.resize(6);
	caras[0]._0 = 0;
	caras[0]._1 = 1;
	caras[0]._2 = 4;
	caras[1]._0 = 1;
	caras[1]._1 = 2;
	caras[1]._2 = 4;
	caras[2]._0 = 2;
	caras[2]._1 = 3;
	caras[2]._2 = 4;
	caras[3]._0 = 3;
	caras[3]._1 = 0;
	caras[3]._2 = 4;
	caras[4]._0 = 3;
	caras[4]._1 = 1;
	caras[4]._2 = 0;
	caras[5]._0 = 3;
	caras[5]._1 = 2;
	caras[5]._2 = 1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply()
{
	// leer lista de coordenadas de vértices y lista de indices de vértices
}

int _objeto_ply::parametros(char *archivo)
{
	int n_ver, n_car;

	vector<float> ver_ply;
	vector<int> car_ply;

	_file_ply::read(archivo, ver_ply, car_ply);

	n_ver = ver_ply.size() / 3;
	n_car = car_ply.size() / 3;

	printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

	//if (n_ver<3 || n_car<1){
	//	printf("Error %d %d\n",__FILE__,__LINE__);
	//	exit(-1);
	//	}

	vertices.resize(n_ver);
	caras.resize(n_car);

	_vertex3f ver_aux;
	_vertex3i car_aux;

	for (int i = 0; i < n_ver; i++)
	{
		ver_aux.x = ver_ply[i * 3];
		ver_aux.y = ver_ply[i * 3 + 1];
		ver_aux.z = ver_ply[i * 3 + 2];
		vertices[i] = ver_aux;
	}

	for (int i = 0; i < n_car; i++)
	{
		car_aux.x = car_ply[i * 3];
		car_aux.y = car_ply[i * 3 + 1];
		car_aux.z = car_ply[i * 3 + 2];
		caras[i] = car_aux;
	}

	return (0);
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)
{
	int i, j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// tratamiento de los vértice

	num_aux = perfil.size();
	vertices.resize(num_aux * num);
	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux; i++)
		{
			vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
							perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
			vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
							perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
			vertice_aux.y = perfil[i].y;
			vertices[i + j * num_aux] = vertice_aux;
		}
	}

	// tratamiento de las caras

	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux - 1; i++)
		{
			cara_aux._0 = i + ((j + 1) % num) * num_aux;
			cara_aux._1 = i + 1 + ((j + 1) % num) * num_aux;
			cara_aux._2 = i + 1 + j * num_aux;
			caras.push_back(cara_aux);

			cara_aux._0 = i + 1 + j * num_aux;
			cara_aux._1 = i + j * num_aux;
			cara_aux._2 = i + ((j + 1) % num) * num_aux;
			caras.push_back(cara_aux);
		}
	}

	// tapa inferior
	if (fabs(perfil[0].x) > 0.0 && tapa == 1)
	{

		vertice_aux.x = 0;
		vertice_aux.y = perfil[0].y;
		vertice_aux.z = 0;
		vertices.push_back(vertice_aux);
		for (j = 0; j < num; j++)
		{
			cara_aux._0 = j * num_aux;
			cara_aux._1 = vertices.size() - 1;
			cara_aux._2 = ((j + 1) % num) * num_aux;
			caras.push_back(cara_aux);
		}
	}

	// tapa superior
	if (fabs(perfil[num_aux - 1].x) > 0.0 && tapa == 1)
	{
		vertice_aux.x = 0;
		vertice_aux.y = perfil[num_aux - 1].y;
		vertice_aux.z = 0;
		vertices.push_back(vertice_aux);
		for (j = 0; j < num; j++)
		{
			cara_aux._0 = (num_aux - 1) + j * num_aux;
			cara_aux._1 = (vertices.size() - 1);
			cara_aux._2 = (num_aux - 1) + ((j + 1) % num) * num_aux;
			caras.push_back(cara_aux);
		}
	}
}

//************************************************************************
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis()
{
	// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x = 0.107;
	aux.y = -0.5;
	aux.z = 0.0;
	perfil.push_back(aux);
	aux.x = 0.107;
	aux.y = 0.5;
	aux.z = 0.0;
	perfil.push_back(aux);
	rodamiento.parametros(perfil, 12, 1);
	altura = 0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glScalef(1.0, 0.22, 0.95);
	base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 1, 0, 0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
	altura = 0.18;
	anchura = 0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glScalef(0.65, 0.18, 0.6);
	base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.325, 0, 0);
	glRotatef(90.0, 0, 0, 1);
	glScalef(0.18, 0.16, 0.6);
	parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
	// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x = 0.04;
	aux.y = -0.4;
	aux.z = 0.0;
	perfil.push_back(aux);
	aux.x = 0.04;
	aux.y = 0.4;
	aux.z = 0.0;
	perfil.push_back(aux);
	tubo_abierto.parametros(perfil, 12, 0);
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

	glPushMatrix();
	glTranslatef(0.4, 0, 0);
	glRotatef(90.0, 0, 0, 1);
	tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

//************************************************************************

_tanque::_tanque()
{
	giro_tubo = 2.0;
	giro_torreta = 0.0;
	giro_tubo_min = -9;
	giro_tubo_max = 20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

	glRotatef(giro_torreta, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0.0, (chasis.altura + torreta.altura) / 2.0, 0.0);
	torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(torreta.anchura / 2.0, (chasis.altura + torreta.altura) / 2.0, 0.0);
	glRotatef(giro_tubo, 0, 0, 1);
	tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
	glPopMatrix();
};

/*********************Clases para la escavadora*************************************/

_base_escavadora::_base_escavadora()
{
	altura_base = 0.2;
	largo_base = 0.8;
	ancho_base = 0.6;
	altura_rodamiento = 0.1;

	// perfil para el rodamiento
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x = ancho_base / 2;
	aux.y = (-altura_rodamiento / 2);
	aux.z = 0.0;
	perfil.push_back(aux);
	aux.x = ancho_base / 2;
	aux.y = (altura_rodamiento / 2);
	aux.z = 0.0;
	perfil.push_back(aux);
	rodamiento.parametros(perfil, 12, 1);

	//perfil para las ruedas
	vector<_vertex3f> perfil2;
	_vertex3f aux2;
	aux2.x = altura_base / 2;
	aux2.y = (-ancho_base / 2) - 0.01;
	aux2.z = 0.0;
	perfil2.push_back(aux2);
	aux2.x = altura_base / 2;
	aux2.y = (ancho_base / 2) + 0.01;
	aux2.z = 0.0;
	perfil2.push_back(aux2);
	rueda.parametros(perfil2, 12, 1);
}

void _base_escavadora::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

	glPushMatrix();
	glScalef(largo_base, altura_base, ancho_base);
	base.brillo = brillo;
	base.ambiente_difusa = ambiente_difusa;
	base.especular = especular;
	base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	rueda.brillo = brillo;
	rueda.ambiente_difusa = ambiente_difusa;
	rueda.especular = especular;

	glPushMatrix();
	glTranslatef(-largo_base / 2, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-largo_base / 4, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(largo_base / 4, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(largo_base / 2, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	rodamiento.brillo = brillo;
	rodamiento.ambiente_difusa = ambiente_difusa;
	rodamiento.especular = especular;
	glPushMatrix();
	glTranslatef(0.0, (altura_base / 2) + (altura_rodamiento / 2), 0.0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

_brazo::_brazo()
{

	giro_segundo_brazo = -45;
	giro_cazo = -45;
	largo_brazo = 0.8;
	ancho_brazo = 0.15;
	alto_brazo = 0.3;

	largo_cazo = 0.2;
	ancho_cazo = 0.6;
	alto_cazo = 0.4;
}

void _brazo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	tramo_brazo.brillo = brillo;
	tramo_brazo.ambiente_difusa = ambiente_difusa;
	tramo_brazo.especular = especular;

	glPushMatrix();
	glScalef(largo_brazo, alto_brazo, ancho_brazo);
	tramo_brazo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(largo_brazo / 2, 0, 0);
	glRotatef(giro_segundo_brazo, 0, 0, 1);

	glPushMatrix();
	glScalef(largo_brazo, alto_brazo, ancho_brazo);
	glTranslatef(largo_brazo / 2, 0, 0);
	tramo_brazo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(largo_brazo - 0.1, 0, 0);
	glRotatef(giro_cazo, 0, 0, 1);
	glTranslatef((largo_cazo / 2), -alto_cazo / 2, 0);
	glScalef(largo_cazo, alto_cazo, ancho_cazo);
	tramo_brazo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPopMatrix();
}

_escavadora::_escavadora()
{
	altura_motor = 0.2;
	altura_cabina = 0.4;
	giro_primer_brazo = 45;
}

void _escavadora::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

	glPushMatrix();
	base.brillo = brillo;
	base.ambiente_difusa = ambiente_difusa;
	base.especular = especular;
	base.draw(modo, 1.0, 0.01, 0.01, 0.0, 0.0, 0.0, grosor);

	glRotatef(giro_base, 0, 1, 0);

	motor.brillo = brillo;
	motor.ambiente_difusa = ambiente_difusa;
	motor.especular = especular;

	glPushMatrix();
	glTranslatef(0, (base.altura_base / 2) + base.altura_rodamiento + (altura_motor / 2), 0.0);
	glScalef(base.largo_base, altura_motor, base.ancho_base);
	motor.draw(modo, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, grosor);
	glPopMatrix();

	cabina.brillo = brillo;
	cabina.ambiente_difusa = ambiente_difusa;
	cabina.especular = especular;

	glPushMatrix();
	glTranslatef((base.largo_base / 3), (base.altura_base / 2) + base.altura_rodamiento + (altura_cabina / 2), -(base.ancho_base / 4) - 0.01);
	glScalef(base.largo_base / 2, altura_cabina, base.ancho_base / 2);
	cabina.draw(modo, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, grosor);
	glPopMatrix();

	glTranslatef((base.largo_base - 0.5), (base.altura_base / 2) + base.altura_rodamiento + (altura_cabina / 2), (base.ancho_base / 3) - 0.01);
	glRotatef(giro_primer_brazo, 0, 0, 1);
	glTranslatef(0.4, 0, 0);
	glPushMatrix(); //brazo entero

	brazo.brillo = brillo;
	brazo.ambiente_difusa = ambiente_difusa;
	brazo.especular = especular;

	brazo.giro_cazo = giro_cazo;
	brazo.giro_segundo_brazo = giro_segundo_brazo;
	brazo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

	glPopMatrix(); //brazo entero

	glPopMatrix();
}

_esfera::_esfera(float radio2, int longitud2, int latitud2)
{

	radio = radio2;
	longitud = longitud2;
	latitud = latitud2 * 2;
	crearPerfil();
	parametros();
}

void _esfera::crearPerfil()
{
	_vertex3f vertice_aux;
	for (int i = (-latitud / 4) + 1; i < (latitud / 4); i++)
	{
		vertice_aux.x = radio * cos(2 * M_PI * i / latitud);
		vertice_aux.y = radio * sin(2 * M_PI * i / latitud);
		vertice_aux.z = 0;
		perfil.push_back(vertice_aux);
	}
}

void _esfera::parametros()
{
	int i, j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// tratamiento de los vértice

	num_aux = perfil.size();
	vertices.resize(num_aux * longitud);
	for (j = 0; j < longitud; j++)
	{
		for (i = 0; i < num_aux; i++)
		{

			vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * longitud)) +
							perfil[i].z * sin(2.0 * M_PI * j / (1.0 * longitud));

			vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * longitud)) +
							perfil[i].z * cos(2.0 * M_PI * j / (1.0 * longitud));
			vertice_aux.y = perfil[i].y;

			vertices[i + j * num_aux] = vertice_aux;
		}
	}

	// tratamiento de las caras

	for (j = 0; j < longitud; j++)
	{
		for (i = 0; i < num_aux - 1; i++)
		{
			cara_aux._0 = i + ((j + 1) % longitud) * num_aux;
			cara_aux._1 = i + 1 + ((j + 1) % longitud) * num_aux;
			cara_aux._2 = i + 1 + j * num_aux;
			caras.push_back(cara_aux);

			cara_aux._0 = i + 1 + j * num_aux;
			cara_aux._1 = i + j * num_aux;
			cara_aux._2 = i + ((j + 1) % longitud) * num_aux;
			caras.push_back(cara_aux);
		}
	}

	// tapa inferior
	if (fabs(perfil[0].x) > 0.0)
	{
		vertice_aux.x = 0;
		vertice_aux.y = -radio;
		vertice_aux.z = 0;
		vertices.push_back(vertice_aux);
		for (j = 0; j < longitud; j++)
		{
			cara_aux._0 = j * num_aux;
			cara_aux._1 = vertices.size() - 1;
			cara_aux._2 = ((j + 1) % longitud) * num_aux;
			caras.push_back(cara_aux);
		}
	}
	// tapa superior
	if (fabs(perfil[num_aux - 1].x) > 0.0)
	{
		vertice_aux.x = 0;
		vertice_aux.y = radio;
		vertice_aux.z = 0;
		vertices.push_back(vertice_aux);
		for (j = 0; j < longitud; j++)
		{
			cara_aux._2 = (num_aux - 1) + j * num_aux;
			cara_aux._1 = (vertices.size() - 1);
			cara_aux._0 = (num_aux - 1) + ((j + 1) % longitud) * num_aux;
			caras.push_back(cara_aux);
		}
	}
}

_imagen::_imagen()
{
}

void _imagen::Load(const char path[])
{
	std::vector<unsigned char> data;

	CImg<unsigned char> logo;
	logo.load(path);

	// empaquetamos bien los datos
	for (long y = 0; y < logo.height(); y++)
		for (long x = 0; x < logo.width(); x++)
		{
			unsigned char *r = logo.data(x, y, 0, 0);
			unsigned char *g = logo.data(x, y, 0, 1);
			unsigned char *b = logo.data(x, y, 0, 2);
			data.push_back(*r);
			data.push_back(*g);
			data.push_back(*b);
		}

	glGenTextures(1, &textura_id);
	glBindTexture(GL_TEXTURE_2D, textura_id);

	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// TRASFIERE LOS DATOS A GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo.width(), logo.height(),
				 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}


void _imagen::draw()
{
	GLfloat vertices[] = {
		-0.5, 0.0, 0.5,   0.5, 0.0, 0.5,   0.5, 1.0, 0.5,  -0.5, 1.0, 0.5,
		-0.5, 1.0, -0.5,  0.5, 1.0, -0.5,  0.5, 0.0, -0.5, -0.5, 0.0, -0.5,
		0.5, 0.0, 0.5,   0.5, 0.0, -0.5,  0.5, 1.0, -0.5,  0.5, 1.0, 0.5,
		-0.5, 0.0, -0.5,  -0.5, 0.0, 0.5,  -0.5, 1.0, 0.5, -0.5, 1.0, -0.5
  };
  GLfloat texVertices[] = {
		0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
		0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
		0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
		0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0
  };

   GLubyte cubeIndices[24] = {0,1,2,3, 4,5,6,7, 3,2,5,4, 7,6,1,0,
                                  8,9,10,11, 12,13,14,15};
   glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textura_id);
      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glColor3f(1.0f, 1.0f, 1.0f);

      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glEnableClientState(GL_VERTEX_ARRAY);

      glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
      glVertexPointer(3, GL_FLOAT, 0, vertices);

      glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
      glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
}

void _imagen::draw_portatil()
{
	GLfloat vertices[] = {	0.5,0,0, 
							0.5,0.5,0,
							-0.5,0.5,0,
							-0.5,0,0,
							-0.5,0,0.5,
							0.5,0,0.5,


							
							  };
  GLfloat texVertices[] = {	1,0.5,
  						   	1,0,
							0,0,
							0,0.5,
							0,1,
							1,1};
GLubyte cubeIndices[8] = {	0,1,2,3,
							0,3,4,5
							};

   glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textura_id);
      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glColor3f(1.0f, 1.0f, 1.0f);

      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glEnableClientState(GL_VERTEX_ARRAY);

      glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
      glVertexPointer(3, GL_FLOAT, 0, vertices);

      glDrawElements(GL_QUADS, 8, GL_UNSIGNED_BYTE, cubeIndices);
      glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
}
void _imagen::draw_skybox()
{

GLfloat vertices[] = { 	1,1,0, 1,1,1, 0,1,1,  0,1,0,
								0,0,0, 0,1,1, 0,0,1,
								1,0,0,
								1,0,1, 1,1,1,
								0,0,1, 0,1,1,
								1,0,1, 0,0,1};

GLfloat texVertices[] = {	0.5,0.33, 0.5,0, 0.25,0, 0.25,0.33,
  							0.25,0.66, 0,0.33, 0,0.66,
							0.5,0.66,
							0.75,0.66, 0.75,0.33,
							1,0.66, 1,0.33,
							0.5,0.99, 0.25,0.99};
GLubyte cubeIndices[24] = {	0,1,2,3,
							4,3,5,6,
							7,0,3,4,
							8,9,0,7,
							10,11,9,8,
							12,7,4,13};

   glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textura_id);
      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glColor3f(1.0f, 1.0f, 1.0f);

      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glEnableClientState(GL_VERTEX_ARRAY);

      glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
      glVertexPointer(3, GL_FLOAT, 0, vertices);

      glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
      glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
}

void _imagen::draw_piramide()
{

GLfloat vertices[] = { 	0,1,0, 0.5,0,0.5,  -0.5,0,0.5,
						0,1,0, -0.5,0,0.5,  -0.5,0,-0.5,
						0,1,0, -0.5,0,-0.5, 0.5,0,-0.5,
						0,1,0, 0.5,0,-0.5, -0.5,0,0.5};

GLfloat texVertices[] = {	0.5,0, 0,1, 1,1,
							0.5,0, 0,1, 1,1,
							0.5,0, 0,1, 1,1,
							0.5,0, 0,1, 1,1
						};
GLubyte cubeIndices[18] = {	0,1,2, 0,2,3, 0,3,4, 0,4,1};

   glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textura_id);
      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glColor3f(1.0f, 1.0f, 1.0f);

      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glEnableClientState(GL_VERTEX_ARRAY);

      glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
      glVertexPointer(3, GL_FLOAT, 0, vertices);

      glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, cubeIndices);
      glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
}

void _imagen::libera()
{
	glDeleteTextures(1, &textura_id);
}