// Figura.h: interface for the Figura class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIGURA_H__FA1D504B_277D_46DB_B55F_3ACE1626D2DA__INCLUDED_)
#define AFX_FIGURA_H__FA1D504B_277D_46DB_B55F_3ACE1626D2DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "glut.h"
#include "math.h"
#include "Punto3D.h"
#include "Punto2D.h"
#include "Visual.h"
#include "Ventana.h"
#include "Cara.h"
#include "Cara2D.h"
#include "Arista2D.h"
#include <stdio.h>

#define PI acos(-1)

class Figura {

public:

   static void drawPixel(int x1, int y1) {
      glBegin(GL_POINTS);
         glVertex2i(x1, y1);
      glEnd();
   }

   static void drawLine(int x1, int y1, int x2, int y2) {
      glBegin (GL_LINES);
         glVertex2i (x1, y1);
         glVertex2i (x2, y2);
      glEnd(); 
   }

   static void clearScreen() {
      glClear(GL_COLOR_BUFFER_BIT);
   }


   static double absolute(double d) {
      if (d < 0) return -d;
      return d;
   }

   static Punto3D calcularNormal(Punto3D v1, Punto3D v2, Punto3D v3) {
      Punto3D r1, r2, res;

      r1.modX(v2.cogerX() - v1.cogerX()); r1.modY(v2.cogerY() - v1.cogerY()); r1.modZ(v2.cogerZ() - v1.cogerZ());
      r2.modX(v3.cogerX() - v1.cogerX()); r2.modY(v3.cogerY() - v1.cogerY()); r2.modZ(v3.cogerZ() - v1.cogerZ());

      res.modX(r1.cogerY() * r2.cogerZ()  - r1.cogerZ() * r2.cogerY());
      res.modY(-(r1.cogerX() * r2.cogerZ() - r1.cogerZ() * r2.cogerX()));
      res.modZ(r1.cogerX() * r2.cogerY() - r1.cogerY() * r2.cogerX());

      return res;
   }  
   
   static Punto3D normalizar(Punto3D normal) {
      double raiz;
      Punto3D m;

      raiz = sqrt(pow(normal.cogerX(), 2) + pow(normal.cogerY(), 2) + pow(normal.cogerZ(), 2));
      m.modX(normal.cogerX() / raiz);
      m.modY(normal.cogerY() / raiz);
      m.modZ(normal.cogerZ() / raiz);

      return m;
   }

   static double calcularLanda(Punto3D p, Visual v) {
      double d, denominador, alpha, landa;
      alpha = v.cogerAngulo();
      d = (v.cogerX() * cos(alpha)) + (v.cogerY() * sin(alpha)) + 0.5;


      denominador = (cos(alpha) * (p.cogerX() - v.cogerX())) + (sin(alpha) * (p.cogerY() - v.cogerY()));
      while (absolute(denominador) < 0.000001) {
         v.modX(v.cogerX() + 0.001);
         v.modY(v.cogerY() + 0.001);
         denominador = (cos(alpha) * (p.cogerX() - v.cogerX())) + (sin(alpha) * (p.cogerY() - v.cogerY()));
      }

      landa = (d - ((cos(alpha) * v.cogerX()) + (sin(alpha) * v.cogerY()))) / denominador;
      return landa;
   }

