// Visual.h: interface for the Visual class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUAL_H__48071D2F_8960_4CA0_8BF0_B55BE1B5CB94__INCLUDED_)
#define AFX_VISUAL_H__48071D2F_8960_4CA0_8BF0_B55BE1B5CB94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto3D.h"

class Visual : public Punto3D {
private:
   double angAlpha;

public:
   Visual(double, double, double, double);
   virtual ~Visual();
   double cogerAngulo(void) { return angAlpha; }
   int modAngulo(double alpha);
};

#endif // !defined(AFX_VISUAL_H__48071D2F_8960_4CA0_8BF0_B55BE1B5CB94__INCLUDED_)