/*
 		glui.c

User interface extension for glut

Author:  Rafael García Fernández		Diciembre 2011

 
 Copyright (c) Rafael Garcia Fernandez (Univ. de Granada, SPAIN)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html


Description
===========

This file contains the code for the glui functions.


To do
=====

Avoid dimissing the height bellow a minimum

*/
#include "glui.h"
#include <stdio.h>

#define GLUI_MAX_TOOLBAR_MENUS 10
#define GLUI_MAX_ICONMENU_OPTIONS 12

// ================= Internal data structures ===================
int 	GLUI_WINDOWID=-1,	// Main window identifier 
	GLUI_WINDOWHEIGHT,	// Main window height
	GLUI_WINDOWWIDTH,	// Main window width
	GLUI_CANVASHEIGHT,	// Canvas height
	GLUI_CANVASWIDTH,	// Canvas width
	GLUI_CANVASID=-1,	// Canvas id
	GLUI_TOOLBARHEIGHT=24,	// height of menus in pixels
	GLUI_MENUWIDTH=80,	// width of menus in pixels
	GLUI_ICONSIZE=50,	// size for icons
	GLUI_TOOLBARMENUS=-1,	// number of menus	
	GLUI_OPENMENU=-1,	// identifier of menu open
	GLUI_ICONMENUS=-1,	// number of actual icon in the menu
	GLUI_ICONNX=1,		// Number of icon columns
	GLUI_ICONSIZE,		// size of the icon in the menu
	GLUI_OUTPUTX,
	GLUI_OUTPUTY,		// position for text output
	GLUI_OUTPUTID,		
	GLUI_INPUTX,
	GLUI_INPUTY,		// position for text input window
	GLUI_INPUTID,		// identifier for text input window
	GLUI_INPUTN=0;		// number of character in the input string

char 	GLUI_OUTPUT[64];	// Output string
unsigned  char	GLUI_INPUT[32];		// Input string

void (*GLUI_INPUTFUNC) ( unsigned char *name);	// input callback


typedef struct {
	int windowId;		// Window identifier
	int n;			// Number of options
	char *name;		// Name
	void (*func) (int value);	// callback
	int menu;		// glut menu
	int isMouseOn;
	} GLUI_TOOLBAR_STRUCT;

GLUI_TOOLBAR_STRUCT GLUI_TOOLBAR_DATA[GLUI_MAX_TOOLBAR_MENUS];

typedef struct {
	int windowId;		// Window identifier
	int isMouseOn;
	} GLUI_ICONMENU_STRUCT;

GLUI_ICONMENU_STRUCT GLUI_ICONMENU_DATA[GLUI_MAX_ICONMENU_OPTIONS];


void glui_compute_canvas_size()
/*
2
toobar
5
canvas
5
toolbar
2

5 canvas 5 icon 2
*/
{
GLUI_CANVASHEIGHT=GLUI_WINDOWHEIGHT-2*GLUI_TOOLBARHEIGHT-14;	// 4 ext. border
GLUI_CANVASWIDTH=GLUI_WINDOWWIDTH-GLUI_ICONSIZE*GLUI_ICONNX-12;	//
GLUI_OUTPUTX=5;
GLUI_INPUTX=GLUI_CANVASWIDTH/2+10;
GLUI_OUTPUTY=GLUI_WINDOWHEIGHT-GLUI_TOOLBARHEIGHT-2;
GLUI_INPUTY=GLUI_OUTPUTY+2;
}


int gluiGetWindowX()
{
int x,o,ventana;
x = glutGet(GLUT_WINDOW_X);
ventana=glutGetWindow();

glutSetWindow( GLUI_WINDOWID );
o = glutGet(GLUT_WINDOW_X);

glutSetWindow( ventana );
return x-o;
}

int gluiGetWindowY()
{
int y,o,ventana;
y = glutGet(GLUT_WINDOW_Y);
ventana=glutGetWindow();

glutSetWindow( GLUI_WINDOWID );
o = glutGet(GLUT_WINDOW_Y);

glutSetWindow( ventana );
return y-o;
}


