// Xdodecaedro.h: interface for the Xdodecaedro class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XDODECAEDRO_H__FFE3E142_1D14_4E36_A3A9_DF540666554A__INCLUDED_)
#define AFX_XDODECAEDRO_H__FFE3E142_1D14_4E36_A3A9_DF540666554A__INCLUDED_

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

class Xdodecaedro : public Poligono {

private:
   Punto3D vertices[20];
   float RGBaristas[3];
   float RGBcaras[3];

   Cara * caras[12];

public:
   Xdodecaedro(double);
   virtual ~Xdodecaedro();
   void dibujar(Visual, Ventana);
   void CalcularLandas(Visual);
   void CalcularLandaMin();
   void modRGBaristas(float r, float g, float b);
   void modRGBcaras(float r, float g, float b);
   Punto3D * listaVertices() { return vertices; }
};

#endif // !defined(AFX_XDODECAEDRO_H__FFE3E142_1D14_4E36_A3A9_DF540666554A__INCLUDED_)