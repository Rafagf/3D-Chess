/*
 		glui.h

User interface extension for glut

Author:  Rafael Garcia Fernandez

 
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

This file contains headers for functions included in the module glui.c

*/
#include <GL/glut.h>
#ifndef __glui_h_
#define __glui_h_



int gluiCreateWindow(char *name);
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

void gluiCreateToolbar();
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

int gluiCreateMenu( char *name, void (*func) (int value));
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
void gluiAddSubMenu( char *name, void (*func) (int value));

void gluiAddMenuEntry(  char *name, int value );
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

void gluiCreateIconMenu( int size); //, int nx);	
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

int gluiAddIcon(); //int size, int x, int y);
/* 
--------------------------------------------------------------
inputs
	none
return
	icon window identifier

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

void gluiInput(void (*func) (unsigned char *name));	
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

usage
	gluiInput(inputCB);
--------------------------------------------------------------
*/

int gluiCreateCanvas();
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

void gluiOutput( char *name);
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
void gluiPostRedisplay();
/*
	Redisplay the canvas
*/

int gluiIsMouseOverIcon();
/*

return
	1 if the nouse is on the active icon window
	0 otherwise
	undefined if the active window is not an icon
*/
void gluiClearColor();
/*

*/

void glui_iconFeedback();
/*


*/

void gluiSetCanvasWindow();
#endif