   static Punto2D punto3Da2D(Punto3D p, Visual v, Ventana win) {
      double alpha, landa, aux;
      Punto3D perspectivo;
      Punto2D real;

      alpha = v.cogerAngulo();

      landa = calcularLanda(p, v);

      perspectivo.modX(v.cogerX() + landa * (p.cogerX() - v.cogerX()));                  // x'p
      perspectivo.modY(v.cogerY() + landa * (p.cogerY() - v.cogerY()));                  // y'p
      perspectivo.modZ(v.cogerZ() + landa * (p.cogerZ() - v.cogerZ()));                  // z'p

      perspectivo.modZ(perspectivo.cogerZ() - v.cogerZ() + (win.cogerAltoMetros() / 2)); // z''p
      perspectivo.modX(perspectivo.cogerX() - v.cogerX() - (0.5 * cos(alpha)));          // x''p
      perspectivo.modY(perspectivo.cogerY() - v.cogerY() - (0.5 * sin(alpha)));          // y''p

      aux = perspectivo.cogerX();
      perspectivo.modX((cos(PI - alpha) * aux) + (-sin(PI - alpha) * perspectivo.cogerY()));  // x'''p
      perspectivo.modY((sin(PI - alpha) * aux) + (cos(PI - alpha) * perspectivo.cogerY()));   // y'''p

      perspectivo.modY(perspectivo.cogerY() + (win.cogerAnchoMetros() / 2));

      real.modX(((perspectivo.cogerY() * (win.cogerAncho() / 2)) / (win.cogerAnchoMetros() / 2)));
      real.modY(((perspectivo.cogerZ() * (win.cogerAlto() / 2)) / (win.cogerAltoMetros() / 2)));

      real.modY(win.cogerAlto() - real.cogerY());
      return real;
   }

   static Punto2D solucionarVisibilidad(Punto2D vir, Punto2D novir) {
      Punto2D aux;
      double raiz;

      aux.modX(novir.cogerX() - vir.cogerX());
      aux.modY(novir.cogerY() - vir.cogerY());

      raiz = sqrt(pow(aux.cogerX(), 2) + pow(aux.cogerY(), 2));

      aux.modX(1000 * (aux.cogerX() / raiz));
      aux.modY(1000 * (aux.cogerY() / raiz));

      aux.modX(aux.cogerX() + novir.cogerX());
      aux.modY(aux.cogerY() + novir.cogerY());

      return aux;
   }

   static int calcularCaras(Visual v, Cara c) {
      double matriz[3][3];
      double mu;    
        
      matriz[0][0] = v.cogerX() - c.cogerC1().cogerX();
      matriz[0][1] = c.cogerC2().cogerX() - c.cogerC1().cogerX();
      matriz[0][2] = c.cogerC3().cogerX() - c.cogerC1().cogerX();
      matriz[1][0] = v.cogerY() - c.cogerC1().cogerY();
      matriz[1][1] = c.cogerC2().cogerY() - c.cogerC1().cogerY();
      matriz[1][2] = c.cogerC3().cogerY() - c.cogerC1().cogerY();
      matriz[2][0] = v.cogerZ() - c.cogerC1().cogerZ();
      matriz[2][1] = c.cogerC2().cogerZ() - c.cogerC1().cogerZ();
      matriz[2][2] = c.cogerC3().cogerZ() - c.cogerC1().cogerZ();

      mu = (matriz[0][0] * matriz[1][1] * matriz[2][2]) + (matriz[0][1] * matriz[1][2] * matriz[2][0]) + (matriz[0][2] * matriz[1][0] * matriz[2][1]);
      mu = mu - (matriz[0][2] * matriz[1][1] * matriz[2][0]) - (matriz[0][0] * matriz[1][2] * matriz[2][1]) - (matriz[0][1] * matriz[1][0] * matriz[2][2]);

      if (mu > 0) return 0;
      return 1; 
   }

   static Punto3D vectorUnitario(Punto3D vector) {
      double raiz;
      Punto3D vUni;

      raiz = sqrt(pow(vector.cogerX(), 2) + pow(vector.cogerY(), 2) + pow(vector.cogerZ(), 2));

      vUni.modX(vector.cogerX() / raiz);
      vUni.modY(vector.cogerY() / raiz);
      vUni.modZ(vector.cogerZ() / raiz);

      return vUni;
   }

