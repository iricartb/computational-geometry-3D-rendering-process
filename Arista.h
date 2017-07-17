// Arista.h: interface for the Arista class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARISTA_H__E4F25A03_FC8D_4DEA_9C0D_6B2B239BAF96__INCLUDED_)
#define AFX_ARISTA_H__E4F25A03_FC8D_4DEA_9C0D_6B2B239BAF96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto3D.h"

class Arista  {
private:
   Punto3D * p1, * p2;

public:
   Arista(Punto3D *, Punto3D *);
   virtual ~Arista();

   Punto3D cogerPunto1(void) { return * p1; }
   Punto3D cogerPunto2(void) { return * p2; }

};

#endif // !defined(AFX_ARISTA_H__E4F25A03_FC8D_4DEA_9C0D_6B2B239BAF96__INCLUDED_)
