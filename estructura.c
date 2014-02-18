/*	AJEDREZ

	C.A.D. 						Curso 2011-2012
 	
	Codigo base para la realización de las practicas de CAD

	modulo estructura.c
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
 Seccion de los perfiles para la estructura
**/
#define seccion 0.1 

/**	float modulo(float x,float y,float z)

Calcula el modulo del vector (x,y,z)
**/

float modulo(float x,float y,float z)
{
return sqrt(x*x+y*y+z*z);
}


/** 	void caja( float a, float b, float m)

Construye un paralelepipedo alineado con los ejes de
dimension a x b x m. El objeto se construye en el semiespacio y>=0, con el origen en el
centro de la base. 

**/
void caja( float a, float b, float m)

{
	float x,y,z;
	
	x= a/2;
	z= m/2;
	y = b;

   glShadeModel( GL_FLAT );

   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( 0.0, 0.0, -1.0 );   /* Vertical hacia atras */

      glVertex3f( x, 0, -z );
      glVertex3f( -x, 0, -z );


      glVertex3f( x, y, -z );
      glVertex3f( -x, y, -z );

glNormal3f( 0.0, 1.0, 0.0 );       /* Superior, horizontal */

      glVertex3f( x, y, z );
      glVertex3f( -x, y, z );
glNormal3f( 0.0, 0.0, 1.0 );       /*Vertical delantera*/
      glVertex3f( x, 0, z );
      glVertex3f( -x, 0, z );

glNormal3f( 0.0, -1.0, 0.0 );       /*Inferior */
      glVertex3f( x, 0, -z );
      glVertex3f( -x, 0, -z );  }
    glEnd();

   /* Costados */
   glBegin( GL_QUADS );{
      glNormal3f( 1.0, 0.0, 0.0 );
      glVertex3f( x, 0, -z );
      glVertex3f( x, y, -z );
      glVertex3f( x, y, z );
      glVertex3f( x, 0, z ); }
   glEnd();


   glBegin( GL_QUADS );{
      glNormal3f( -1.0, 0.0, 0.0 );
      glVertex3f( -x, 0, -z );
      glVertex3f( -x, 0, z );
      glVertex3f( -x, y, z );
      glVertex3f( -x, y, -z ); }
   glEnd();
}


/**	void fasloCilindro(float h, float r)

Crea un paralelepipedo con sombreado como phong (simulando un cilindro)
con centro de las bases en 0,0,0 y 0,h,0, y radio de la base r.

**/
void falsoCilindro(float h, float r)
{
float a2;

// m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	// glTranslatef(x0,y0,z0);
//	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
//	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);

	a2= r; //  a/2.0;
   glShadeModel( GL_SMOOTH );

   /* Caras laterales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( 1.0, 0.0, -1.0 );  
      
      glVertex3f(  a2, h, -a2 );
      glVertex3f(  a2, 0, -a2 );

     glNormal3f( -1.0, 0.0, -1.0 );  
 
      glVertex3f( -a2, h, -a2 );
      glVertex3f( -a2, 0, -a2 );

     glNormal3f( -1.0, 0.0, 1.0 );    

      glVertex3f( -a2, h, a2 );
      glVertex3f( -a2, 0, a2 );
      
    glNormal3f( 1.0, 0.0, 1.0 );      
    
      glVertex3f(  a2, h, a2 );
      glVertex3f(  a2, 0, a2 );

     glNormal3f( 1.0, 0.0, -1.0 );      

      glVertex3f(  a2, h, -a2 );
      glVertex3f(  a2, 0, -a2 );  }
    glEnd();
   glShadeModel( GL_FLAT );
  /* Tapas */
   glBegin( GL_QUADS );{
      glNormal3f( 0.0, 1.0, 0.0 );
      glVertex3f( -a2, h, -a2 );
      glVertex3f( -a2, h,  a2 );
      glVertex3f(  a2, h,  a2 );
      glVertex3f(  a2, h, -a2 ); }
   glEnd();


   glBegin( GL_QUADS );{
      glNormal3f( 0.0, -1.0, 0.0 );
      glVertex3f( -a2, 0, -a2 );
      glVertex3f(  a2, 0, -a2 );
      glVertex3f(  a2, 0,  a2 );
      glVertex3f( -a2, 0,  a2 ); }
   glEnd();
	
glPopMatrix();

}	


