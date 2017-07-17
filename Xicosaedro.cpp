// Xicosaedro.cpp: implementation of the Xicosaedro class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Xicosaedro.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Xicosaedro::Xicosaedro(double r) {
   double a, ra, apocaras;
   int i;

   a = r;
   ra = (((4 * r) * sqrt(10)) / (sqrt(10 - (2 * sqrt(5))) * sqrt(25 + (11 * sqrt(5)))));
   apocaras = ra * cos((36 * PI) / 180);

   for (i = 0; i < 5; i++) {
      vDodecaedro[i] = Punto3D(cos(((i + 1) * 72 * PI) / 180) * ra, sin(((i + 1) * 72 * PI) / 180) * ra, 0); 
      vDodecaedro[i + 5] = Punto3D(cos(((i + 1) * 72 * PI) / 180) * (-apocaras - ((sqrt(5) / 5) * (ra + apocaras))), sin(((i + 1) * 72 * PI) / 180) * (-apocaras - ((sqrt(5) / 5) * (ra + apocaras))), 2 * (sqrt(5) / 5) * (ra + apocaras));
      vDodecaedro[i + 10] = Punto3D(cos(((i + 1) * 72 * PI) / 180) * -ra, sin(((i + 1) * 72 * PI) / 180) * -ra, 2 * a);
      vDodecaedro[i + 15] = Punto3D(cos(((i + 1) * 72 * PI) / 180) * (apocaras + ((sqrt(5) / 5) * (ra + apocaras))), sin(((i + 1) * 72 * PI) / 180) * (apocaras + ((sqrt(5) / 5) * (ra + apocaras))), (2 * a) - (2 * ((sqrt(5) / 5) * (ra + apocaras))));
   }

   for (i = 0; i < 20; i++){
      vDodecaedro[i].modX(-1 * (vDodecaedro[i].cogerX()) + 8);
      vDodecaedro[i].modY(-1 * (vDodecaedro[i].cogerY()) + 5);
      vDodecaedro[i].modZ((vDodecaedro[i].cogerZ()) - 0.3);
   }
        
   vertices[0] = Figura::baricentro(new Cara(&vDodecaedro[0], &vDodecaedro[4], &vDodecaedro[3], &vDodecaedro[2], &vDodecaedro[1])); 
   vertices[1] = Figura::baricentro(new Cara(&vDodecaedro[0], &vDodecaedro[1], &vDodecaedro[16], &vDodecaedro[8], &vDodecaedro[15]));  
   vertices[2] = Figura::baricentro(new Cara(&vDodecaedro[1], &vDodecaedro[2], &vDodecaedro[17], &vDodecaedro[9], &vDodecaedro[16]));
   vertices[3] = Figura::baricentro(new Cara(&vDodecaedro[2], &vDodecaedro[3], &vDodecaedro[18], &vDodecaedro[5], &vDodecaedro[17]));
   vertices[4] = Figura::baricentro(new Cara(&vDodecaedro[3], &vDodecaedro[4], &vDodecaedro[19], &vDodecaedro[6], &vDodecaedro[18]));
   vertices[5] = Figura::baricentro(new Cara(&vDodecaedro[4], &vDodecaedro[0], &vDodecaedro[15], &vDodecaedro[7], &vDodecaedro[19]));
   vertices[6] = Figura::baricentro(new Cara(&vDodecaedro[10], &vDodecaedro[11], &vDodecaedro[12], &vDodecaedro[13], &vDodecaedro[14]));
   vertices[7] = Figura::baricentro(new Cara(&vDodecaedro[10], &vDodecaedro[5], &vDodecaedro[18], &vDodecaedro[6], &vDodecaedro[11]));
   vertices[8] = Figura::baricentro(new Cara(&vDodecaedro[11], &vDodecaedro[6], &vDodecaedro[19], &vDodecaedro[7], &vDodecaedro[12]));
   vertices[9] = Figura::baricentro(new Cara(&vDodecaedro[12], &vDodecaedro[7], &vDodecaedro[15], &vDodecaedro[8], &vDodecaedro[13]));
   vertices[10] = Figura::baricentro(new Cara(&vDodecaedro[13], &vDodecaedro[8], &vDodecaedro[16], &vDodecaedro[9], &vDodecaedro[14]));
   vertices[11] = Figura::baricentro(new Cara(&vDodecaedro[14], &vDodecaedro[9], &vDodecaedro[17], &vDodecaedro[5], &vDodecaedro[10])); 

   caras[0] = new Cara(&vertices[0], &vertices[2], &vertices[1]);
   caras[1] = new Cara(&vertices[0], &vertices[3], &vertices[2]);
   caras[2] = new Cara(&vertices[0], &vertices[4], &vertices[3]);
   caras[3] = new Cara(&vertices[0], &vertices[5], &vertices[4]);
   caras[4] = new Cara(&vertices[0], &vertices[1], &vertices[5]);
   caras[5] = new Cara(&vertices[10], &vertices[1], &vertices[2]);
   caras[6] = new Cara(&vertices[11], &vertices[2], &vertices[3]);
   caras[7] = new Cara(&vertices[7], &vertices[3], &vertices[4]);
   caras[8] = new Cara(&vertices[8], &vertices[4], &vertices[5]);
   caras[9] = new Cara(&vertices[9], &vertices[5], &vertices[1]);
   caras[10] = new Cara(&vertices[2], &vertices[11], &vertices[10]);
   caras[11] = new Cara(&vertices[3], &vertices[7], &vertices[11]);
   caras[12] = new Cara(&vertices[4], &vertices[8], &vertices[7]);
   caras[13] = new Cara(&vertices[5], &vertices[9], &vertices[8]);
   caras[14] = new Cara(&vertices[1], &vertices[10], &vertices[9]);
   caras[15] = new Cara(&vertices[6], &vertices[10], &vertices[11]);
   caras[16] = new Cara(&vertices[6], &vertices[11], &vertices[7]);
   caras[17] = new Cara(&vertices[6], &vertices[7], &vertices[8]);
   caras[18] = new Cara(&vertices[6], &vertices[8], &vertices[9]);
   caras[19] = new Cara(&vertices[6], &vertices[9], &vertices[10]);

   RGBaristas[0] = 0.0;
   RGBaristas[1] = 0.0;
   RGBaristas[2] = 0.0;

   RGBcaras[0] = 1.0;
   RGBcaras[1] = 1.0;
   RGBcaras[2] = 1.0;
   pintar = false;
}

