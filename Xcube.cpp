// Xcube.cpp: implementation of the Xcube class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Xcube.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Xcube::Xcube(Punto3D * p1, Punto3D * p2, Punto3D * p3, Punto3D * p4, Punto3D * p5, Punto3D * p6, Punto3D * p7, Punto3D * p8) {
   vertices[0] = *p1; vertices[1] = *p2; vertices[2] = *p3; vertices[3] = *p4;
   vertices[4] = *p5; vertices[5] = *p6; vertices[6] = *p7; vertices[7] = *p8;

   aristas[0] = new Arista(&vertices[0], &vertices[1]);
   aristas[1] = new Arista(&vertices[1], &vertices[2]);
   aristas[2] = new Arista(&vertices[0], &vertices[3]);
   aristas[3] = new Arista(&vertices[2], &vertices[3]);
   aristas[4] = new Arista(&vertices[0], &vertices[4]);
   aristas[5] = new Arista(&vertices[4], &vertices[5]);
   aristas[6] = new Arista(&vertices[1], &vertices[5]);
   aristas[7] = new Arista(&vertices[5], &vertices[6]);
   aristas[8] = new Arista(&vertices[2], &vertices[6]);
   aristas[9] = new Arista(&vertices[4], &vertices[7]);
   aristas[10] = new Arista(&vertices[6], &vertices[7]);
   aristas[11] = new Arista(&vertices[3], &vertices[7]);
   
   caras[0] = new Cara(&vertices[0], &vertices[3], &vertices[2], &vertices[1]);
   caras[1] = new Cara(&vertices[1], &vertices[2], &vertices[6], &vertices[5]);
   caras[2] = new Cara(&vertices[2], &vertices[3], &vertices[7], &vertices[6]);
   caras[3] = new Cara(&vertices[3], &vertices[0], &vertices[4], &vertices[7]);
   caras[4] = new Cara(&vertices[5], &vertices[6], &vertices[7], &vertices[4]);
   caras[5] = new Cara(&vertices[0], &vertices[1], &vertices[5], &vertices[4]);

   RGBaristas[0] = 0.0;
   RGBaristas[1] = 0.0;
   RGBaristas[2] = 0.0;

   RGBcaras[0] = 1.0;
   RGBcaras[1] = 1.0;
   RGBcaras[2] = 1.0;
   pintar = false;
}

Xcube::~Xcube() { }

void Xcube::CalcularLandas(Visual v) {
   for (int j = 0; j < 8; j++) vertices[j].modL(Figura::calcularLanda(vertices[j], v));
}

void Xcube::CalcularLandaMin() {
   double landa = vertices[0].cogerL();

   for (int j = 1; j < 8; j++) { 
      if (landa > vertices[j].cogerL()) {
	     landa = vertices[j].cogerL();
	  }
   }
   landaMin = landa;
}

void Xcube::dibujar(Visual v, Ventana win) {

   Punto2D aux1, aux2;
   Arista2D aux2D;
   Cara2D Cpintar(4);

   for (int i = 0; i < 6; i++) caras[i]->modVisible(Figura::calcularCaras(v, * caras[i]));

   for (int c = 0; c < 6; c++) {
      if (this->caras[c]->visible() == 0) {
		  for (int n = 0; n < 4; n++) {
	         if (((*(this->caras[c]->listarVertices() + n))->cogerL() > 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 4)))->cogerL() > 0)) {
		        aux1 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + n)), v, win);
	    	    aux2 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + ((n + 1) % 4))), v, win);
				aux2D = Arista2D(&aux1, &aux2);
				Cpintar.addArista2D(&aux2D);			
			 }
			 else if ((((*(this->caras[c]->listarVertices() + n))->cogerL() > 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 4)))->cogerL() < 0)) || 
				(((*(this->caras[c]->listarVertices() + n))->cogerL() < 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 4)))->cogerL() > 0))) {
				 if (((*(this->caras[c]->listarVertices() + n))->cogerL() > 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 4)))->cogerL() < 0)) {
                    aux1 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + n)), v, win);              // A' no es virtual
	    	        aux2 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + ((n + 1) % 4))), v, win);  // B' es virtual	
				    aux2 = Figura::solucionarVisibilidad(aux2, aux1);                                          // B''
					aux2D = Arista2D(&aux1, &aux2);
					Cpintar.addArista2D(&aux2D);	
				 }
                 else {
                    aux1 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + n)), v, win);              // A' es virtual
	    	        aux2 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + ((n + 1) % 4))), v, win);  // B' no es virtual	
				    aux1 = Figura::solucionarVisibilidad(aux1, aux2);                                          // A''
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
}

void Xcube::modRGBaristas(float r, float g, float b) {
   RGBaristas[0] = r;
   RGBaristas[1] = g;
   RGBaristas[2] = b;
}

void Xcube::modRGBcaras(float r, float g, float b) {
   RGBcaras[0] = r;
   RGBcaras[1] = g;
   RGBcaras[2] = b;
}