/**	void falsoCono( float h, float r)

Crea una piramide sombreada como un cono con centro de las bases en
0,0,0, cuspide en  0,h,0, y radio de la base r.

**/
void falsoCono( float h, float r)
{
float a2,m,norma,n1,n2;

m=h;
glPushMatrix();

	a2= r/2.0;
	norma=sqrt(a2*a2+2*m*m);
	n1= a2/norma;
	n2= m/norma;
   glShadeModel( GL_SMOOTH );

   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( n2, n1, -n2 );  
      
      glVertex3f(  0, m, 0 );
      glVertex3f(  a2, 0, -a2 );

     glNormal3f( -n2, n1, -n2 );  
 
      glVertex3f( 0, m, 0 );
      glVertex3f( -a2, 0, -a2 );

     glNormal3f( -n2, n1, n2 );    

      glVertex3f( 0, m,0 );
      glVertex3f( -a2, 0, a2 );
      
    glNormal3f( n2, n1, n2 );      
    
      glVertex3f(  0, m, 0 );
      glVertex3f(  a2, 0, a2 );

     glNormal3f( n2, n1, -n2 );      

      glVertex3f(  0, m, 0 );
      glVertex3f(  a2, 0, -a2 );  }
    glEnd();

 glShadeModel( GL_FLAT );
  /* Tapa */
   glBegin( GL_QUADS );{
      glNormal3f( 0.0, -1.0, 0.0 );
      glVertex3f( -a2, 0, -a2 );
      glVertex3f(  a2, 0, -a2 );
      glVertex3f(  a2, 0,  a2 );
      glVertex3f( -a2, 0,  a2 ); }
   glEnd();
	
glPopMatrix();

}	

/** 	void ejes(float a)

Dibuja unos ejes de tamanyo a

**/
void ejes(float a)
{
  float c1[4]={1.0,1.0,0.0,1.}, c2[4]={1.0,0.0,1.0,1},c3[4]={0.0,1.0,1.0,1};
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,c1);
	falsoCilindro(0.75*a,0.05*a);
	glTranslatef(0.0,0.75*a,0.0);
	falsoCono(0.25*a,0.15*a);
  glPopMatrix();
   
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,c2);
  glPushMatrix();  
	glRotatef(-90.0,0,0,1);	
	falsoCilindro(0.75*a,0.05*a);
	glTranslatef(0.0,0.75*a,0.0);
	falsoCono(0.25*a,0.15*a);
  glPopMatrix();

	
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,c3);	
  glPushMatrix();  
	glRotatef(90.0,1,0,0);	
	falsoCilindro(0.75*a,0.05*a);
	glTranslatef(0.0,0.75*a,0.0);
	falsoCono(0.25*a,0.15*a);
  glPopMatrix();
}


/**	void paralelepipedo(float x0, float y0, float z0, float x1, float y1, float z1,  float a, float b)

Crea un paralelepipedo con centro de las bases en
x0,y0,z0 y x1,y1,z1, y tamanyo de la base axb.

**/
void paralelepipedo(float x0, float y0, float z0, 
		    float x1, float y1, float z1, 
		    float a, float b)
{
float m;

m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);
	caja(a,m,b);
glPopMatrix();
}	


/**	void creaEstructura(float h, float a, float b, int n)

Crea un fragmento de estructura de una grua, con centro de las bases en
0,0,0 y 0,h,0. Las secciones de las bases tienen tamanyo axb
n es el numero de niveles que tiene la estructura.

Los perfiles tienen seccion cuadrada, dada por el parametro seccion.
	
Para crear la estructura se utiliza el procedimiento paralelepipedo.
**/
void creaEstructura(float h, float a, float b, int n)

