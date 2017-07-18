// Arista2D.cpp: implementation of the Arista2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Arista2D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Arista2D::Arista2D(Punto2D * punto1, Punto2D * punto2) {
   p1 = punto1;
   p2 = punto2;
}

Arista2D::Arista2D(Punto2D punto1, Punto2D punto2) {
   this->punto1 = punto1;
   this->punto2 = punto2;
}

Arista2D::Arista2D() { }

Arista2D::~Arista2D() { }

Arista2D& Arista2D::operator= (const Arista2D &a) {
   p1 = a.p1;
   p2 = a.p2;
   this->punto1 = a.punto1;
   this->punto2 = a.punto2;

   return (* this);
}

void Arista2D::copia(Arista2D * a) {
   punto1.modX((a->p1)->cogerX());
   punto1.modY((a->p1)->cogerY());
   punto2.modX((a->p2)->cogerX());
   punto2.modY((a->p2)->cogerY());
}