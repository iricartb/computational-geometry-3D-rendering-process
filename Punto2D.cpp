// Punto2D.cpp: implementation of the Punto2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Punto2D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Punto2D::Punto2D(double x1, double y1) {
   x = x1;
   y = y1;
}

Punto2D::~Punto2D() { }
Punto2D::Punto2D() { }

int Punto2D::modX(double x1) { 
   if (x == x1) return -1; 
   x = x1;
   return 0;
}

int Punto2D::modY(double y1) { 
   if (y == y1) return -1; 
   y = y1;
   return 0;
}

Punto2D& Punto2D::operator= (const Punto2D &p) {
   x = p.x;
   y = p.y;

   return (* this);
}

bool Punto2D::operator==(const Punto2D &p) {
   if ((int(x) == int(p.x)) && (int(y) == int(p.y))) return true;
   return false;
}