{
float x, y,z,a2,b2;
int i;
float m,e;

if(n<1) { printf("\n Error: Numero de segmentos en estructura menor que 1\n");return;}

// m= modulo(x1-x0,y1-y0,z1-z0);
m=h;
glPushMatrix();
// 	glTranslatef(x0,y0,z0);
// 	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
// 	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);
// Creamos la estructura vertical, con altura m

e=m/n;	// Altura entre dos niveles


y=0;
a2= a/2.;
b2= b/2.;
for(i=0;i<n;++i)
	{
	// Barras horizontales
	paralelepipedo(-a2,y,-b2, a2,y,-b2,seccion,seccion);
	paralelepipedo( a2,y,-b2, a2,y, b2,seccion,seccion);
	paralelepipedo( a2,y, b2,-a2,y, b2,seccion,seccion);
	paralelepipedo(-a2,y, b2,-a2,y,-b2,seccion,seccion);
	
	// Barras oblicuas
	if(i%2) {
		paralelepipedo(-a2,y,-b2, a2,y+e,-b2,seccion,seccion);
		paralelepipedo( a2,y,-b2, a2,y+e, b2,seccion,seccion);
		paralelepipedo( a2,y, b2,-a2,y+e, b2,seccion,seccion);
		paralelepipedo(-a2,y, b2,-a2,y+e,-b2,seccion,seccion);
		}
	else {
		paralelepipedo( a2,y,-b2,-a2,y+e,-b2,seccion,seccion);
		paralelepipedo( a2,y, b2, a2,y+e,-b2,seccion,seccion);
		paralelepipedo(-a2,y, b2, a2,y+e, b2,seccion,seccion);
		paralelepipedo(-a2,y,-b2,-a2,y+e, b2,seccion,seccion);	
	}
			
	// Barras verticales
	paralelepipedo(-a2,y,-b2,-a2,y+e,-b2,seccion,seccion);
	paralelepipedo( a2,y,-b2, a2,y+e,-b2,seccion,seccion);
	paralelepipedo(-a2,y, b2,-a2,y+e, b2,seccion,seccion);
	paralelepipedo( a2,y, b2, a2,y+e, b2,seccion,seccion);
	
	// Siguiente nivel
	y=y+e;
	}
	
// Barras horizontales de terminacion
paralelepipedo(-a2,y,-b2, a2,y,-b2,seccion,seccion);
paralelepipedo( a2,y,-b2, a2,y, b2,seccion,seccion);
paralelepipedo( a2,y, b2,-a2,y, b2,seccion,seccion);
paralelepipedo(-a2,y, b2,-a2,y,-b2,seccion,seccion);

glPopMatrix();
}

/**	void creaBrazo(float h, float a, int n)

Crea un fragmento del brazo de una grua, con centro una de las aristas 
de los extremos en
0,0,0 y 0,h,0. Los lados de las bases tienen tamanyo a,
n es el numero de tramos.

Los perfiles tienen seccion triangular
	
Para crear la estructura se utiliza el procedimiento paralelepipedo.
**/

void creaBrazo(float h, float a, int n)

{
float x, y,z,a2,b;
int i;
float m,e;

if(n<2) { printf("\n Error: Numero de segmentos en brazo menor que 2\n");return;}

//glEnable(GL_NORMALIZE);
//m= modulo(x1-x0,y1-y0,z1-z0);
m=h;
glPushMatrix();
// 	glTranslatef(x0,y0,z0);
// 	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
// 	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);
// Creamos el brazo vertical, con altura m

e=m/n;	// Altura entre dos tramos

y=0;
a2= a/2.;
b= sqrt(3)*a/2.0; // Altura del triángulo de la base.

paralelepipedo( 0, y,-a2, 0,y, a2,seccion,seccion);

paralelepipedo( 0, y,-a2, 0,y+e, a2,seccion,seccion);
paralelepipedo( 0, y, a2,-b,y+e, 0,seccion,seccion);
paralelepipedo( 0, y,-a2,-b,y+e, 0,seccion,seccion);

paralelepipedo(0,y,-a2,0,y+e,-a2,seccion,seccion);
paralelepipedo( 0,y,a2, 0,y+e,a2,seccion,seccion);
y=y+e;

for(i=1;i<n;++i)
	{
	// Barras horizontales
	paralelepipedo( 0, y,-a2, 0,y, a2,seccion,seccion);
	paralelepipedo( 0, y, a2,-b,y, 0,seccion,seccion);
	paralelepipedo(-b, y, 0,  0,y,-a2,seccion,seccion);
	
	// Barras oblicuas
	if(i%2) {
		paralelepipedo( 0, y,-a2, 0,y+e, a2,seccion,seccion);
		paralelepipedo( 0, y, a2,-b,y+e, 0,seccion,seccion);
		paralelepipedo(-b, y, 0,  0,y+e,-a2,seccion,seccion);
		}
	else {
		paralelepipedo( 0, y, a2, 0,y+e,-a2,seccion,seccion);
		paralelepipedo(-b, y, 0,  0,y+e, a2,seccion,seccion);
		paralelepipedo( 0, y, -a2,-b,y+e, 0,seccion,seccion);
	}
	// Barras verticales
	paralelepipedo(0,y,-a2,0,y+e,-a2,seccion,seccion);
	paralelepipedo( 0,y,a2, 0,y+e,a2,seccion,seccion);
	paralelepipedo(  -b,y, 0, -b,y+e,0,seccion,seccion);
	
	// Siguiente nivel
	y=y+e;
	}
	
	// Barras horizontales
	paralelepipedo( 0, y,-a2, 0,y, a2,seccion,seccion);
	paralelepipedo( 0, y, a2,-b,y, 0,seccion,seccion);
	paralelepipedo(-b, y, 0,  0,y,-a2,seccion,seccion);

glPopMatrix();
}

