//=====================================================================
// LoadTGA.h
// Image loader for files in TGA format.
// Assumption:  Uncompressed data.
//
// Author:
// R. Mukundan, Department of Computer Science and Software Engineering
// University of Canterbury, Christchurch, New Zealand.
//=====================================================================

#if !defined(cannon)
#define cannon

#include <iostream>
#include <fstream>
#include <GL/freeglut.h>
using namespace std;

void loadMeshFile(const char* fname);

void normal(int indx);

void drawCannon();

void canonAndStand();

#endif

