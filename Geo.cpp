// Geo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ventana.h"
#include "Figura.h"
#include "Xcube.h"
#include "XcubeV.h"
#include "XcubeDestroy.h"
#include "Xcuadrado.h"
#include "Xcara.h"
#include "Xdodecaedro.h"
#include "Xicosaedro.h"
#include "Punto3D.h"
#include "Poligono.h"
#include <stdio.h>
#include <pthread.h>
#include <windows.h>

/* ################################################ [ CONSTANTES ] ########################################################### */

#define ALTURA        768
#define ANCHURA      1024
#define M_ALTURA     0.24                   
#define M_ANCHURA    0.32                      
#define DELAY        0.03
#define DELAY2        0.3
#define DELAYSALTO     50
#define DELAYAGACHAR   50
#define SEGUNDOS      0.5
#define PI       acos(-1)
#define EPSILON       0.1
#define NUMPOLIGONOS   11
#define MAX            10

/* ############################################### [ DEFINICIONES ] ########################################################## */

typedef struct {
  Punto3D punto;
  Punto3D vector;
  double angulo;
} Input_param;

void inicializarParam(void);
void keyPress(unsigned char key_code, int xpos, int ypos);
void keySpecPress(int key_code, int xpos, int ypos);
void mouseClick(int button, int state, int x, int y); 
void paint(void);
void * rotarCubo(void * datos);
void * abrirCubo(void * datos);
void * explotarCubo(void * e);
void * disparar(void * d);
bool distancia(Punto3D p1, Punto3D p2);
void xchange(int i, int j);
void ordenarPoligonos();
void calcularLandas();
void keyb(void);

/* ############################################# [ OBJETOS GLOBALES ] ######################################################## */

bool destroyThread = false, createThread = false, explotar = false, explotado = false, saltar = false, bajada = false, agachar = false;
bool paintMaterial = false;
int numPoligonos, mousey = -1, dsalto = 0;
char x[MAX], y[MAX], z[MAX], angulo[MAX], v1[MAX], v2[MAX];
pthread_t ID_Thread, ID_Thread2;
Input_param datos, datos2;
Visual v(10, 5, 1.6, PI);
Ventana win(ANCHURA, ALTURA, M_ANCHURA, M_ALTURA);
Xcube cubo(new Punto3D(0, 0, 0), new Punto3D(1, 0, 0), new Punto3D(1, 1, 0), new Punto3D(0, 1, 0), new Punto3D(0, 0, 1), new Punto3D(1, 0, 1), new Punto3D(1, 1, 1), new Punto3D(0, 1, 1));
XcubeV habitacion(new Punto3D(0, 0, 0), new Punto3D(10, 0, 0), new Punto3D(10, 20, 0), new Punto3D(0, 20, 0), new Punto3D(0, 0, 3), new Punto3D(10, 0, 3), new Punto3D(10, 20, 3), new Punto3D(0, 20, 3));
Xcube ortoedro1(new Punto3D(4, 14, 0), new Punto3D(6, 14, 0), new Punto3D(6, 16, 0), new Punto3D(4, 16, 0), new Punto3D(4, 14, 1), new Punto3D(6, 14, 1), new Punto3D(6, 16, 1), new Punto3D(4, 16, 1));
Xcube ortoedro2(new Punto3D(4, 14, 2), new Punto3D(6, 14, 2), new Punto3D(6, 16, 2), new Punto3D(4, 16, 2), new Punto3D(4, 14, 3), new Punto3D(6, 14, 3), new Punto3D(6, 16, 3), new Punto3D(4, 16, 3));
XcubeDestroy cuboDestroy(Xcuadrado(new Punto3D(0, 0, 0), new Punto3D(0, 1, 0), new Punto3D(1, 1, 0), new Punto3D(1, 0, 0)), Xcuadrado(new Punto3D(1, 0, 0), new Punto3D(1, 1, 0), new Punto3D(1, 1, 1), new Punto3D(1, 0, 1)), Xcuadrado(new Punto3D(1, 1, 0), new Punto3D(0, 1, 0), new Punto3D(0, 1, 1), new Punto3D(1, 1, 1)), 
                         Xcuadrado(new Punto3D(0, 1, 0), new Punto3D(0, 0, 0), new Punto3D(0, 0, 1), new Punto3D(0, 1, 1)), Xcuadrado(new Punto3D(1, 0, 1), new Punto3D(1, 1, 1), new Punto3D(0, 1, 1), new Punto3D(0, 0, 1)), Xcuadrado(new Punto3D(0, 0, 0), new Punto3D(1, 0, 0), new Punto3D(1, 0, 1), new Punto3D(0, 0, 1)));
						 
