// XcubeDestroy.h: interface for the XcubeDestroy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCUBEDESTROY_H__88B2B9A0_3FBB_43BD_A917_41D681F43EE5__INCLUDED_)
#define AFX_XCUBEDESTROY_H__88B2B9A0_3FBB_43BD_A917_41D681F43EE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto3D.h"
#include "Visual.h"
#include "Ventana.h"
#include "Figura.h"
#include "Arista.h"
#include "Cara.h"
#include "Xcuadrado.h"

class XcubeDestroy {
private:
   Xcuadrado caras[6];

public:
   XcubeDestroy(Xcuadrado, Xcuadrado, Xcuadrado, Xcuadrado, Xcuadrado, Xcuadrado);
   virtual ~XcubeDestroy();
   Xcuadrado * listaCaras() { return caras; }
};

#endif // !defined(AFX_XCUBEDESTROY_H__88B2B9A0_3FBB_43BD_A917_41D681F43EE5__INCLUDED_)
