/*	AJEDREZ

	C.A.D. 						Curso 2011-2012
 	
	Codigo base para la realización de las practicas de CAD

	modulo entradaTeclado.c
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

/** 

Imprime en la consola las instrucciones del programa

**/
void printHelp(){
  	
	printf("\n\n                        C.A.D. 		Curso 2011-2012");
 
 // Anyade la informacion de las opciones que introduzcas aqui !! 	
	
	printf("\n Escape: Salir");
  	printf("\n\n\n");
}




/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)

Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra

Para anyadir nuevas ordenes de teclado coloca el correspondiente case.

Parametros de entrada:

k: codigo del caracter pulsado

x:

y:

**/

void letra (unsigned char k, int x, int y)
{
  switch (k) {
  case 'h':
  case 'H':
           printHelp(); // H y h imprimen ayuda
  	break;
  case '3':
	VISTA_PERSPECTIVA= 1; 
	estado= paseando;
	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
	fijaProyeccion();
	break;
  case '2':
	VISTA_PERSPECTIVA= 0;
	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
	fijaProyeccion();
	break;
  case 'x':	// desplaza la camara en X
     if(VISTA_PERSPECTIVA) x_camara -= 5.0;   
     else origenXVentanaMundoParalelo-=5;
    break;
  case 'X':
     if(VISTA_PERSPECTIVA) x_camara += 5.0;   
     else origenXVentanaMundoParalelo+=5;
    break;
  case 'z':	// desplaza la camara en Z
     if(VISTA_PERSPECTIVA) z_camara -= 5.0;   
     else origenYVentanaMundoParalelo-=5;
    break;
  case 'Z':
    if(VISTA_PERSPECTIVA) z_camara += 5.0;   
    else origenYVentanaMundoParalelo+=5;
    break;
	case 'Y':	//Para modificar la camara en Y
		if(VISTA_PERSPECTIVA) y_camara += 1.0;
		else origenYVentanaMundoParalelo -=1;
		break;
	case 'y':
		if(VISTA_PERSPECTIVA) y_camara -= 1.0;
		else origenYVentanaMundoParalelo +=1;
		break;
  case '+':             // + Camara mas cerca
    if(ventanaMundoParalela>10) ventanaMundoParalela = ventanaMundoParalela*0.75;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    fijaProyeccion();
    break;
  case '-':             // - Camara mas lejos
    ventanaMundoParalela =ventanaMundoParalela* 1.25;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    fijaProyeccion();
    break;
  case 27:  // Escape  Terminar
    exit(0);
    break;  
  default:
    return;
  }
glutPostRedisplay();  	// Algunas de las opciones cambian paramentros
}                       // de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes

Parametros de entrada:

k: codigo del caracter pulsado (definido en glut mediante constantes).

x:

y:

**/
void especial(int k, int x, int y)

{
  switch (k) {
  case GLUT_KEY_UP:
    if(VISTA_PERSPECTIVA)     view_rotx += 5.0;   // Cursor arriba + rotacion x
    break;
  case GLUT_KEY_DOWN:
    if(VISTA_PERSPECTIVA)    view_rotx -= 5.0;
    break;
  case GLUT_KEY_LEFT:
    if(VISTA_PERSPECTIVA) {
	view_roty += 5.0;
    	if(view_roty>360) view_roty-=360;
	}
    break;
  case GLUT_KEY_RIGHT:
    if(VISTA_PERSPECTIVA) {
    	view_roty -= 5.0;
    	if(view_roty<0) view_roty+=360;
	}
    break;
  case GLUT_KEY_PAGE_DOWN:  	// Avanza en la direccion en la que se mira
     if(VISTA_PERSPECTIVA) {
     	x_camara+=-sin(3.14159*view_roty/180.0);
     	z_camara+= cos(3.14159*view_roty/180.0);
	}
     break;
  case GLUT_KEY_PAGE_UP:
    if(VISTA_PERSPECTIVA) {
     	x_camara+= sin(3.14159*view_roty/180.0);
     	z_camara+=-cos(3.14159*view_roty/180.0);
	}
     break;
  default:
    return;
  }
   glutPostRedisplay();  // Actualiza la imagen (ver proc. letra)
}
 
