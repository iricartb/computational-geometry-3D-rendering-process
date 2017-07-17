// Ventana.h: interface for the Ventana class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VENTANA_H__80172ABF_64E4_4C8B_BCD9_E3078C6F1C2F__INCLUDED_)
#define AFX_VENTANA_H__80172ABF_64E4_4C8B_BCD9_E3078C6F1C2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "glut.h"

class Ventana {

private:
  int ancho, alto;
  double m_ancho, m_alto;
  bool fscreen;

public:
   Ventana(int, int, double, double);
   virtual ~Ventana();
   int cogerAncho(void) { return ancho; }
   int cogerAlto(void) { return alto; }
   double cogerAnchoMetros(void) { return m_ancho; }
   double cogerAltoMetros(void) { return m_alto; }
   bool cogerFullScreen(void) { return fscreen; }
   int dibujar(void);
   void fullScreen(void);
   void inicializar(void);
};

#endif // !defined(AFX_VENTANA_H__80172ABF_64E4_4C8B_BCD9_E3078C6F1C2F__INCLUDED_)
