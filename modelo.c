/*	AJEDREZ

	C.A.D. 						Curso 2011-2012
 	
	Codigo base para la realización de las practicas de CAD

	modulo ajedrez.c
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

#define __modelo__			// Hace que se asigne memoria a las variables globales

#include "ajedrez.h"


int COLORTABLERO=0;


/**	void initModel()

Inicializa el modelo y de las variables globales

**/

void initModel()
{
/**
	Definicion de los colores usados.
**/
float colores[11][4]={{1,1,0,1.},{0.7,0.7,0.7,1},{1.0,0.3,0.3,1},
   		   {0.7,0.6,0.2,1},{0.2,1.0,1.0,1},{1.0,0.86,0.3,1},
		   {0.4,1,0.4,1.},{1,0.6,1,1.},{0,0,1,1.},{0.9,0.9,0.9,1},{0.20,0.20,0.20,1}};
int i,j;
	for(i=0;i<4;++i)
		for(j=0;j<11;++j)
			color[j][i]=colores[j][i];

	COLORTABLERO=0;

	color_original = negro;

/**
	Otros parametros
**/

	turno_jugador = 0; //0 negras 1 blancas

	comida_negrax = 6.25*4 + 6.25/2;
	comida_negraz = -6.25*3 - 6.25/2;

	comida_blancax = -6.25*4 - 6.25/2;
	comida_blancaz = 6.25*3 + 6.25/2;

	tiempo_jugador1 = 12000; //25 segundos por cada 1000
	tiempo_jugador2 = 12000;

	modo_tiempo = 1;
	modo_dificultad = 0;

/** 

Parametros iniciales de la camara

**/
	view_rotx=46.5;	// Angulos de rotacion 
	view_roty=-180;
	view_rotz=0.0;
	d=100.0;

	x_camara=0;		// Posicion de la camara [MODIFICADO]
	y_camara=58;		//[MODIFICADO] 20 para verlo bien
	z_camara=-61;		//[MODIFICADO] //-56 negra

	VISTA_PERSPECTIVA=1;	// Flag perspectiva/paralela

	ventanaMundoParalela=200;	// Ventana para proyeccion paralela
	origenXVentanaMundoParalelo=0;	
	origenYVentanaMundoParalelo=0;


/** 

Parametros de las casillas

**/
	int cont_aux = 0;
	int c = 0;
	int aux_c1 = 4;
	int aux_c2 = 1;	
	int colcas = 4;
	int aux_posz = 15.625;
	int aux_corx = 3;
	int aux_corz = 3;

	for(c; c < 64; c++){	

		casillas[c].dimbase = 6.25;
		casillas[c].dimaltura = 2;
		casillas[c].dimfondo = 6.25;
		
		if((c >= 0 && c <= 15) || (c >= 48 && c < 64)) 

			casillas[c].estado = 1; //ocupadas
		
		else

			casillas[c].estado = 0;

		casillas[c].poscasillax = casillas[c].dimbase*aux_corx + casillas[c].dimbase/2;
		casillas[c].poscasillaz = -casillas[c].dimbase*aux_corz -casillas[c].dimbase/2;
		casillas[c].altura = 2;
		casillas[c].color = colcas;


		if(colcas == aux_c1)

			colcas = aux_c2;

		else

			colcas = aux_c1;

		cont_aux++;
		aux_corx--;

		if(cont_aux == 8){

			cont_aux = 0;
			aux_corx = 3;
			aux_corz = aux_corz - 1;

			if(colcas == aux_c1)

				colcas = aux_c2;

			else

				colcas = aux_c1;

		}
	}	



/**

Parametros iniciales de las piezas

**/

	//Negras

	piezas[0].pospiezax = 6.25*3 + 6.25/2;
	piezas[0].pospiezay = -6.25*3 - 6.25/2;
	piezas[0].altura = 4.2;
	piezas[0].color = negro;
	piezas[0].tipo = 't';
	piezas[0].sobre_casilla = 40;

	piezas[1].pospiezax = 6.25*2 + 6.25/2;
	piezas[1].pospiezay = -6.25*3 - 6.25/2;
	piezas[1].altura = 4.2;
	piezas[1].color = negro;
	piezas[1].tipo = 'c';
	piezas[1].sobre_casilla = 41;

	piezas[2].pospiezax = 6.25 +6.25/2;
	piezas[2].pospiezay = -6.25*3 - 6.25/2;
	piezas[2].altura = 4.2;
	piezas[2].color = negro;
	piezas[2].tipo = 'a';
	piezas[2].sobre_casilla = 42;	

	piezas[3].pospiezax = 6.25/2;
	piezas[3].pospiezay = -6.25*3 - 6.25/2;
	piezas[3].altura = 4.2;
	piezas[3].color = negro;
	piezas[3].tipo = 'k';
	piezas[3].sobre_casilla = 43;

	piezas[4].pospiezax = -6.25/2;
	piezas[4].pospiezay = -6.25*3 -6.25/2;
	piezas[4].altura = 4.2;
	piezas[4].color = negro;
	piezas[4].tipo = 'q';
	piezas[4].sobre_casilla = 44;

	piezas[5].pospiezax = -6.25 - 6.25/2;
	piezas[5].pospiezay = -6.25*3 -6.25/2;
	piezas[5].altura = 4.2;
	piezas[5].color = negro;
	piezas[5].tipo = 'a';
	piezas[5].sobre_casilla = 45;

	piezas[6].pospiezax = -6.25*2 - 6.25/2;
	piezas[6].pospiezay = -6.25*3 - 6.25/2;
	piezas[6].altura = 4.2;
	piezas[6].color = negro;
	piezas[6].tipo = 'c';
	piezas[6].sobre_casilla = 46;

	piezas[7].pospiezax = -6.25*3 -6.25/2;
	piezas[7].pospiezay = -6.25*3 -6.25/2;
	piezas[7].altura = 4.2;
	piezas[7].color = negro;
	piezas[7].tipo = 't';
	piezas[7].sobre_casilla = 47;

	int h;	

	for(h = 0; h < 8; h++){

		piezas[8+h].pospiezax = 6.25*(3-h) + 6.25/2;
		piezas[8+h].pospiezay = -6.25*2 - 6.25/2;
		piezas[8+h].altura = 4.2;
		piezas[8+h].color = negro;
		piezas[8+h].tipo = 'p';
		piezas[8+h].sobre_casilla = 48+h;

	}

	//Blancas

	piezas[16].pospiezax = 6.25*3 + 6.25/2;
	piezas[16].pospiezay = 6.25*3 + 6.25/2;
	piezas[16].altura = 4.2;
	piezas[16].color = blanco;
	piezas[16].tipo = 't';
	piezas[16].sobre_casilla = 96;

	piezas[17].pospiezax = 6.25*2 + 6.25/2;
	piezas[17].pospiezay = 6.25*3 + 6.25/2;
	piezas[17].altura = 4.2;
	piezas[17].color = blanco;
	piezas[17].tipo = 'c';
	piezas[17].sobre_casilla = 97;

	piezas[18].pospiezax = 6.25 +6.25/2;
	piezas[18].pospiezay = 6.25*3 + 6.25/2;
	piezas[18].altura = 4.2;
	piezas[18].color = blanco;
	piezas[18].tipo = 'a';
	piezas[18].sobre_casilla = 98;
	
	piezas[19].pospiezax = 6.25/2;
	piezas[19].pospiezay = 6.25*3 + 6.25/2;
	piezas[19].altura = 4.2;
	piezas[19].color = blanco;
	piezas[19].tipo = 'q';
	piezas[19].sobre_casilla = 99;

	piezas[20].pospiezax = -6.25/2;
	piezas[20].pospiezay = 6.25*3 + 6.25/2;
	piezas[20].altura = 4.2;
	piezas[20].color = blanco;
	piezas[20].tipo = 'k';
	piezas[20].sobre_casilla = 100;

	piezas[21].pospiezax = -6.25 - 6.25/2;
	piezas[21].pospiezay = 6.25*3 + 6.25/2;
	piezas[21].altura = 4.2;
	piezas[21].color = blanco;
	piezas[21].tipo = 'a';
	piezas[21].sobre_casilla = 101;

	piezas[22].pospiezax = -6.25*2 - 6.25/2;
	piezas[22].pospiezay = 6.25*3 + 6.25/2;
	piezas[22].altura = 4.2;
	piezas[22].color = blanco;
	piezas[22].tipo = 'c';
	piezas[22].sobre_casilla = 102;

	piezas[23].pospiezax = -6.25*3 - 6.25/2;
	piezas[23].pospiezay = 6.25*3 + 6.25/2;
	piezas[23].altura = 4.2;
	piezas[23].color = blanco;
	piezas[23].tipo = 't';
	piezas[23].sobre_casilla = 103;

	for(h = 0; h < 8; h++){

		piezas[24+h].pospiezax = 6.25*(3-h) + 6.25/2;
		piezas[24+h].pospiezay = 6.25*2 + 6.25/2;
		piezas[24+h].altura = 4.2;
		piezas[24+h].color = blanco;
		piezas[24+h].tipo = 'p';
		piezas[24+h].sobre_casilla = 88+h;

	}

}

