//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"
#include "vertex.h"

void menu(){
  cout << endl;
  cout << "************************************" << endl;
  cout << "P -> exit" << endl;
  cout << "CAMBIAR VISTA:" << endl;
  cout << "A -> Puntos" << endl;
  cout << "S -> Aristas" << endl;
  cout << "D -> Solido" << endl;
  cout << "F -> Solido/Ajedrez" << endl;
  cout << endl;
  cout << "CAMBIAR DIBUJOS: " << endl;
  cout << "C -> Beethoven" << endl;
  cout << "B -> Hormiga" << endl;
  cout << "************************************" << endl;
  cout << endl;
}

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw_cube()
{
    GLfloat v[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};
    GLint e[12][2] = {{0,1},{0,3},{1,2},{2,3},{3,7},{2,6},{6,7},{1,5},{5,6},{0,4},{4,5},{4,7}};
    GLint f[12][3] = {{0,1,2},{0,1,4},{0,2,3},{0,3,7},{0,4,7},{1,2,5},{1,4,5},{2,6,5},{2,3,7},{2,6,7},{4,5,6},{4,6,7}};
    vector<_vertex3f> Vertices;
    vector<_vertex2i> Edges;
    vector<_vertex3i> Faces;
    Vertices.resize(24);
    Edges.resize(24);
    Faces.resize(36);
    for(int i=0; i<12;i++){
         if(i<8){
            Vertices[i].x=v[i][0];
            Vertices[i].y=v[i][1];
            Vertices[i].z=v[i][2];
         }
         Edges[i]._0=e[i][0];
         Edges[i]._1=e[i][1];
         Faces[i]._0=f[i][0];
         Faces[i]._1=f[i][1];
         Faces[i]._2=f[i][2];
      }
}
//**************************************************************************
// Funcion para dibujar los vertices de un tetraedro
//***************************************************************************

void draw_tetraedro()
{

     GLfloat v[4][3]= {{-0.5,-0.5,-0.5},{0.0,0.5,0.0},{0.5,-0.5,-0.5},{0.0,-0.5,0.5}};
     GLint e[6][2] = {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}};
     GLint f[4][3] = {{0,1,2},{0,1,3},{0,2,3},{1,2,3}};
     vector<_vertex3f> Vertices;
     vector<_vertex2i> Edges;
     vector<_vertex3i> Faces;
     Vertices.resize(12);
     Edges.resize(12);
     Faces.resize(12);
     for(int i=0; i<6;i++){
          if(i<4){
             Vertices[i].x=v[i][0];
             Vertices[i].y=v[i][1];
             Vertices[i].z=v[i][2];
             Faces[i]._0=f[i][0];
             Faces[i]._1=f[i][1];
             Faces[i]._2=f[i][2];
          }
          Edges[i]._0=e[i][0];
          Edges[i]._1=e[i][1];
       }
}


//**************************************************************************
// Funcion para dibujar vertices
//**************************************************************************

void draw_vertices(vector<_vertex3f> &Vertices)
{
  glColor3f(0,1,0);
  glPointSize(5);
  glBegin(GL_POINTS);
  for (unsigned i=0;i<Vertices.size();i++){
      glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
  }
  glEnd();
}

//**************************************************************************
// Funcion para dibujar aristas
//**************************************************************************

void draw_edges(vector<_vertex3f> &Vertices, vector<_vertex2i> &Edges)
{
  glColor3f(0,0,1);
  glLineWidth(3);
  glBegin(GL_LINES);
  for (unsigned i=0;i<Edges.size();i++){
      glVertex3f(Vertices[Edges[i]._0].x, Vertices[Edges[i]._0].y, Vertices[Edges[i]._0].z);
      glVertex3f(Vertices[Edges[i]._1].x, Vertices[Edges[i]._1].y, Vertices[Edges[i]._1].z);
  }
  glEnd();
}

//**************************************************************************
// Funcion para dibujar caras
//**************************************************************************

void draw_faces(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces)
{
  glColor3f(0,0,1);
  glBegin(GL_TRIANGLES);
  for (unsigned i=0;i<Faces.size();i++){
      glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
      glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
      glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);

  }
  glEnd();
}

//**************************************************************************
// Funcion para dibujar archivos PLY
//**************************************************************************

void draw_file(bool color, int valor, bool ajedrez)
{
  if(valor==0){
    char * archivo = "ant.ply";
    vector<float> Vertices;
    vector<int> Faces;
    _file_ply ply;
    ply.open(archivo);
    ply.read(Vertices, Faces);
    ply.close();
    ply.write(Vertices,Faces,color,ajedrez);
    //ply.write_examen(Vertices,Faces, color, ajedrez); //Examen
  }
  else if(valor==1){
  char * archivo = "beethoven.ply";
  vector<float> Vertices;
  vector<int> Faces;
  _file_ply ply;
  ply.open(archivo);
  ply.read(Vertices, Faces);
  ply.close();
  ply.write(Vertices,Faces,color,ajedrez);
  //ply.write_examen(Vertices,Faces, color, ajedrez); //Examen
  }
}