/**	void creaTorre(float h, float a, float b, int n)

Crea un fragmento de la terminacion de la estructura de una grua, 
con centro de las bases en
0,0,0 y 0,h,0. Las secciones de las bases tienen tamanyo axb
n es el numero de niveles que tiene la estructura.

Los perfiles tienen seccion cuadrada, dada por el parametro seccion.
	
Para crear la estructura se utiliza el procedimiento paralelepipedo.

**/
void creaTorre(float h, float a, float b, int n)

{
float x, y,z,a2,b2;
int i;
float m,e,da,db; //da es el decremento de seccion

if(n<1) { printf("\n Error: Numero de segmentos en torre menor que 1\n");return;}

// m= modulo(x1-x0,y1-y0,z1-z0);
m=h;
glPushMatrix();
// 	glTranslatef(x0,y0,z0);
// 	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
// 	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);
// Creamos la estructura vertical, con altura m

e=m/n;	// Altura entre dos niveles

da = a / (2.0*n);
db = b / (2.0*n);
y=0;
a2= a/2.;
b2= b/2.;
for(i=0;i<n;++i)
	{
	// Barras horizontales
	paralelepipedo(-a2,y,-b2, a2,y,-b2,seccion,seccion);
	paralelepipedo( a2,y,-b2, a2,y, b2,seccion,seccion);
	paralelepipedo( a2,y, b2,-a2,y, b2,seccion,seccion);
	paralelepipedo(-a2,y, b2,-a2,y,-b2,seccion,seccion);
	
	// Barras oblicuas
	if(i%2) {
		paralelepipedo(-a2,y,-b2, a2-da,y+e,-b2+db,seccion,seccion);
		paralelepipedo( a2,y,-b2, a2-da,y+e, b2-db,seccion,seccion);
		paralelepipedo( a2,y, b2,-a2+da,y+e, b2-db,seccion,seccion);
		paralelepipedo(-a2,y, b2,-a2+da,y+e,-b2+db,seccion,seccion);
		}
	else {
		paralelepipedo( a2,y,-b2,-a2+da,y+e,-b2+db,seccion,seccion);
		paralelepipedo( a2,y, b2, a2-da,y+e,-b2+db,seccion,seccion);
		paralelepipedo(-a2,y, b2, a2-da,y+e, b2-db,seccion,seccion);
		paralelepipedo(-a2,y,-b2,-a2+da,y+e, b2-db,seccion,seccion);	
	}
			
	// Barras verticales
	paralelepipedo(-a2,y,-b2,-a2+da,y+e,-b2+db,seccion,seccion);
	paralelepipedo( a2,y,-b2, a2-da,y+e,-b2+db,seccion,seccion);
	paralelepipedo(-a2,y, b2,-a2+da,y+e, b2-db,seccion,seccion);
	paralelepipedo( a2,y, b2, a2-da,y+e, b2-db,seccion,seccion);
	
	// Siguiente nivel
	y=y+e;
	a2 = a2 - da;
	b2 = b2 -db;
	}
	
// Barras horizontales de terminacion
paralelepipedo(-a2,y,-b2, a2,y,-b2,seccion,seccion);
paralelepipedo( a2,y,-b2, a2,y, b2,seccion,seccion);
paralelepipedo( a2,y, b2,-a2,y, b2,seccion,seccion);
paralelepipedo(-a2,y, b2,-a2,y,-b2,seccion,seccion);

glPopMatrix();
}