void glui_reshape(GLsizei ancho,GLsizei alto)
/*
	Reshape the main window
*/
{
int ventana,k;


// compute canvax size 
GLUI_WINDOWHEIGHT=alto;
GLUI_WINDOWWIDTH=ancho;
glui_compute_canvas_size();

// ventana=glutGetWindow();

glutSetWindow( GLUI_WINDOWID );
glViewport(0,0,ancho,alto);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GLUI_WINDOWWIDTH,0,GLUI_WINDOWHEIGHT,0,1);
glutPostRedisplay();

for(k=0;k<GLUI_TOOLBARMENUS;++k) {
 	glutSetWindow(GLUI_TOOLBAR_DATA[k].windowId);
	glutPostRedisplay();
	}

for(k=0;k<GLUI_ICONMENUS;++k) {
 	glutSetWindow(GLUI_ICONMENU_DATA[k].windowId);
	// Cambiar posicion de la ventana
	glutPositionWindow( GLUI_CANVASWIDTH+10, k*(GLUI_ICONSIZE+2)+GLUI_TOOLBARHEIGHT);
	glutPostRedisplay();
	}

// Reshape output
glutSetWindow(GLUI_OUTPUTID);
glutPositionWindow(GLUI_OUTPUTX,GLUI_OUTPUTY);
glutReshapeWindow(GLUI_CANVASWIDTH/2-4,GLUI_TOOLBARHEIGHT-4);
glutPostRedisplay();

// Reshape input
/*glutSetWindow(GLUI_INPUTID);
glutPositionWindow(GLUI_INPUTX,GLUI_INPUTY);
glutReshapeWindow(GLUI_CANVASWIDTH/2-4,GLUI_TOOLBARHEIGHT-4);
glutPostRedisplay();*/

glutSetWindow( GLUI_CANVASID );
if( GLUI_CANVASHEIGHT>0 && GLUI_CANVASWIDTH>0)		// %% This must not happen!!
	glutReshapeWindow( GLUI_CANVASWIDTH, GLUI_CANVASHEIGHT);
glutPostRedisplay();

// glutSetWindow( ventana );
}

void gluiPostRedisplay()
/*
	Redisplay the canvas
*/
{
glutSetWindow( GLUI_CANVASID );
glutPostRedisplay();
}

void glui_display()
/*
	Fill the main window

	The border decoration are drawn here.
*/
{
float x0,x1,x2,x3,y0,y1,y2,y3;

glClearColor(0.8,0.8,0.8,1);
  // Inicializa el buffer de color
glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

x0= 0;
x1= 5;
x2= x1+GLUI_CANVASWIDTH;
x3=x2+5;

y0= GLUI_WINDOWHEIGHT- GLUI_TOOLBARHEIGHT -2;
y1= y0- 5;
y2= y1 - GLUI_CANVASHEIGHT;
y3=y2-5;

glLineWidth(2);	
glBegin( GL_QUADS);{
	glColor3f(0.9,0.9,0.9);
	glVertex2f( x0, y0);
  	glVertex2f( x1, y1);
   	glVertex2f( x2, y1);
     	glVertex2f( x3, y0);

	glColor3f(0.85,0.85,0.85);
	glVertex2f( x3, y0);
  	glVertex2f( x2, y1);
   	glVertex2f( x2, y2);
     	glVertex2f( x3, y3);

	glColor3f(0.65,0.65,0.65);
	glVertex2f( x0, y3);
  	glVertex2f( x1, y2);
   	glVertex2f( x2, y2);
     	glVertex2f( x3, y3);

	glColor3f(0.7,0.7,0.7);
	glVertex2f( x0, y0);
  	glVertex2f( x1, y1);
   	glVertex2f( x1, y2);
     	glVertex2f( x0, y3);
   	}glEnd();

glutSwapBuffers();
glutSetWindow( GLUI_CANVASID );
}

