/*	Grua 

	C.A.D. 						Curso 2008-2009
 	
	Codigo base para la realización de las practicas de CAD

	modulo mouse.c
	Gestion de eventos de raton
=======================================================
	J.C. Torres 
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


/**	 void clickRaton( int boton, int estado, int x, int y )

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

 void clickRaton( int boton, int estadob, int x, int y )
{

	float incrementoX = 0;
	float incrementoY = 0;
    	float xm = 0;
    	float zm = 0;
    	int num_pieza = 0;
	int num_casilla = 0;
	int terminado;

    if(boton == GLUT_LEFT_BUTTON && estadob == GLUT_DOWN){

    switch(estado){

	case jugando:

		terminado = juegoTerminado();

		if(terminado){

			gluiOutput( "PARTIDA FINALIZADA");	// Nuestra mensaje en interfaz

		}

		num_pieza = pick(x,y);
		
		if((num_pieza >= 1 && num_pieza <= 36) && piezas[num_pieza-1].estado != 1){

			if((turno_jugador == 0 && piezas[num_pieza-1].color == negro) || (turno_jugador == 1 && piezas[num_pieza-1].color == blanco)){

				seleccionada = num_pieza-1;

				if(piezas[seleccionada].tipo == 't'){

					gluiOutput( "Pieza seleccionada: Torre");	// Nuestra mensaje en interfaz

						rellenarPosiblesTorre(seleccionada);	

				}

				if(piezas[seleccionada].tipo == 'p'){

					gluiOutput( "Pieza seleccionada: Peon");	// Nuestra mensaje en interfaz
					
						rellenarPosiblesPeon(seleccionada);	

				}

				if(piezas[seleccionada].tipo == 'k'){

					gluiOutput( "Pieza seleccionada: Rey");	// Nuestra mensaje en interfaz

						rellenarPosiblesRey(seleccionada);	

				}

				if(piezas[seleccionada].tipo == 'c'){

					gluiOutput( "Pieza seleccionada: Caballo");	// Nuestra mensaje en interfaz

						rellenarPosiblesCaballo(seleccionada);
	
				}

				if(piezas[seleccionada].tipo == 'a'){

					gluiOutput( "Pieza seleccionada: Alfil");	// Nuestra mensaje en interfaz

						rellenarPosiblesAlfil(seleccionada);	

				}

				if(piezas[seleccionada].tipo == 'q'){

					gluiOutput( "Pieza seleccionada: Reina");	// Nuestra mensaje en interfaz

						rellenarPosiblesReina(seleccionada);

				}

				color_original = piezas[seleccionada].color;
				piezas[num_pieza-1].color = azul;
				xRef = x;
				zRef = y;

				if(modo_dificultad == 1){

					apagarEncendidas();
				}
				estado = piezaseleccionada;

			}

		}

	break; 

	case piezaseleccionada:

		num_casilla = pick(x,y);
		int casilla_seleccionada = 0;

		if((num_casilla >= 1 && num_casilla <=36) || (num_casilla >= 40 && num_casilla <=103)){	

			casilla_seleccionada = num_casilla;
			char tipo = piezas[seleccionada].tipo;
			int movida = 0;

			switch(tipo){

				estado = jugando;

				case 't':
					
					movida = movimientoPieza(seleccionada, casilla_seleccionada, num_casilla);
					piezas[seleccionada].color = color_original;
				
					if(movida == 1){

						estado = pieza_movida;

					}
	
					else{

						estado = jugando;					
					}

					apagarEncendidas();

					break;

				case 'c':

					movida = movimientoPieza(seleccionada, casilla_seleccionada, num_casilla);
					piezas[seleccionada].color = color_original;

					if(movida == 1){

						estado = pieza_movida;

					}

					else{

						estado = jugando;

					}

					apagarEncendidas();

					break;
	
				case 'a':

					movida = movimientoPieza(seleccionada, casilla_seleccionada, num_casilla);
					piezas[seleccionada].color = color_original;

					if(movida == 1){

						estado = pieza_movida;
					
					}					
			
					else{

						estado = jugando;
				
					}

					apagarEncendidas();

					break;

				case 'k':

					movida = movimientoPieza(seleccionada, casilla_seleccionada, num_casilla);
					piezas[seleccionada].color = color_original;
				
					if(movida == 1){

						estado = pieza_movida;
					
					}

					else{

						estado = jugando;	

					}
					apagarEncendidas();

					break;

				case 'q':

					movida = movimientoPieza(seleccionada, casilla_seleccionada, num_casilla);
					piezas[seleccionada].color = color_original;

					if(movida == 1){

						estado = pieza_movida;
								
					}

					else{

						estado = jugando;

					}
				
					apagarEncendidas();
					

					break;

				case 'p':

					movida = movimientoPieza(seleccionada, casilla_seleccionada, num_casilla, color_original);
					piezas[seleccionada].color = color_original;

					if(movida == 1){

						estado = pieza_movida;	
					}

					else{

						estado = jugando;					
					}

					apagarEncendidas();

				break;
			}
	
		}

	break;
	
	case pieza_movida:

		terminado = juegoTerminado();

		if(!terminado){

			estado = jugando;
			setCamara();

		}
			
		else{

			gluiOutput( "PARTIDA FINALIZADA");	// Muestra mensaje en interfaz

		}
	
	break;

    }
    
    glutPostRedisplay();
    }

}


/**	void RatonMovido( int x, int y )

Procedimiento para gestionar los eventos de movimiento del raton.

Argumentos:

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void RatonMovido( int x, int y )
{

/* Codigo para arrastar piezas. Utilidad descartada

	float incrementoX = 0;
	float incrementoY = 0;
	float dist = 0;
	int t = 0;
	float xm = 0;
	float zm = 0;

	switch(estado){

		case piezaseleccionada:		
				
			
			incrementoX = x - xRef;
			incrementoY = y - zRef;
			piezas[seleccionada].pospiezax += incrementoX*0.1;  
			piezas[seleccionada].pospiezay += incrementoY*0.1;
			xRef = x;
			zRef = y;

	}*/

}