/**	void creaGancho( float alto)
Crea un gancho colgando del punto (0,0,0) de tamanyo alto
El gancho siempre esta vertical
**/

void creaGancho( float alto)

{
float esqueleto[5][2]={{0,0},{0,-0.3},{-0.3,-0.6},{0,-0.8},{0.2,-0.7}};
float normal[5][2]={{1,0},{0.89,0.45},{1,0},{0.2,0.98},{0.45,0.89}};
int i,N=5; // Número de puntos del esqueleto
float grueso=0.1;

glPushMatrix();
//	glTranslatef(x0,y0,z0);

for(i=1;i<N;++i){
	esqueleto[i][0]*=alto;
	esqueleto[i][1]*=alto;
}	
	
for(i=0;i<N-1;++i) {
	glShadeModel(GL_SMOOTH);
	glBegin( GL_QUAD_STRIP );{
		glNormal3f( normal[i][0],  normal[i][1], 0.0 );   
	      	glVertex3f( esqueleto[i][0]+grueso,  esqueleto[i][1], 0 );
		glNormal3f( normal[i+1][0],  normal[i+1][1], 0.0 );   
	      	glVertex3f( esqueleto[i+1][0]+grueso,  esqueleto[i+1][1], 0 );
		glNormal3f( 0.0, normal[i][1], -normal[i][0] );
 		glVertex3f(  esqueleto[i][0],  esqueleto[i][1], -grueso);
		glNormal3f( 0.0, normal[i+1][1], -normal[i+1][0] );
	      	glVertex3f(  esqueleto[i+1][0],  esqueleto[i+1][1], -grueso );
		glNormal3f( -normal[i][0], normal[i][1], 0.0 );   
	      	glVertex3f( esqueleto[i][0]-grueso,  esqueleto[i][1], 0 );
		glNormal3f( -normal[i+1][0], normal[i+1][1], 0.0 );   
	      	glVertex3f( esqueleto[i+1][0]-grueso,  esqueleto[i+1][1], 0 );
		glNormal3f( 0.0, normal[i][1], normal[i][0] );   
 		glVertex3f(  esqueleto[i][0],  esqueleto[i][1], grueso );
		glNormal3f( 0.0, normal[i+1][1], normal[i+1][0] );   	      	
		glVertex3f(  esqueleto[i+1][0],  esqueleto[i+1][1], grueso  );
		glNormal3f( normal[i][0], normal[i][1], 0.0 );   
	      	glVertex3f( esqueleto[i][0]+grueso,  esqueleto[i][1], 0 );
		glNormal3f( normal[i+1][0], normal[i+1][1], 0.0 );   
	      	glVertex3f( esqueleto[i+1][0]+grueso,  esqueleto[i+1][1], 0 );		
	glEnd();}
	}
i=N-1;
glBegin( GL_TRIANGLE_FAN );{
		glNormal3f( normal[i][0],  normal[i][1], 0.0 );   
	      	glVertex3f( esqueleto[i][0],  esqueleto[i][1], 0 );
i=N-2;	
		glNormal3f( normal[i][0], normal[i][1], 0 );
		glVertex3f( esqueleto[i][0]+grueso,  esqueleto[i][1], 0 );
		glNormal3f( 0.0, normal[i][1], -normal[i][0] );
		glVertex3f(  esqueleto[i][0],  esqueleto[i][1], -grueso );
		glNormal3f( -normal[i][0], normal[i][1], 0.0 );   
	      	glVertex3f( esqueleto[i][0]-grueso,  esqueleto[i][1], 0 );
		glNormal3f( 0.0, normal[i][1], normal[i][0] );   
 		glVertex3f(  esqueleto[i][0],  esqueleto[i][1], grueso );
		glNormal3f( normal[i][0], normal[i][1], 0.0 );   
	      	glVertex3f( esqueleto[i][0]+grueso,  esqueleto[i][1], 0 );
	glEnd();}
	
glPopMatrix();
glShadeModel(GL_FLAT);
}