Xicosaedro::~Xicosaedro() { }

void Xicosaedro::CalcularLandas(Visual v) {
   for (int j = 0; j < 12; j++) vertices[j].modL(Figura::calcularLanda(vertices[j], v));
}

void Xicosaedro::CalcularLandaMin() {
   double landa = vertices[0].cogerL();

   for (int j = 1; j < 12; j++) { 
      if (landa > vertices[j].cogerL()) {
         landa = vertices[j].cogerL();
      }
   }
   landaMin = landa;
}

void Xicosaedro::dibujar(Visual v, Ventana win) {
   Punto2D aux1, aux2;
   Arista2D aux2D;
   Cara2D Cpintar(3);

   for (int i = 0; i < 20; i++) caras[i]->modVisible(Figura::calcularCaras(v, * caras[i]));

   for (int c = 0; c < 20; c++) {
      if (this->caras[c]->visible() == 0) {
         for (int n = 0; n < 3; n++) {
            if (((*(this->caras[c]->listarVertices() + n))->cogerL() > 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 3)))->cogerL() > 0)) {
               aux1 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + n)), v, win);
               aux2 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + ((n + 1) % 3))), v, win);
               aux2D = Arista2D(&aux1, &aux2);
               Cpintar.addArista2D(&aux2D);
            }
            else if ((((*(this->caras[c]->listarVertices() + n))->cogerL() > 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 3)))->cogerL() < 0)) || 
            (((*(this->caras[c]->listarVertices() + n))->cogerL() < 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 3)))->cogerL() > 0))) {
               if (((*(this->caras[c]->listarVertices() + n))->cogerL() > 0) && ((*(this->caras[c]->listarVertices() + ((n + 1) % 3)))->cogerL() < 0)) {
                  aux1 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + n)), v, win);              // A' no es virtual
                  aux2 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + ((n + 1) % 3))), v, win);  // B' es virtual			   
                  aux2 = Figura::solucionarVisibilidad(aux2, aux1);                                          // B''
                  aux2D = Arista2D(&aux1, &aux2);
                  Cpintar.addArista2D(&aux2D);			    
               }
               else {
                  aux1 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + n)), v, win);              // A' es virtual
                  aux2 = Figura::punto3Da2D((*(this->caras[c]->listarVertices() + ((n + 1) % 3))), v, win);  // B' no es virtual			   
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

void Xicosaedro::modRGBaristas(float r, float g, float b) {
   RGBaristas[0] = r;
   RGBaristas[1] = g;
   RGBaristas[2] = b;
}

void Xicosaedro::modRGBcaras(float r, float g, float b) {
   RGBcaras[0] = r;
   RGBcaras[1] = g;
   RGBcaras[2] = b;
}