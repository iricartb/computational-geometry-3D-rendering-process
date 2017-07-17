// Xcara.h: interface for the Xcara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCARA_H__A03DF27F_ADF5_46C1_9652_F760F288DA61__INCLUDED_)
#define AFX_XCARA_H__A03DF27F_ADF5_46C1_9652_F760F288DA61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto3D.h"
#include "Visual.h"
#include "Ventana.h"
#include "Figura.h"
#include "Arista.h"
#include "Cara.h"
#include "Poligono.h"
#include "Cara2D.h"

class Xcara : public Poligono {
private:
   Punto3D verticesTapa[4];
   float RGBaristas[3];
   float RGBcaras[3];
   bool open;

public:
   Xcara(Punto3D *, Punto3D *, Punto3D *, Punto3D *);
   virtual ~Xcara();
   void dibujar(Visual, Ventana);
   void CalcularLandas(Visual);
   void CalcularLandaMin();
   Punto3D * listaVerticesTapa() { return verticesTapa; }
   bool cogerTapa() { return open; }
   void modRGBaristas(float r, float g, float b);
   void modRGBcaras(float r, float g, float b);
   int modTapa(bool t);
};

#endif // !defined(AFX_XCARA_H__A03DF27F_ADF5_46C1_9652_F760F288DA61__INCLUDED_)
