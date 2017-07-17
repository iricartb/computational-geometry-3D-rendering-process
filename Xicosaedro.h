// Xicosaedro.h: interface for the Xicosaedro class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XICOSAEDRO_H__94EEE5FE_D4C0_4469_B920_DC5A6B39FFF9__INCLUDED_)
#define AFX_XICOSAEDRO_H__94EEE5FE_D4C0_4469_B920_DC5A6B39FFF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto3D.h"
#include "Cara.h"
#include "Visual.h"
#include "Ventana.h"
#include "Figura.h"
#include "Arista.h"
#include "Poligono.h"

class Xicosaedro : public Poligono {

private:
   Punto3D vertices[12];
   Punto3D vDodecaedro[20];
   float RGBaristas[3];
   float RGBcaras[3];

   Cara * caras[20];

public:
   Xicosaedro(double);
   virtual ~Xicosaedro();
   void dibujar(Visual, Ventana);
   void CalcularLandas(Visual);
   void CalcularLandaMin();
   void modRGBaristas(float r, float g, float b);
   void modRGBcaras(float r, float g, float b);
   Punto3D * listaVertices() { return vertices; }
};

#endif // !defined(AFX_XICOSAEDRO_H__94EEE5FE_D4C0_4469_B920_DC5A6B39FFF9__INCLUDED_)
