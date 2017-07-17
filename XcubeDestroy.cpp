// XcubeDestroy.cpp: implementation of the XcubeDestroy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XcubeDestroy.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XcubeDestroy::XcubeDestroy(Xcuadrado x1, Xcuadrado x2, Xcuadrado x3, Xcuadrado x4, Xcuadrado x5, Xcuadrado x6) {
   caras[0] = x1;
   caras[1] = x2;
   caras[2] = x3;
   caras[3] = x4;
   caras[4] = x5;
   caras[5] = x6;
}

XcubeDestroy::~XcubeDestroy() { }
