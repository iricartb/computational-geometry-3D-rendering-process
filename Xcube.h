// Xcube.h: interface for the Xcube class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCUBE_H__066041CD_4DE2_41BD_AB1D_9AD66B90BB29__INCLUDED_)
#define AFX_XCUBE_H__066041CD_4DE2_41BD_AB1D_9AD66B90BB29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto3D.h"
#include "Visual.h"
#include "Ventana.h"
#include "Figura.h"
#include "Arista.h"
#include "Cara.h"
#include "Cara2D.h"
#include "Arista2D.h"
#include "Poligono.h"

class Xcube : public Poligono {

protected:
   Punto3D vertices[8];
   float RGBaristas[3];
   float RGBcaras[3];

   Arista * aristas[12];
   Cara * caras[6];
	   
public:
   Xcube(Punto3D *, Punto3D *, Punto3D *, Punto3D *, Punto3D *, Punto3D *, Punto3D *, Punto3D *);
   virtual ~Xcube();
   void dibujar(Visual, Ventana);
   void CalcularLandas(Visual);
   void CalcularLandaMin();
   void modRGBaristas(float r, float g, float b);
   void modRGBcaras(float r, float g, float b);
   Punto3D * listaVertices() { return vertices; }
};

#endif // !defined(AFX_XCUBE_H__066041CD_4DE2_41BD_AB1D_9AD66B90BB29__INCLUDED_)