void glui_displayOutput()
/*
	Fill the output window
*/
{
int x,k;

glPushAttrib(GL_CURRENT_BIT);
// x = glutGet(GLUT_WINDOW_X);
glutSetWindow( GLUI_OUTPUTID);
glClearColor(0.8,0.8,0.8,1);
  // Inicializa el buffer de color
glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

// draw text
glColor3f( 0.0,0.0,0.0);
glRasterPos2f(-0.9,-0.8);
for(k=0; GLUI_OUTPUT[k]!= 0;++k) {
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) GLUI_OUTPUT[k]);
	}
glPopAttrib();
glutSwapBuffers();
// glutSetWindow( x );
glutSetWindow( GLUI_CANVASID );
}

void glui_displayInput()
/*
	Fill the input window
*/
{
int x,k;

glPushAttrib(GL_CURRENT_BIT);
// x = glutGet(GLUT_WINDOW_X);
glutSetWindow( GLUI_INPUTID);
glClearColor(1.0,1.0,1.0,1);
  // Inicializa el buffer de color
glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

// draw text
glColor3f( 0.0,0.0,0.0);
glRasterPos2f(-0.9,-0.7);
for(k=0; GLUI_INPUT[k]!= 0;++k) {
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) GLUI_INPUT[k]);
	}
glPopAttrib();
glutSwapBuffers();
// glutSetWindow( x );
glutSetWindow( GLUI_CANVASID );
}


int gluiCreateWindow(char *name) 
/* 
--------------------------------------------------------------
inputs
	name: name of the window

return
	glut identifier of the window	

effects
	creates a window for the GL application, to contains both menus 
	and a drawing canvax. The window parameters (size, position, etc)
	are defined by the glut environment, as it calls glutCreateWindow.

errors
	glut is not initialized

usage
	gluiCreateWindow("MyWindow");
--------------------------------------------------------------
*/
{
int state;

// check that glut is initialized
state= 1; //glutGet(GLUT_INIT_STATE);	// if 0 gl is not initialized
if(state) {
	// create main window
	GLUI_WINDOWID= glutCreateWindow(name);
	// Initialize data structures
	GLUI_WINDOWHEIGHT= glutGet(GLUT_WINDOW_HEIGHT);
	GLUI_WINDOWWIDTH= glutGet(GLUT_WINDOW_WIDTH);
	glutReshapeFunc(glui_reshape);
	glutDisplayFunc(glui_display);
	}
else printf("GLUI ERROR: OpenGL has not been initialied. Use glutInit.\n");

// %% To do: draw the background
}


void gluiCreateToolbar()
/* 
--------------------------------------------------------------
inputs
	none

return
	void	

effects
	creates the toolbar for the glui windodow.
	if the toolbar was already created it is cleared.

errors
	the glui window has not been created


usage
	gluiCreateToobar();
--------------------------------------------------------------
*/
{
// Check that gui window has been created

if(GLUI_WINDOWID>0) {
		// Initialize data structures
		GLUI_TOOLBARMENUS=0;	// number of actual menus
	}
else printf("GLUI ERROR: GLUI has not been initialied. Use gluiCreateWindow.\n");
}


int gluiCloseMenu( )
/* 
	Check if there is a Menu open and close it.ç

	Internally called by:  gluiCreateMenu, gluiCreateIconMenu,
	gluiCreateCanvas() 
*/
{
if(GLUI_OPENMENU>-1) {
	//there is a menu already created
	GLUI_OPENMENU=-1;

// && To Do: if there is no options apply callback to mouse event
	}
}


void glui_iconFeedback()
{
glColor3f(0,0,0);
glLineWidth(2);	
glBegin( GL_LINE_STRIP );{
	glVertex2f( -0.9, -0.9);
  	glVertex2f( 0.9, -0.9);
   	glVertex2f( 0.9, 0.9);
     	glVertex2f( -0.9, 0.9); 
	glVertex2f( -0.9, -0.9);}
   	glEnd();
}