Xcara cubotapa(new Punto3D(0, 0, 3), new Punto3D(10, 0, 3), new Punto3D(10, 20, 3), new Punto3D(0, 20, 3));
Xdodecaedro dodecaedro(0.8);
Xicosaedro icosaedro(0.8);
Xcube disparo(new Punto3D(0, 0, 0), new Punto3D(0.4, 0, 0), new Punto3D(0.4, 0.4, 0), new Punto3D(0, 0.4, 0), new Punto3D(0, 0, 0.4), new Punto3D(0.4, 0, 0.4), new Punto3D(0.4, 0.4, 0.4), new Punto3D(0, 0.4, 0.4));
Poligono * listaPoligonos[NUMPOLIGONOS];

/* ################################################## [ METODOS ] ############################################################ */

int main(int argc, char * argv[]) {
   glutInit(&argc, argv);
   inicializarParam();                                                            // Inicializamos Parámetros inciales   
    
   if (win.dibujar() < 1) { return -1; }                                          // Dibujamos la Ventana

   win.inicializar();	                                                          // Iniciamos los parámetros -> Ventana 

   glutKeyboardFunc(keyPress);                                                    // Capturamos los eventos del teclado -> Keyboard
   glutSpecialFunc(keySpecPress);                                                 // Capturamos los eventos del teclado -> Keyboard Arrows
   glutMouseFunc(mouseClick);                                                     // Capturamos los eventos del raton -> Mouse buttons  

   glutDisplayFunc(paint);
   glutIdleFunc(paint);
   glutMainLoop();
   return 0;
}

void paint(void) {
   Figura::clearScreen();
   
   keyb();
   ordenarPoligonos();

   /* Dibujamos las Figuras Geométricas */
   habitacion.dibujar(v, win);
   for (int j = 0; j < numPoligonos; j++) listaPoligonos[j]->dibujar(v, win);
   glutSwapBuffers();
}

void keyb(void) {
   if (saltar) {
      if (dsalto != DELAYSALTO) {
         v.modZ(v.cogerZ() + DELAY / 2);
         calcularLandas();
         dsalto++;
         if (!paintMaterial) Sleep(5);
      }
      else {
         dsalto = 0;		 
         bajada = true;
         saltar = false;
         if (!paintMaterial) Sleep(50);
      }
   }
   else if (bajada) {
      if (dsalto != DELAYSALTO) {
         v.modZ(v.cogerZ() - DELAY / 2);
         calcularLandas();
         dsalto++;
         if (!paintMaterial) Sleep(5);
      }
      else {
         dsalto = 0;
         bajada = false;
      }
   }
}

