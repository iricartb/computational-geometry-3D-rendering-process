// Cara.cpp: implementation of the Cara class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cara.h"
#include "Punto3D.h"

#define epsilon 0.1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cara::Cara(Punto3D * c1, Punto3D * c2, Punto3D * c3) {
   this->c1 = c1;
   this->c2 = c2;
   this->c3 = c3;
   this->v = 1;

   listaCaras[0] = c1;
   listaCaras[1] = c2;
   listaCaras[2] = c3;
   numCaras = 3;
}

Cara::Cara(Punto3D * c1, Punto3D * c2, Punto3D * c3, Punto3D * c4) {
   this->c1 = c1;
   this->c2 = c2;
   this->c3 = c3;
   this->c4 = c4;
   this->v = 1;

   listaCaras[0] = c1;
   listaCaras[1] = c2;
   listaCaras[2] = c3;
   listaCaras[3] = c4;
   numCaras = 4;
}

Cara::Cara(Punto3D * c1, Punto3D * c2, Punto3D * c3, Punto3D * c4, Punto3D * c5) {
   this->c1 = c1;
   this->c2 = c2;
   this->c3 = c3;
   this->c4 = c4;
   this->c5 = c5;
   this->v = 1;
 
   listaCaras[0] = c1;
   listaCaras[1] = c2;
   listaCaras[2] = c3;
   listaCaras[3] = c4;
   listaCaras[4] = c5;
   numCaras = 5;
}

Cara::Cara() { }
Cara::~Cara() { }

int Cara::modVisible(int v) { 
   if (this->v == v) return -1; 
   this->v = v;
   return 0;
}
