//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "file_ply_stl.h"
#include <iostream>

using namespace std;

void draw_cube();

void draw_tetraedro();

void draw_vertices(vector<_vertex3f> &Vertices);

void draw_edges(vector<_vertex3f> &Vertices, vector<_vertex2i> &Edges);

void draw_faces(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces);

void draw_file(bool color, int valor, bool ajedrez);


