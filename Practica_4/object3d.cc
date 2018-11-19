/*
* Prácticas de IG
* Copyright Domingo Martín Perandrés 2014-218
* dmartin@ugr.es
*
* GPL 3
*/

#include "object3d.h"

using namespace _colors_ne;

/**
*
*@param
*@returns
*/

void _object3D::draw_line()
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glPolygonOffset(-1,1);
  glBegin(GL_TRIANGLES);
  for (unsigned int i=0;i<Triangles.size();i++){
    glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
    glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
    glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
  }
  glEnd();
}


/**
*
*@param
*@returns
*/

void _object3D::draw_fill()
{

}


/**
*
*@param
*@returns
*/

void _object3D::draw_chess()
{

}


/**
*
*@param
*@returns
*/

void _object3D::draw_illumination_flat_shading()
{

}

/**
*
*@param
*@returns
*/

void _object3D::draw_illumination_smooth_shading()
{

}


/**
*
*@param
*@returns
*/

void _object3D::draw_texture()
{

}

/**
*
*@param
*@returns
*/

void _object3D::draw_texture_illumination_flat_shading()
{
  
}

/**
*
*@param
*@returns
*/

void _object3D::draw_texture_illumination_smooth_shading()
{
  
}


/**
*
*@param
*@returns
*/

void _object3D::compute_triangles_normals()
{

}

/**
*
*@param
*@returns
*/

void _object3D::compute_vertices_normals()
{

}

