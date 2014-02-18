/*	Grua 

	C.A.D. 						Curso 2011-2012
 	
	Codigo base para la realización de las practicas de CAD

	modulo iu.c
	Gestion de interfaz de usuario (menus de persiana e iconos)
=======================================================
	Rafael Garcia Fernandez
	Dpto. Lenguajes y Sistemas Informticos
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


/** Variables de configuracion

**/

int nPalancas=3;

float Palanca[3]={0,0,0};	// Estado de las palancas

/**	void  creaIU()

	Define la interfaz. Creando los menus de persianas e iconos

**/

void  creaIU(){
// ==================== Toolbar
 gluiCreateToolbar();					// Crea el toolbar
    gluiCreateMenu("Opciones", seleccionMenu );		// Crea un menu de persiana   							// añade opciones al menu
	gluiAddMenuEntry("Empezar partida", JUGAR);
    gluiCreateMenu("Tiempo", seleccionMenu);
	gluiAddMenuEntry("Sin limite", NO_TIEMPO);
	gluiAddMenuEntry("5 minutos", TIEMPO1);
	gluiAddMenuEntry("10 minutos", TIEMPO2);
    gluiCreateMenu("Dificultad", seleccionMenu);
	gluiAddMenuEntry("Amateur", AMATEUR);
	gluiAddMenuEntry("Profesional", PRO);
    gluiCreateMenu("Vista", seleccionMenu );
  	gluiAddMenuEntry("3D",PASEAR);
	gluiAddMenuEntry("2D",DESDEARRIBA);
    gluiCreateMenu("Salir", seleccionMenu );
   	glutAddMenuEntry( "Confirmar", SALIR );

 gluiCreateIconMenu( 64); 
// cierra el toolbar y le asocia el botón izquierdo
// y crea el menú de iconos a la derecha de 64x64 pixels

     gluiAddIcon(); 						// Añade un icono
	glutDisplayFunc( drawSeleccionColor);			// Funcion de dibujo del icono
	glutMouseFunc( seleccionColor); 			// Funcion de gestion de eventos del icono

    gluiAddIcon(); 
	glutDisplayFunc( DrawPalancas);
	glutMouseFunc( seleccionaPalancas); 
	glutMotionFunc( muevePalanca );
 
//   gluiInput(entrada);			

 gluiCreateCanvas();

}

/**	void drawSeleccionColor()

Función de dibujo del icono de paleta de colores

**/

void drawSeleccionColor()
/*
	icon draw
*/
{ 
int k;
float x,y;

gluiClearColor();
  // Inicializa el buffer de color
glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

glDisable(GL_LIGHTING);

x=-0.8;
y=-0.8;
for(k=0;k<9;++k){
   glColor3f(color[k][0],color[k][1],color[k][2]);
   glBegin( GL_QUADS );{
      glVertex2f( x, y);
      glVertex2f( x+0.5, y);
      glVertex2f( x+0.5, y+0.5);
      glVertex2f( x, y+0.5); }
   glEnd();
   x+=0.55;
   if(x>0.5) {
	x=-0.8;
	y+=0.55;
	}
    }
 
if(gluiIsMouseOverIcon()) glui_iconFeedback(); 

glutSwapBuffers();
}

/**	void seleccionColor( int boton, int estado, int x, int y)

	Función de gestion de eventos de raton del icono de paleta de colores

	Argumentos:
	boton: Codigo glut del boton que ha manipulado el usuario.
	estado: Estado en el que esta el boton que se ha pulsado.
	x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

	Efecto: Modifica la variable local color
	
**/
void seleccionColor( int boton, int estado, int x, int y)
{
int kx,ky,color;

if(boton== GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
	kx= (x-6)/18;
	ky= (y-6)/18;
	if(kx<0 || ky<0||kx>2||ky>2) return;
	color=kx+(2-ky)*3;

// ------------ Inserta codigo de asignación de color aqui

	gluiPostRedisplay();
	}
}


/** 	void DrawPalancas()

Función de dibujo del icono de

**/

void DrawPalancas()
/*
	icon draw
*/
{
int i;
float x,r,dx;
float pos[4]={10,3,3,1};

gluiClearColor();
  // Inicializa el buffer de color
glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-1,1, -1,1,-4,10);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glEnable(GL_LIGHTING);
glColor3f(0,0,0);
dx= 0.6/(nPalancas+1);
glLightfv( GL_LIGHT0, GL_POSITION, pos );
glEnable( GL_LIGHT0);

glShadeModel(GL_SMOOTH);
for(i=0;i<nPalancas;++i){
	x= 2.0*(i+1)/(nPalancas+1.0)-1.0;
	r=45*Palanca[i];
//	r=-30+30*i;
	glPushMatrix();
	glTranslatef(x,0,0);
	glRotatef(r,1,0,0);
 	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[amarillo] );
        glPushMatrix();
		glRotatef(90,1,0,0);
		falsoCilindro(1,dx/3.0);
	glPopMatrix();
 	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color[rojo] );
	glTranslatef(0,0,1);
	glutSolidSphere(dx,8,4);
	glPopMatrix();
	}
glShadeModel(GL_FLAT);
glDisable(GL_LIGHTING);
if(gluiIsMouseOverIcon()) glui_iconFeedback();
glutSwapBuffers();
}



int kold=-1;	// Identificador de la ultima palanca sobre la que se ha actuado


/**	void seleccionaPalancas( int boton, int estado, int x, int y)

	Función de gestion de eventos de pulsacion de raton del icono de paleta de colores

	Argumentos:
	boton: Codigo glut del boton que ha manipulado el usuario.
	estado: Estado en el que esta el boton que se ha pulsado.
	x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

	Efecto: Modifica el identificador de la ultima palanca usada (kold)
	
**/
void seleccionaPalancas( int boton, int estado, int x, int y)
{
int k;

if(boton== GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
	k= (x/64.0) * (nPalancas+1) -0.5;
	if(k<nPalancas && k>-1) {
		if(k==kold) Palanca[k]= (y-32)/32.0;
		kold=k;
		}
	else k=-1;

/*	if(k==0) 	// velocidad giro grua =Palanca[0];
	else if(k==1)  // velocidad pluma  =Palanca[1];
	else if(k==2) 	// velocidad cuerda =Palanca[2];
*/	
	glutPostRedisplay();
	gluiPostRedisplay();
	}
	else k=-1;
}


/**	void muevePalanca( int x, int y)

	Función de gestion de eventos de movimiento de raton del icono de paleta de colores

	Argumentos:
	x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

	Efecto: Modifica el valor de altura de la ultima palanca usada (kold), que se encuentra
	en Palanca[kold]. El valor esta entre -1 y 1 
	
**/
void muevePalanca( int x, int y)
{
int k;

k= (x/64.0) * (nPalancas+1) -0.5;
if(k<nPalancas && k>-1 && k==kold) {
	Palanca[k]= (y-32)/32.0;
	if(Palanca[k]>1) Palanca[k]= 1;
	if(Palanca[k]<-1) Palanca[k]= -1;
	if(Palanca[k]<0.1 && Palanca[k]>-0.1) Palanca[k]=0;
/*	if(k==0) // velocidad giro grua =Palanca[0];
	else if(k==1) // velocidad pluma  =Palanca[1];
	else if(k==2) // velocidad cuerda =Palanca[2];
*/
	glutPostRedisplay();
	gluiPostRedisplay();
	}
}