void inicializarParam(void) {
   glClearColor(0.0, 0.0, 0.0, 0.0);								              // Color de borrado de pantalla -> Negro
   printf("  ############################## [ CURSORES ] ################################\n");
   printf("  ####                                                                    ####\n");
   printf("  ####          [ %c ] Giro hacia la derecha                               ####\n", 16);
   printf("  ####          [ %c ] Giro hacia la izquierda                             ####\n", 17);
   printf("  ####          [ %c ] Movimiento hacia delante                            ####\n", 30);
   printf("  ####          [ %c ] Movimiento hacia detras                             ####\n", 31);
   printf("  ####          [ . ] Movimiento hacia la derecha                         ####\n");
   printf("  ####          [ , ] Movimiento hacia la izquierda                       ####\n");
   printf("  ####          [ . ] Movimiento hacia la derecha                         ####\n");
   printf("  ####          [ R ] Rotate     -> Rotar el cubo entorno una recta       ####\n");   
   printf("  ####          [ K ] Kill       -> Parar de rotar el cubo                ####\n");
   printf("  ####          [ O ] Open       -> Abrir la tapa del cubo                ####\n");
   printf("  ####          [ D ] Destroy    -> Destruir el cubo                      ####\n");
   printf("  ####          [ M ] Material   -> Rellenar las figuras                  ####\n");
   printf("  ####          [ F ] Fullscreen -> Maximizar la ventana                  ####\n");
   printf("  ####          [ Q ] Quit       -> Salir de la aplicacion                ####\n");
   printf("  ####                                                                    ####\n");
   printf("  ############################## [ CURSORES ] ################################\n");

   char chr = '?';
   printf("\n-> Visual (v1): ");                                   // Pedimos la componente de la visual v1
   scanf("%s", &v1);                                    

   while (chr != 10) chr = getchar();

   chr = '?';
   printf("\n-> Visual (v2): ");                                   // Pedimos la componente de la visual v2
   scanf("%s", &v2);

   while (chr != 10) chr = getchar();

   v = Visual(atof(v1), atof(v2), 1.6, PI);

   cubo.modRGBaristas(0.9, 0.9, 0.9);
   cubo.modRGBcaras(0.7, 0.5, 0.3);
   
   cubotapa.modRGBaristas(0.9, 0.9, 0.9);
   cubotapa.modRGBcaras(0.65, 0.4, 0.2);
   
   ortoedro1.modRGBaristas(0.9, 0.9, 0.9);
   ortoedro1.modRGBcaras(0.5, 0.1, 0.1);

   ortoedro2.modRGBaristas(0.9, 0.9, 0.9);
   ortoedro2.modRGBcaras(0.5, 0.1, 0.1);

   dodecaedro.modRGBaristas(0.9, 0.9, 0.9);
   dodecaedro.modRGBcaras(0.1, 0.4, 0.5);
 
   icosaedro.modRGBaristas(0.9, 0.9, 0.9);
   icosaedro.modRGBcaras(0.8, 0.6, 0.2);

   listaPoligonos[0] = &cubo;                                                     // Inicializamos la lista de polígonos -> Cubo
   listaPoligonos[1] = &cubotapa;                                                 // Inicializamos la lista de polígonos -> Tapa
   listaPoligonos[2] = &ortoedro1;                                                // Inicializamos la lista de polígonos -> Ortoedro1
   listaPoligonos[3] = &ortoedro2;                                                // Inicializamos la lista de polígonos -> Ortoedro2 
   listaPoligonos[4] = &dodecaedro;                                               // Inicializamos la lista de polígonos -> Dodecaedro
   listaPoligonos[5] = &icosaedro;                                                // Inicializamos la lista de polígonos -> Icosaedro

   numPoligonos = 6;
   calcularLandas();
}