/**	void dibujarRey()

Dibuja un rey en el tablero

**/

void dibujarRey(int c){


	glPushMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //base
	glTranslatef(0, 0, 0);
	caja(4, 0.6, 4);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.6, 0);
	caja(2.5, 1, 2.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 1, 0);
	caja(2.5, 3.5, 2.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza intermedia
	glTranslatef(0, 3.5, 0);
	caja(3.5, 0.5, 3.5);	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.5, 0);
	caja(2.5, 1.5, 2.5);	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 1.5, 0);
	caja(3.5, 0.5, 3.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cruz vertical
	glTranslatef(0, 0.5, 0);
	caja(1, 3, 1);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cruz horizontal
	glTranslatef(0, 1.25, 0);
	caja(3, 1, 1);

	glTranslatef(0, -8.85, 0);

	glPopMatrix();

}

/**	void dibujarReina()

Dibuja una reina en el tablero

**/

void dibujarReina(int c){

	glPushMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //base
	glTranslatef(0, 0, 0);
	caja(4, 0.6, 4);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.6, 0);
	caja(2.5, 1, 2.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 1, 0);
	caja(2.5, 3.5, 2.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza intermedia
	glTranslatef(0, 3.5, 0);
	caja(3.5, 0.5, 3.5);	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.5, 0);
	caja(2.5, 1.5, 2.5);	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 1.5, 0);
	caja(3.5, 0.5, 3.5);	

	glTranslatef(0, -7.1, 0); 

	glPopMatrix();

}

/**	void dibujarCaballo()

Dibuja un caballo en el tablero

**/

void dibujarCaballo(int c){

	glPushMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //base
	glTranslatef(0, 0, 0);
	caja(4, 0.6, 4);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.6, 0);
	caja(2.5, 1, 2.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 1, 0);
	caja(3, 2.5, 3);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0.75, 2.5, 0);
	caja(1.75, 1.5, 1.75);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(-0.9, 1.5, 0);
	caja(3, 1.5, 3);

	glTranslatef(0.15, -5.4, 0);

	glPopMatrix();

}

/**	void dibujarAlfil()

Dibuja un alfil en el tablero

**/

void dibujarAlfil(int c){

	glPushMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //base
	glTranslatef(0, 0, 0);
	caja(4, 0.7, 4);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.7, 0);
	caja(2.5, 0.5, 2.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2.2, 0.5, 2.2);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(1.9, 0.5, 1.9);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(1.6, 0.5, 1.6);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(1.3, 0.5, 1.2);


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.25, 0);
	caja(1.4, 0.25, 1.4);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.25, 0);
	caja(1.5, 0.25, 1.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.25, 0);
	caja(1.6, 0.25, 1.6);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza intermedia
	glTranslatef(0, 0.25, 0);
	caja(2.5, 0.25, 2.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza intermedia
	glTranslatef(0, 0.25, 0);
	caja(2.1, 0.25, 2.1);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza intermedia
	glTranslatef(0, 0.25, 0);
	caja(2, 0.25, 2);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza intermedia
	glTranslatef(0, 0.25, 0);
	caja(1.9, 0.25, 1.9);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza intermedia
	glTranslatef(0, 0.25, 0);
	caja(1.8, 0.25, 1.8);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.25, 0);
	caja(2, 0.25, 1.9);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.25, 0);
	caja(2.2, 0.25, 2);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.25, 0);
	caja(2.4, 0.25, 2.1);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.25, 0);
	caja(2.6, 0.25, 2.2);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.25, 0);
	caja(2.4, 0.25, 2.1);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.25, 0);
	caja(2.2, 0.25, 2);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.25, 0);
	caja(2, 0.25, 1.9);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.25, 0);
	caja(1.8, 0.25, 1.8);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.25, 0);
	caja(0.8, 0.3, 1.9);


	glTranslatef(0, -7.2, 0);

	glPopMatrix();

}

/**	void dibujarTorre()

Dibuja una torre en el tablero

**/

void dibujarTorre(int c){

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //base
	glTranslatef(0, 0, 0);
	caja(4, 1.5, 4);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 1.5, 0);
	caja(3, 0.5, 3);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2.9, 0.5, 2.9);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2.8, 0.5, 2.8);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2.7, 0.5, 2.7);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2.6, 0.5, 2.6);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2.5, 0.5, 2.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2.4, 0.5, 2.4);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.5, 0);
	caja(2.3, 0.5, 2.3);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2.2, 0.5, 2.2);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2.1, 0.5, 2.1);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2, 0.5, 2);	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza
	glTranslatef(0, 0.5, 0);
	caja(3, 1.5, 3);

	glTranslatef(0, -7, 0); //Restablecemos la altura

	glPopMatrix();

}

/**	void dibujarPeon()

Dibuja un peon en el tablero

**/


void dibujarPeon(int c){

	glPushMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //base
	glTranslatef(0, 0, 0);
	caja(3.3, 0.7, 3.3);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.7, 0);
	caja(2.5, 0.5, 2.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(2.2, 0.5, 2.2);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(1.9, 0.5, 1.9);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(1.6, 0.5, 1.6);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cuerpo
	glTranslatef(0, 0.5, 0);
	caja(1.3, 0.5, 1.3);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza intermedia
	glTranslatef(0, 0.5, 0);
	caja(2.1, 0.5, 2.1);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza 
	glTranslatef(0, 0.5, 0);
	caja(1.5, 0.15, 1.5);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza 
	glTranslatef(0, 0.15, 0);
	caja(1.7, 0.15, 1.7);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza 
	glTranslatef(0, 0.15, 0);
	caja(1.9, 0.15, 1.9);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza 
	glTranslatef(0, 0.15, 0);
	caja(2.1, 0.15, 2.1);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza 
	glTranslatef(0, 0.15, 0);
	caja(1.9, 0.15, 1.9);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza 
	glTranslatef(0, 0.15, 0);
	caja(1.7, 0.15, 1.7);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[c]); //cabeza 
	glTranslatef(0, 0.15, 0);
	caja(1.5, 0.15, 1.5);

	glTranslatef(0, -4.6, 0); //Restablecemos altura

	glPopMatrix();

}

/**	void posicionarPiezas

Se encarga del dibujo y posicionamiento de las piezas en el tablero

**/

