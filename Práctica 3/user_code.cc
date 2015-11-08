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

const float pi=3.14159265;
bool arriba=false, abajo=false, leido0=true, leido1=false, leido2=false, leido3=false, inicio=true, revo=false, aje, aumento=true,id, in=true;
float vy1, vy2, ang1 = 0.0 ,ang2 = 360.0, gr1=0,gr2, gr3=0,desp=0, aum=1;
int rep=25, fig=0,gral,val, movimiento=100;
vector<_vertex3f> Vertices, normal_caras, normal_vertices, bariv;
vector<_vertex3i> Faces;
vector<int> fa;
vector<float> ve;
_file_ply ply;
char * archivo = "beethoven.ply";



//**************************************************************************
// Funciones auxiliares
//**************************************************************************
void mostrar_vertices(vector<_vertex3f> &Vertices){
  for(unsigned i=0; i<Vertices.size(); i++)
      cout << "POSICION " << i << " "  << Vertices[i].x << " " << Vertices[i].y << " " << Vertices[i].z << endl;

}

void mostrar_caras(vector<_vertex3i> &Faces){
  for(unsigned i=0; i<Faces.size(); i++)
      cout << "POSICION " << i << " " << Faces[i]._0 << " " << Faces[i]._1 << " " << Faces[i]._2 << endl;

}

bool is_here(int v0, int v1, int v2, int val){
  bool found=false;
  if ((v0 == val || v1 == val || v2 == val) && !(v0==0 && v1==0 && v2==0))
      found=true;
  return found;
}

void menu(){
  cout << endl;
  cout << "************************************" << endl;
  cout << "BOTONES:" << endl;
  cout << "************************************" << endl;
  cout << "PRÁCTICA 1 -> 1" << endl;
  cout << "************************************" << endl;
  cout << "PRÁCTICA 2 -> 2" << endl;
  cout << "************************************" << endl;
  cout << "PRÁCTICA 3 -> 3" << endl;
  cout << "Z/z -> 1º grado de libertad" << endl;
  cout << "X/x -> 2º grado de libertad" << endl;
  cout << "C/c -> 3º grado de libertad" << endl;
  cout << "V/v -> Mover en eje x" << endl;
  cout << "Para conseguir animacion cambiar en PRACTICA3.CC la variable de la linea 7 idle=true" << endl;
  cout << "************************************" << endl;
  cout << "Para todas las prácticas" << endl;
  cout << "P -> exit" << endl;
  cout << "CAMBIAR VISTA:" << endl;
  cout << "P -> Puntos" << endl;
  cout << "L -> Aristas" << endl;
  cout << "S -> Solido" << endl;
  cout << "A -> Solido/Ajedrez" << endl;
  cout << "RePag -> Alejar vista" << endl;
  cout << "AvPag -> Acercar vista" << endl;
  cout << "************************************" << endl;
  cout << endl;
}

