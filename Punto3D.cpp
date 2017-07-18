// Punto3D.cpp: implementation of the Punto3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Punto3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Punto3D::Punto3D(double x1, double y1, double z1) : Punto2D(x1, y1) {
   this->z = z1;
   this->l = 0;
}

Punto3D::Punto3D(Punto3D * p) { 
   this->x = p->x;
   this->y = p->y;
   this->z = p->z;
   this->l = 0;
}

Punto3D::~Punto3D() { }
Punto3D::Punto3D() { }

int Punto3D::modZ(double z1) { 
   if (z == z1) return -1; 
   z = z1;
   return 0;
}

int Punto3D::modL(double l1) { 
   if (l == l1) return -1; 
   l = l1;
   return 0;
}

Punto3D& Punto3D::operator= (const Punto3D &p) {
   x = p.x;
   y = p.y;
   z = p.z;
   l = p.l;

   return (* this);
}

Punto3D& Punto3D::operator+ (const Punto3D &p) {
   x += p.x;
   y += p.y;
   z += p.z;

   return (* this);
}

Punto3D& Punto3D::operator- (const Punto3D &p) {
   x -= p.x;
   y -= p.y;
   z -= p.z;

   return (* this);
}