void posicionarPiezas(){


	int i = 1;
	
	glPushMatrix();
	glLoadName(i);
	glTranslatef(piezas[0].pospiezax, piezas[0].altura, piezas[0].pospiezay);
	dibujarTorre(piezas[0].color);
	glPopMatrix();
	i++;
	
	glPushMatrix();
	glLoadName(i);
	glTranslatef(piezas[1].pospiezax, piezas[1].altura, piezas[1].pospiezay);
	dibujarCaballo(piezas[1].color);
	glPopMatrix();
	i++;


	glPushMatrix();
	glLoadName(i);
	glTranslatef(piezas[2].pospiezax, piezas[2].altura, piezas[2].pospiezay);
	dibujarAlfil(piezas[2].color);
	glPopMatrix();
	i++;


	glPushMatrix();
	glLoadName(i);
	glTranslatef(piezas[3].pospiezax, piezas[3].altura, piezas[3].pospiezay);
	dibujarRey(piezas[3].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glLoadName(i);
	glTranslatef(piezas[4].pospiezax, piezas[4].altura, piezas[4].pospiezay);
	dibujarReina(piezas[4].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glLoadName(i);
	glTranslatef(piezas[5].pospiezax, piezas[5].altura, piezas[5].pospiezay);
	dibujarAlfil(piezas[5].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glLoadName(i);
	glTranslatef(piezas[6].pospiezax, piezas[6].altura, piezas[6].pospiezay);
	dibujarCaballo(piezas[6].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glLoadName(i);
	glTranslatef(piezas[7].pospiezax, piezas[7].altura, piezas[7].pospiezay);
	dibujarTorre(piezas[7].color);
	glPopMatrix();
	i++;

	int j;	

	for(j = 0; j < 8; j++){
	
		glPushMatrix();
		glLoadName(i);
		glTranslatef(piezas[8+j].pospiezax, piezas[8+j].altura, piezas[8+j].pospiezay);
		if(piezas[8+j].tipo == 'p')

			dibujarPeon(piezas[8+j].color);

		else

			dibujarReina(piezas[8+j].color);	
		
		glPopMatrix();
		i++;
		
	}

	//Blancas
	
	glPushMatrix();
	glTranslatef(piezas[i-1].pospiezax, piezas[i-1].altura, piezas[i-1].pospiezay);
	glLoadName(i);
	dibujarTorre(piezas[i-1].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glTranslatef(piezas[i-1].pospiezax, piezas[i-1].altura, piezas[i-1].pospiezay);
	glLoadName(i);
	dibujarCaballo(piezas[i-1].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glTranslatef(piezas[i-1].pospiezax, piezas[i-1].altura, piezas[i-1].pospiezay);
	glLoadName(i);
	dibujarAlfil(piezas[i-1].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glTranslatef(piezas[i-1].pospiezax, piezas[i-1].altura, piezas[i-1].pospiezay);
	glLoadName(i);
	dibujarReina(piezas[i-1].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glTranslatef(piezas[i-1].pospiezax, piezas[i-1].altura, piezas[i-1].pospiezay);
	glLoadName(i);
	dibujarRey(piezas[i-1].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glTranslatef(piezas[i-1].pospiezax, piezas[i-1].altura, piezas[i-1].pospiezay);
	glLoadName(i);
	dibujarAlfil(piezas[i-1].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glTranslatef(piezas[i-1].pospiezax, piezas[i-1].altura, piezas[i-1].pospiezay);
	glLoadName(i);
	dibujarCaballo(piezas[i-1].color);
	glPopMatrix();
	i++;

	glPushMatrix();
	glTranslatef(piezas[i-1].pospiezax, piezas[i-1].altura, piezas[i-1].pospiezay);
	glLoadName(i);
	dibujarTorre(piezas[i-1].color);
	glPopMatrix();
	i++;

	for(j = 0; j < 8; j++){
	
		glPushMatrix();
		glLoadName(i);
		glTranslatef(piezas[24+j].pospiezax, piezas[24+j].altura, piezas[24+j].pospiezay);
		
		if(piezas[24+j].tipo == 'p'){

			dibujarPeon(piezas[24+j].color);

		}

		else{

			dibujarReina(piezas[24+j].color);

		}
		glPopMatrix();
		i++;
		
	}
}

/**	void posicionarCasillas

Se encarga del dibujo y posicionamiento de las casillas en el tablero

**/

void posicionarCasillas(){

	int i = 40;
	
	for(i; i < 104; i++){

		glPushMatrix();
		glLoadName(i);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[casillas[i-40].color]);
		glTranslatef(casillas[i-40].poscasillax, casillas[i-40].altura, casillas[i-40].poscasillaz);
		caja(casillas[i-40].dimbase, casillas[i-40].dimaltura, casillas[i-40].dimfondo);
		glPopMatrix();
	}
}

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja( void )
	
{
   static GLfloat pos[4] = {20.0, 10.0, 10.0, 0.0 };		// Posicion de la fuente de luz
   static GLfloat pos2[4] = {20, 10.0, -10.0, 0.0};   
   static GLfloat intensidad[4] = {0.6,0.6,0.6,1};

   glPushMatrix();		// Apila la transformacion geometrica actual
 
   glClearColor(0,0,0.6,1);	// Fija el color de fondo a azul
 
   glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );	 // Inicializa el buffer de color
 
   transformacionVisualizacion();	 // Carga transformacion de visualizacion
 
   glLightfv( GL_LIGHT0, GL_POSITION, pos );	// Declaracion de luz. Colocada aqui esta fija en la escena
   glLightfv( GL_LIGHT1, GL_POSITION, pos2);	//Segunda luz

   glLightfv( GL_LIGHT0, GL_DIFFUSE, intensidad);	//Segunda luz
   glLightfv( GL_LIGHT1, GL_DIFFUSE, intensidad);	//Segunda luz

   ejes(3);	// Dibuja los ejes

    // Dibuja el suelo

    glPushName(-1); 

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[verde]);
    glTranslatef(0,-0.5,0);
    glLoadName(0);
    caja(200,0.5,200);
       
	// Dibujamos el tablero

    glPushMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[marron]);
    glTranslatef(0, 1, 0);
    caja(73, 2, 60);

	int i = 0;
	int j = 0;
	int col = 1;

	//TIEMPO
	int ter = juegoTerminado();

	if(ter != 1){

		if(turno_jugador == 1){

			tiempo_jugador1 = tiempo_jugador1 - 1;
		}

		else{

			tiempo_jugador2 = tiempo_jugador2 - 1;
		}

		int long_caja = 0;

		if(modo_tiempo != 0){

			if(modo_tiempo == 1){

				long_caja = 160;
			}

			else if(modo_tiempo == 2){

				long_caja = 320;

			}		

			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[4]);
			glTranslatef(0, 1, -33);
			caja(tiempo_jugador2/long_caja, 2, 2);
			glPopMatrix();
			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color[4]);	
			glTranslatef(0, 1, 33);
			caja(tiempo_jugador1/long_caja, 2, 2);
			glPopMatrix();
		}
	}

	
	glPopMatrix();

	posicionarCasillas();
	posicionarPiezas();

	glPopMatrix(); 		// Desapila la transformacion geometrica

	glutSwapBuffers();	// Intercambia el buffer de dibujo y visualizacion

}



/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle()
{

	 gluiPostRedisplay();			// Redibuja
	 glutTimerFunc(30,idle,0);		// Vuelve a lanzar otro evento de redibujado en 30 ms
}


/**	int pick()

Se encarga de reconocer donde hemos realizado un click

**/

int pick(int x, int y){ //Devuelve de 0 en adelante si es una pieza, en caso contrario -1
             
    GLuint buff[512];
    GLint viewport[4];
    GLint hits;
      
    glSelectBuffer(512, buff);    
    glRenderMode(GL_SELECT);
    glInitNames(); //inicialización pila de nombres
      
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
      
    glGetIntegerv (GL_VIEWPORT, viewport); //obtiene el tamaño del viewport

    gluPickMatrix(x, viewport[3]-y, 5,5, viewport);
  
    fijaProyeccion();
    Dibuja();
      
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	fijaProyeccion();
	hits = glRenderMode (GL_RENDER); //al cambiar a modo Render, nos da el numero de componentes elegidos en el modelo
      
	//Introducimos buffer en nuestras estructuras
     
	int k = 0;
	
  	//Codigo para imprimir el buffer
    		
	/*if(hits>0){
	
		printf ("\n #hits: %i  \n",hits);

		for(k=0;k<20;++k){ 
			printf(" ,%u", buff[k]);
		}
	    printf("\n");
   	}*/

	int i=0;
	
	SELECCION seleccion;
	seleccion.nObjetos=hits;

	float Zminaux = 1;
	int piezaSeleccionada = -1;
	int seleccionada=0;
	for(k=0;k<hits;k++){
//		printf("Dentro del 1º for \n");
		seleccion.objeto[k].nNames=buff[k*4];
		//for(i=0;i<=seleccion.objeto[k].nNames;i+=3+seleccion.objeto[k].nNames){
	//		printf("Dentro del 2º for \n");
			seleccion.objeto[k].zmin=buff[k*4+1]/0xFFFFFFFF;
			seleccion.objeto[k].zmax=buff[k*4+2];
			seleccion.objeto[k].names[0]=buff[k*4+3];
			if(buff[k*4+3]>0){
		//		printf("Dentro de if \n");
				piezaSeleccionada=buff[k*4+3];
				//printf("\n La pieza seleccionada es: %i \n", piezaSeleccionada);
				seleccionada=1;
				if(seleccion.objeto[k].zmin < Zminaux){

					Zminaux = seleccion.objeto[k].zmin;
					seleccionada = piezaSeleccionada;
	
				}
			}
		//}
	}

	if(!seleccionada) piezaSeleccionada = -1;

	//printf("\n La pieza seleccionada es: %i \n", piezaSeleccionada);

	glMatrixMode (GL_PROJECTION); //restauramos la transformacion de la visualizacion
	glLoadIdentity();
	fijaProyeccion();

	      
      
    return piezaSeleccionada;
}

/** void eliminarPiezaTablero(int pieza)

Elimina una pieza del juego cuando esta ha sido comida por otra del oponente.

**/

void eliminarPiezaTablero(int pieza){

	if(piezas[pieza].color == negro){

		piezas[pieza].altura = piezas[pieza].altura + 10;

		if(piezas[pieza].pospiezax < comida_negrax){

			while(piezas[pieza].pospiezax < comida_negrax){

				piezas[pieza].pospiezax = piezas[pieza].pospiezax + 0.5;	
				Dibuja();

			}
		}

		else{

			while(piezas[pieza].pospiezax > comida_negrax){

				piezas[pieza].pospiezax = piezas[pieza].pospiezax - 0.5;
				Dibuja();

			}
		}

		if(piezas[pieza].pospiezay < comida_negraz){

			while(piezas[pieza].pospiezay < comida_negraz){

				piezas[pieza].pospiezay = piezas[pieza].pospiezay + 0.5;	
				Dibuja();

			}
		}

		else{

			while(piezas[pieza].pospiezay > comida_negraz){

				piezas[pieza].pospiezay = piezas[pieza].pospiezay - 0.5;
				Dibuja();

			}
		}
		
		piezas[pieza].altura = piezas[pieza].altura-10;

		comida_negraz +=5.5;

		if(comida_negraz >=  6.25*3 + 6.25/3 - 1){

			comida_negraz = -6.25*3 - 6.25/2;
			comida_negrax += 5.5;
		}
	}

	else if(piezas[pieza].color == blanco){

		piezas[pieza].altura = piezas[pieza].altura + 10;

		if(piezas[pieza].pospiezax < comida_blancax){

			while(piezas[pieza].pospiezax < comida_blancax){

				piezas[pieza].pospiezax = piezas[pieza].pospiezax + 0.5;	
				Dibuja();

			}

		}

		else{

			while(piezas[pieza].pospiezax > comida_blancax){

				piezas[pieza].pospiezax = piezas[pieza].pospiezax - 0.5;
				Dibuja();

			}

		}

		if(piezas[pieza].pospiezay < comida_blancaz){

			while(piezas[pieza].pospiezay < comida_blancaz){

				piezas[pieza].pospiezay = piezas[pieza].pospiezay + 0.5;	
				Dibuja();

			}
		}

		else{

			while(piezas[pieza].pospiezay > comida_blancaz){

				piezas[pieza].pospiezay = piezas[pieza].pospiezay - 0.5;
				Dibuja();

			}

		}
		
		piezas[pieza].altura = piezas[pieza].altura-10;
		comida_blancaz -=5.5;

		if(comida_blancaz <=  -6.25*3 - 6.25/3 + 1){

			comida_blancaz = 6.25*3 + 6.25/2;
			comida_blancax -= 5.5;
		}

	}

}


/** void animacionMoverPieza(int seleccionada, int casilla)

Realiza la animación del movimiento de la pieza.

**/

void animacionMoverPieza(int seleccionada, int casilla){

	char tipo = piezas[seleccionada].tipo;
	int pos_actual = piezas[seleccionada].sobre_casilla;
	
	switch(tipo){

		case 'p':

			if((pos_actual < casilla) && ((pos_actual-40)%8 == (casilla-40)%8)){

				while(piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					Dibuja();

				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)%8 == (casilla-40)%8)){

				while(piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					Dibuja();

				}

			}

			else if((pos_actual < casilla) && ((pos_actual-40)%8 < (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					Dibuja();

				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)%8 > (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					Dibuja();

				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)%8 < (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					Dibuja();

				}

			}

			else if((pos_actual < casilla) && ((pos_actual-40)%8 > (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					Dibuja();

				}

			}

			break;		

		case 'a':			

			if((pos_actual < casilla) && ((pos_actual-40)%8 > (casilla-40)%8)){

				while((piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax) && (piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz))
				{

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					Dibuja();

				}		
			}

			if((pos_actual < casilla) && ((pos_actual-40)%8 < (casilla-40)%8)){

				while((piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax) && (piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz))
				{

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					Dibuja();

				}		
			}

			if((pos_actual > casilla) && ((pos_actual-40)%8 > (casilla-40)%8)){

				while((piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax) && (piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz))
				{

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					Dibuja();

				}		
			}

			if((pos_actual > casilla) && ((pos_actual-40)%8 < (casilla-40)%8)){

				while((piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax) && (piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz))
				{

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					Dibuja();

				}		
			}		

			break;
		
		case 'k':


			if((pos_actual < casilla) && ((pos_actual-40)/8 == (casilla-40)/8)){
	
				while(piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax){

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					Dibuja();
				}


			}

			else if((pos_actual > casilla) && ((pos_actual-40)/8 == (casilla-40)/8)){

				while(piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax){

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					Dibuja();
				}		


			}

			else if((pos_actual < casilla) && ((pos_actual-40)%8 == (casilla-40)%8)){

				while(piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					Dibuja();

				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)%8 == (casilla-40)%8)){

				while(piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					Dibuja();

				}

			}

			else if((pos_actual < casilla) && ((pos_actual-40)%8 < (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					Dibuja();

				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)%8 > (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					Dibuja();

				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)%8 < (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					Dibuja();

				}

			}

			else if((pos_actual < casilla) && ((pos_actual-40)%8 > (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					Dibuja();

				}

			}

			else if((pos_actual < casilla) && ((pos_actual-40)/8 == (casilla-40)/8)){

				while(piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax){

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					Dibuja();
				}


			}

			else if((pos_actual > casilla) && ((pos_actual-40)/8 == (casilla-40)/8)){

				while(piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax){

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					Dibuja();
				}		


			}



			break;		


		case 'q':

			if((pos_actual < casilla) && ((pos_actual-40)/8 == (casilla-40)/8)){
				
				while(piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax){

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					Dibuja();
				}


			}

			else if((pos_actual > casilla) && ((pos_actual-40)/8 == (casilla-40)/8)){

				while(piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax){

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					Dibuja();
				}		


			}

			else if((pos_actual < casilla) && ((pos_actual-40)%8 == (casilla-40)%8)){

				while(piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					Dibuja();

				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)%8 == (casilla-40)%8)){

				while(piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					Dibuja();

				}

			}

			else if((pos_actual < casilla) && ((pos_actual-40)%8 < (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					Dibuja();

				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)%8 > (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					Dibuja();

				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)%8 < (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					Dibuja();

				}

			}

			else if((pos_actual < casilla) && ((pos_actual-40)%8 > (casilla-40)%8)){

				while((piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz) && (piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax)){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					Dibuja();

				}

			}


			break;

		case 't':

			if((pos_actual < casilla) && ((pos_actual-40)/8 == (casilla-40)/8)){
		
				while(piezas[seleccionada].pospiezax > casillas[casilla-40].poscasillax){
			
					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
					Dibuja();
				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)/8 == (casilla-40)/8)){

				while(piezas[seleccionada].pospiezax < casillas[casilla-40].poscasillax){

					piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
					Dibuja();
				}	
			             
			}

			else if((pos_actual < casilla) && ((pos_actual-40)/8 != (casilla-40)/8)){
				
				while(piezas[seleccionada].pospiezay < casillas[casilla-40].poscasillaz){
			
					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
					Dibuja();
				}

			}

			else if((pos_actual > casilla) && ((pos_actual-40)/8 != (casilla-40)/8)){

				while(piezas[seleccionada].pospiezay > casillas[casilla-40].poscasillaz){

					piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
					Dibuja();
				}	
			             
			}

			break;

		

		case 'c':

			piezas[seleccionada].altura = piezas[seleccionada].altura + 7;

			if(pos_actual < casilla){

					while(piezas[seleccionada].pospiezay <= casillas[casilla-40].poscasillaz){

						piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay + 0.5;
						Dibuja();

					}

					if((pos_actual-40)%8 >= (casilla-40)%8){

						while(piezas[seleccionada].pospiezax <= casillas[casilla-40].poscasillax){

							piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
							Dibuja();
						}
					}
			
					else{

						while(piezas[seleccionada].pospiezax >= casillas[casilla-40].poscasillax){

							piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
							Dibuja();
						}											
					}
			}
	
			else{

				while(piezas[seleccionada].pospiezay >= casillas[casilla-40].poscasillaz){

						piezas[seleccionada].pospiezay = piezas[seleccionada].pospiezay - 0.5;
						Dibuja();

					}

					if((pos_actual-40)%8 <= (casilla-40)%8){

						while(piezas[seleccionada].pospiezax >= casillas[casilla-40].poscasillax){

							piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax - 0.5;
							Dibuja();
						}
					}
			
					else{

						while(piezas[seleccionada].pospiezax <= casillas[casilla-40].poscasillax){

							piezas[seleccionada].pospiezax = piezas[seleccionada].pospiezax + 0.5;
							Dibuja();
						}											
					}


			}

			piezas[seleccionada].altura = piezas[seleccionada].altura - 7;

			break;

		}

}

/** int movimientoPieza(int seleccionada, int casilla_seleccionada, int num_casilla)

Se encarga del movimiento de las piezas

**/

int movimientoPieza(int seleccionada, int casilla_seleccionada, int num_casilla){

	int movida = 0;
	int i = 0;
	int sal = 0;
	int aux_pieza = 0;
	int pos_actual = piezas[seleccionada].sobre_casilla;

	if(num_casilla >= 40 && num_casilla <= 103){

		for(i; i < piezas[seleccionada].num_posibles && sal == 0; i++){

			if(num_casilla == piezas[seleccionada].posibles[i]){

				aux_pieza = piezaSobreCasilla(num_casilla);

				if(aux_pieza != 0){

					sal = 1;
					movida = 1;
					animacionMoverPieza(seleccionada, casilla_seleccionada);
					piezas[seleccionada].sobre_casilla = num_casilla;

					if((piezas[seleccionada].tipo == 'p') && ((piezas[seleccionada].sobre_casilla <= 103 && piezas[seleccionada].sobre_casilla > 95) || (piezas[seleccionada].sobre_casilla < 48 && piezas[seleccionada].sobre_casilla >= 40))){

							piezas[seleccionada].tipo = 'q';

					}
 
					casillas[pos_actual-40].estado = 0;
					estado = jugando;
					eliminarPiezaTablero(aux_pieza);
					piezas[aux_pieza].sobre_casilla = 0;
					piezas[aux_pieza].estado = 1;					

				}

				else{

					sal = 1;
					movida = 1;					
					animacionMoverPieza(seleccionada, casilla_seleccionada);
					piezas[seleccionada].sobre_casilla = num_casilla;

					if((piezas[seleccionada].tipo == 'p') && ((piezas[seleccionada].sobre_casilla <= 103 && piezas[seleccionada].sobre_casilla > 95) || (piezas[seleccionada].sobre_casilla < 48 && piezas[seleccionada].sobre_casilla >= 40))){

							piezas[seleccionada].tipo = 'q';

					}
 		
				
					casillas[casilla_seleccionada-40].estado = 1;
					casillas[pos_actual-40].estado = 0;	
					estado = jugando;
				}
			}
		}
	}

	else{
	
		int nueva_num_casilla = piezas[num_casilla-1].sobre_casilla;

		for(i; i < piezas[seleccionada].num_posibles && sal == 0; i++){

			if(nueva_num_casilla == piezas[seleccionada].posibles[i]){

				aux_pieza = piezaSobreCasilla(nueva_num_casilla);

				if(aux_pieza != 0){  
					
					sal = 1;
					movida = 1;
					animacionMoverPieza(seleccionada, nueva_num_casilla);
					piezas[seleccionada].sobre_casilla = nueva_num_casilla;		
				

					if((piezas[seleccionada].tipo == 'p') && ((piezas[seleccionada].sobre_casilla <= 103 && piezas[seleccionada].sobre_casilla > 95) || (piezas[seleccionada].sobre_casilla < 48 && piezas[seleccionada].sobre_casilla >= 40))){
							
							piezas[seleccionada].tipo = 'q';
							Dibuja();
					}
 
					casillas[pos_actual-40].estado = 0;
					estado = jugando;
					eliminarPiezaTablero(aux_pieza);
					piezas[aux_pieza].sobre_casilla = 0;
					piezas[aux_pieza].estado = 1;		

				}
			}
		}
	}

	return movida;

}



void setCamara(){

	if(turno_jugador == 1){

	
		while(z_camara > -61){

			z_camara = z_camara - 3;		
			Dibuja();
		}

	while(view_roty > -180){

			view_roty = view_roty - 5;
			Dibuja();
		}	

		turno_jugador = 0;

	}

	else{



		while(z_camara < 61){

			z_camara = z_camara + 3;
			Dibuja();
		}

		while(view_roty < 0){

			view_roty=view_roty+5;
			Dibuja();
		}

		turno_jugador = 1;

	}

}


void rellenarPosiblesAlfil(int seleccionada){

	int t = 1;
	int sal = 0;
	int aux_casilla = piezas[seleccionada].sobre_casilla;
	piezas[seleccionada].num_posibles = 0;
	int fila_actual = (piezas[seleccionada].sobre_casilla - 40) / 8;
	int fila_futura = 0;
	int col_actual = (piezas[seleccionada].sobre_casilla - 40) % 8;
	int col_futura = 0;
	int diferencia_fil = 0;
	int diferencia_col = 0;
	int pieza_aux = 0;

	for(t; t < 8 && sal == 0 && aux_casilla < 97 ; t++){
	
		aux_casilla = aux_casilla + 7;
		fila_futura = (aux_casilla-40) / 8;
		col_futura = (aux_casilla-40) % 8;

		diferencia_fil = fila_futura - fila_actual;
		diferencia_col = col_actual - col_futura;

		if(casillas[aux_casilla-40].estado == 1 || (diferencia_fil != diferencia_col)){

			pieza_aux = piezaSobreCasilla(aux_casilla);

			if((casillas[aux_casilla-40].estado == 1) && (piezas[pieza_aux].color != piezas[seleccionada].color) && (diferencia_fil == diferencia_col)){

				sal = 1;
				piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;

				casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
				casillas[aux_casilla-40].color = rojo;
				piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
				
			}

			else{

				sal = 1;
	
			}

		}

		else{
	
			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
			casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
			casillas[aux_casilla-40].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

		}
	}

	t = 1;
	sal = 0;
	aux_casilla = piezas[seleccionada].sobre_casilla;
	fila_futura = 0;
	col_futura = 0;
	diferencia_fil = 0;
	diferencia_col = 0;

	for(t; t < 8 && sal == 0 && aux_casilla > 46  ; t++){
	
		aux_casilla = aux_casilla - 7;

		fila_futura = (aux_casilla-40) / 8;
		col_futura = (aux_casilla-40) % 8;

		diferencia_fil = fila_actual - fila_futura;
		diferencia_col = col_futura - col_actual;


		if(casillas[aux_casilla-40].estado == 1 || (diferencia_fil != diferencia_col)){

			pieza_aux = piezaSobreCasilla(aux_casilla);

			if((casillas[aux_casilla-40].estado == 1) && (piezas[pieza_aux].color != piezas[seleccionada].color) && (diferencia_fil == diferencia_col)){

				sal = 1;
				piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
				casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
				casillas[aux_casilla-40].color = rojo;
				piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
				
			}

			else{

				sal = 1;
	
			}

		}

		else{
	
			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
			casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
			casillas[aux_casilla-40].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

		}
	}

	t = 1;
	sal = 0;
	aux_casilla = piezas[seleccionada].sobre_casilla;
	fila_futura = 0;
	col_futura = 0;
	diferencia_fil = 0;
	diferencia_col = 0;

	for(t; t < 8 && sal == 0 && aux_casilla < 95 ; t++){
	
		aux_casilla = aux_casilla + 9;
		fila_futura = (aux_casilla-40) / 8;
		col_futura = (aux_casilla-40) % 8;

		diferencia_fil = fila_futura - fila_actual;
		diferencia_col = col_futura - col_actual;

		if(casillas[aux_casilla-40].estado == 1 || (diferencia_fil != diferencia_col)){

			pieza_aux = piezaSobreCasilla(aux_casilla);

			if((casillas[aux_casilla-40].estado == 1) && (piezas[pieza_aux].color != piezas[seleccionada].color) && (diferencia_fil == diferencia_col)){

				sal = 1;
				piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
				casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
				casillas[aux_casilla-40].color = rojo;
				piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
				
			}

			else{

				sal = 1;
	
			}

		}

		else{
	
			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
			casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
			casillas[aux_casilla-40].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

		}
	}

	t = 1;
	sal = 0;
	aux_casilla = piezas[seleccionada].sobre_casilla;
	fila_futura = 0;
	col_futura = 0;
	diferencia_fil = 0;
	diferencia_col = 0;


	for(t; t < 8 && sal == 0 && aux_casilla > 46  ; t++){
	
		aux_casilla = aux_casilla - 9;
		fila_futura = (aux_casilla-40) / 8;
		col_futura = (aux_casilla-40) % 8;

		diferencia_fil = fila_actual - fila_futura;
		diferencia_col = col_actual - col_futura;

		if(casillas[aux_casilla-40].estado == 1  || (diferencia_fil != diferencia_col)){

			pieza_aux = piezaSobreCasilla(aux_casilla);

			if((casillas[aux_casilla-40].estado == 1) && (piezas[pieza_aux].color != piezas[seleccionada].color) && (diferencia_fil == diferencia_col)){

				sal = 1;
				piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
				casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
				casillas[aux_casilla-40].color = rojo;
				piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
				
			}

			else{

				sal = 1;
	
			}

		}

		else{
	
			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
			casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
			casillas[aux_casilla-40].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

		}
	}

}

void rellenarPosiblesCaballo(int seleccionada){

	int t = 1;
	int sal = 0;
	int aux_casilla = piezas[seleccionada].sobre_casilla;
	piezas[seleccionada].num_posibles = 0;
	int fila_actual = (piezas[seleccionada].sobre_casilla - 40) / 8;
	int fila_futura = 0;
	int pieza_aux = 0;


	if(aux_casilla + 17 < 104 && casillas[aux_casilla-40+17].estado == 0){
	
		fila_futura = (aux_casilla - 40 + 17) / 8;

		if(fila_futura-fila_actual == 2){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+17;
			casillas[aux_casilla-40+17].color_antiguo = casillas[aux_casilla-40+17].color;
			casillas[aux_casilla-40+17].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

		}	

	}

	if(aux_casilla + 17 < 104 && casillas[aux_casilla-40+17].estado == 1){

		fila_futura = (aux_casilla - 40 + 17) / 8;
		pieza_aux = piezaSobreCasilla(aux_casilla + 17);

		if((fila_futura-fila_actual == 2) && (piezas[pieza_aux].color != piezas[seleccionada].color)){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+17;
			casillas[aux_casilla-40+17].color_antiguo = casillas[aux_casilla-40+17].color;
			casillas[aux_casilla-40+17].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;		

		}
	 }

	if(aux_casilla + 15 < 104 && casillas[aux_casilla-40+15].estado == 0){
	
		fila_futura = (aux_casilla - 40 + 15) / 8;

		if(fila_futura-fila_actual == 2){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+15;
			casillas[aux_casilla-40+15].color_antiguo = casillas[aux_casilla-40+15].color;
			casillas[aux_casilla-40+15].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	

		}

	}

	if(aux_casilla + 15 < 104 && casillas[aux_casilla-40+15].estado == 1){

		fila_futura = (aux_casilla - 40 + 15) / 8;
		pieza_aux = piezaSobreCasilla(aux_casilla + 15);

		if((fila_futura-fila_actual == 2) && (piezas[pieza_aux].color != piezas[seleccionada].color)){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+15;
			casillas[aux_casilla-40+15].color_antiguo = casillas[aux_casilla-40+15].color;
			casillas[aux_casilla-40+15].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;		

		}
	 }

	if(aux_casilla - 17 > 39 && casillas[aux_casilla-40-17].estado == 0){
	
		fila_futura = (aux_casilla - 40 - 17) / 8;

		if(fila_actual-fila_futura == 2){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-17;
			casillas[aux_casilla-40-17].color_antiguo = casillas[aux_casilla-40-17].color;
			casillas[aux_casilla-40-17].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}
	}

	if(aux_casilla - 17 > 39 && casillas[aux_casilla-40-17].estado == 1){

		fila_futura = (aux_casilla - 40 - 17) / 8;
		pieza_aux = piezaSobreCasilla(aux_casilla - 17);

		if((fila_actual-fila_futura == 2) && (piezas[pieza_aux].color != piezas[seleccionada].color)){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-17;
			casillas[aux_casilla-40-17].color_antiguo = casillas[aux_casilla-40-17].color;
			casillas[aux_casilla-40-17].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;		

		}
	 }

	if(aux_casilla - 15 > 39 && casillas[aux_casilla-40-15].estado == 0){
	
		fila_futura = (aux_casilla - 40 - 15) / 8;

		if(fila_actual-fila_futura == 2){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-15;
			casillas[aux_casilla-40-15].color_antiguo = casillas[aux_casilla-40-15].color;
			casillas[aux_casilla-40-15].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}
	}

	if(aux_casilla - 15 > 39 && casillas[aux_casilla-40-15].estado == 1){

		fila_futura = (aux_casilla - 40 - 15) / 8;
		pieza_aux = piezaSobreCasilla(aux_casilla - 15);

		if((fila_actual-fila_futura == 2) && (piezas[pieza_aux].color != piezas[seleccionada].color)){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-15;
			casillas[aux_casilla-40-15].color_antiguo = casillas[aux_casilla-40-15].color;
			casillas[aux_casilla-40-15].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;		

		}
	 }

	if(aux_casilla + 6 < 104 && casillas[aux_casilla-40+6].estado == 0){
	
		fila_futura = (aux_casilla - 40 + 6) / 8;

		if(fila_futura - fila_actual == 1){		

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+6;
			casillas[aux_casilla-40+6].color_antiguo = casillas[aux_casilla-40+6].color;
			casillas[aux_casilla-40+6].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}

	}

	if(aux_casilla + 6 < 104 && casillas[aux_casilla-40+6].estado == 1){

		fila_futura = (aux_casilla - 40 + 6) / 8;
		pieza_aux = piezaSobreCasilla(aux_casilla + 6);

		if((fila_futura-fila_actual == 1) && (piezas[pieza_aux].color != piezas[seleccionada].color)){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+6;
			casillas[aux_casilla-40+6].color_antiguo = casillas[aux_casilla-40+6].color;
			casillas[aux_casilla-40+6].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;		

		}
	 }

	if(aux_casilla + 10 < 104 && casillas[aux_casilla-40+10].estado == 0){
	
		fila_futura = (aux_casilla -40 + 10) / 8;

		if(fila_futura - fila_actual == 1){		

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+10;
			casillas[aux_casilla-40+10].color_antiguo = casillas[aux_casilla-40+10].color;
			casillas[aux_casilla-40+10].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	

		}

	}

	if(aux_casilla + 10 < 104 && casillas[aux_casilla-40+10].estado == 1){

		fila_futura = (aux_casilla - 40 + 10) / 8;
		pieza_aux = piezaSobreCasilla(aux_casilla + 10);

		if((fila_futura-fila_actual == 1) && (piezas[pieza_aux].color != piezas[seleccionada].color)){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+10;
			casillas[aux_casilla-40+10].color_antiguo = casillas[aux_casilla-40+10].color;
			casillas[aux_casilla-40+10].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;		

		}
	 }

	if(aux_casilla - 10 > 39 && casillas[aux_casilla-40-10].estado == 0){
	
		fila_futura = (aux_casilla - 40 - 10) / 8;

		if(fila_actual - fila_futura == 1){	

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-10;
			casillas[aux_casilla-40-10].color_antiguo = casillas[aux_casilla-40-10].color;
			casillas[aux_casilla-40-10].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}
	}

	if(aux_casilla - 10 > 39 && casillas[aux_casilla-40-10].estado == 1){

		fila_futura = (aux_casilla - 40 - 10) / 8;
		pieza_aux = piezaSobreCasilla(aux_casilla - 10);

		if((fila_actual-fila_futura == 1) && (piezas[pieza_aux].color != piezas[seleccionada].color)){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-10;
			casillas[aux_casilla-40-10].color_antiguo = casillas[aux_casilla-40-10].color;
			casillas[aux_casilla-40-10].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;		

		}
	 }

	if(aux_casilla - 6 > 39 && casillas[aux_casilla-40-6].estado == 0){

		fila_futura = (aux_casilla - 40 - 6) / 8;

		if(fila_actual - fila_futura == 1){		

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-6;
			casillas[aux_casilla-40-6].color_antiguo = casillas[aux_casilla-40-6].color;
			casillas[aux_casilla-40-6].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}
	}

	if(aux_casilla - 6 > 39 && casillas[aux_casilla-40-6].estado == 1){

		fila_futura = (aux_casilla - 40 - 6) / 8;
		pieza_aux = piezaSobreCasilla(aux_casilla - 6);

		if((fila_futura-fila_actual == 1) && (piezas[pieza_aux].color != piezas[seleccionada].color)){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-6;
			casillas[aux_casilla-40-6].color_antiguo = casillas[aux_casilla-40-6].color;
			casillas[aux_casilla-40-6].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;		

		}
	 }

}

void rellenarPosiblesRey(int seleccionada){

	int t = 1;
	int sal = 0;
	int aux_casilla = piezas[seleccionada].sobre_casilla;
	piezas[seleccionada].num_posibles = 0;
	int pieza_aux = 0;

	if(aux_casilla + 1 < 104 && casillas[aux_casilla-40+1].estado == 0){

		piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+1;
		casillas[aux_casilla-40+1].color_antiguo = casillas[aux_casilla-40+1].color;
		casillas[aux_casilla-40+1].color = rojo;
		piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	

	}

	if(aux_casilla + 1 < 104 && casillas[aux_casilla-40+1].estado == 1){
	
		pieza_aux = piezaSobreCasilla(aux_casilla+1);

		if(piezas[pieza_aux].color != piezas[seleccionada].color){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+1;
			casillas[aux_casilla-40+1].color_antiguo = casillas[aux_casilla-40+1].color;
			casillas[aux_casilla-40+1].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}

	}

	if(aux_casilla -1 > 39 && casillas[aux_casilla-41].estado == 0){

		piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-1;
		casillas[aux_casilla-40-1].color_antiguo = casillas[aux_casilla-40-1].color;
		casillas[aux_casilla-40-1].color = rojo;
		piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;


	}

	if(aux_casilla - 1 > 39 && casillas[aux_casilla-40+-1].estado == 1){
	
		pieza_aux = piezaSobreCasilla(aux_casilla-1);

		if(piezas[pieza_aux].color != piezas[seleccionada].color){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-1;
			casillas[aux_casilla-40-1].color_antiguo = casillas[aux_casilla-40-1].color;
			casillas[aux_casilla-40-1].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}

	}

	if(aux_casilla + 8 < 104 && casillas[aux_casilla-40+8].estado == 0){

		piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+8;
		casillas[aux_casilla-40+8].color_antiguo = casillas[aux_casilla-40+8].color;
		casillas[aux_casilla-40+8].color = rojo;
		piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

	}

	if(aux_casilla + 8 < 104 && casillas[aux_casilla-40+8].estado == 1){
	
		pieza_aux = piezaSobreCasilla(aux_casilla+8);

		if(piezas[pieza_aux].color != piezas[seleccionada].color){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+8;
			casillas[aux_casilla-40+8].color_antiguo = casillas[aux_casilla-40+8].color;
			casillas[aux_casilla-40+8].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}

	}

	if(aux_casilla - 8 > 39 && casillas[aux_casilla-48].estado == 0){

		piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-8;
		casillas[aux_casilla-40-8].color_antiguo = casillas[aux_casilla-40-8].color;
		casillas[aux_casilla-40-8].color = rojo;
		piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

	}

	if(aux_casilla - 8 > 39 && casillas[aux_casilla-40-8].estado == 1){
	
		pieza_aux = piezaSobreCasilla(aux_casilla-8);

		if(piezas[pieza_aux].color != piezas[seleccionada].color){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-8;
			casillas[aux_casilla-40-8].color_antiguo = casillas[aux_casilla-40-8].color;
			casillas[aux_casilla-40-8].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}

	}

	if(aux_casilla + 9 < 104 && casillas[aux_casilla-40+9].estado == 0){

		piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+9;
		casillas[aux_casilla-40+9].color_antiguo = casillas[aux_casilla-40+9].color;
		casillas[aux_casilla-40+9].color = rojo;
		piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

	}

	if(aux_casilla + 9 < 104 && casillas[aux_casilla-40+9].estado == 1){
	
		pieza_aux = piezaSobreCasilla(aux_casilla+9);

		if(piezas[pieza_aux].color != piezas[seleccionada].color){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+9;
			casillas[aux_casilla-40+9].color_antiguo = casillas[aux_casilla-40+9].color;
			casillas[aux_casilla-40+9].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}

	}



	if(aux_casilla + 7 < 104 && casillas[aux_casilla-40+7].estado == 0){

		piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+7;
		casillas[aux_casilla-40+7].color_antiguo = casillas[aux_casilla-40+7].color;
		casillas[aux_casilla-40+7].color = rojo;
		piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

	}

	if(aux_casilla + 7 < 104 && casillas[aux_casilla-40+7].estado == 1){
	
		pieza_aux = piezaSobreCasilla(aux_casilla+7);

		if(piezas[pieza_aux].color != piezas[seleccionada].color){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+7;
			casillas[aux_casilla-40+7].color_antiguo = casillas[aux_casilla-40+7].color;
			casillas[aux_casilla-40+7].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}

	}

	if(aux_casilla - 7 > 39 && casillas[aux_casilla-40-7].estado == 0){

		piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-7;
		casillas[aux_casilla-40-7].color_antiguo = casillas[aux_casilla-40-7].color;
		casillas[aux_casilla-40-7].color = rojo;
		piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

	}

	if(aux_casilla - 7 > 39 && casillas[aux_casilla-40-7].estado == 1){
	
		pieza_aux = piezaSobreCasilla(aux_casilla-7);

		if(piezas[pieza_aux].color != piezas[seleccionada].color){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-7;
			casillas[aux_casilla-40-7].color_antiguo = casillas[aux_casilla-40-7].color;
			casillas[aux_casilla-40-7].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}

	}

	if(aux_casilla - 9 > 39 && casillas[aux_casilla-49].estado == 0){

		piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-9;
		casillas[aux_casilla-40-9].color_antiguo = casillas[aux_casilla-40-9].color;
		casillas[aux_casilla-40-9].color = rojo;
		piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

	}

	if(aux_casilla - 9 > 39 && casillas[aux_casilla-40-9].estado == 1){
	
		pieza_aux = piezaSobreCasilla(aux_casilla-9);

		if(piezas[pieza_aux].color != piezas[seleccionada].color){

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-9;
			casillas[aux_casilla-40-9].color_antiguo = casillas[aux_casilla-40-9].color;
			casillas[aux_casilla-40-9].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;	
		}

	}
	

}

void rellenarPosiblesPeon(int seleccionada){


		int t = 1;
		int sal = 0;
		int aux_casilla = piezas[seleccionada].sobre_casilla;
		piezas[seleccionada].num_posibles = 0;
		int pieza_aux = 0;

		if(turno_jugador == 0){ //NEGRAS

			if(aux_casilla + 7 < 104 && casillas[aux_casilla-40+7].estado == 1){

				pieza_aux = piezaSobreCasilla(aux_casilla+7);

				if((piezas[pieza_aux].color != piezas[seleccionada].color)&&(piezas[pieza_aux].sobre_casilla/8 != piezas[seleccionada].sobre_casilla/8)){
	
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+7;
					casillas[aux_casilla-40+7].color_antiguo = casillas[aux_casilla-40+7].color;
					casillas[aux_casilla-40+7].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

				}
			}

			if(aux_casilla + 9 < 104 && casillas[aux_casilla-40+9].estado == 1){

				pieza_aux = piezaSobreCasilla(aux_casilla+9);
				if((piezas[pieza_aux].color != piezas[seleccionada].color)&&(piezas[pieza_aux].sobre_casilla/8 != piezas[seleccionada].sobre_casilla/8)){
		
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+9;
					casillas[aux_casilla-40+9].color_antiguo = casillas[aux_casilla-40+9].color;
					casillas[aux_casilla-40+9].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

				}
			}


			if(aux_casilla + 8 < 104 && casillas[aux_casilla-40+8].estado == 0){

				piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+8;
				casillas[aux_casilla-40+8].color_antiguo = casillas[aux_casilla-40+8].color;
				casillas[aux_casilla-40+8].color = rojo;
				piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
			
				if(aux_casilla <= 55 && aux_casilla >= 48 && casillas[aux_casilla-40+16].estado == 0){

					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla+16;
					casillas[aux_casilla-40+16].color_antiguo = casillas[aux_casilla-40+16].color;
					casillas[aux_casilla-40+16].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
				}				

			}

		}

		else{

			if(aux_casilla -7 > 39 && casillas[aux_casilla-40-7].estado == 1){

				pieza_aux = piezaSobreCasilla(aux_casilla-7);

				if(piezas[pieza_aux].color != piezas[seleccionada].color){

					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-7;
					casillas[aux_casilla-40-7].color_antiguo = casillas[aux_casilla-40-7].color;
					casillas[aux_casilla-40-7].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

				}
			}

			if(aux_casilla -9 > 39 && casillas[aux_casilla-40-9].estado == 1){

				pieza_aux = piezaSobreCasilla(aux_casilla-9);

				if(piezas[pieza_aux].color != piezas[seleccionada].color){

					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-9;
					casillas[aux_casilla-40-9].color_antiguo = casillas[aux_casilla-40-9].color;
					casillas[aux_casilla-40-9].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

				}
			}

			if(aux_casilla - 8 > 39 && casillas[aux_casilla-40-8].estado == 0){

				piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-8;
				casillas[aux_casilla-40-8].color_antiguo = casillas[aux_casilla-40-8].color;
				casillas[aux_casilla-40-8].color = rojo;
				piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

				if(aux_casilla <= 95 && aux_casilla >= 88 && casillas[aux_casilla-56].estado == 0){

					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla-16;
					casillas[aux_casilla-40-16].color_antiguo = casillas[aux_casilla-40-16].color;
					casillas[aux_casilla-40-16].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
				}				

			}

		}




}

void rellenarPosiblesTorre(int seleccionada){

		int t = 1;
		int sal = 0;
		int aux_casilla = piezas[seleccionada].sobre_casilla;
		piezas[seleccionada].num_posibles = 0;
		int pieza_aux = 0;


		for(t; t < 8 && sal == 0 && aux_casilla < 96 ; t++){
	
			aux_casilla = aux_casilla + 8;
			printf("aux casilla es %i \n ", aux_casilla);
			if(casillas[aux_casilla-40].estado == 1){

				pieza_aux = piezaSobreCasilla(aux_casilla);
				if(piezas[pieza_aux].color != piezas[seleccionada].color){

					sal = 1;
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
					casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
					casillas[aux_casilla-40].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;				
				}

				else{
					
					printf("La pieza seleccionada tiene color %i ", piezas[seleccionada].color);
					printf(" y es la pieza numero %i \n ", seleccionada);
					printf("La pieza donde queremos ir tiene color %i ", piezas[pieza_aux].color);
					printf(" y esta en la pieza numero %i \n \n", pieza_aux);
					sal = 1;
				}

			}

			else{
	
				piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
				casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
				casillas[aux_casilla-40].color = rojo;
				piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
			}
		}

		t = 1;
		sal = 0;
		aux_casilla = piezas[seleccionada].sobre_casilla;

		for(t; t < 8 && sal == 0 && aux_casilla > 47 ; t++){
	
			aux_casilla = aux_casilla - 8;

			if(casillas[aux_casilla-40].estado == 1){

				pieza_aux = piezaSobreCasilla(aux_casilla);

				if(piezas[pieza_aux].color != piezas[seleccionada].color){

					sal = 1;
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
					casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
					casillas[aux_casilla-40].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;				
				}

				else{

					sal = 1;
				}
			}

			else{
	
				piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
				casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
				casillas[aux_casilla-40].color = rojo;
				piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
			}
		}

		t = 1;		
		aux_casilla = piezas[seleccionada].sobre_casilla;
		sal = 0;
		int fila_actual = (piezas[seleccionada].sobre_casilla - 40) / 8;	
		int fila_futura = 0;
		pieza_aux = 0;

		for(t; t < 8 && sal == 0 && aux_casilla < 103 ; t++){
	
			aux_casilla = aux_casilla + 1;

			if((aux_casilla-40)/8 != fila_actual){

				sal = 1;

			}

			else if(casillas[aux_casilla-40].estado == 1){

				pieza_aux = piezaSobreCasilla(aux_casilla);
				if(piezas[pieza_aux].color != piezas[seleccionada].color){

					sal = 1;
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
					casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
					casillas[aux_casilla-40].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;				
				}

				else{

					sal = 1;
				}
			}

			else{

				fila_futura = (aux_casilla - 40) / 8;
				if(fila_futura == fila_actual){
		
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
					casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
					casillas[aux_casilla-40].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
				}			
			}
		}

		t = 1;		
		aux_casilla = piezas[seleccionada].sobre_casilla;
		sal = 0;
		fila_actual = (piezas[seleccionada].sobre_casilla - 40) / 8;	

		for(t; t < 8 && sal == 0 && aux_casilla > 40 ; t++){
	
			aux_casilla = aux_casilla - 1;

			if((aux_casilla-40)/8 != fila_actual){

				sal = 1;

			}

			else if(casillas[aux_casilla-40].estado == 1){

				pieza_aux = piezaSobreCasilla(aux_casilla);
				if(piezas[pieza_aux].color != piezas[seleccionada].color){

					sal = 1;
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
					casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
					casillas[aux_casilla-40].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;				
				}

				else{

					sal = 1;
				}
			}

			else{

				fila_futura = (aux_casilla - 40) / 8;
				if(fila_futura == fila_actual){
	
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
					casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
					casillas[aux_casilla-40].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;
				}
			}
		}
}

void rellenarPosiblesReina(int seleccionada){


	rellenarPosiblesTorre(seleccionada);

	int t = 1;
	int sal = 0;
	int aux_casilla = piezas[seleccionada].sobre_casilla;
	int fila_actual = (piezas[seleccionada].sobre_casilla - 40) / 8;
	int fila_futura = 0;
	int col_actual = (piezas[seleccionada].sobre_casilla - 40) % 8;
	int col_futura = 0;
	int diferencia_fil = 0;
	int diferencia_col = 0;
	int pieza_aux = 0;

	for(t; t < 8 && sal == 0 && aux_casilla < 97 ; t++){
	
		aux_casilla = aux_casilla + 7;

		fila_futura = (aux_casilla-40) / 8;
		col_futura = (aux_casilla-40) % 8;

		diferencia_fil = fila_futura - fila_actual;
		diferencia_col = col_actual - col_futura;

		if(casillas[aux_casilla-40].estado == 1 || (diferencia_fil != diferencia_col)){

			if((casillas[aux_casilla-40].estado == 1) && (diferencia_fil == diferencia_col)){

				pieza_aux = piezaSobreCasilla(aux_casilla);
				if(piezas[pieza_aux].color != piezas[seleccionada].color){

					sal = 1;
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
					casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
					casillas[aux_casilla-40].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;				
				}

				else{

					sal = 1;

				}

			}

			else{

				sal = 1;

			}

		}

		else{

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
			casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
			casillas[aux_casilla-40].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

		}
	}

	t = 1;
	sal = 0;
	aux_casilla = piezas[seleccionada].sobre_casilla;
	fila_futura = 0;
	col_futura = 0;
	diferencia_fil = 0;
	diferencia_col = 0;

	for(t; t < 8 && sal == 0 && aux_casilla > 46  ; t++){
	
		aux_casilla = aux_casilla - 7;

		fila_futura = (aux_casilla-40) / 8;
		col_futura = (aux_casilla-40) % 8;

		diferencia_fil = fila_actual - fila_futura;
		diferencia_col = col_futura - col_actual;


		if(casillas[aux_casilla-40].estado == 1 || (diferencia_fil != diferencia_col)){

			if((casillas[aux_casilla-40].estado == 1) && (diferencia_fil == diferencia_col)){

				pieza_aux = piezaSobreCasilla(aux_casilla);
				if(piezas[pieza_aux].color != piezas[seleccionada].color){

					sal = 1;
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
					casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
					casillas[aux_casilla-40].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;				
				}

				else{

					sal = 1;

				}
			}

			else{

				sal = 1;

			}
		}
				
		else{

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
			casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
			casillas[aux_casilla-40].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

		}
	}

	t = 1;
	sal = 0;
	aux_casilla = piezas[seleccionada].sobre_casilla;
	fila_futura = 0;
	col_futura = 0;
	diferencia_fil = 0;
	diferencia_col = 0;

	for(t; t < 8 && sal == 0 && aux_casilla < 95 ; t++){
	
		aux_casilla = aux_casilla + 9;
		fila_futura = (aux_casilla-40) / 8;
		col_futura = (aux_casilla-40) % 8;
		diferencia_fil = fila_futura - fila_actual;
		diferencia_col = col_futura - col_actual;

		if(casillas[aux_casilla-40].estado == 1 || (diferencia_fil != diferencia_col)){

			if((casillas[aux_casilla-40].estado == 1) && (diferencia_fil == diferencia_col)){

				pieza_aux = piezaSobreCasilla(aux_casilla);
				if(piezas[pieza_aux].color != piezas[seleccionada].color){

					sal = 1;
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
					casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
					casillas[aux_casilla-40].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;				
				}

				else{

					sal = 1;

				}
			}

			else{

				sal = 1;

			}
		}

		else{

			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
			casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
			casillas[aux_casilla-40].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

		}
	}

	t = 1;
	sal = 0;
	aux_casilla = piezas[seleccionada].sobre_casilla;
	fila_futura = 0;
	col_futura = 0;
	diferencia_fil = 0;
	diferencia_col = 0;


	for(t; t < 8 && sal == 0 && aux_casilla > 46  ; t++){
	
		aux_casilla = aux_casilla - 9;
		fila_futura = (aux_casilla-40) / 8;
		col_futura = (aux_casilla-40) % 8;
		diferencia_fil = fila_actual - fila_futura;
		diferencia_col = col_actual - col_futura;

		if(casillas[aux_casilla-40].estado == 1  || (diferencia_fil != diferencia_col)){

			if((casillas[aux_casilla-40].estado == 1) && (diferencia_fil == diferencia_col)){

				pieza_aux = piezaSobreCasilla(aux_casilla);
				if(piezas[pieza_aux].color != piezas[seleccionada].color){

					sal = 1;
					piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
					casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
					casillas[aux_casilla-40].color = rojo;
					piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;				
				}

				else{

					sal = 1;

				}
			}

			else{

				sal = 1;

			}

		}

		else{
	
			piezas[seleccionada].posibles[piezas[seleccionada].num_posibles] = aux_casilla;
			casillas[aux_casilla-40].color_antiguo = casillas[aux_casilla-40].color;
			casillas[aux_casilla-40].color = rojo;
			piezas[seleccionada].num_posibles = piezas[seleccionada].num_posibles + 1;

		}
	}


	
}

void apagarEncendidas(){	

	int i = 0;
	int aux1;
	
	int por_borrar = piezas[seleccionada].num_posibles;

	for(i; i < por_borrar; i++){
	
		aux1 = piezas[seleccionada].posibles[i];
		casillas[aux1-40].color = casillas[aux1-40].color_antiguo;

	}
}

int piezaSobreCasilla(aux_casilla){

	int pieza = 0;
	int sal = 0;
	int i = 0;

	for(i; i < 16 && sal == 0; i++){


		if(piezas[i].sobre_casilla == aux_casilla){

			pieza = i;
			sal = 1;
		}
	}

	i = 16;

	for(i; i < 32 && sal == 0; i++){


		if(piezas[i].sobre_casilla == aux_casilla){

			pieza = i;
			sal = 1;
		}
	}

	return pieza;

}

int juegoTerminado(){

	int terminado = 0;

	if(piezas[3].estado == 1 || piezas[20].estado == 1){

		terminado = 1;

	}

	if(tiempo_jugador1 == 0 || tiempo_jugador2 == 0){

		terminado = 1;

	}

	return terminado;

}