void keyPress(unsigned char key_code, int xpos, int ypos) {
   int j;
   switch(key_code) {
      case 'q': exit(0);
                break;

      case '.': if (agachar) {
                   v.modX(v.cogerX() + (DELAY2 / 4 * sin(v.cogerAngulo())));      // Movimiento hacia la derecha 
                   v.modY(v.cogerY() + (DELAY2 / 4 * -cos(v.cogerAngulo())));
                }
                else {
                   v.modX(v.cogerX() + (DELAY2 * sin(v.cogerAngulo())));          // Movimiento hacia la derecha 
                   v.modY(v.cogerY() + (DELAY2 * -cos(v.cogerAngulo())));
                }
                calcularLandas();
                break;

      case ',': if (agachar) {
                   v.modX(v.cogerX() + (DELAY2 / 4 * -sin(v.cogerAngulo())));     // Movimiento hacia la izquierda 
                   v.modY(v.cogerY() + (DELAY2 / 4 * cos(v.cogerAngulo())));
                }
                else {
                   v.modX(v.cogerX() + (DELAY2 * -sin(v.cogerAngulo())));         // Movimiento hacia la izquierda 
                   v.modY(v.cogerY() + (DELAY2 * cos(v.cogerAngulo())));
                }
                calcularLandas();
                break;
      
	  case 'r': if ((!createThread) && (!explotar)) {
                  if (win.cogerFullScreen()) { win.fullScreen(); break; } 

                  int n = 0; char chr = '?';
                  if (cubotapa.cogerTapa()) cubotapa.modTapa(false);
                  printf("\n-> Punto (x1 x2 x3): ");                              // Pedimos el punto de rotación
                  scanf("%s %s %s", &x, &y, &z);                                    

                  while (chr != 10) chr = getchar();
                  chr = '?';

                  datos.punto.modX(atof(x));
                  datos.punto.modY(atof(y));
                  datos.punto.modZ(atof(z));

                  do {
                     if (n != 0) 
                     printf("\n[!] Error -> Datos incorrectos (0, 0, 0)\n");

                     printf("\n-> Vector (v1 v2 v3): ");                          // Pedimos el vector de rotación
                     scanf("%s %s %s", &x, &y, &z);
                     while (chr != 10) chr = getchar();
                     chr = '?';
                     n = 1;
                  } while ((atof(x) == 0) && (atof(y) == 0) && (atof(z) == 0));

                  datos.vector.modX(atof(x));
                  datos.vector.modY(atof(y));
                  datos.vector.modZ(atof(z));				

                  printf("\n-> Angulo (grados): ");                               // Pedimos el ángulo de rotación
                  scanf("%s", &angulo);

                  while (chr != 10) chr = getchar();
                  datos.angulo = atof(angulo);

                  createThread = true;
                  pthread_create(&ID_Thread, NULL, &rotarCubo, (void *) &datos);
               }
               break;

	  case 'k': if (createThread) destroyThread = true;			                   // Destruimos el hilo de ejecución
               break;

      case 'f': win.fullScreen();                                                 // Modo de pantalla completa
                break;

      case 'm': for (j = 0; j < numPoligonos; j++)                                // Rellenar las figuras 3D
                   listaPoligonos[j]->pintarCaras();       

                for(j = 0; j < 6; j++)
                   (cuboDestroy.listaCaras() + j)->pintarCaras();

                habitacion.pintarCaras();

                if (!paintMaterial) paintMaterial = true;
                else paintMaterial = false;
                break;

	  case 'o': if ((!explotar) && !(cubotapa.cogerTapa())) {
                  *(cubotapa.listaVerticesTapa()) = (cubo.listaVertices() + 4);
                  *(cubotapa.listaVerticesTapa() + 1) = (cubo.listaVertices() + 5);
                  *(cubotapa.listaVerticesTapa() + 2) = (cubo.listaVertices() + 6);
                  *(cubotapa.listaVerticesTapa() + 3) = (cubo.listaVertices() + 7);

                  datos2.punto = cubotapa.listaVerticesTapa();
                  datos2.vector = new Punto3D((cubotapa.listaVerticesTapa() + 1)->cogerX() - (cubotapa.listaVerticesTapa())->cogerX(),
                  (cubotapa.listaVerticesTapa() + 1)->cogerY() - (cubotapa.listaVerticesTapa())->cogerY(),
                  (cubotapa.listaVerticesTapa() + 1)->cogerZ() - (cubotapa.listaVerticesTapa())->cogerZ());
                  datos2.angulo = 25;

                  cubotapa.modTapa(true);
                  pthread_create(&ID_Thread, NULL, &abrirCubo, (void *) &datos2); // Abrimos la parte superior del cubo
               }
               break;

	  case 'd': if (createThread) destroyThread = true;                            // Destruimos el cubo aunque este rotando
               if (!explotar) { 
                  explotar = true;                                                // Explotamos el cubo

                  for(int i = 0; i < 6; i++) {
                     (cuboDestroy.listaCaras() + i)->modRGBaristas(0.9, 0.9, 0.9);
                     (cuboDestroy.listaCaras() + i)->modRGBcaras(0.7, 0.5, 0.3);
                  }

                  *((cuboDestroy.listaCaras())->listaVertices()) = (cubo.listaVertices());
                  *((cuboDestroy.listaCaras())->listaVertices() + 1) = (cubo.listaVertices() + 3);
                  *((cuboDestroy.listaCaras())->listaVertices() + 2) = (cubo.listaVertices() + 2);
                  *((cuboDestroy.listaCaras())->listaVertices() + 3) = (cubo.listaVertices() + 1);

                  *((cuboDestroy.listaCaras() + 1)->listaVertices()) = (cubo.listaVertices() + 1);
                  *((cuboDestroy.listaCaras() + 1)->listaVertices() + 1) = (cubo.listaVertices() + 2);
                  *((cuboDestroy.listaCaras() + 1)->listaVertices() + 2) = (cubo.listaVertices() + 6);
                  *((cuboDestroy.listaCaras() + 1)->listaVertices() + 3) = (cubo.listaVertices() + 5);

                  *((cuboDestroy.listaCaras() + 2)->listaVertices()) = (cubo.listaVertices() + 2);
                  *((cuboDestroy.listaCaras() + 2)->listaVertices() + 1) = (cubo.listaVertices() + 3);
                  *((cuboDestroy.listaCaras() + 2)->listaVertices() + 2) = (cubo.listaVertices() + 7);
                  *((cuboDestroy.listaCaras() + 2)->listaVertices() + 3) = (cubo.listaVertices() + 6);

                  *((cuboDestroy.listaCaras() + 3)->listaVertices()) = (cubo.listaVertices() + 3);
                  *((cuboDestroy.listaCaras() + 3)->listaVertices() + 1) = (cubo.listaVertices());
                  *((cuboDestroy.listaCaras() + 3)->listaVertices() + 2) = (cubo.listaVertices() + 4);
                  *((cuboDestroy.listaCaras() + 3)->listaVertices() + 3) = (cubo.listaVertices() + 7);

                  *((cuboDestroy.listaCaras() + 4)->listaVertices()) = (cubo.listaVertices() + 5);
                  *((cuboDestroy.listaCaras() + 4)->listaVertices() + 1) = (cubo.listaVertices() + 6);
                  *((cuboDestroy.listaCaras() + 4)->listaVertices() + 2) = (cubo.listaVertices() + 7);
                  *((cuboDestroy.listaCaras() + 4)->listaVertices() + 3) = (cubo.listaVertices() + 4);

                  *((cuboDestroy.listaCaras() + 5)->listaVertices()) = (cubo.listaVertices());
                  *((cuboDestroy.listaCaras() + 5)->listaVertices() + 1) = (cubo.listaVertices() + 1);
                  *((cuboDestroy.listaCaras() + 5)->listaVertices() + 2) = (cubo.listaVertices() + 5);
                  *((cuboDestroy.listaCaras() + 5)->listaVertices() + 3) = (cubo.listaVertices() + 4);

                  listaPoligonos[0] = &ortoedro1;                                // Modificamos la lista de polígonos -> Ortoedro1
                  listaPoligonos[1] = &ortoedro2;                                // Modificamos la lista de polígonos -> Ortoedro2
                  listaPoligonos[2] = &dodecaedro;                               // Modificamos la lista de polígonos -> Dodecaedro
                  listaPoligonos[3] = &icosaedro;                                // Modificamos la lista de polígonos -> Icosaedro
                  listaPoligonos[4] = cuboDestroy.listaCaras();                  // Modificamos la lista de polígonos -> Cara1 -> cubo 
                  listaPoligonos[5] = (cuboDestroy.listaCaras() + 1);            // Modificamos la lista de polígonos -> Cara2 -> cubo
                  listaPoligonos[6] = (cuboDestroy.listaCaras() + 2);            // Modificamos la lista de polígonos -> Cara3 -> cubo
                  listaPoligonos[7] = (cuboDestroy.listaCaras() + 3);            // Modificamos la lista de polígonos -> Cara4 -> cubo
                  listaPoligonos[8] = (cuboDestroy.listaCaras() + 4);            // Modificamos la lista de polígonos -> Cara5 -> cubo
                  listaPoligonos[9] = (cuboDestroy.listaCaras() + 5);            // Modificamos la lista de polígonos -> Cara6 -> cubo

                  numPoligonos = 10;
                  pthread_create(&ID_Thread, NULL, &explotarCubo, NULL);
               }
               break;
		  
        default: break;
    }
}