   static Punto3D rotacion(Punto3D v, Punto3D punto, Punto3D vector, int angulo) {
      double matriz[3][3];
      double matrizAux[3];
      double matrizAux2[3];
      Punto3D pRotado;

      matriz[0][0] = pow(vector.cogerX(), 2) + ((1 - pow(vector.cogerX(), 2)) * cos((angulo * PI)/360));
      matriz[0][1] = (vector.cogerX() * vector.cogerY() * (1 - cos((angulo * PI)/360))) - (vector.cogerZ() * sin((angulo * PI)/360));
      matriz[0][2] = (vector.cogerZ() * vector.cogerX() * (1 - cos((angulo * PI)/360))) + (vector.cogerY() * sin((angulo * PI)/360));
      matriz[1][0] = (vector.cogerX() * vector.cogerY() * (1 - cos((angulo * PI)/360))) + (vector.cogerZ() * sin((angulo * PI)/360));
      matriz[1][1] = pow(vector.cogerY(), 2) + ((1 - pow(vector.cogerY(), 2)) * cos((angulo * PI)/360));
      matriz[1][2] = (vector.cogerY() * vector.cogerZ() * (1 - cos((angulo * PI)/360))) - (vector.cogerX() * sin((angulo * PI)/360));
      matriz[2][0] = (vector.cogerZ() * vector.cogerX() * (1 - cos((angulo * PI)/360))) - (vector.cogerY() * sin((angulo * PI)/360));
      matriz[2][1] = (vector.cogerY() * vector.cogerZ() * (1 - cos((angulo * PI)/360))) + (vector.cogerX() * sin((angulo * PI)/360));
      matriz[2][2] = pow(vector.cogerZ(), 2) + ((1 - pow(vector.cogerZ(), 2)) * cos((angulo * PI)/360));

      matrizAux[0] = (matriz[0][0] * v.cogerX()) + (matriz[0][1] * v.cogerY()) + (matriz[0][2] * v.cogerZ());
      matrizAux[1] = (matriz[1][0] * v.cogerX()) + (matriz[1][1] * v.cogerY()) + (matriz[1][2] * v.cogerZ());
      matrizAux[2] = (matriz[2][0] * v.cogerX()) + (matriz[2][1] * v.cogerY()) + (matriz[2][2] * v.cogerZ());

      matrizAux2[0] = (matriz[0][0] * punto.cogerX()) + (matriz[0][1] * punto.cogerY()) + (matriz[0][2] * punto.cogerZ());
      matrizAux2[1] = (matriz[1][0] * punto.cogerX()) + (matriz[1][1] * punto.cogerY()) + (matriz[1][2] * punto.cogerZ());
      matrizAux2[2] = (matriz[2][0] * punto.cogerX()) + (matriz[2][1] * punto.cogerY()) + (matriz[2][2] * punto.cogerZ());

      matrizAux2[0] = punto.cogerX() - matrizAux2[0];
      matrizAux2[1] = punto.cogerY() - matrizAux2[1];
      matrizAux2[2] = punto.cogerZ() - matrizAux2[2];

      pRotado.modX(matrizAux[0] + matrizAux2[0]);
      pRotado.modY(matrizAux[1] + matrizAux2[1]);
      pRotado.modZ(matrizAux[2] + matrizAux2[2]);

      return pRotado;
   }

   static bool rangoScreen(Punto2D * p, Ventana win) {
      if (((p->cogerX() >= 0) && (p->cogerX() <= win.cogerAncho())) && ((p->cogerY() >= 0) && (p->cogerY() <= win.cogerAlto()))) return true;
      return false;
   }

   static bool rangoScreenX(double p, Ventana win) {
      if ((p >= 0) && (p <= win.cogerAncho())) return true;
      return false;
   }

   static bool rangoScreenY(double p, Ventana win) {
      if ((p >= 0) && (p <= win.cogerAlto())) return true;
      return false;
   }

