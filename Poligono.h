// Poligono.h: interface for the Poligono class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLIGONO_H__C3A2F3CA_A167_47F6_9A44_2E2B02696558__INCLUDED_)
#define AFX_POLIGONO_H__C3A2F3CA_A167_47F6_9A44_2E2B02696558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Visual.h"
#include "Ventana.h"

class Poligono {
protected:
	double landaMin;
	bool pintar;

public:
	Poligono();
	virtual ~Poligono();
	virtual void dibujar(Visual, Ventana) = 0;
	virtual void CalcularLandas(Visual) = 0;
	virtual void CalcularLandaMin() = 0;
	double cogerLandaMin() { return landaMin; }
	void pintarCaras(void); 
};

#endif // !defined(AFX_POLIGONO_H__C3A2F3CA_A167_47F6_9A44_2E2B02696558__INCLUDED_)