void leidos(bool leido0, bool leido1, bool leido2, bool leido3){
  leido0=true;
  leido1=false;
  leido2=false;
  leido3=false;
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

//**************************************************************************
// Funcion de las normales
//**************************************************************************

void normal_faces(vector<_vertex3f> &Vertices,vector<_vertex3i> &Faces, vector<_vertex3f> &n, vector<_vertex3f> &bariv){
    int v0,v1,v2, tam=Faces.size();
    float normalizar;
    n.reserve(tam);
    _vertex3f a,b;
    bariv.reserve(tam);
    for(unsigned i=0; i<Faces.size(); i++){
        v0 = Faces[i]._0;
        v1 = Faces[i]._1;
        v2 = Faces[i]._2;
        bariv[i].x=(Vertices[v0].x+Vertices[v1].x+Vertices[v2].x)/3;
        bariv[i].y=(Vertices[v0].y+Vertices[v1].y+Vertices[v2].y)/3;
        bariv[i].z=(Vertices[v0].z+Vertices[v1].z+Vertices[v2].z)/3;

        a= Vertices[v2]-Vertices[v0];
        b= Vertices[v1]-Vertices[v0];


        n[i]=a.cross_product(b);
        normalizar=sqrt(n[i].x*n[i].x + n[i].y*n[i].y + n[i].z*n[i].z);
        n[i].x/=normalizar;
        n[i].y/=normalizar;
        n[i].z/=normalizar;
    }
}


void normal_points(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces, vector<_vertex3f> &nv, vector<_vertex3f> &nf){
    unsigned v0,v1,v2,cnt;
   int tam=Vertices.size();
   nv.reserve(tam);
   for(unsigned i=0; i<Vertices.size();i++){
       cnt=0;
       nv[i].x=0;
       nv[i].y=0;
       nv[i].z=0;
       for(unsigned j=0; j<Faces.size(); j++){
           v0 = Faces[j]._0;
           v1 = Faces[j]._1;
           v2 = Faces[j]._2;
           if(is_here(v0,v1,v2,i)){
               nv[i].x+=nf[j].x;
               nv[i].y+=nf[j].y;
               nv[i].z+=nf[j].z;
               cnt++;
           }
       }
       nv[i].x/=cnt;
       nv[i].y/=cnt;
       nv[i].z/=cnt;

       nv[i].normalize();
   }
}

//**************************************************************************
// Funciones de ajuste
//**************************************************************************


void update_points(vector<_vertex3f> &Vertices, int &rep){
    arriba=false;
    abajo=false;
    float x,y,z,ang,sy,cy;
    vector<_vertex3f> punt;
    punt.resize(Vertices.size());
    if(Vertices[0].x==0){
        arriba=true;
        punt.resize(punt.size()-1);
        vy1=Vertices[0].y;
    }
    if(Vertices[Vertices.size()-1].x==0){
        abajo=true;
        punt.resize(punt.size()-1);
        vy2=Vertices[Vertices.size()-1].y;
    }
    int cnt=0;
    if(arriba &&  abajo) {
        for(unsigned i=1; i<Vertices.size()-1; i++){
            punt[cnt].x = Vertices[i].x;
            punt[cnt].y = Vertices[i].y;
            punt[cnt].z = Vertices[i].z;
            cnt++;
        }
    }
    else if(arriba && !abajo){
        for(unsigned i=1; i<Vertices.size(); i++){
            punt[cnt].x = Vertices[i].x;
            punt[cnt].y = Vertices[i].y;
            punt[cnt].z = Vertices[i].z;
            cnt++;
        }
    }
    else if(!arriba && abajo){
        for(unsigned i=0; i<Vertices.size()-1; i++){
            punt[cnt].x = Vertices[i].x;
            punt[cnt].y = Vertices[i].y;
            punt[cnt].z = Vertices[i].z;
            cnt++;
        }
    }
    else if(!arriba && !abajo){
        for(unsigned i=0; i<Vertices.size(); i++){
            punt[i].x = Vertices[i].x;
            punt[i].y = Vertices[i].y;
            punt[i].z = Vertices[i].z;
        }
    }
  if(val==1) rep+=1;
  int tam=punt.size();
  Vertices.resize(tam*rep);
  float pi=3.1415926535;
  float t, r=rep;
  for(int i=0; i<tam; i++){
      for(int j=0; j<rep ; j++){
          t=(j)/(r-1);
          ang = ((1-t)*ang1+t*ang2)*pi/180;
          sy=sin((ang));
          cy=cos((ang));
          x=punt[i].x;
          y=punt[i].y;
          z=punt[i].z;
          Vertices[i+j*tam].x = (x * cy) + (z * sy);
          Vertices[i+j*tam].y = y;
          Vertices[i+j*tam].z = (z * cy) - (x * sy);

      }
    }
}

void update_points_mitad(vector<_vertex3f> &Vertices, int &rep, float an1, float an2){
    arriba=false;
    abajo=false;
    float x,y,z,ang,sy,cy;
    vector<_vertex3f> punt;
    punt.resize(Vertices.size());
    if(Vertices[0].x==0){
        arriba=true;
        punt.resize(punt.size()-1);
        vy1=Vertices[0].y;
    }
    if(Vertices[Vertices.size()-1].x==0){
        abajo=true;
        punt.resize(punt.size()-1);
        vy2=Vertices[Vertices.size()-1].y;
    }
    int cnt=0;
    if(arriba &&  abajo) {
        for(unsigned i=1; i<Vertices.size()-1; i++){
            punt[cnt].x = Vertices[i].x;
            punt[cnt].y = Vertices[i].y;
            punt[cnt].z = Vertices[i].z;
            cnt++;
        }
    }
    else if(arriba && !abajo){
        for(unsigned i=1; i<Vertices.size(); i++){
            punt[cnt].x = Vertices[i].x;
            punt[cnt].y = Vertices[i].y;
            punt[cnt].z = Vertices[i].z;
            cnt++;
        }
    }
    else if(!arriba && abajo){
        for(unsigned i=0; i<Vertices.size()-1; i++){
            punt[cnt].x = Vertices[i].x;
            punt[cnt].y = Vertices[i].y;
            punt[cnt].z = Vertices[i].z;
            cnt++;
        }
    }
    else if(!arriba && !abajo){
        for(unsigned i=0; i<Vertices.size(); i++){
            punt[i].x = Vertices[i].x;
            punt[i].y = Vertices[i].y;
            punt[i].z = Vertices[i].z;
        }
    }
  if(val==1) rep+=1;
  int tam=punt.size();
  Vertices.resize(tam*rep);
  float pi=3.1415926535;
  float t, r=rep;
  for(int i=0; i<tam; i++){
      for(int j=0; j<rep ; j++){
          t=(j)/(r-1);
          ang = ((1-t)*an1+t*an2)*pi/180;
          sy=sin((ang));
          cy=cos((ang));
          x=punt[i].x;
          y=punt[i].y;
          z=punt[i].z;
          Vertices[i+j*tam].x = (x * cy) + (z * sy);
          Vertices[i+j*tam].y = y;
          Vertices[i+j*tam].z = (z * cy) - (x * sy);

      }
    }
}

void update_faces(vector<_vertex3f> &Vertices,vector<_vertex3i> &Faces, int rep){
    int tam=Vertices.size(), last_tam=tam/rep;
    Faces.clear();
    vector<_vertex3i> f;
    f.resize(Vertices.size()*2);
    Faces.resize(Vertices.size()*2);
    for(int j=1; j<rep; j++){
        for(int i=0; i<last_tam-1; i++){
            if(j==0){
            f[i+j*last_tam]._0=(i+1+(rep-1)*last_tam)%tam;
            f[i+j*last_tam]._1=(i+1+j*last_tam)%tam;
            f[i+j*last_tam]._2=(i+j*last_tam)%tam;

            }
            else{
                f[i+j*last_tam]._0=(i+1+j*last_tam-last_tam)%tam;
                f[i+j*last_tam]._1=(i+1+j*last_tam)%tam;
                f[i+j*last_tam]._2=(i+j*last_tam)%tam;
            }
    }

        for(int i=0; i<last_tam-1; i++){
            if(j==0){
            f[i+j*last_tam+tam]._0=(i+1+(rep-1)*last_tam)%tam;
            f[i+j*last_tam+tam]._1=(i+j*last_tam)%tam;
            f[i+j*last_tam+tam]._2=(i+(rep-1)*last_tam)%tam;
            }
            else{
                f[i+j*last_tam+tam]._0=(i+1+j*last_tam-last_tam)%tam;
                f[i+j*last_tam+tam]._1=(i+j*last_tam)%tam;
                f[i+j*last_tam+tam]._2=(i+j*last_tam-last_tam)%tam;
            }
    }

}
    int cnt=0;
    for(unsigned i=0; i<Faces.size()/2; i++){
            Faces[cnt]._0=f[i]._0;
            Faces[cnt]._1=f[i]._1;
            Faces[cnt]._2=f[i]._2;
            cnt+=2;
    }
    cnt=1;
    for(unsigned i=Faces.size()/2; i<Faces.size(); i++){
            Faces[cnt]._0=f[i]._0;
            Faces[cnt]._1=f[i]._1;
            Faces[cnt]._2=f[i]._2;
            cnt+=2;
    }

    int t = Faces.size();
    if(arriba){
        Vertices.resize(Vertices.size()+1);
        Faces.resize(Faces.size()+rep);
        Vertices[tam].x=0;
        Vertices[tam].y=vy1;
        Vertices[tam].z=0;
        for(int i=0; i<rep-1; i++){
            Faces[t+i]._0=tam;
            Faces[t+i]._1=last_tam*i;
            if(i==rep-1)
                Faces[t+i]._2=0;
            else
                Faces[t+i]._2=last_tam*(i+1);
        }
    }
    if(abajo){
      Vertices.resize(Vertices.size()+1);
      Faces.resize(Faces.size()+rep);
      Vertices[tam+1].x=0;
      Vertices[tam+1].y=vy2;
      Vertices[tam+1].z=0;

      for(int i=0; i<rep-1; i++){
         Faces[t+rep+i]._0=tam+1;
         Faces[t+rep+i]._1=last_tam*(i+1)-1;
         if(i==rep-1)
             Faces[t+rep+i]._2=last_tam-1;
         else
             Faces[t+rep+i]._2=last_tam*(i+2)-1;
     }
    }
}



void update_components(vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces, int rep){
    update_points(Vertices,rep);
    update_faces(Vertices,Faces,rep);
}

void adjust(vector<float> &v, vector<int> &f, vector<_vertex3f> &Vertices, vector<_vertex3i> &Faces){
  Vertices.resize(v.size()/3);
  Faces.resize(f.size()/3);
  int j;
  for(unsigned i=0; i<v.size(); i+=3){
    j=i/3;
    Vertices[j].x=v[i];
    Vertices[j].y=v[i+1];
    Vertices[j].z=v[i+2];
    }
  for(unsigned i=0; i<f.size(); i+=3){
    j=i/3;
    Faces[j]._0=f[i];
    Faces[j]._1=f[i+1];
    Faces[j]._2=f[i+2];
    }

}

//**************************************************************************
//  Funciones de dibujado
//**************************************************************************

void draw(vector<_vertex3f> &Vertices,vector<_vertex3i> &Faces, bool ajedrez){
    glPointSize(2);
    if(!ajedrez){
      glBegin(GL_TRIANGLES);
      for (unsigned i=0;i<Faces.size();i++){
          glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
          glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
          glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
      }
    glEnd();
    }
    else
      {
        glBegin(GL_TRIANGLES);
        for (unsigned i=0;i<Faces.size();i++){
            if(i%2==0)
              glColor3f(0,1,1);
            else
              glColor3f(1,1,0);
            glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
            glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
            glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
        }
      glEnd();
      }
}

void write(vector<_vertex3f> &Vertices,vector<_vertex3i> &Faces, bool color, bool ajedrez){
    glPointSize(3);
    if(color){
    if(ajedrez){
    glBegin(GL_TRIANGLES);
    for (unsigned i=0;i<Faces.size();i++){
        if(i%2==0)
          glColor3f(0,1,0);
        else
          glColor3f(0,0,1);
        glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
        glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
        glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
    }
    glEnd();
      }
    else
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
    }
    else
    {
      glColor3f(1,1,1);
      glBegin(GL_TRIANGLES);
      for (unsigned i=0;i<Faces.size();i++){
              glVertex3f(Vertices[Faces[i]._0].x, Vertices[Faces[i]._0].y, Vertices[Faces[i]._0].z);
              glVertex3f(Vertices[Faces[i]._1].x, Vertices[Faces[i]._1].y, Vertices[Faces[i]._1].z);
              glVertex3f(Vertices[Faces[i]._2].x, Vertices[Faces[i]._2].y, Vertices[Faces[i]._2].z);
           }
      glEnd();
    }
}



//**************************************************************************
//  Objetos
//**************************************************************************


void cilindro(){
  GLfloat v[4][3]= {{0.0,0.5,0.0},{0.5, 0.5, 0},{0.5, -0.5, 0},{0.0,-0.5,0.0}};
    Vertices.resize(4);
    for(int i=0; i<4;i++){
      Vertices[i].x=v[i][0];
      Vertices[i].y=v[i][1];
      Vertices[i].z=v[i][2];
    }
    update_points(Vertices,rep);
    update_faces(Vertices,Faces,rep);
  draw(Vertices,Faces,aje);
}


void semicilindro(){
  GLfloat v[4][3]= {{0.0,0.5,0.0},{0.5, 0.5, 0},{0.5, -0.5, 0},{0.0,-0.5,0.0}};
    Vertices.resize(4);
    for(int i=0; i<4;i++){
      Vertices[i].x=v[i][0];
      Vertices[i].y=v[i][1];
      Vertices[i].z=v[i][2];
    }
    float a1=0, a2=180;
    update_points_mitad(Vertices,rep,a1,a2);
    update_faces(Vertices,Faces,rep);
  draw(Vertices,Faces,aje);
}


void semiesfera(){
    GLfloat punt[1][3]= {{0.5,0.0,0.0}};
    vector<_vertex3f> v;
    vector<_vertex3f> Vertices;
    vector<_vertex3i> Faces;
    v.resize(rep);
    float pi=3.1415926535;
    float ang, t, r=rep,cy,sy,x,y,z;
      for(int j=0; j<rep ; j++){
        t=(j)/(r-1);
        ang = ((1-t)*0+t*90)*pi/180;
        sy=sin((ang));
        cy=cos((ang));
        x=punt[0][0];
        y=punt[0][1];
        z=punt[0][2];
        v[j].x = x*cy-y*sy;
        v[j].y = x*sy+z*cy;
        v[j].z = z;
      }
      int tam=v.size();
      Vertices.resize(tam*rep);
      for(int i=0; i<tam; i++){
          for(int j=0; j<rep ; j++){
            t=(j)/(r-1);
            ang = ((1-t)*0+t*360)*pi/180;
            sy=sin((ang));
            cy=cos((ang));
            x=v[i].x;
            y=v[i].y;
            z=v[i].z;
            Vertices[i+j*tam].x = x*cy+z*sy;
            Vertices[i+j*tam].y = y;
            Vertices[i+j*tam].z = -x*sy+z*cy;
          }
      }
      update_faces(Vertices,Faces,rep);


    draw(Vertices,Faces,aje);

}


void esfera(){
    GLfloat punt[1][3]= {{0.5,0.0,0.0}};
    vector<_vertex3f> v;
    vector<_vertex3f> Vertices;
    vector<_vertex3i> Faces;
    v.resize(rep);
    float pi=3.1415926535;
    float ang, t, r=rep,cy,sy,x,y,z;
      for(int j=0; j<rep ; j++){
        t=(j)/(r-1);
        ang = ((1-t)*0+t*360)*pi/180;
        sy=sin((ang));
        cy=cos((ang));
        x=punt[0][0];
        y=punt[0][1];
        z=punt[0][2];
        v[j].x = x*cy-y*sy;
        v[j].y = x*sy+z*cy;
        v[j].z = z;
      }
      int tam=v.size();
      Vertices.resize(tam*rep);
      for(int i=0; i<tam; i++){
          for(int j=0; j<rep ; j++){
            t=(j)/(r-1);
            ang = ((1-t)*0+t*360)*pi/180;
            sy=sin((ang));
            cy=cos((ang));
            x=v[i].x;
            y=v[i].y;
            z=v[i].z;
            Vertices[i+j*tam].x = x*cy+z*sy;
            Vertices[i+j*tam].y = y;
            Vertices[i+j*tam].z = -x*sy+z*cy;
          }
      }
      update_faces(Vertices,Faces,rep);


    draw(Vertices,Faces,aje);

}

void cubo(){
  GLfloat v[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};
  GLint f[12][3] = {{0,1,2},{0,1,4},{0,2,3},{0,3,7},{0,4,7},{1,2,5},{1,4,5},{2,6,5},{2,3,7},{2,6,7},{4,5,6},{4,6,7}};
    Vertices.resize(8);
    Faces.resize(12);
    for(int i=0; i<12;i++){
      if(i<8){
        Vertices[i].x=v[i][0];
        Vertices[i].y=v[i][1];
        Vertices[i].z=v[i][2];
      }
      Faces[i]._0=f[i][0];
      Faces[i]._1=f[i][1];
      Faces[i]._2=f[i][2];
    }
  draw(Vertices, Faces,aje);
}


void tetraedro()
{
     GLfloat v[4][3]= {{-0.5,-0.5,-0.5},{0.0,0.5,0.0},{0.5,-0.5,-0.5},{0.0,-0.5,0.5}};
     GLint f[4][3] = {{0,1,2},{0,1,3},{0,2,3},{1,2,3}};
     Vertices.resize(4);
     Faces.resize(4);
     for(int i=0; i<6;i++){
          if(i<4){
             Vertices[i].x=v[i][0];
             Vertices[i].y=v[i][1];
             Vertices[i].z=v[i][2];
             Faces[i]._0=f[i][0];
             Faces[i]._1=f[i][1];
             Faces[i]._2=f[i][2];
          }
       }
  draw(Vertices,Faces,aje);
}

void cilindro2(){
  GLfloat v[4][3]= {{0.0,0.5,0.0},{0.5, 0.5, 0},{0.75, -0.5, 0},{0.0,-0.5,0.0}};
    Vertices.resize(4);
    for(int i=0; i<4;i++){
      Vertices[i].x=v[i][0];
      Vertices[i].y=v[i][1];
      Vertices[i].z=v[i][2];
    }
    update_points(Vertices,rep);
    update_faces(Vertices,Faces,rep);
  draw(Vertices,Faces,aje);
}
void cilindro3(){
  GLfloat v[4][3]= {{0.0,0.5,0.0},{0.5, 0.5, 0},{0.40, -0.5, 0},{0.0,-0.5,0.0}};
    Vertices.resize(4);
    for(int i=0; i<4;i++){
      Vertices[i].x=v[i][0];
      Vertices[i].y=v[i][1];
      Vertices[i].z=v[i][2];
    }
    update_points(Vertices,rep);
    update_faces(Vertices,Faces,rep);
  draw(Vertices,Faces,aje);
}


void figura(){
    ply.open(archivo);
    ply.read(ve, fa);
    ply.close();
    adjust(ve,fa,Vertices,Faces);
    draw(Vertices,Faces,aje);
}

//**************************************************************************
// Estructura del modelo
//**************************************************************************


void beethoven(){
  glPushMatrix();
      glTranslatef(4,6,0);
      glScalef(0.2,0.2,0.2);
      glColor3f(1,1,1);
      figura();
  glPopMatrix();
}

void pecho(){
  //pecho
  glPushMatrix();
    glTranslatef(0,5.5,0.3);
    glScalef(2,2,2);
    glColor3f(1,0.52,0.047);
    cilindro2();
  glPopMatrix();
}

void cintura_arriba(){
  //cintura2
  glPushMatrix();
    glTranslatef(0,3.5,0.3);
    glRotatef(180,0,1,0);
    glScalef(4,4,4);
    glColor3f(1,0.52,0.047);
    semiesfera();
  glPopMatrix();

}

void cintura_abajo(){
  //cintura1
  glPushMatrix();
        glTranslatef(0,3.5,0.3);
        glRotatef(180,0,0,1);
        glScalef(4,2,4);
        glColor3f(0.33,0.67,0.968);
        semiesfera();
  glPopMatrix();
}

void hombroi(){
  //hombroi
  glPushMatrix();
      glTranslatef(-1.25,6,0);
      glRotatef(90,0,0,1);
      glColor3f(1,0.52,0.047);
      esfera();
  glPopMatrix();
}

void hombrod(){
  //hombrod
  glPushMatrix();
      glTranslatef(1.25,6,0);
      glRotatef(90,0,0,1);
      glColor3f(1,0.52,0.047);
      esfera();
  glPopMatrix();
}

void brazoi(){
  //brazoi
  glPushMatrix();
      glTranslatef(-2.25,6,0);
      glRotatef(270,0,0,1);
      glScalef(1,1.5,1);
      glColor3f(1,0.52,0.047);
      cilindro();
  glPopMatrix();
}

void brazod(){
  //brazod
  glPushMatrix();
      glTranslatef(2.25,6,0);
      glRotatef(90,0,0,1);
      glScalef(1,1.5,1);
      glColor3f(1,0.52,0.047);
      cilindro();
  glPopMatrix();
}

void manod(){
  //manod
  glPushMatrix();
    glTranslatef(3,6,0);
    glColor3f(1,0.85,0.05);
    esfera();
  glPopMatrix();
}

void manoi(){
  //manoi
  glPushMatrix();
        glTranslatef(-3,6,0);
        glColor3f(1,0.85,0.05);
        esfera();
  glPopMatrix();
}

void cuello(){
  //cuello
  glPushMatrix();
      glTranslatef(0,7,0.5);
      glRotatef(15,1,0,0);
      glScalef(1.5,1.25,1.5);
      glColor3f(1,0.85,0.05);
      cilindro();
  glPopMatrix();
}

void cabeza(){
  //cabeza
  glPushMatrix();
      glTranslatef(0,9.25,1);
      glRotatef(355,1,0,0);
      glScalef(1.5,1.5,1.5);
      head();
  glPopMatrix();
}

  void pied(){
  //pied
  glPushMatrix();
      glTranslatef(-1.25,0,0.3);
      glScalef(1.5,1.5,2.25);
      glColor3f(0.5,0.2,0.05);
      semiesfera();
  glPopMatrix();
  }
  void piei(){
  //piei
  glPushMatrix();
      glTranslatef(1.25,0,0.3);
      glScalef(1.5,1.5,2.25);
      glColor3f(0.5,0.2,0.05);
      semiesfera();
  glPopMatrix();
  }

  void piernad(){
  //piernad
  glPushMatrix();
      glTranslatef(-1.25,2,0);
      glScalef(1,3,1);
      glColor3f(0.33,0.67,0.968);
      cilindro();
  glPopMatrix();
  }
  void piernai(){
  //piernai
  glPushMatrix();
      glTranslatef(1.25,2,0);
      glScalef(1,3,1);
      glColor3f(0.33,0.67,0.968);
      cilindro();
  glPopMatrix();
  }

  void skeleton(){
  float v1,v2,v3;
  v1 = ecRect(gr1,100,0,40);
  v2 = ecRect(gr2,30,0,40);
  v3 = ecRect(gr3,60,0,90);
  glPushMatrix();
    pied();
    piei();
    piernad();
    piernai();
    glTranslatef(0,4.5,0);
    glRotatef(v1,1,0,0); //2º grado de libertad
    glTranslatef(0,-4.5,0);
    glPushMatrix();
        cintura_abajo();
        cintura_arriba();
        pecho();
        glPushMatrix();
            glTranslatef(1.25,6,0);
            glRotatef(360-v2,0,0,1);//3º grado de libertad
            glTranslatef(-1.25,-6,0);
            glPushMatrix();
                hombrod();
                brazod();
                glPushMatrix();
                  glTranslatef(2.5,7,0.5);
                  glRotatef(20,1,0,0);
                  glColor3f(0,0,1);
                  cilindro();
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(3,6,0);
                    glRotatef(360-v3,0,1,0); //4º grado de libertad
                    glTranslatef(-3,-6,0);
                    glPushMatrix();
                      manod();
                      beethoven();

                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-1.25,6,0);
            glRotatef(v2,0,0,1);
            glTranslatef(1.25,-6,0);
            glPushMatrix();
                hombroi();
                brazoi();
                manoi();
            glPopMatrix();
        glPopMatrix();
        cuello();
        cabeza();
    glPopMatrix();
  glPopMatrix();
  }

