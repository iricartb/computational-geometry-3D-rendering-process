// XcubeV.cpp: implementation of the XcubeV class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XcubeV.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XcubeV::XcubeV(Punto3D * p1, Punto3D * p2, Punto3D * p3, Punto3D * p4, Punto3D * p5, Punto3D * p6, Punto3D * p7, Punto3D * p8) : Xcube(p1, p2, p3, p4, p5, p6, p7, p8) { }

XcubeV::~XcubeV() { }

void XcubeV::dibujar(Visual v, Ventana win) {
   Arista2D aux2D;
   Cara2D Cpintar(4);
   Punto2D aux1, aux2;

   for (int i = 0; i < 6; i++) caras[i]->modVisible(Figura::calcularCaras(v, * caras[i]));
   for (int j = 0; j < 8; j++) vertices[j].modL(Figura::calcularLanda(vertices[j], v));
   
   for (int c = 0; c < 6; c++) {
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
      
	  if (pintar) glColor3f(1.0f, 1.0f, 1.0f);
	  else glColor3f(0.2f, 0.6f, 0.2f);
 
	  for(int i = 0; i < Cpintar.cogerCont2(); i++) {
	     if (Figura::pintarSegmentos(&(Cpintar.listarAristas() + i)->cogerP1(), &(Cpintar.listarAristas() + i)->cogerP2(), win))
		    Figura::drawLine(int((Cpintar.listarAristas() + i)->cogerP1().cogerX()), int((Cpintar.listarAristas() + i)->cogerP1().cogerY()), int((Cpintar.listarAristas() + i)->cogerP2().cogerX()), int((Cpintar.listarAristas() + i)->cogerP2().cogerY()));
	  }
	  Cpintar.erase();
   }
}
