// Xcuadrado.h: interface for the Xcuadrado class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCUADRADO_H__7DD0D64B_2E53_4A25_B0A3_8AC00E5D25BB__INCLUDED_)
#define AFX_XCUADRADO_H__7DD0D64B_2E53_4A25_B0A3_8AC00E5D25BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto3D.h"
#include "Visual.h"
#include "Ventana.h"
#include "Figura.h"
#include "Arista.h"
#include "Poligono.h"

class Xcuadrado : public Poligono {
private:
   Punto3D vertices[4];
   Punto3D normal;
   float RGBaristas[3];
   float RGBcaras[3];

public:
   Xcuadrado(Punto3D *, Punto3D *, Punto3D *, Punto3D *);
   Xcuadrado();
   virtual ~Xcuadrado();
   void dibujar(Visual, Ventana);
   void CalcularLandas(Visual);
   void CalcularLandaMin();
   Punto3D * listaVertices() { return vertices; }
   Punto3D cogerNormal(void) { return normal; }
   void modRGBaristas(float r, float g, float b);
   void modRGBcaras(float r, float g, float b);
   int modNormal(Punto3D);
};

#endif // !defined(AFX_XCUADRADO_H__7DD0D64B_2E53_4A25_B0A3_8AC00E5D25BB__INCLUDED_)