void keySpecPress(int key_code, int xpos, int ypos) {
   switch(key_code) {
	  case GLUT_KEY_UP: if (agachar) {
                          v.modX(v.cogerX() + (DELAY2 / 4 * cos(v.cogerAngulo())));       // Movimiento hacia delante
                          v.modY(v.cogerY() + (DELAY2 / 4 * sin(v.cogerAngulo())));
                       }
                       else {
                          v.modX(v.cogerX() + (1.5 * DELAY2 * cos(v.cogerAngulo())));     // Movimiento hacia delante
                          v.modY(v.cogerY() + (1.5 * DELAY2 * sin(v.cogerAngulo())));                           
                       }
                       calcularLandas();
                       break;

	  case GLUT_KEY_DOWN: if (agachar) {
                           v.modX(v.cogerX() + (-DELAY2 / 4 * cos(v.cogerAngulo())));    // Movimiento hacia detras
                           v.modY(v.cogerY() + (-DELAY2 / 4 * sin(v.cogerAngulo())));
                         }
                         else {
                            v.modX(v.cogerX() + (1.5 * -DELAY2 * cos(v.cogerAngulo())));  // Movimiento hacia detras
                            v.modY(v.cogerY() + (1.5 * -DELAY2 * sin(v.cogerAngulo())));                           
                         }
                         calcularLandas();
                         break;

	  case GLUT_KEY_LEFT: v.modAngulo(v.cogerAngulo() + DELAY);                    // Modificamos la visual -> Giro hacia la izquierda
                         calcularLandas();
                         break;

	  case GLUT_KEY_RIGHT: v.modAngulo(v.cogerAngulo() - DELAY);                   // Modificamos la visual -> Giro hacia la derecha
                          calcularLandas();
                          break;

      default: break;
   }
}