void glui_displayMenu()
/*
	Fill the menu window
*/
{
int x,mw,k;	// current menu

// Get current menu. (This must be improved
//glPushAttrib(GL_CURRENT_BIT);

x = gluiGetWindowX();
mw= x / GLUI_MENUWIDTH;
glClearColor(0.8,0.8,0.8,1);
  // Inicializa el buffer de color
glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

// draw text
glColor3f( 0.0,0.0,0.0);
glRasterPos2f(-0.7,-0.4);
for(k=0;k<10;++k) {
    if(((int) GLUI_TOOLBAR_DATA[mw].name[k])== 0)
	k=10;
    else
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) GLUI_TOOLBAR_DATA[mw].name[k]);
    if(GLUI_TOOLBAR_DATA[mw].isMouseOn) glui_iconFeedback();
	
    }
//glPopAttrib();

glutSwapBuffers();
if(GLUI_CANVASID>0) glutSetWindow( GLUI_CANVASID );
}


void gluiMenuEntryFunc( int state)
{
int x,k;

x = gluiGetWindowX();
k= (x+1)/GLUI_MENUWIDTH;

//GLUI_MENUWIDTH*GLUI_OPENMENU
if(k>-1 && k <GLUI_TOOLBARMENUS) {
   if(state==GLUT_LEFT) {
	GLUI_TOOLBAR_DATA[k].isMouseOn=0;
	glutHideOverlay();
	}
   else {
	GLUI_TOOLBAR_DATA[k].isMouseOn=1;
	}
   glutPostRedisplay();
   }
}


int gluiCreateMenu( char *name, void (*func) (int value))
/* 
--------------------------------------------------------------
inputs
	name: name of the toolbar menu (will be displayed on the interface)
	func: callback function that will process this menu.
return
	glut identifier of the subwindow (A glut window is allocated 
	for every toolbar menu).

effects
	creates a subwindow for the toolbar and allocates the new menu.
	Menus are created as glut menus and attached using the left button.
	
	If a menu was already created it is closed.

errors
	the toolbar has not been created

usage
	gluiCreateMenu("MyMenu",myCallBack);
--------------------------------------------------------------
*/
{
int ventana,mw;

ventana=glutGetWindow();

// Check that the toolbar has been initialized
if(GLUI_TOOLBARMENUS>-1) {
    // Check if there is a menu already created
    gluiCloseMenu();
    if( GLUI_TOOLBARMENUS <= GLUI_MAX_TOOLBAR_MENUS) {
	GLUI_OPENMENU=GLUI_TOOLBARMENUS;
	
	// Create a window for the menu
	glutSetWindow( GLUI_WINDOWID );	// select main glui window
	mw=glutCreateSubWindow(GLUI_WINDOWID,  GLUI_MENUWIDTH*GLUI_OPENMENU,1, GLUI_MENUWIDTH-12, GLUI_TOOLBARHEIGHT);

	// allocate menu information
	GLUI_TOOLBAR_DATA[GLUI_OPENMENU].windowId=mw;	// Window identifier
	GLUI_TOOLBAR_DATA[GLUI_OPENMENU].n=0;		// Number of options
	GLUI_TOOLBAR_DATA[GLUI_OPENMENU].name=name;	// Name
	GLUI_TOOLBAR_DATA[GLUI_OPENMENU].func=func;	// callback	
	GLUI_TOOLBAR_DATA[GLUI_OPENMENU].isMouseOn=0;
	// Set the display function
	glutDisplayFunc(glui_displayMenu);
  	GLUI_TOOLBAR_DATA[GLUI_OPENMENU].menu = glutCreateMenu( func );
	glutEntryFunc(gluiMenuEntryFunc);	
	// attach menu to left button
	glutAttachMenu( GLUT_LEFT_BUTTON );

	// Increment the number of menus	
	GLUI_TOOLBARMENUS+=1;	
	}
    else printf("GLUI ERROR: Too many menus (modify GLUI_MAX_TOOLBAR_MENUS in glui.c and recompile).\n");
    }
else printf("GLUI ERROR: GLUI toolbar has not been initialied. Use gluiCreateToolbar.\n");

}


void gluiAddSubMenu( char *name, void (*func) (int value))
{

}

