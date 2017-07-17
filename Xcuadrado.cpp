// Xcuadrado.cpp: implementation of the Xcuadrado class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Xcuadrado.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Xcuadrado::Xcuadrado(Punto3D * p1, Punto3D * p2, Punto3D * p3, Punto3D * p4) {
   vertices[0] = *p1;
   vertices[1] = *p2;
   vertices[2] = *p3;
   vertices[3] = *p4;

   RGBaristas[0] = 0.0;
   RGBaristas[1] = 0.0;
   RGBaristas[2] = 0.0;

   RGBcaras[0] = 1.0;
   RGBcaras[1] = 1.0;
   RGBcaras[2] = 1.0;
   pintar = false;
}

Xcuadrado::Xcuadrado() { }

Xcuadrado::~Xcuadrado() { }

void Xcuadrado::CalcularLandas(Visual v) {
   for (int j = 0; j < 4; j++) vertices[j].modL(Figura::calcularLanda(vertices[j], v));
}

void Xcuadrado::CalcularLandaMin() {
   double landa = vertices[0].cogerL();

   for (int j = 1; j < 4; j++) { 
      if (landa > vertices[j].cogerL()) {
         landa = vertices[j].cogerL();
      }
   }
   landaMin = landa;
}

int Xcuadrado::modNormal(Punto3D n) { 
   if ((normal.cogerX() == n.cogerX()) && (normal.cogerY() == n.cogerY()) && (normal.cogerY() == n.cogerY())) return -1;
   normal = n;
   return 0;
}

void Xcuadrado::dibujar(Visual v, Ventana win) {
   Punto2D aux1, aux2;
   Arista2D aux2D;
   Cara2D Cpintar(4);

   for (int n = 0; n < 4; n++) { 
      if ((vertices[n].cogerL() > 0) && (vertices[(n + 1) % 4].cogerL() > 0)) {
         aux1 = Figura::punto3Da2D(vertices[n], v, win);
         aux2 = Figura::punto3Da2D(vertices[(n + 1) % 4], v, win);		        	    
         aux2D = Arista2D(&aux1, &aux2);
         Cpintar.addArista2D(&aux2D);
      }
      else if (((vertices[n].cogerL() < 0) && (vertices[(n + 1) % 4].cogerL() > 0)) || 
         ((vertices[n].cogerL() > 0) && (vertices[(n + 1) % 4].cogerL() < 0))) {
         if ((vertices[n].cogerL() < 0) && (vertices[(n + 1) % 4].cogerL() > 0)) {
            aux1 = Figura::punto3Da2D(vertices[n], v, win);              // A' no es virtual
            aux2 = Figura::punto3Da2D(vertices[(n + 1) % 4], v, win);    // B' es virtual			   
            aux2 = Figura::solucionarVisibilidad(aux2, aux1);            // B''
            aux2D = Arista2D(&aux1, &aux2);
            Cpintar.addArista2D(&aux2D);			    
         }
         else {
            aux1 = Figura::punto3Da2D(vertices[n], v, win);              // A' es virtual
            aux2 = Figura::punto3Da2D(vertices[(n + 1) % 4], v, win);    // B' no es virtual			   
            aux1 = Figura::solucionarVisibilidad(aux1, aux2);            // A''
            aux2D = Arista2D(&aux1, &aux2);
            Cpintar.addArista2D(&aux2D);
         }
      }
   }

   if (pintar) {
      glColor3f(RGBcaras[0], RGBcaras[1], RGBcaras[2]);
      if (Cpintar.cogerCont2() == Cpintar.cogerNumAristas()) {
         Figura::calcularOrdenadas(&Cpintar);
         Figura::pintarCara(&Cpintar, win, v);
      }
   }
   glColor3f(RGBaristas[0], RGBaristas[1], RGBaristas[2]);
   for(int i = 0; i < Cpintar.cogerCont2(); i++) {
      if (Figura::pintarSegmentos(&(Cpintar.listarAristas() + i)->cogerP1(), &(Cpintar.listarAristas() + i)->cogerP2(), win))
         Figura::drawLine(int((Cpintar.listarAristas() + i)->cogerP1().cogerX()), int((Cpintar.listarAristas() + i)->cogerP1().cogerY()), int((Cpintar.listarAristas() + i)->cogerP2().cogerX()), int((Cpintar.listarAristas() + i)->cogerP2().cogerY()));
   }
   Cpintar.erase();
}

void Xcuadrado::modRGBaristas(float r, float g, float b) {
   RGBaristas[0] = r;
   RGBaristas[1] = g;
   RGBaristas[2] = b;
}

void Xcuadrado::modRGBcaras(float r, float g, float b) {
   RGBcaras[0] = r;
   RGBcaras[1] = g;
   RGBcaras[2] = b;
}