void head(){
  //forma
  glPushMatrix();
      glScalef(2,2,2);
      glColor3f(1,0.85,0.05);
      cilindro();
  glPopMatrix();
  //ojoi
  glPushMatrix();
      glTranslatef(-0.4,0.1,0.82);
      glRotatef(90,1,0,0);
      glRotatef(15,0,0,1);
      glScalef(0.75,0.75,0.75);
      glColor3f(1,1,1);
      semiesfera();
  glPopMatrix();
  //ojod
  glPushMatrix();
      glTranslatef(0.4,0.1,0.82);
      glRotatef(90,1,0,0);
      glRotatef(345,0,0,1);
      glScalef(0.75,0.75,0.75);
      glColor3f(1,1,1);
      semiesfera();
  glPopMatrix();
  //pupilad
  glPushMatrix();
      glTranslatef(0.4,0.1,1.2);
      glRotatef(90,1,0,0);
      glScalef(0.08,0.08,0.08);
      glColor3f(0,0,0);
      esfera();
  glPopMatrix();
  //pupilai
  glPushMatrix();
      glTranslatef(-0.4,0.1,1.2);
      glRotatef(90,1,0,0);
      glScalef(0.08,0.08,0.08);
      glColor3f(0,0,0);
      esfera();
  glPopMatrix();
  //nariz
  glPushMatrix();
      glTranslatef(0,-0.2,1);
      glRotatef(90,1,0,0);
      glScalef(0.25,0.25,0.25);
      glColor3f(1,0.85,0.05);
      cilindro();
  glPopMatrix();
  //punta nariz
  glPushMatrix();
      glTranslatef(0,-0.2,1.1);
      glRotatef(90,1,0,0);
      glScalef(0.25,0.25,0.25);
      glColor3f(1,0.85,0.05);
      semiesfera();
  glPopMatrix();
  //boca1
  glPushMatrix();
      glTranslatef(0,-1,-0.2);
      glRotatef(180,1,0,0);
      glRotated(90,0,1,0);
      glScalef(1.55,0.7,2);
      glColor3f(1,0.85,0.05);
      semiesfera();
  glPopMatrix();
  //boca2
  glPushMatrix();
      glTranslatef(0,-1.05,0.15);
      glScalef(1.8,0.05,1);
      glColor3f(0,0,0);
      cilindro();
  glPopMatrix();
  //orejad
  glPushMatrix();
      glTranslatef(1.05,-0.45,-0.2);
      glRotatef(90,0,0,1);
      glRotatef(340,1,0,0);
      glScalef(0.5,0.15,0.5);
      glColor3f(1,0.85,0.05);
      cilindro();
  glPopMatrix();
  //orejai
  glPushMatrix();
      glTranslatef(-1.05,-0.45,-0.2);
      glRotatef(90,0,0,1);
      glRotatef(20,1,0,0);
      glScalef(0.5,0.15,0.5);
      glColor3f(1,0.85,0.05);
      cilindro();
  glPopMatrix();
  //pelo
  for(unsigned i=0; i<40; i++){
      glPushMatrix();
      glRotatef(i*10,0,1,0);
      hair();
      glPopMatrix();
  }
}

