// Cara2D.h: interface for the Cara2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARA2D_H__CFAA00E2_761E_42D8_9FC2_D9F9C0354505__INCLUDED_)
#define AFX_CARA2D_H__CFAA00E2_761E_42D8_9FC2_D9F9C0354505__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto2D.h"
#include "Arista2D.h"

class Cara2D {

private:
   Punto2D listaVertices[5];
   Arista2D listaAristas[5];
   int numVertices, numAristas, cont, cont2;
   int Xmax, Xmin;
   void addPunto2D(Punto2D);
   bool buscarPunto(Punto2D p);

public:
   Cara2D(int);
   virtual ~Cara2D();
   Punto2D * listarVertices(void) { return &listaVertices[0]; }
   Arista2D * listarAristas(void) { return &listaAristas[0]; }   
   void addArista2D(Arista2D *);
   int cogerNumVertices(void) { return numVertices; }
   int cogerNumAristas(void) { return numAristas; }
   int cogerXmax(void) { return Xmax; }
   int cogerXmin(void) { return Xmin; }
   int cogerCont(void) { return cont; }
   int cogerCont2(void) { return cont2; }
   void erase(void);
   int modXmax(int);
   int modXmin(int);
};

#endif // !defined(AFX_CARA2D_H__CFAA00E2_761E_42D8_9FC2_D9F9C0354505__INCLUDED_)