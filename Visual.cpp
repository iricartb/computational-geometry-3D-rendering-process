// Visual.cpp: implementation of the Visual class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Visual.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Visual::Visual(double x1, double y1, double z1, double angulo) : Punto3D(x1, y1, z1) {
   this->angAlpha = angulo;
}

Visual::~Visual() { }

int Visual::modAngulo(double angulo) {
   if (angAlpha == angulo) return -1; 
   angAlpha = angulo;
   return 0;
}