void mouseClick(int button, int state, int x, int y) {
   int i;
   if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN) && (!saltar) && (!bajada)) { saltar = true; }
   else if (button == GLUT_MIDDLE_BUTTON) {
      if (state == GLUT_DOWN) {
         for(i = 0; i < DELAYAGACHAR; i++) {
            v.modZ(v.cogerZ() - DELAY / 2);
            calcularLandas();
            agachar = true;
            paint();
            if (!paintMaterial) Sleep(5);
         }
      }
      else {
         for(i = 0; i < DELAYAGACHAR; i++) {
            v.modZ(v.cogerZ() + DELAY / 2);
            calcularLandas();
            agachar = false;
            paint();
            if (!paintMaterial) Sleep(5);
         }	  
      }
   }    
}

bool distancia(Punto3D p1, Punto3D p2) {
   Punto3D aux = new Punto3D(p2.cogerX() - p1.cogerX(), p2.cogerY() - p1.cogerY(), p2.cogerZ() - p1.cogerZ());
   return (sqrt(pow(aux.cogerX(), 2) + pow(aux.cogerY(), 2) + pow(aux.cogerZ(), 2)) < 0.2);
}

void xchange(int i, int j) {
   Poligono * aux;

   aux = listaPoligonos[i];
   listaPoligonos[i] = listaPoligonos[j];
   listaPoligonos[j] = aux;
}

