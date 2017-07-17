// Ventana.cpp: implementation of the Ventana class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ventana.h"
#include "Figura.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ventana::Ventana(int width, int height, double m_width, double m_height) {
   ancho = width;
   alto = height;
   m_ancho = m_width;
   m_alto = m_height;
   fscreen = false;
}

Ventana::~Ventana() { }

int Ventana::dibujar(void) {
   
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);                                 // Modo de Pantalla RGB, Doble Buffer
   glutInitWindowSize(ancho, alto);                                             // Ventana -> Dimensión
   glutInitWindowPosition(100, 100);                                            // Ventana -> Posición
   return (glutCreateWindow("Geometria Computacional"));						// Ventana -> Titulo
}

void Ventana::inicializar(void) {
   Figura::clearScreen();                                                       // Borramos la pantalla
   glOrtho(0, ancho, alto, 0, 0 ,1);                                            // Visión Planar 2D
}

void Ventana::fullScreen(void) {                                                // Pantalla completa
   if (!fscreen) {
      glutFullScreen();
	  fscreen = true;
   }
   else {
      glutReshapeWindow(ancho, alto);
      glutPositionWindow(100, 100);
	  fscreen = false;
   }
}

