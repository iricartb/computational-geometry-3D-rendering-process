// Xdodecaedro.cpp: implementation of the Xdodecaedro class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Xdodecaedro.h"
#include "math.h"
#include "Arista2D.h"

#define PI acos(-1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Xdodecaedro::Xdodecaedro(double r) {
   double l, a, ra, apocaras;
   int i;
   
   l = ((4 * r) / sqrt(18 + (6 * sqrt(5))));
   a = (l / 2) * sqrt((25 + (11 * sqrt(5))) / 10);
   ra = (2 * l) / sqrt(10 - 2 * sqrt(5));
   apocaras = ra * cos((36 * PI) / 180);

   for (i = 0; i < 5; i++) {
      vertices[i] = Punto3D(cos(((i + 1) * 72 * PI) / 180) * ra, sin(((i + 1) * 72 * PI) / 180) * ra, 0); 
      vertices[i + 5] = Punto3D(cos(((i + 1) * 72 * PI) / 180) * (-apocaras - ((sqrt(5) / 5) * (ra + apocaras))), sin(((i + 1) * 72 * PI) / 180) * (-apocaras - ((sqrt(5) / 5) * (ra + apocaras))), 2 * (sqrt(5) / 5) * (ra + apocaras));
      vertices[i + 10] = Punto3D(cos(((i + 1) * 72 * PI) / 180) * -ra, sin(((i + 1) * 72 * PI) / 180) * -ra, 2 * a);
      vertices[i + 15] = Punto3D(cos(((i + 1) * 72 * PI) / 180) * (apocaras + ((sqrt(5) / 5) * (ra + apocaras))), sin(((i + 1) * 72 * PI) / 180) * (apocaras + ((sqrt(5) / 5) * (ra + apocaras))), (2 * a) - (2 * ((sqrt(5) / 5) * (ra + apocaras))));
   }

   for (i = 0; i < 20; i++){
      vertices[i].modX(-1 * (vertices[i].cogerX()) + 5);
      vertices[i].modY(-1 * (vertices[i].cogerY()) + 5);
   }
        
   caras[0] = new Cara(&vertices[0], &vertices[4], &vertices[3], &vertices[2], &vertices[1]); 
   caras[1] = new Cara(&vertices[0], &vertices[1], &vertices[16], &vertices[8], &vertices[15]);  
   caras[2] = new Cara(&vertices[1], &vertices[2], &vertices[17], &vertices[9], &vertices[16]);
   caras[3] = new Cara(&vertices[2], &vertices[3], &vertices[18], &vertices[5], &vertices[17]);
   caras[4] = new Cara(&vertices[3], &vertices[4], &vertices[19], &vertices[6], &vertices[18]);
   caras[5] = new Cara(&vertices[4], &vertices[0], &vertices[15], &vertices[7], &vertices[19]);
   caras[6] = new Cara(&vertices[10], &vertices[11], &vertices[12], &vertices[13], &vertices[14]);
   caras[7] = new Cara(&vertices[10], &vertices[5], &vertices[18], &vertices[6], &vertices[11]);
   caras[8] = new Cara(&vertices[11], &vertices[6], &vertices[19], &vertices[7], &vertices[12]);
   caras[9] = new Cara(&vertices[12], &vertices[7], &vertices[15], &vertices[8], &vertices[13]);
   caras[10] = new Cara(&vertices[13], &vertices[8], &vertices[16], &vertices[9], &vertices[14]);
   caras[11] = new Cara(&vertices[14], &vertices[9], &vertices[17], &vertices[5], &vertices[10]); 

   RGBaristas[0] = 0.0;
   RGBaristas[1] = 0.0;
   RGBaristas[2] = 0.0;

   RGBcaras[0] = 1.0;
   RGBcaras[1] = 1.0;
   RGBcaras[2] = 1.0;
   pintar = false;
}

Xdodecaedro::~Xdodecaedro() { }

void Xdodecaedro::CalcularLandas(Visual v) {
   for (int j = 0; j < 20; j++) vertices[j].modL(Figura::calcularLanda(vertices[j], v));
}

void Xdodecaedro::CalcularLandaMin() {
   double landa = vertices[0].cogerL();

   for (int j = 1; j < 20; j++) { 
      if (landa > vertices[j].cogerL()) {
	     landa = vertices[j].cogerL();
	  }
   }
   landaMin = landa;
}

void Xdodecaedro::dibujar(Visual v, Ventana win) {

   Punto2D aux1, aux2;
   Arista2D aux2D;
   Cara2D Cpintar(5);

   for (int i = 0; i < 12; i++) caras[i]->modVisible(Figura::calcularCaras(v, * caras[i]));

   for (int c = 0; c < 12; c++) {
      if (this->caras[c]->visible() == 0) {
		  for (int n = 0; n < 5; n++) {
	         if (((*(this->caras[c]->listarVertices() + n))->cogerL() > 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 5)))->cogerL() > 0)) {
		        aux1 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + n)), v, win);
	    	    aux2 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + ((n + 1) % 5))), v, win);
				aux2D = Arista2D(&aux1, &aux2);
				Cpintar.addArista2D(&aux2D);
			 }
			 else if ((((*(this->caras[c]->listarVertices() + n))->cogerL() > 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 5)))->cogerL() < 0)) || 
				(((*(this->caras[c]->listarVertices() + n))->cogerL() < 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 5)))->cogerL() > 0))) {
				 if (((*(this->caras[c]->listarVertices() + n))->cogerL() > 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 5)))->cogerL() < 0)) {
                    aux1 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + n)), v, win);              // A' no es virtual
	    	        aux2 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + ((n + 1) % 5))), v, win);  // B' es virtual			   
				    aux2 = Figura::solucionarVisibilidad(aux2, aux1);                                          // B''
				    aux2D = Arista2D(&aux1, &aux2);
				    Cpintar.addArista2D(&aux2D);			    
				 }
                 else {
                    aux1 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + n)), v, win);              // A' es virtual
	    	        aux2 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + ((n + 1) % 5))), v, win);  // B' no es virtual			   
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

void Xdodecaedro::modRGBaristas(float r, float g, float b) {
   RGBaristas[0] = r;
   RGBaristas[1] = g;
   RGBaristas[2] = b;
}

void Xdodecaedro::modRGBcaras(float r, float g, float b) {
   RGBcaras[0] = r;
   RGBcaras[1] = g;
   RGBcaras[2] = b;
}