// Punto3D.h: interface for the Punto3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUNTO3D_H__6453BB38_81BE_42B6_9B28_01E3C1DBF084__INCLUDED_)
#define AFX_PUNTO3D_H__6453BB38_81BE_42B6_9B28_01E3C1DBF084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Punto2D.h"

class Punto3D : public Punto2D {
private:
	double z, l;

public:
	Punto3D(double, double, double);
	Punto3D(Punto3D *);
	Punto3D();
	virtual ~Punto3D();
	int modZ(double);
	double cogerZ(void) { return z; }
	int modL(double);
	double cogerL(void) { return l; }
	Punto3D& operator= (const Punto3D&);
	Punto3D& operator+ (const Punto3D&);
	Punto3D& operator- (const Punto3D&);
};

#endif // !defined(AFX_PUNTO3D_H__6453BB38_81BE_42B6_9B28_01E3C1DBF084__INCLUDED_)
