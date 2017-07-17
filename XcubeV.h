// XcubeV.h: interface for the XcubeV class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCUBEV_H__CE94E4B0_C542_40EF_A6AC_69BF7C2094A3__INCLUDED_)
#define AFX_XCUBEV_H__CE94E4B0_C542_40EF_A6AC_69BF7C2094A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Xcube.h"

class XcubeV : public Xcube {
public:
   XcubeV(Punto3D *, Punto3D *, Punto3D *, Punto3D *, Punto3D *, Punto3D *, Punto3D *, Punto3D *);
   virtual ~XcubeV();
   void XcubeV::dibujar(Visual v, Ventana win);
};

#endif // !defined(AFX_XCUBEV_H__CE94E4B0_C542_40EF_A6AC_69BF7C2094A3__INCLUDED_)