void gluiAddMenuEntry(  char *name, int value )
/* 
--------------------------------------------------------------
inputs
	name: name of the option to be displayed
	value: integer code that will be passed back to the menu call back 
		function when this option is choosen

return
	void

effects
	Add a new option at the bottom of the current menu

errors
	there is no glui menu open

usage
	gluiAddMenuEntry("Option",3);
--------------------------------------------------------------
*/
{
// Check if there is a menu already created
if(GLUI_OPENMENU>-1) 
 glutAddMenuEntry( name, value );
else printf("GLUI ERROR: GLUI menu has not been initialied. Use gluiCreateMenu.\n");
}


void gluiCreateIconMenu( int size ) //, int nx)
{
/* 
--------------------------------------------------------------
inputs
	size: size in pixel of every icon 
return
	none

effects
	Initializes the icons menu-
	If there is a option menu open it is closed

errors
	the gui has not been initialized

usage
	gluiCreateIconMenu(30);
--------------------------------------------------------------
*/

if(GLUI_WINDOWID>0) {
   	// Close toolbar if it has been initialized
   	gluiCloseMenu();
  	// Initialize data structures
	GLUI_ICONMENUS=0;	// number of actual icon in the menu
	GLUI_ICONSIZE=size;	// size of the icon in the menu
//	GLUI_ICONNX=nx;
	// Computes canvas size
	glui_compute_canvas_size();
	}
else printf("GLUI ERROR: GLUI has not been initialied. Use gluiCreateWindow.\n");
}	


void gluiIconEntryFunc( int state)
{
int y,k;

y = gluiGetWindowY();
k= (y-GLUI_TOOLBARHEIGHT)/(GLUI_ICONSIZE+2);
//GLUI_ICONMENUS*(GLUI_ICONSIZE+2)+GLUI_TOOLBARHEIGHT
if(k>-1 && k <=GLUI_ICONMENUS) {
   if(state==GLUT_LEFT) {
	GLUI_ICONMENU_DATA[k].isMouseOn=0;
	}
   else {
	GLUI_ICONMENU_DATA[k].isMouseOn=1;
	}
   glutPostRedisplay();
   }
}

int gluiAddIcon() //int size, int x, int y) // (*func) () )
/* 
--------------------------------------------------------------
inputs
	none
return
	icon window identifier
//	function to be used as idlefunc while the mouse is over

effects
	Create a subwindow for the icon. This window become the actual
	window.
	The caller module is responsible to create callback for 
	rendering and selecting at less.


errors
	the gui icon menu has not been initialized

usage
	myIcon = gluiAddIcon();
--------------------------------------------------------------
*/
{
int mw;

// Check that the icons menu has been already created
if(GLUI_ICONMENUS>-1) {
    // Create a window for the menu
    glutSetWindow( GLUI_WINDOWID );	// select main glui window
    if( GLUI_ICONMENUS <= GLUI_MAX_ICONMENU_OPTIONS) {
	// Create a windows for the icon 	
	mw=glutCreateSubWindow(GLUI_WINDOWID, GLUI_CANVASWIDTH+10, GLUI_ICONMENUS*(GLUI_ICONSIZE+2)+GLUI_TOOLBARHEIGHT ,GLUI_ICONSIZE,GLUI_ICONSIZE);

	// store window identifier
	GLUI_ICONMENU_DATA[GLUI_ICONMENUS].windowId=mw;
	
	GLUI_ICONMENU_DATA[GLUI_ICONMENUS].isMouseOn=0;
	// increment number of actual icon in the menu
	GLUI_ICONMENUS+=1;
	glutEntryFunc(gluiIconEntryFunc);	
	}
    else 
    printf("GLUI ERROR: Too many icons (modify  GLUI_MAX_ICONMENU_OPTIONS in glui.c and recompile).\n");
    }
else printf("GLUI ERROR: GLUI icon menu has not been initialied. Use gluiCreateIconMenu.\n");

return mw;
}


void gluiKeyboarInput( unsigned char k, int x, int y )
{
int n,i;

n=GLUI_INPUTN;	
if(n<31) {
	GLUI_INPUT[n]=k;
	GLUI_INPUTN=n+1;
	}
GLUI_INPUT[GLUI_INPUTN]=0;
glutPostRedisplay();
}

