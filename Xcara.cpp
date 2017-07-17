// Xcara.cpp: implementation of the Xcara class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Xcara.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Xcara::Xcara(Punto3D * p1, Punto3D * p2, Punto3D * p3, Punto3D * p4) {
   verticesTapa[0] = *p1;
   verticesTapa[1] = *p2;
   verticesTapa[2] = *p3;
   verticesTapa[3] = *p4;
   open = false;

   RGBaristas[0] = 0.0;
   RGBaristas[1] = 0.0;
   RGBaristas[2] = 0.0;

   RGBcaras[0] = 1.0;
   RGBcaras[1] = 1.0;
   RGBcaras[2] = 1.0;
   pintar = false;
}

Xcara::~Xcara() { }

void Xcara::CalcularLandas(Visual v) {
   for (int j = 0; j < 4; j++) verticesTapa[j].modL(Figura::calcularLanda(verticesTapa[j], v));
}

void Xcara::CalcularLandaMin() {
   double landa = verticesTapa[0].cogerL();

   for (int j = 1; j < 4; j++) { 
      if (landa > verticesTapa[j].cogerL()) {
	     landa = verticesTapa[j].cogerL();
	  }
   }
   landaMin = landa;
}

int Xcara::modTapa(bool t) {
   if (t == open) return -1; 
   open = t;
   return 0;  
}

void Xcara::dibujar(Visual v, Ventana win) {
   Punto2D aux1, aux2;
   Arista2D aux2D;
   Cara2D Cpintar(4);

   if (open) {
      for (int n = 0; n < 4; n++) { 
         if ((verticesTapa[n].cogerL() > 0) && (verticesTapa[(n + 1) % 4].cogerL() > 0)) {
            aux1 = Figura::punto3Da2D(verticesTapa[n], v, win);
            aux2 = Figura::punto3Da2D(verticesTapa[(n + 1) % 4], v, win);
		    aux2D = Arista2D(&aux1, &aux2);
			Cpintar.addArista2D(&aux2D);
		 }
	     else if (((verticesTapa[n].cogerL() < 0) && (verticesTapa[(n + 1) % 4].cogerL() > 0)) || 
		    ((verticesTapa[n].cogerL() > 0) && (verticesTapa[(n + 1) % 4].cogerL() < 0))) {
		    if ((verticesTapa[n].cogerL() < 0) && (verticesTapa[(n + 1) % 4].cogerL() > 0)) {
               aux1 = Figura::punto3Da2D(verticesTapa[n], v, win);              // A' no es virtual
	           aux2 = Figura::punto3Da2D(verticesTapa[(n + 1) % 4], v, win);    // B' es virtual			   
			   aux2 = Figura::solucionarVisibilidad(aux2, aux1);                // B''
			   aux2D = Arista2D(&aux1, &aux2);
			   Cpintar.addArista2D(&aux2D);		    
			}
            else {
               aux1 = Figura::punto3Da2D(verticesTapa[n], v, win);              // A' es virtual
	    	   aux2 = Figura::punto3Da2D(verticesTapa[(n + 1) % 4], v, win);    // B' no es virtual			   
			   aux1 = Figura::solucionarVisibilidad(aux1, aux2);                // A''
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
}

void Xcara::modRGBaristas(float r, float g, float b) {
   RGBaristas[0] = r;
   RGBaristas[1] = g;
   RGBaristas[2] = b;
}

void Xcara::modRGBcaras(float r, float g, float b) {
   RGBcaras[0] = r;
   RGBcaras[1] = g;
   RGBcaras[2] = b;
}