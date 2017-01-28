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

bool arriba=false, abajo=false, leido0=false, leido1=false, leido2=false, leido3=false;
float vy1, vy2;
vector<float> v;
vector<int> f;
vector<_vertex3f> Vertices, normal_caras, normal_vertices, bariv;
vector<_vertex3i> Faces;
int rep=6;
float ang1 = 30.0;
float ang2 = 150.0;
_file_ply ply;


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
  cout << "Y -> Dibujo0" << endl;
  cout << "U -> Dibujo1" << endl;
  cout << "I -> Dibujo2" << endl;
  cout << "O -> Dibujo3" << endl;
  cout << "************************************" << endl;
  cout << endl;
}

void leidos(bool leido0, bool leido1, bool leido2, bool leido3){
  leido0=true;
  leido1=false;
  leido2=false;
  leido3=false;
}

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
  rep+=1;
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



bool is_here(int v0, int v1, int v2, int val){
  bool found=false;
  if ((v0 == val || v1 == val || v2 == val) && !(v0==0 && v1==0 && v2==0))
      found=true;
  return found;
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

void write(vector<_vertex3f> &Vertices,vector<_vertex3i> &Faces, vector<_vertex3f> &n, vector<_vertex3f> bariv, bool color, bool ajedrez, bool normal){
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
      glColor3f(0,0,0);
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
// Funcion para dibujar archivos PLY
//**************************************************************************

void draw_file(int valor, bool color, bool ajedrez, bool normal){
  switch (valor) {
    case 0:
      if(!leido0){
        leidos(leido0,leido1,leido2,leido3);
        ply.open("dibujo0.ply");
        ply.read(v, f);
        ply.close();
        adjust(v,f,Vertices,Faces);
        update_components(Vertices, Faces, rep);
      }
      write(Vertices, Faces, normal_caras, bariv, color, ajedrez, normal);
      //normal_faces(Vertices,Faces,normal_caras,bariv);
      //normal_points(Vertices,Faces,normal_vertices,normal_caras);
      break;
    case 1:
      if(!leido1){
        leidos(leido1,leido0,leido2,leido3);
        ply.open("dibujo1.ply");
        ply.read(v, f);
        ply.close();
        adjust(v,f,Vertices,Faces);
        update_components(Vertices, Faces, rep);
      }
      write(Vertices, Faces, normal_caras, bariv, color, ajedrez, normal);
      //normal_faces(Vertices,Faces,normal_caras,bariv);
      //normal_points(Vertices,Faces,normal_vertices,normal_caras);
      break;
    case 2:
      if(!leido2){
        leidos(leido2,leido0,leido1,leido3);
        ply.open("dibujo2.ply");
        ply.read(v, f);
        ply.close();
        adjust(v,f,Vertices,Faces);
        update_components(Vertices, Faces, rep);
      }
      write(Vertices, Faces, normal_caras, bariv, color, ajedrez, normal);
      //normal_faces(Vertices,Faces,normal_caras,bariv);
      //normal_points(Vertices,Faces,normal_vertices,normal_caras);
      break;
    case 3:
      if(!leido3){
        leidos(leido3,leido0,leido1,leido2);
        ply.open("dibujo3.ply");
        ply.read(v, f);
        ply.close();
        adjust(v,f,Vertices,Faces);
        update_components(Vertices, Faces, rep);
      }
      write(Vertices, Faces, normal_caras, bariv, color, ajedrez, normal);
      //normal_faces(Vertices,Faces,normal_caras,bariv);
      //normal_points(Vertices,Faces,normal_vertices,normal_caras);
      break;
    }

}