void gluiSpecialInput( int k, int x, int y)
{
int n;
switch (k) {
  case GLUT_KEY_LEFT:
	n=GLUI_INPUTN;	
	if(n>0) {
		GLUI_INPUT[n-1]=0;
		GLUI_INPUTN=n-1;
		}
  	break;
   case GLUT_KEY_DOWN:
	GLUI_INPUTFUNC(GLUI_INPUT); // run the call back
	GLUI_INPUTN=0;
	GLUI_INPUT[0]=0;
	break;
  }
glutPostRedisplay();
}

void gluiInput(void (*func) (unsigned char *name))
{
/* 
--------------------------------------------------------------
inputs
	function to be used as callback for the input events.
	The function signature must be 
	void func();

return
	void

effects
	The function passed as argument is call when a text is input 
	on the input area.
	Initialize the input string;

usage
	gluiInput(inputCB);
--------------------------------------------------------------
*/
GLUI_INPUTN=0;
GLUI_INPUT[0]=0;
GLUI_INPUTFUNC=func;

// create glut subwindow for input
GLUI_INPUTID=glutCreateSubWindow(GLUI_WINDOWID, GLUI_INPUTX,GLUI_INPUTY,GLUI_CANVASWIDTH/2-20,GLUI_TOOLBARHEIGHT-4);
GLUI_INPUT[0]=0;
glutDisplayFunc(glui_displayInput);
glutKeyboardFunc(gluiKeyboarInput);
glutSpecialFunc(gluiSpecialInput);

}


int gluiCreateCanvas()
/* 
--------------------------------------------------------------
inputs
	none

return
	glut identifier of the drawing window	

effects
	creates a window where the GL application can draw. The window
	size is computed from the main window size. All other parameter
	are defined by the glut environment.
	Created the window for the output and input areas.
usage
	myCanvas=gluiCreateCanvas();
--------------------------------------------------------------
*/
{
// check that glui window is created
if(GLUI_WINDOWID>0) {
	
	// Set the main window as active window
	glutSetWindow( GLUI_WINDOWID );

	// compute canvax size
	glui_compute_canvas_size();

	// create glut subwindow for output
	GLUI_OUTPUTID=glutCreateSubWindow(GLUI_WINDOWID, GLUI_OUTPUTX,GLUI_OUTPUTY,GLUI_CANVASWIDTH/2-4,GLUI_TOOLBARHEIGHT-4);
 	glutDisplayFunc(glui_displayOutput);

	// create glut subwindow for canvas
	GLUI_CANVASID=glutCreateSubWindow(GLUI_WINDOWID, 5,GLUI_TOOLBARHEIGHT+7,GLUI_CANVASWIDTH,GLUI_CANVASHEIGHT);
 //GLUI_TOOLBARHEIGHT,10,10); // GLUI_CANVASWIDTH, 10);GLUI_CANVASHEIGHT);

	}
else printf("GLUI ERROR: glui window has not been created. Use gluiCreateWindow.\n");
return GLUI_CANVASID;
}

void gluiOutput( char *name)
/* 
--------------------------------------------------------------
inputs
	string to be displayed

return
	none

effects
	render the text on the output area

usage
	gluiOutout( "hola");
--------------------------------------------------------------
*/

{
int k;

for(k=0;k<63;++k)
	GLUI_OUTPUT[k]=name[k];
GLUI_OUTPUT[63]=0;
glutSetWindow(GLUI_OUTPUTID);
glutPostRedisplay();
glutSetWindow(GLUI_CANVASID);
}

int gluiIsMouseOverIcon()
{
int y,k;

y = gluiGetWindowY();
k= (y-GLUI_TOOLBARHEIGHT)/(GLUI_ICONSIZE+2);

if(k>-1 && k <=GLUI_ICONMENUS)
	return GLUI_ICONMENU_DATA[k].isMouseOn;
else
	return 0;
}

void gluiClearColor()
{
glClearColor(0.8,0.8,0.8,1);
}

void gluiSetCanvasWindow()
{
glutSetWindow(GLUI_CANVASID);
}

// Fijar glutMenuStatusFunc para que a la salida del menu cambie al canvas??
