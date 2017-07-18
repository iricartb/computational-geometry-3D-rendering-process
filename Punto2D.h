// Punto2D.h: interface for the Punto2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUNTO2D_H__E1303FED_F9C2_4782_97B5_406BC2BFF313__INCLUDED_)
#define AFX_PUNTO2D_H__E1303FED_F9C2_4782_97B5_406BC2BFF313__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Punto2D {

protected:
   double x, y;

public:
   Punto2D(double, double);
   Punto2D();
   virtual ~Punto2D();
   int modX(double);
   int modY(double);
   double cogerX(void) { return x; }
   double cogerY(void) { return y; }
   Punto2D& operator= (const Punto2D&);
   bool operator==(const Punto2D&);
};

#endif // !defined(AFX_PUNTO2D_H__E1303FED_F9C2_4782_97B5_406BC2BFF313__INCLUDED_)