void hair(){
  glPushMatrix();
      glTranslatef(0,1.2,0.94);
      glRotatef(300,0,1,0);
      glScalef(0.25,0.5,0.25);
      glColor3f(1,0.85,0.05);
      tetraedro();
  glPopMatrix();
}

void skateboard(){
  glPushMatrix();
  //base
      glScalef(4,0.15,2);
      glColor3f(0,0.4,0);
      cubo();
  glPopMatrix();
  //lateral1
  glPushMatrix();
      glTranslatef(-2,0,0);
      glRotatef(90,0,1,0);
      glScalef(2,0.15,2);
      glColor3f(0,0.4,0);
      semicilindro();
  glPopMatrix();
  //lateral2
  glPushMatrix();
      glTranslatef(2,0,0);
      glRotatef(270,0,1,0);
      glScalef(2,0.15,2);
      glColor3f(0,0.4,0);
      semicilindro();
  glPopMatrix();
//rueda1
  glPushMatrix();
      glRotatef(90,1,0,0);
      glTranslatef(-1.5,0.75,0.30);
      glRotatef(5,0,1,0);
      glScalef(0.5,0.125,0.5);
      glColor3f(0,0,0.5);
      cilindro();
  glPopMatrix();
  //rueda2
  glPushMatrix();
      glRotatef(90,1,0,0);
      glTranslatef(-1.5,-0.75,0.30);
      glRotatef(5,0,1,0);
      glScalef(0.5,0.125,0.5);
      glColor3f(0,0,0.5);
      cilindro();
  glPopMatrix();
  //rueda3
  glPushMatrix();
      glRotatef(90,1,0,0);
      glTranslatef(1.5,0.75,0.30);
      glScalef(0.5,0.125,0.5);
      glColor3f(0,0,0.5);
      cilindro();
  glPopMatrix();
  //rueda4
  glPushMatrix();
      glRotatef(90,1,0,0);
      glTranslatef(1.5,-0.75,0.30);
      glScalef(0.5,0.125,0.5);
      glColor3f(0,0,0.5);
      cilindro();
  glPopMatrix();
}


