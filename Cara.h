// Cara.h: interface for the Cara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARA_H__F0041EDF_F347_42A9_B9FD_15B9FA78DAF4__INCLUDED_)
#define AFX_CARA_H__F0041EDF_F347_42A9_B9FD_15B9FA78DAF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto3D.h"

class Cara {

private:
   Punto3D * c1, * c2, * c3, * c4, * c5;
   Punto3D * listaCaras[5];
   int v;
   int numCaras;

public:
   Cara(Punto3D *, Punto3D *, Punto3D *);
   Cara(Punto3D *, Punto3D *, Punto3D *, Punto3D *);
   Cara(Punto3D *, Punto3D *, Punto3D *, Punto3D *, Punto3D *);
   Cara();
   virtual ~Cara();
   Punto3D cogerC1(void) { return * c1; }
   Punto3D cogerC2(void) { return * c2; }
   Punto3D cogerC3(void) { return * c3; }
   Punto3D cogerC4(void) { return * c4; }
   Punto3D cogerC5(void) { return * c5; }
   Punto3D ** listarVertices(void) { return &listaCaras[0]; }
   int cogerNumCaras(void) { return numCaras; }
   int visible(void) { return v; }
   int modVisible(int);
};

#endif // !defined(AFX_CARA_H__F0041EDF_F347_42A9_B9FD_15B9FA78DAF4__INCLUDED_)