   static bool pintarSegmentos(Punto2D * p1, Punto2D * p2, Ventana win) {
      double a1, a2, b1, b2, alpha, beta;
      int num = 0;
      bool draw = false;
      Punto2D sel[4];

      a1 = p1->cogerX();
      a2 = p1->cogerY();
      b1 = p2->cogerX();
      b2 = p2->cogerY();
      alpha = win.cogerAncho();
      beta = win.cogerAlto();

      // 1er Caso
      if (((a1 < 0) && (b1 < 0)) || ((a1 > alpha) && (b1 > alpha)) || ((a2 < 0) && (b2 < 0)) || ((a2 > beta) && (b2 > beta))) {
         draw = false;
      }
      // 2o Caso
      else if ((rangoScreen(p1, win)) && (rangoScreen(p2, win))) {
         draw = true;
      } 
      // 3er Caso
      else if ((!(rangoScreen(p1, win))) && (!(rangoScreen(p2, win)))) {
         // Subcaso 1: a1 == b1
         if (a1 == b1) { 
            p1->modX(a1); p1->modY(0);
            p2->modX(a1); p2->modY(beta);
            draw = true; 
         }
         // Subcaso 2: a2 == b2
         else if (a2 == b2) {
            p1->modX(0); p1->modY(a2);
            p2->modX(alpha); p2->modY(a2);
            draw = true; 
         }
         // Subcaso 3: eq recta
         else {
            // Subcaso 1: (x, 0)
            Punto2D c1((((-a2 * b1) + (a1 * b2)) / (b2 - a2)), 0);
            // Subcaso 2: (x, beta)
            Punto2D c2((((-a2 * b1) + (a1 * b2) + (beta * b1) - (beta * a1)) / (b2 - a2)), beta);
            // Subcaso 3: (0, y)
            Punto2D c3(0, (((-a2 * b1) + (a1 * b2)) / (a1 - b1)));
            // Subcaso 4: (alpha, y)
            Punto2D c4(alpha, (((-a2 * b1) + (a1 * b2) - (alpha * b2) + (alpha * a2)) / (a1 - b1)));

            if (rangoScreen(&c1, win)) { sel[num] = c1; num++; }
            if (rangoScreen(&c2, win)) { sel[num] = c2; num++; }
            if (rangoScreen(&c3, win)) { sel[num] = c3; num++; }
            if (rangoScreen(&c4, win)) { sel[num] = c4; num++; }

            if (num == 2) {		 
               p1->modX(sel[0].cogerX());
               p1->modY(sel[0].cogerY());
               p2->modX(sel[1].cogerX());
               p2->modY(sel[1].cogerY());
               draw = true;
            }   
            else if (num == 3) {
               if (sel[0] == sel[1]) sel[1] = sel[2];
               p1->modX(sel[0].cogerX());
               p1->modY(sel[0].cogerY());
               p2->modX(sel[1].cogerX());
               p2->modY(sel[1].cogerY());
               draw = true;
            }
            else if (num == 4) {
               if (sel[0] == sel[1]) sel[1] = sel[2];
               p1->modX(sel[0].cogerX());
               p1->modY(sel[0].cogerY());
               p2->modX(sel[1].cogerX());
               p2->modY(sel[1].cogerY());
               draw = true;
            }
         }
      }
      // Subcaso 4: A dentro rango
      else if ((rangoScreen(p1, win)) && (!(rangoScreen(p2, win)))) {
         // Subcaso 1: a1 == b1
         if (a1 == b1) {
            if (b2 <= 0) {
               p1->modX(a1); p1->modY(a2);
               p2->modX(a1); p2->modY(0);
               draw = true; 			   
            }
            else {
               p1->modX(a1); p1->modY(a2);
               p2->modX(a1); p2->modY(beta);
               draw = true; 			
            }
         }
         // Subcaso 2: a2 == b2
         else if (a2 == b2) {
            if (b1 > 0) {
               p1->modX(a1); p1->modY(a2);
               p2->modX(alpha); p2->modY(a2);
               draw = true; 
            }
            else {
               p1->modX(a1); p1->modY(a2);
               p2->modX(0); p2->modY(a2);
               draw = true; 		
            }
         }
         // Subcaso 3: eq recta
         else {
            // Subcaso 1: (x, 0)
            Punto2D c1((((-a2 * b1) + (a1 * b2)) / (b2 - a2)), 0);
            // Subcaso 2: (x, beta)
            Punto2D c2((((-a2 * b1) + (a1 * b2) + (beta * b1) - (beta * a1)) / (b2 - a2)), beta);
            // Subcaso 3: (0, y)
            Punto2D c3(0, (((-a2 * b1) + (a1 * b2)) / (a1 - b1)));
            // Subcaso 4: (alpha, y)
            Punto2D c4(alpha, (((-a2 * b1) + (a1 * b2) - (alpha * b2) + (alpha * a2)) / (a1 - b1)));

            if (rangoScreen(&c1, win)) { sel[num] = c1; num++; }
            if (rangoScreen(&c2, win)) { sel[num] = c2; num++; }
            if (rangoScreen(&c3, win)) { sel[num] = c3; num++; }
            if (rangoScreen(&c4, win)) { sel[num] = c4; num++; }

            if (num == 2) {
               if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) < 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) < 0))) {
                  p2->modX(sel[0].cogerX());
                  p2->modY(sel[0].cogerY());
                  draw = true;                  
               }
               else if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) > 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) > 0))) {
                  p2->modX(sel[1].cogerX());
                  p2->modY(sel[1].cogerY());
                  draw = true;				   
               }
            }
            else if (num == 3) {
               if (sel[0] == sel[1]) sel[1] = sel[2];
               if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) < 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) < 0))) {
                  p2->modX(sel[0].cogerX());
                  p2->modY(sel[0].cogerY());
                  draw = true;
               }
               else if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) > 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) > 0))) {
                  p2->modX(sel[1].cogerX());
                  p2->modY(sel[1].cogerY());
                  draw = true;					   
               }
            }
            else if (num == 4) {
               if (sel[0] == sel[1]) sel[1] = sel[2];
               if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) < 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) < 0))) {
                  p2->modX(sel[0].cogerX());
                  p2->modY(sel[0].cogerY());
                  draw = true;
               }
               else if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) > 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) > 0))) {
                  p2->modX(sel[1].cogerX());
                  p2->modY(sel[1].cogerY());
                  draw = true;					   
               }
            }           
         }
      }
      // Subcaso 5: B dentro rango
      else if ((rangoScreen(p2, win)) && (!(rangoScreen(p1, win)))) {
         // Subcaso 1: a1 == b1
         if (a1 == b1) {
            if (a2 <= 0) {
               p1->modX(b1); p1->modY(b2);
               p2->modX(b1); p2->modY(0);
               draw = true;		   
            }
            else {
               p1->modX(b1); p1->modY(b2);
               p2->modX(b1); p2->modY(beta);
               draw = true;			
            }
         }
         // Subcaso 2: a2 == b2
         else if (a2 == b2) {
            if (a1 > 0) {
               p1->modX(b1); p1->modY(b2);
               p2->modX(alpha); p2->modY(b2);
               draw = true;
            }
            else {
               p1->modX(b1); p1->modY(b2);
               p2->modX(0); p2->modY(b2);
               draw = true;			
            }
         }
         // Subcaso 3: eq recta
         else {
            // Subcaso 1: (x, 0)
            Punto2D c1((((-a2 * b1) + (a1 * b2)) / (b2 - a2)), 0);
            // Subcaso 2: (x, beta)
            Punto2D c2((((-a2 * b1) + (a1 * b2) + (beta * b1) - (beta * a1)) / (b2 - a2)), beta);
            // Subcaso 3: (0, y)
            Punto2D c3(0, (((-a2 * b1) + (a1 * b2)) / (a1 - b1)));
            // Subcaso 4: (alpha, y)
            Punto2D c4(alpha, (((-a2 * b1) + (a1 * b2) - (alpha * b2) + (alpha * a2)) / (a1 - b1)));

            if (rangoScreen(&c1, win)) { sel[num] = c1; num++; }
            if (rangoScreen(&c2, win)) { sel[num] = c2; num++; }
            if (rangoScreen(&c3, win)) { sel[num] = c3; num++; }
            if (rangoScreen(&c4, win)) { sel[num] = c4; num++; }

            if (num == 2) {
               if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) < 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) < 0))) {
                  p1->modX(sel[0].cogerX());
                  p1->modY(sel[0].cogerY());
                  draw = true;                  
               }
               else if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) > 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) > 0))) {
                  p1->modX(sel[1].cogerX());
                  p1->modY(sel[1].cogerY());
                  draw = true;				   
               }
            }
            else if (num == 3) {
               if (sel[0] == sel[1]) sel[1] = sel[2];
               if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) < 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) < 0))) {
                  p1->modX(sel[0].cogerX());
                  p1->modY(sel[0].cogerY());
                  draw = true;
               }
               else if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) > 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) > 0))) {
                  p1->modX(sel[1].cogerX());
                  p1->modY(sel[1].cogerY());
                  draw = true;					   
               }
            }
            else if (num == 4) {
               if (sel[0] == sel[1]) sel[1] = sel[2];
               if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) < 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) < 0))) {
                  p1->modX(sel[0].cogerX());
                  p1->modY(sel[0].cogerY());
                  draw = true;
               }
               else if ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) > 0) || 
               ((((sel[0].cogerX() - a1) * (sel[0].cogerX() - b1)) == 0) && (((sel[0].cogerY() - a2) * (sel[0].cogerY() - b2)) > 0))) {
                  p1->modX(sel[1].cogerX());
                  p1->modY(sel[1].cogerY());
                  draw = true;					   
               }
            }
         }
      }
      return draw;
   }

   static Punto3D baricentro(Cara * c) {
      Punto3D v;        
      v.modX(((c->cogerC1().cogerX() + c->cogerC2().cogerX() + c->cogerC3().cogerX() + c->cogerC4().cogerX() + c->cogerC5().cogerX()) / 5));
      v.modY(((c->cogerC1().cogerY() + c->cogerC2().cogerY() + c->cogerC3().cogerY() + c->cogerC4().cogerY() + c->cogerC5().cogerY()) / 5));
      v.modZ(((c->cogerC1().cogerZ() + c->cogerC2().cogerZ() + c->cogerC3().cogerZ() + c->cogerC4().cogerZ() + c->cogerC5().cogerZ()) / 5));

      return v;
   }

   static Punto2D eqRecta(Arista2D arista, int p) {
      double m;
      Punto2D punto;

      m = ((arista.cogerP2().cogerY() - arista.cogerP1().cogerY()) / (arista.cogerP2().cogerX() - arista.cogerP1().cogerX()));

      punto.modX(p);
      punto.modY(m * (p - arista.cogerP1().cogerX()) + arista.cogerP1().cogerY());

      return punto;
   }

   static void pintarCara(Cara2D * c, Ventana win, Visual v) { 
      int num = 0, k;
      Punto2D p1, p2;

      if (c->cogerXmax() > win.cogerAncho()) c->modXmax(win.cogerAncho());
      if (c->cogerXmin() < 0) c->modXmin(0);

      for(k = c->cogerXmin(); k <= c->cogerXmax(); k++) {
         for(int i = 0; ((i < c->cogerNumAristas()) && (num < 2)); i++) {
            if (((k >= (c->listarAristas() + i)->cogerP1().cogerX()) && (k <= (c->listarAristas() + i)->cogerP2().cogerX())) || 
            ((k <= (c->listarAristas() + i)->cogerP1().cogerX()) && (k >= (c->listarAristas() + i)->cogerP2().cogerX()))) {
               if (num == 0) { p1 = eqRecta(*(c->listarAristas() + i), k); num++; }
               else { 
                  p2 = eqRecta(*(c->listarAristas() + i), k); 
                  if (!(p1 == p2)) num++;
               }
            }
         }
         num = 0;
         
         if (Figura::pintarSegmentos(&p1, &p2, win)) {
            Figura::drawLine(int(p1.cogerX()), int(p1.cogerY()), int(p2.cogerX()), int(p2.cogerY()));
         }
      }
   }

   static void calcularOrdenadas(Cara2D * c) {
      int Xmax = 0;
      int Xmin = 65000;

      for(int i = 0; i < c->cogerNumAristas(); i++) {
         if ((c->listarVertices() + i)->cogerX() > Xmax) {
            Xmax = int((c->listarVertices() + i)->cogerX());
         }
         if ((c->listarVertices() + i)->cogerX() < Xmin) {
            Xmin = int((c->listarVertices() + i)->cogerX());	
         }
      }
      c->modXmax(Xmax);
      c->modXmin(Xmin);
   }
};

#endif // !defined(AFX_FIGURA_H__FA1D504B_277D_46DB_B55F_3ACE1626D2DA__INCLUDED_)