void skater(){
    glPushMatrix();
        glTranslatef(0,4.5,0);
        glTranslatef(0,-4.5,0);
        glPushMatrix();
            //skateboard
                glPushMatrix();
                glTranslatef(0,0,0);
                glScalef(1.5,1.5,1.5);
                skateboard();
            glPopMatrix();
            //muñeco
            glPushMatrix();
                glTranslatef(0,0.17,-0.5);
                skeleton();
        glPopMatrix();
    glPopMatrix();
}


void escena(){
    glPushMatrix();
        //skater
        glPushMatrix();
            glTranslatef(desp,0,0); //1º grado de libertad
            skater();
        glPopMatrix();
    glPopMatrix();
}

void animar(){
    if(aumento){
      if(aum>0 && aum<movimiento-1){
        desp+=0.3;
        gr1++;
        gr2++;
        gr3++;
        aum++;
      }
      else if(aum==movimiento-1){
          aumento=false;
        }
    }
    else
      {
        if(aum>0 && aum<=movimiento){
          desp-=0.3;
          gr1--;
          gr2--;
          gr3--;
          aum--;
        }
        else if(aum==0){
            aumento=true;
            aum+=1;
          }
      }
}


//**************************************************************************
// Funcion para dibujar archivos PLY
//**************************************************************************

