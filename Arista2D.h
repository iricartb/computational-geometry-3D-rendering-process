// Arista2D.h: interface for the Arista2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARISTA2D_H__74E9BD53_8C45_4734_880D_2F1917F4DC0E__INCLUDED_)
#define AFX_ARISTA2D_H__74E9BD53_8C45_4734_880D_2F1917F4DC0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto2D.h"

class Arista2D {
private:
	Punto2D * p1, * p2;
	Punto2D punto1, punto2;

public:
   Arista2D(Punto2D *, Punto2D *);
   Arista2D(Punto2D, Punto2D);
   Arista2D::Arista2D();
   virtual ~Arista2D();

   Punto2D cogerPunto1(void) { return * p1; }
   Punto2D cogerPunto2(void) { return * p2; }
   Punto2D cogerP1(void) { return punto1; }
   Punto2D cogerP2(void) { return punto2; }
   void copia(Arista2D *);
   Arista2D& operator= (const Arista2D&);
};

#endif // !defined(AFX_ARISTA2D_H__74E9BD53_8C45_4734_880D_2F1917F4DC0E__INCLUDED_)
