// Cara2D.cpp: implementation of the Cara2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cara2D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cara2D::Cara2D(int n) {
   numVertices = n;
   numAristas = n;
   cont = 0;
   cont2 = 0;
}

Cara2D::~Cara2D() { }

void Cara2D::addPunto2D(Punto2D p) {
   if (cont < numVertices) {
      listaVertices[cont] = p;
      cont++;
   }
}

bool Cara2D::buscarPunto(Punto2D p) {
   bool encontrado = false;

   for(int i = 0; ((i < cont) && (!encontrado)); i++) {
      if (listaVertices[i] == p) encontrado = true;
   }
   if (encontrado) return true;
   return false;
}

void Cara2D::addArista2D(Arista2D * a) {
   if (cont2 < numAristas) {
      listaAristas[cont2].copia(a);
      cont2++;
      if (cont2 == 1) {
         addPunto2D(a->cogerPunto1());
         addPunto2D(a->cogerPunto2());
      }
      else {
         if (!buscarPunto(a->cogerPunto1())) {
            addPunto2D(a->cogerPunto1());
         }	
         if (!buscarPunto(a->cogerPunto2())) {
            addPunto2D(a->cogerPunto2());
         }
      }
   }	
}

void Cara2D::erase(void) {
   cont = 0;
   cont2 = 0;
}

int Cara2D::modXmax(int m) {
   if (Xmax == m) return -1;
   Xmax = m;
   return 0;
}

int Cara2D::modXmin(int m) {
   if (Xmin == m) return -1;
   Xmin = m;
   return 0;
}