void draw_file(int valor, bool color, bool ajedrez, bool normal, int gl,bool idle){
  if(inicio){
     menu();
     inicio=false;
    }
    val=valor;
    switch (val) {
    case 0:
        ply.open(archivo);
        ply.read(ve, fa);
        ply.close();
        ply.write(ve,fa, color, ajedrez);
        break;

    case 1:
        if(!revo){
            Vertices.clear();
            Faces.clear();
            ve.clear();
            fa.clear();
            revo=true;
          ply.open("dibujo0.ply");
          ply.read(ve, fa);
          ply.close();
          adjust(ve,fa,Vertices,Faces);
          update_components(Vertices, Faces, rep);
        }
        write(Vertices, Faces, color, ajedrez);
        //normal_faces(Vertices,Faces,normal_caras,bariv);
        //normal_points(Vertices,Faces,normal_vertices,normal_caras);
        break;
    case 2:
        Vertices.clear();
        Faces.clear();
        glMatrixMode(GL_MODELVIEW);
          gral=gl;
          aje=ajedrez;
          id=idle;
          if(!idle){
            switch(gral){
            case 0:
                desp+=0.25;
              break;
            case 1:
                desp-=0.25;
              break;
            case 2:
                gr1+=1;
              break;
            case 3:
                gr1-=1;
              break;
            case 4:
                gr2+=1;
              break;
            case 5:
                gr2-=1;
                break;
            case 6:
                gr3+=1;
              break;
            case 7:
                gr3-=1;
                break;
            }
              escena();
              gral=-1;
          break;
      }
    else
    {
    animar();
    escena();
    gral=-1;
    }
  }
}


