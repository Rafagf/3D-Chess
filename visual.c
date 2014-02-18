/*	AJEDREZ

	C.A.D. 						Curso 2011-2012
 	
	Codigo base para la realización de las practicas de CAD

	modelo visual.c
	Programa principal
=======================================================
	Rafael Garcia Fernández
	(Univ. de Granada, SPAIN)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================
Queda prohibido cobrar canon por la copia de este software

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL
#include "ajedrez.h"


/** 	void transformacionVisualizacion()

Fija la transformacion de visualizacion en funcion de los angulos de rotacion view_rotx,
view_roty y view_rotz y el desplazamiento de la camara d.

**/ 
void transformacionVisualizacion()
{

if(VISTA_PERSPECTIVA){

// Colocar aqui la luz si esta fija respecto del observador
    	glTranslatef(0,0,-1.5);
 	
 	glRotatef( view_rotx, 1.0, 0.0, 0.0 );
   	glRotatef( view_roty, 0.0, 1.0, 0.0 );
//   	glRotatef( view_rotz, 0.0, 0.0, 1.0 );
	
	glTranslatef(-x_camara,-y_camara,-z_camara);
	}
  else 	
  	{
	glTranslatef(-origenXVentanaMundoParalelo,-origenYVentanaMundoParalelo,-40);
   	glRotatef(90,1,0,0);        //@ Transf. para colocar camara arriba
	}
}

/**	void fijaProyeccion()

Fija la transformacion de proyeccion en funcion del tamaño de la ventana y del tipo de proyeccion

**/
void fijaProyeccion()
{
	float calto; 	// altura de la ventana corregida
	
  	if(anchoVentana>0)
  		calto = altoVentana/anchoVentana;
  	else
  		calto = 1;
if(VISTA_PERSPECTIVA)	
	glFrustum(-1,1,-calto,calto,1.5,1500);
else 	
	glOrtho(-ventanaMundoParalela/2, ventanaMundoParalela/2, -ventanaMundoParalela*calto/2, ventanaMundoParalela*calto/2,2,1000);

// A partir de este momento las transformaciones son de modelado.	

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
}


/**	void inicializaVentana(GLsizei ancho,GLsizei alto)

Inicializa el viewport para que ocupe toda la ventana X, y llama a fijaProyeccion.

**/

void inicializaVentana(GLsizei ancho,GLsizei alto)
{
	altoVentana=alto;
	anchoVentana=ancho;

  	glViewport(0,0,ancho,alto);	 // Establecemos el Viewport usando la nueva anchura y altura de la ventana X

  	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	fijaProyeccion();	// Cargamos la transformacion de proyeccion

}


