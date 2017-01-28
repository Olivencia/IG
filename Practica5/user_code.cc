//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include <math.h>
#include <stdio.h>
#include "object.cc"
#include "Camara.cc"


const float pi=3.14159265;
bool arriba=false, abajo=false, leido0=true, leido1=false, leido2=false, leido3=false, norm_ver=false, norm_car=false, ini=true, revo1=false, revo2=false, aje, aumento=true,id, in=true, nnormal=false, texin1=false, texin2=false, t_on=false;
float vy1, vy2, ang1 = 0.0 ,ang2 = 360.0, gr1=0,gr2, gr3=0,desp=0, aum=1;
int gral,val, movimiento=100;
jpg::Imagen * img_lata1, *img_lata2, * img_madera;
_file_ply ply;
char * archivo1 = "ply/beethoven.ply";
char * archivo2 = "ply/perfil.ply";
Object peon, peon_text, latasup, latacue1, latacue2, latainf, ply_beethoven, ply_beethoven2, generic, sphere_form, semisphere_form, cylinder_form, cylinder2_form, cylinder3_form, semicylinder_form, cube_form, tetrahedron_form;
enum Figuras { cube=0, sphere=1, semisphere=2, cylinder=3, cylinder_2 = 4, cylinder_3 = 5, semicylinder=6, tetrahedron=7 };

/******************************************************************************/
//MATERIALES
/******************************************************************************/

GLfloat skin_a[]={0.8,0.65,0.3,0.0}, skin_d[]={1,0.85,0.5,1.0}, skin_s[]={0.0,0.0,0.0,1.0}, skin_e=5.0; // Piel
GLfloat shirt_a[]={1,0.52,0.047,1.0}, shirt_d[]={1,0.52,0.047,1.0}, shirt_s[]={0.1,0.1,0.1,1.0}, shirt_e=2.0; // Camiseta
GLfloat jeans_a[]={0.33,0.67,0.968}, jeans_d[]={0.33,0.67,0.968,1.0}, jeans_s[]={0.1,0.1,0.1,1.0}, jeans_e=2.0; // Pantalones
GLfloat shoes_a[]={0.5,0.2,0.05,1.0}, shoes_d[]={0.5,0.2,0.05,1.0}, shoes_s[]={1.0,1.0,1.0,1.0}, shoes_e=50.0; // Zapatos
GLfloat iron_a[]={0.5,0.5,0.5,1.0}, iron_d[]={0.5,0.5,0.5,1.0}, iron_s[]={1.0,1.0,1.0,1.0}, iron_e=75.0; // Hierro


GLfloat tex_a[]={1.0,1.0,1.0,1.0}, tex_d[]={1.0,1.0,1.0,1.0}, tex_s[]={1.0,1.0,1.0,1.0}, tex_e=70.0; //text
GLfloat mat1_a[]={0.3,0.3,0.3,1.0}, mat1_d[]={0.6,0.6,0.6,1.0}, mat1_s[]={0.0,0.0,0.0,1.0}, e1=0.0; // blanca
GLfloat mat2_a[]={0.0,0.0,0.0,1.0}, mat2_d[]={0.2,0.2,0.2,1.0}, mat2_s[]={1.0,1.0,1.0,1.0}, e2=100.0; //negra

//**************************************************************************
// Funciones auxiliares
//**************************************************************************
void mostrar_vertices(vector<_vertex3f> &Vertices){
  for(unsigned i=0; i<Vertices.size(); i++)
      cout << "POSICION " << i << " "  << Vertices[i].x << " " << Vertices[i].y << " " << Vertices[i].z << endl;

}

void view_objects_1();

void mostrar_caras(vector<_vertex3i> &Faces){
  for(unsigned i=0; i<Faces.size(); i++)
      cout << "POSICION " << i << " " << Faces[i]._0 << " " << Faces[i]._1 << " " << Faces[i]._2 << endl;

}

bool is_here(int v0, int v1, int v2, int val){
  bool found=false;
  if ((v0 == val || v1 == val || v2 == val) && !(v0==0 && v1==0 && v2==0)){
      found=true;

    }
  return found;
}

void load_images(){
  img_madera = new jpg::Imagen("imagenes/text-madera.jpg");
  img_lata1 = new jpg::Imagen("imagenes/duff.jpg");
  img_lata2 = new jpg::Imagen("imagenes/lata.jpg");
}

void load_objects()
{
  load_images();
  ply_beethoven.load_ply("ply/beethoven.ply");
  generic.load("ply/dibujo0.ply",NULL,100);
  cube_form.load_form(cube);
  sphere_form.load_form(sphere);
  semisphere_form.load_form(semisphere);
  cylinder_form.load_form(cylinder,20);
  cylinder2_form.load_form(cylinder_2);
  cylinder3_form.load_form(cylinder_3);
  semicylinder_form.load_form(semicylinder);
  tetrahedron_form.load_form(tetrahedron);
  peon.load(archivo2);
  peon_text.load(archivo2,img_madera);
  latasup.load("ply/lata-psup.ply",NULL,50);
  latacue1.load("ply/lata-pcue.ply",img_lata1,50);
  latainf.load("ply/lata-pinf.ply",NULL,50);
  latacue2.load("ply/lata-pcue.ply",img_lata2,50);
  ply_beethoven2.load_ply("ply/beethoven.ply");
}


void menu(){
  cout << endl;
  cout << "************************************************************************" << endl;
  cout << "PRÁCTICA 5" << endl;
  cout << "W/A/S/D para moverse" << endl;
  cout << "Rueda del ratón para acercar alejar" << endl;
  cout << "Click izquierdo en las diferentes figujas para cambiar el color" << endl;
  cout << "Click derecho y mantener en cualquier lugar para girar la cámara" << endl;
  cout << "************************************************************************" << endl;
  cout << endl;
}

float ecRect(float &gr, int mov, float ang1, float ang2){
    float g;
      if((gr<mov && gr>0))
        g=gr/(mov-1);
      else if(gr>=mov){
          gr=(mov-1);
          g=1;
      }
      else if(gr<=0){
          gr=0;
          g=0;
      }
    return ((1-g)*ang1+g*ang2);
}


//**************************************************************************
// Funcion para dibujar vertices
//**************************************************************************

void draw_vertices(vector<_vertex3f> &Vertices)
{
  glColor3f(0,0,0);
  glPointSize(4);
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
  glColor3f(0,0,0);
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