void ordenarPoligonos() {

   for (int i = 0; i < numPoligonos - 1; i++) {
      for(int j = numPoligonos - 1; j >= (i + 1); j--) {
         if (Figura::absolute(listaPoligonos[j]->cogerLandaMin()) < Figura::absolute(listaPoligonos[j - 1]->cogerLandaMin())) {
            xchange(j, j-1);
         }
      }   
   }
}

void calcularLandas() {
   for (int j = 0; j < numPoligonos; j++) {
      listaPoligonos[j]->CalcularLandas(v);
      listaPoligonos[j]->CalcularLandaMin();
   }
}

/* ################################################## [ THREADS ] ############################################################ */

void * rotarCubo(void * datos) {
   Punto3D aux;
   int i;

   while(!destroyThread) {
      for (i = 0; i < 8; i++) {
         aux = Figura::rotacion(*(cubo.listaVertices() + i), ((Input_param *) datos)->punto, Figura::vectorUnitario(((Input_param *) datos)->vector), ((Input_param *) datos)->angulo);		
         *(cubo.listaVertices() + i) = aux;
      }
      calcularLandas();
      Sleep(SEGUNDOS * 1000);
   }

   destroyThread = false;
   createThread = false;

   pthread_exit(NULL);
   return NULL;	
}

void * abrirCubo(void * datos2) {
   Punto3D aux;

   while (!(distancia(*(cubotapa.listaVerticesTapa() + 2), *(cubo.listaVertices() + 1)))) {
      for(int i = 0; i < 2; i++) {
         aux = Figura::rotacion(*(cubotapa.listaVerticesTapa() + 2 + i), ((Input_param *) datos2)->punto, Figura::vectorUnitario(((Input_param *) datos2)->vector), ((Input_param *) datos2)->angulo);
         *(cubotapa.listaVerticesTapa() + 2 + i) = aux;
      }
      calcularLandas();
      Sleep(SEGUNDOS * 1000);
   }

   pthread_exit(NULL);
   return NULL;
}

void * explotarCubo(void * e) {

   for (int n = 0; n < 10; n++) {
      for (int i = 0; i < 6; i++) {
         (cuboDestroy.listaCaras() + i)->modNormal(Figura::normalizar(Figura::calcularNormal(*((cuboDestroy.listaCaras() + i)->listaVertices()), *((cuboDestroy.listaCaras() + i)->listaVertices() + 1), *((cuboDestroy.listaCaras() + i)->listaVertices() + 2))));
         for (int j = 0; j < 4; j++) { 
            (*((cuboDestroy.listaCaras() + i)->listaVertices() + j)).modX((*((cuboDestroy.listaCaras() + i)->listaVertices() + j)).cogerX() + EPSILON * (cuboDestroy.listaCaras() + i)->cogerNormal().cogerX()); 
            (*((cuboDestroy.listaCaras() + i)->listaVertices() + j)).modY((*((cuboDestroy.listaCaras() + i)->listaVertices() + j)).cogerY() + EPSILON * (cuboDestroy.listaCaras() + i)->cogerNormal().cogerY());
            (*((cuboDestroy.listaCaras() + i)->listaVertices() + j)).modZ((*((cuboDestroy.listaCaras() + i)->listaVertices() + j)).cogerZ() + EPSILON * (cuboDestroy.listaCaras() + i)->cogerNormal().cogerZ());
         }
      }
      calcularLandas();
      Sleep(SEGUNDOS * 1000);
   }

   listaPoligonos[0] = &ortoedro1;                                                // Modificamos la lista de polígonos -> Ortoedro1
   listaPoligonos[1] = &ortoedro2;                                                // Modificamos la lista de polígonos -> Ortoedro2
   listaPoligonos[2] = &dodecaedro;                                               // Modificamos la lista de polígonos -> Dodecaedro
   listaPoligonos[3] = &icosaedro;                                                // Modificamos la lista de polígonos -> Icosaedro
   numPoligonos = 4;

   explotado = true;
   pthread_exit(NULL);
   return NULL;
}