#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"

using namespace std;

//double Txval=0,Tyval=3,Tzval=15,Cxval=0,Cyval=0,Czval=0,dx,dy,dz,d,eps,a=.5;
double Txval=-4,Tyval=-10,Tzval=40,Cxval=-4,Cyval=-10,Czval=-10,dx,dy,dz,d,eps,a=1.0;
double windowHeight=1000, windowWidth=1000;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0,axis_z=0.0,x,z,ay=0.0,ax=0.0;
GLfloat p1=0.0,p2=0.0,p3=0.0,p4=0.0,p5=0.0,p6=0.0,p7=0.0,p8= 0.0,p=0.0,sx=5,sy=-16,sz=-15,rm=0.0,c_x=-5;
GLboolean bRotate = false, uRotate = false;
unsigned int ID[1000];
GLfloat LightColor[][3]={1,1,0,   0,1,1,   0,1,0};
GLint CI=0;int i, flag=0,sd=1,star_clr=0,comet_clr=0;
bool open = false,control=false,t=false,rock=false;
bool lit1 = false, lit2 = false,lit3 =false, lit4 = true, lit5 = false,lit6 =false;
bool amb=true,spec=true,dif=true;
double refer[1][4], eye[1][4], out[1][4];
double rockx=0.0,rockx1=3.0,rocky=0.0;
void control_room();
void spaceship();
void star();

bool s_em =false;
///mouse
///////////////////////////////
class point1
{
public:
    point1()
    {
        x=0;
        y=0;
    }
    int x;
    int y;
}clkpt[2];
GLint viewport[4]; //var to hold the viewport info
GLdouble modelview[16]; //var to hold the modelview info
GLdouble projection[16]; //var to hold the projection matrix info
float wcsClkDn[3],wcsClkUp[3];int clikd=0;
void scsToWcs(float sx,float sy, float wcsv[3] );
void processMouse(int button, int state, int x, int y);
int shcpt=1;
const int L=32;
int ncpt=L+1;
const int nt = 40;				//number of slices along x-direction
const int ntheta = 20;
const double PI = 3.14159265389;
static GLfloat v_cube[8][3] =
{
    {0.0,0.0,0.0},//0
    {0.0,0.0,1.0},//1
    {0.0,1.0,1.0},//2
    {0.0,1.0,0.0},//3

    {1.0,0.0,0.0},//4
    {1.0,0.0,1.0},//5
    {1.0,1.0,1.0},//6
    {1.0,1.0,0.0},//7

};

static GLubyte q_Indices[6][4] =
{
    {2,1,5,6},//front
    {6,5,4,7},//right
    {3,0,1,2},//left
    {7,4,0,3},//back
    {3,2,6,7},//top
    {1,0,4,5},//bottom



    /*{0,1,2,3},
    {0,1,5,4},
    {0,4,7,3},
    {1,2,6,5},
    {4,5,6,7},
    {3,2,6,7}*/

};

static GLfloat colors[8][3] =
{
    {0.0,1.0,0.0},
    {1.0,0.0,1.0},
    {1.0,0.0,1.0},
    {0.0,0.0,1.0},
    {0.0,0.0,1.0},
    {0.0,1.0,0.0},
    {1.0,1.0,0.0},
    {1.0,0.0,1.0},
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}
void material(float clr1, float clr2,float clr3,bool em = false)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { clr1*0.4, clr2*0.4, clr3*0.4, 1.0 };
    GLfloat mat_diffuse[] = { clr1,clr2,clr3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    if(em == true) {glMaterialfv(GL_FRONT, GL_EMISSION, mat_diffuse);}


    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

}
void drawcube()
{
    //glColor3f(1,1,1);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(colors[2][0],colors[2][1],colors[2][2]);
        getNormal3p(v_cube[q_Indices[i][0]][0], v_cube[q_Indices[i][0]][1], v_cube[q_Indices[i][0]][2],
                    v_cube[q_Indices[i][1]][0], v_cube[q_Indices[i][1]][1], v_cube[q_Indices[i][1]][2],
                    v_cube[q_Indices[i][2]][0], v_cube[q_Indices[i][2]][1], v_cube[q_Indices[i][2]][2]);

        glVertex3fv(&v_cube[q_Indices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube[q_Indices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[q_Indices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[q_Indices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();
}

void light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = {-9,2,-16.5};

    if(lit1){glEnable( GL_LIGHT0);  }                       ///LIGHT0
    else{  glDisable(GL_LIGHT0);   }

    //glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    //glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    //glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);


    GLfloat light_ambient1[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse1[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position1[] = {2.2,2,-16};
    //GLfloat light_position1[] = {-9,2,-16.5};
    if(lit2){glEnable( GL_LIGHT1);  }                       ///LIGHT1
    else{  glDisable(GL_LIGHT1);   }
    glLightfv( GL_LIGHT1, GL_POSITION, light_position1);
    //glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient1);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
    //glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular1);


    GLfloat light_ambient2[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse2[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat light_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position2[] = {12,2,-18};
    GLfloat spot_direction2[] = { 0,-1,0};

    if(lit3){glEnable( GL_LIGHT2);  }///LIGHT2
    else{  glDisable(GL_LIGHT2); ;   }
    glLightfv( GL_LIGHT2, GL_POSITION, light_position2);          ///position of spot light
    //glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient2);
    //glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
    //glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 35.0);


    GLfloat light_ambient3[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse3[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular3[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position3[] = {0,18,-10};
    glLightfv( GL_LIGHT3, GL_POSITION, light_position3);
    if(lit4){glEnable( GL_LIGHT3); s_em =true; }                       ///LIGHT3
    else{  glDisable(GL_LIGHT3);  s_em =false;   }
   // glLightfv( GL_LIGHT3, GL_AMBIENT, light_ambient3);
    //glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse3);
    //glLightfv( GL_LIGHT3, GL_SPECULAR, light_specular3);

    GLfloat light_ambient4[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse4[]  = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat light_specular4[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat light_position4[] = {sx,sy,sz};
    glLightfv( GL_LIGHT4, GL_POSITION, light_position4);
    if(lit5){glEnable( GL_LIGHT4);  }                       ///LIGHT4
    else{  glDisable(GL_LIGHT4);   }
    glLightfv( GL_LIGHT4, GL_AMBIENT, light_ambient4);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse4);
    glLightfv( GL_LIGHT4, GL_SPECULAR, light_specular4);

     if(amb)
    {
       glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
       glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient1);
       glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient2);
       glLightfv( GL_LIGHT3, GL_AMBIENT, light_ambient3);
    }
    else
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT3, GL_AMBIENT, no_light);
    }

    if(dif)
    {
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse3);
    }
    else
    {
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT3, GL_DIFFUSE, no_light);
    }
    if(spec)
    {
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular1);
        glLightfv( GL_LIGHT3, GL_SPECULAR, light_specular3);
        glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular2);
    }
    else
    {
        glLightfv( GL_LIGHT0,  GL_SPECULAR, no_light);
        glLightfv( GL_LIGHT1,  GL_SPECULAR, no_light);
        glLightfv( GL_LIGHT2,  GL_SPECULAR, no_light);
        glLightfv( GL_LIGHT3,  GL_SPECULAR, no_light);
    }



}

void drawsphere()
{
    GLUquadric *quad;
    quad = gluNewQuadric();
    gluQuadricTexture(quad, TRUE);
    gluSphere(quad,0.2,100,20);

}
void rotat(int a)
{
    refer[0][0] -= eye[0][0];
    refer[0][1] -= eye[0][1];
    refer[0][2] -= eye[0][2];
    refer[0][3] = 1;
    GLfloat rotat_matrix[4][4] = {
        {cos(a*3.14/180.0),0,sin(a*3.14/180.0),0},
        {0,1,0,0},
        {-sin(a*3.14/180.0),0,cos(a*3.14/180.0),0},
        {0,0,0,1}
    };
    for(int j=0; j<4; j++)      {
        for(int k=0;k<4;k++)
        {
            out[j][k] = 0;
        }
    }
    for(int i=0; i<1; i++)
    {
        for(int j=0;j<4;j++)
        {
            out[i][j] = 0;
            for(int k=0; k<4; k++)
            {
                out[i][j] += refer[i][k] * rotat_matrix[k][j];
            }
        }
    }
    refer[0][0] = out[0][0] + eye[0][0];
    refer[0][1] = out[0][1] + eye[0][1];
    refer[0][2] = out[0][2] + eye[0][2];
}
void solar_system()
{
    glPushMatrix();
    //glColor3f
    material(1,1,1);
    //glScaled(2,2,2);
    glScaled(3,3,3);
    glBindTexture(GL_TEXTURE_2D, ID[8]);      ///MERCURY
    glEnable(GL_TEXTURE_2D);
    x = 1.5 * cos(p1* 3.1416 /180 ); //1,5 -2
    z = -2 * sin(p1* 3.1416 /180);
    //glTranslatef(x,.5, z);
    glTranslatef(x,0, z);
    glRotatef(p1,0,1,0);
    drawsphere();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-.75,0);          ///mercury orbit
    glRotatef(172,0,1,1);
    glScalef(1,1.6,.8);
    GLUquadric *quad;
    quad = gluNewQuadric();
    gluQuadricTexture(quad, TRUE);
    gluDisk(quad,4,4.25,50,50);
    glPopMatrix();


    glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1,s_em);
    glBindTexture(GL_TEXTURE_2D,ID[2]);       ///SUN
    glEnable(GL_TEXTURE_2D);
    glTranslatef(0,0,0);
    glRotatef(p1,0,1,0);
    //glScaled(8,8,8);
    glScaled(10,10,10);
    drawsphere();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    material(1,1,1);
    glScaled(3.6,3.6,3.6);
    glBindTexture(GL_TEXTURE_2D, ID[10]);       ///Venus
    glEnable(GL_TEXTURE_2D);
    x = 2* cos(p2* 3.1416 /180 );
    z = -3 * sin(p2* 3.1416 /180);
    glTranslatef(x,0,z);
    glRotatef(p1,0,1,0);
    drawsphere();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-1.5,0);          ///Venus orbit
    glRotatef(172,0,1,1);
    glScalef(1,1.6,.8);
    gluDisk(quad,7,7.25,50,50);
    glPopMatrix();


    glPushMatrix();
    material(1,1,1);
    glScaled(3.9,3.9,3.9);
    glBindTexture(GL_TEXTURE_2D, ID[1]);            ///EARTH
    glEnable(GL_TEXTURE_2D);
    x = 2.5* cos(p3* 3.1416 /180 );
    //z = -3.7 * sin(p3* 3.1416 /180);
    z = -3.9 * sin(p3* 3.1416 /180);
    glTranslatef(x,0,z);
    glRotatef(p1,0,1,0);
    drawsphere();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2,0);          ///Earth orbit
    glRotatef(172,0,1,1);
    glScalef(1,1.6,.6);
    gluDisk(quad,10,10.25,50,50);
    glPopMatrix();


    glPushMatrix();
    material(1,1,1);
    glScaled(2.8,2.8,2.8);
    glBindTexture(GL_TEXTURE_2D, ID[4]);        ///MARS
    glEnable(GL_TEXTURE_2D);
    //x = 4.8 * cos(p4* 3.1416 /180 );
    //z = -3.8 * sin(p4* 3.1416 /180);
    x = 4.5 * cos(p4* 3.1416 /180 );
    z = -6.5 * sin(p4* 3.1416 /180);
    glTranslatef(x,0,z);
    glRotatef(p1,0,1,0);
    drawsphere();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,0);          ///MARS orbit
    glRotatef(172,0,1,1);
    glScalef(1,1.6,.6);
    gluDisk(quad,13,13.25,50,50);
    glPopMatrix();

    glPushMatrix();
    material(1,1,1);
    glScaled(4.2,4.2,4.2);
    glBindTexture(GL_TEXTURE_2D, ID[3]);        ///JUPITER
    glEnable(GL_TEXTURE_2D);
    //x = 3.5 * cos(p5* 3.1416 /180 );
    //z = -4 * sin(p5* 3.1416 /180);
    x = 3.6 * cos(p5* 3.1416 /180 );
    z = -5.2 * sin(p5* 3.1416 /180);
    glTranslatef(x,0,z);
    glRotatef(p1,0,1,0);
    drawsphere();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.3,0);          ///Jupiter orbit
    glRotatef(172,0,1,1);
    glScalef(1,1.4,.4);
    gluDisk(quad,17,17.25,50,50);
    glPopMatrix();

    glPushMatrix();
    material(1,1,1);
    glScaled(4,4,4);
    //x = 4.5 * cos(p6* 3.1416 /180 );
    //z = -4.8 * sin(p6* 3.1416 /180);
    x = 4.8 * cos(p6* 3.1416 /180 );
    z = -6.2 * sin(p6* 3.1416 /180);
    glTranslatef(x,0,z);
    glRotatef(p1,0,1,0);
    glBindTexture(GL_TEXTURE_2D, ID[5]);           ///SATURN
    glEnable(GL_TEXTURE_2D);
    gluSphere(quad,0.2,100,20);
    glDisable(GL_TEXTURE_2D);
    material(0.961, 0.961, 0.863);
    //glBindTexture(GL_TEXTURE_2D, ID[40]);
   // glEnable(GL_TEXTURE_2D);
    glutSolidTorus(0.05,.3,50,50);
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    material(1,1,1);
    glTranslatef(0,-2.8,0);          ///SATURN orbit
    glRotatef(175,0,1,1);
    glScalef(1,1.4,.6);
    gluDisk(quad,20,20.25,50,50);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1,1,1);
     material(1,1,1);
    //glScaled(2.95,2.95,2.95);
    glScaled(3.95,3.95,3.95);
    glBindTexture(GL_TEXTURE_2D, ID[7]);        ///URANUS
    glEnable(GL_TEXTURE_2D);
    //x = 5.5 * cos(p7* 3.1416 /180 );
    //z = -5.8 * sin(p7* 3.1416 /180);
    x = 5.5 * cos(p7* 3.1416 /180 );
    z = -7.28 * sin(p7* 3.1416 /180);
    glTranslatef(x,0,z);
    glRotatef(p1,0,1,0);
    drawsphere();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.8,0);          ///URANUS orbit
    glRotatef(175,0,1,1);
    glScalef(1,1.4,.6);
    gluDisk(quad,23,23.25,50,50);
    glPopMatrix();



    glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1);
    glScaled(3.95,3.95,3.95);
    glBindTexture(GL_TEXTURE_2D, ID[6]);        ///NEPTUNE
    glEnable(GL_TEXTURE_2D);
    x = 6.4 * cos(p8* 3.1416 /180 );
    //z = -6.5 * sin(p8* 3.1416 /180);
    z = -8.7 * sin(p8* 3.1416 /180);
    glTranslatef(x,0,z);
    glRotatef(p1,0,1,0);
    drawsphere();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,-3,0);          ///neptune orbit
    glRotatef(175,0,1,1);
    glScalef(1,1.4,.6);
    gluDisk(quad,27,27.25,50,50);
    glPopMatrix();


}


GLfloat ctrlpoints[L+1][3] =
{
     {0.6,0.65,0},{1.425,1.1,0},{2.525,1.2,0},
     //{3.125,1,0},{3.375,0.5,0},{3.95,0.25,0},
     {3.7,0.775,0},{4.475,0.675,0},{5.175,0.675,0},
     {4.975,0.375,0},{5.6,0.625,0},{6.3,0.6,0},
     {6.525,0.175,0},{6.6,-0.225,0},
     ///comet lower
    {0.6,0.65,0},{1.425,1.1,0},{2.525,1.2,0},{3.125,1,0},

    /// gacher nich
      {7.225,0.425,0} ,{6.375,0.425,0},{5.225,0.375,0},{3.975,0.35,0},
      {2.625,0.275,0} , {1.25,0.275,0},


      ///pata
      {2.95,0.6,0},{3.6,1.35,0},{4.025,2.7,0},
      {2.95,4.35,0},{2.95,4.35,0},{2.05,4.525,0},

      {3.825,0.175,0},{2.725,0.95,0},{2.05,1.05,0}, {1.5,0.65,0}, {1.5,0.65,0},  {1.35,0.325,0}


};


//control points
long long nCr(int n, int r)
{
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve ( double t,  float xy[2],int s,int e)
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    int L=e-s;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[s][0];
        y+=coef*ctrlpoints[s][1];
        s+=1;

    }
    xy[0] = float(x);
    xy[1] = float(y);
}
void setNormal(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(-Nx,-Ny,-Nz);
}
void comet_lower()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy,11,14);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,xy,11,14);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= 1; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void comet()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve(t,xy,0,10);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < 28; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve(t,xy,0,10);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <=ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

           if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }

            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    }

}
void tree()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve(t,xy,15,20);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve(t,xy,15,20);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

           if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }

            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    }

}

void leaf()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    //const float startx = 0, endx = ctrlpoints[10][0];
    //number of angular slices
    //const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve(t,xy,0,5);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve(t,xy,0,5);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for (j = 0; j <= 2; ++j)
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

           if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }

            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    }

}
void leaf1()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    //const float startx = 0, endx = ctrlpoints[10][0];
    //number of angular slices
    //const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve(t,xy,21,26);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve(t,xy,21,26);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for (j = 0; j <= 1; ++j)
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

           if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }

            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    }

}
void leaf2()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    //const float startx = 0, endx = ctrlpoints[10][0];
    //number of angular slices
    //const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve(t,xy,26,32);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve(t,xy,26,32);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for (j = 0; j <= 2; ++j)
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

           if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }

            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    }

}
void tree1()
{
    glPushMatrix();
    material(0.647, 0.165, 0.165);
    glTranslated(-10, 0,0);
    glScalef(2,1,1);
    tree();
    glPopMatrix();

    glPushMatrix();
    material(0.000, 0.392, 0.000);             ///leaf upper
    glTranslated( 4, -0.45,0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    material(0.000, 0.392, 0.000);
    glTranslated( 4, -0.6,0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    material(0.678, 1.000, 0.184);
    glTranslated(4.6,-.5,-.5);
    leaf();
    glPopMatrix();
    glPushMatrix();
    material(0.678, 1.000, 0.184);
    glScalef(.8,.8,.8);
    glTranslated(4.6,-.35,0);
    leaf();
    glPopMatrix();
    glPushMatrix();
    material(0.196, 0.804, 0.196);
    glTranslated(4,-.6,-0.5);
    leaf();
    glPopMatrix();

    glPushMatrix();
    material(0.196, 0.804, 0.196);
    glTranslated(4,-1,0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(12.5,-2,0.6);
    glRotatef(180,0,0,1);
    for(float l=170;l>=120;l=l-5)
    {
        glPushMatrix();
        material(0.000, 0.502, 0.000);
        glTranslated(8.8,-1.5,-.5);
        glRotated(l,0,0,1);
        leaf();
        glPopMatrix();
    }
    glPopMatrix();


    for(float l=70;l>=10;l=l-5)
    {
        glPushMatrix();
        material(0.000, 0.502, 0.000);
        glTranslated(5,-1,0.6);
        glRotated(l,0,0,1);
        leaf();
        glPopMatrix();
    }

        ///*************************leaf LOWER****************************

    glPushMatrix();
    material(0.486, 0.988, 0.000);
    glTranslated(0,-.6,-.2);
    leaf();
    glPopMatrix();

    glPushMatrix();
    material(0.486, 0.988, 0.0006);
    glTranslated(0,-.8,-.2);
    leaf();
    glPopMatrix();

    glPushMatrix();
    material(0.486, 0.988, 0.000);
    glTranslated(0,-1,-.2);
    leaf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,2,0.6);
    for(float l=170;l>=120;l=l-5)
    {
        glPushMatrix();
        material(0.000, 0.502, 0.000);
        glTranslated(8.8,-1.5,-.5);
        glRotated(l,0,0,1);
        leaf();
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,-.4,-1);
    glRotatef(-180,0,0,1);
    for(float l=70;l>=10;l=l-5)
    {
        glPushMatrix();
        material(0.000, 0.502, 0.000);
        glTranslated(5,-1,0.6);
        glRotated(l,0,0,1);
        leaf();
        glPopMatrix();
    }
    glPopMatrix();




    glPushMatrix();
    material(0.133, 0.545, 0.133);
    glScaled(1.2,1.2,1.2);
    glRotated(90,1,0,0);
    glTranslated(2.9,-.3,.3);
    //leaf();
    glPopMatrix();


    glPushMatrix();
    material(0.133, 0.545, 0.133);
    glTranslated(1,-0.5,0);  ///leaf left
    leaf1();
    glPopMatrix();

    glPushMatrix();
    material(0.133, 0.545, 0.133);
    glTranslated(1.3,-0.5,0);
    leaf1();
    glPopMatrix();

    glPushMatrix();
    material(0.678, 1.000, 0.184);
    glTranslated(1.5,-0.5,0);
    leaf1();
    glPopMatrix();

    glPushMatrix();
    glScalef(.8,.8,.8);
    glTranslated(1.7,-0.5,0);
    leaf1();
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.9,-0.5,0);
    leaf1();
    glPopMatrix();


    glPushMatrix();
    material(0.486, 0.988, 0.000);
    glTranslated(2.2,-1.5,1);
    glRotatef(180,1,0,0);
    leaf1();
    glPopMatrix();

    glPushMatrix();
    material(0.000, 0.392, 0.000);
    glTranslated(2.4,-1.5,1);
    glRotated(180,1,0,0);
    leaf1();
    glPopMatrix();

    glPushMatrix();
    material(0.678, 1.000, 0.184);
    //glScalef(.6,.6,.6);
    glTranslated(2.6,-1.5,1);
    glRotated(180,1,0,0);
    leaf1();
    glPopMatrix();

    glPushMatrix(); ///
    material(0.678, 1.000, 0.184);
    glTranslated(1.8,-1.5,1);
    glRotated(180,1,0,0);
    leaf1();
    glPopMatrix();
    glPushMatrix(); ///
    material(0.678, 1.000, 0.184);
    glTranslated(1.5,-1.5,1);
    glRotated(180,1,0,0);
    leaf1();
    glPopMatrix();
    glPushMatrix(); ///
    material(0.678, 1.000, 0.184);
    glTranslated(1.2,-1.5,1);
    glRotated(180,1,0,0);
    leaf1();
    glPopMatrix();

   /* glPushMatrix();
    material(0.486, 0.988, 0.000);
    glTranslated(5,-.3,0);   ///lower leaf
    glRotatef(90,0,0,1);
    glScalef(.5,.5,.5);
    leaf2();
    glPopMatrix();

    glPushMatrix();
    material(0.133, 0.545, 0.133);
    glTranslated(5,-1,0);
    glRotatef(90,0,0,1);
    glScalef(.6,.6,.6);
    leaf2();
    glPopMatrix();

    glPushMatrix();
    material(0.678, 1.000, 0.184);
    glTranslated(1,-0.4,0.2);
    leaf();
    glPopMatrix();

    glPushMatrix();
    material(0.678, 1.000, 0.184);
    //glTranslated(0.5,-0.9,0);
    glTranslated(1,-0.8,0.2);
    leaf();
    glPopMatrix();

    glPushMatrix();
    material(0.133, 0.545, 0.133);
    //glTranslated(0.5,-.6,0);
    glTranslated(0.5,-.4,0);
    glRotatef(90,1,0,0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    material(0.180, 0.545, 0.341);
    //glTranslated(0.5,-1,0);
    glTranslated(0.5,-.8,0);
    glRotatef(90,1,0,0);
    leaf();
    glPopMatrix();

    glPushMatrix();
    material(0.678, 1.000, 0.184);
    //glTranslated(0.5,-1,0);
    glTranslated(0.5,-.2,0);
    glRotatef(90,1,0,0);
    leaf();
    glPopMatrix();*/

}

void showControlPoints()
{
    glPointSize(5.0);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <=L; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
}

void drawString(float x, float y, float z,char *string) {
  glRasterPos3f(x, y, z);

  for (char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);  // Updates the position
  }
}
void drawscreen()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5,5,-5,5, 4,50);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(0,2,20, 0,0,0, 0,1,0);
    glPushMatrix();
    glColor3f(1,1,1);
    drawString(-5, 3, 0,"WELCOME!!!!!!!!!");
    glColor3f(1,0,0);
    drawString(-5, -2, 0,"NASA Head Office");
    glColor3f(0,1,0);
    drawString(-5, -6, 0,"SOLAR SYSTEM");
    glPopMatrix();

}
void rock_falling()
{
    //while(1)
       //{
           int random = 1 + (rand() % 8);
           printf("inside rock faaling");
           switch(1)
           {
             case 1:
                 printf("mum");
                 glColor3f(1,1,1);
                 glPushMatrix();
                 //glBindTexture(GL_TEXTURE_2D, ID[36]);  ///0,18,-10
                 //glEnable(GL_TEXTURE_2D);
                 //glTranslatef(rockx,rocky,0);
                 glTranslatef(5,30,-10);
                 //glTranslatef(1.5,rockx1,0);
                 glScalef(0.7,0.7,0.7);
                 GLUquadric *quadrock1;
                 quadrock1 = gluNewQuadric();
                 gluQuadricTexture(quadrock1, TRUE);
                 gluSphere(quadrock1,0.8,100,20);
                 //glDisable(GL_TEXTURE_2D);
                 glPopMatrix();
                 break;


           }

       //}
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5,5,-5,5, 4,200);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    //gluLookAt(0,2,20, 0,0,0, 0,1,0);
    gluLookAt(Txval,Tyval,Tzval, Cxval,Cyval,Czval, 0,1,0);
    //gluLookAt(0,0,10, Cxval,Cyval,Czval, 0,1,0);
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info
    glViewport(0, 0, windowHeight, windowWidth);
    glEnable(GL_LIGHTING);
   // glBindTexture(GL_TEXTURE_2D, ID[9]);vv
   // glEnable(GL_TEXTURE_2D);
   /* glPushMatrix();

    glTranslatef(0,0,Tzval);
    glRotatef( alpha,axis_x, axis_y, 0.0 );
   // drawspace();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);*/


    glPushMatrix();
    glTranslatef(sx,sy,sz);
    glRotatef(rm, axis_x,axis_y,axis_z);
    glScalef(.5,.5,.5);
    spaceship();
    glPopMatrix();


    //showControlPoints();



    if(sd == 0)
    {

       drawscreen();
    }
    if(sd == 1)
    {
        glPushMatrix();
        glTranslatef(-23,-12,-8);   ///tree1
        //glTranslatef(-10,-19,8);

        glRotatef(90,0,0,1);
        tree1();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(15,-12,-8);    ///tree2
        glRotatef(90,0,0,1);
        tree1();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-23,-12,-17);   ///tree3
        glRotatef(90,0,0,1);
        tree1();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(15,-12,-17);    ///tree4
        glRotatef(90,0,0,1);
        tree1();
        glPopMatrix();

        glPushMatrix();
        material(1,1,1);
        glBindTexture(GL_TEXTURE_2D, ID[38]);    ///sky
        glEnable(GL_TEXTURE_2D);
        glTranslatef(-80,-25,-30);
        glScalef(300,100,.1);
        drawcube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, ID[39]);  ///ground
        glEnable(GL_TEXTURE_2D);
        glTranslatef(-50,-20,-30);
        glScalef(100,.5,50);
        drawcube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, ID[40]);  ///ground round in front
        glEnable(GL_TEXTURE_2D);
        glTranslatef(-16,-19.2,-10);
        glScalef(25,.1,13);
        drawcube();
        //glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPushMatrix();   ///ground round in front
        glTranslatef(-16,-19.2,3);
        glScalef(65,.1,10);
        drawcube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();     ///lamp light 1
        material(1.000, 0.843, 0.000);
        glTranslatef(-14.2,-10,3);
        glRotated(90,1,0,0);
        glScalef(.3,.5,.2);
        comet();
        glPopMatrix();
        glPushMatrix();
        material(0.412, 0.412, 0.412);
        glTranslatef(-14,-19,3);
        glScalef(.2,9,.2);
        drawcube();
        glPopMatrix();


        glPushMatrix();     ///lamp light 2
        material(1.000, 0.843, 0.000);
        glTranslatef(-14.2,-10,12);
        glRotated(90,1,0,0);
        glScalef(.3,.5,.2);
        comet();
        glPopMatrix();
        glPushMatrix();
        material(0.412, 0.412, 0.412);
        glTranslatef(-14,-19,12);
        glScalef(.2,9,.2);
        drawcube();
        glPopMatrix();

        glPushMatrix();     ///lamp light 3
        material(1.000, 0.843, 0.000);
        glTranslatef(14.2,-10,3);
        glRotated(90,1,0,0);
        glScalef(.3,.5,.2);
        comet();
        glPopMatrix();
        glPushMatrix();
        material(0.412, 0.412, 0.412);
        glTranslatef(14,-19,3);
        glScalef(.2,9,.2);
        drawcube();
        glPopMatrix();


        glPushMatrix();     ///lamp light 4
        material(1.000, 0.843, 0.000);
        glTranslatef(14.2,-10,12);
        glRotated(90,1,0,0);
        glScalef(.3,.5,.2);
        comet();
        glPopMatrix();
        glPushMatrix();
        material(0.412, 0.412, 0.412);
        glTranslatef(14,-19,12);
        glScalef(.2,9,.2);
        drawcube();
        glPopMatrix();




        glPushMatrix();
        material(1,1,1);
        glTranslatef(-5,-17,-12);
        control_room();
        glPopMatrix();
        light();
    }

    if(sd == 2)
    {
        glPushMatrix();
        glTranslatef(-12,20,c_x);
        comet_clr = 1 + (rand() % 3);
        if(comet_clr == 1)
            material(1.000, 0.078, 0.576);
        if(comet_clr == 2)
            material(0.780, 0.082, 0.522);
        if(comet_clr == 3)
            material(0.859, 0.439, 0.576);
        glPushMatrix();
        glTranslated(2,0,0);
        comet();
        glPopMatrix();

        glPushMatrix();
        for(int k=1;k<=4;k++)
        {
            glTranslated(0,-k*.1,0);
            comet_lower();
        }
        glPopMatrix();

        glPushMatrix();
        glTranslated(0,0,-0.6);
        glRotatef(90,1,0,0);
        comet_lower();
        glPopMatrix();

        glPushMatrix();
        glTranslated(0,-.4,-0.6);
        glRotatef(90,1,0,0);
        comet_lower();
        glPopMatrix();


        glPopMatrix();

        glPushMatrix();
        material(1,1,1);
        glBindTexture(GL_TEXTURE_2D, ID[9]);
        glEnable(GL_TEXTURE_2D);
        glTranslatef(-50,-50,-20);
        glScalef(5,100,100);
        drawcube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPushMatrix();
        material(1,1,1);
        glBindTexture(GL_TEXTURE_2D, ID[9]);
        glEnable(GL_TEXTURE_2D);
        glTranslatef(-10,-10,-80);
        //glTranslatef(6,32,0);
        glScalef(100,.5,100);
        drawcube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glTranslated(5,20.14,20);
        glScaled(.2,.5,.2);
        //glRotatef(90,0,1,0);
        star_clr = 1 + (rand() % 4);
        if(star_clr == 1)
            material(0.941, 0.973, 1.000);
        if(star_clr == 2)
            material(0.000, 1.000, 1.000);
        if(star_clr == 3)
            material(1.000, 0.843, 0.000);
        if(star_clr == 4)
            material(0.565, 0.933, 0.565);
        star();
        glPopMatrix();

         glPushMatrix();
         glTranslated(5,20.14,0);
         for(float p=20;p<=25;p+=.5)
         {
//            glTranslated(0,p,);
            glScaled(.2,.5,.2);
             star();}
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,15,-10);
        solar_system();
        glPopMatrix();
        light();
    }




    /*glPushMatrix();
    if(t){rotat(a);}
    glTranslatef(Txval,Tyval,Tzval);
    //glTranslatef(-4,-10,-8);
    //glTranslatef(10,18,-10);
    //glTranslatef(2.2,2,-16);//light right
    //glTranslatef(-9,2,-16.5);//light lft
    //glTranslatef(12,2,-18);
    //glTranslatef(5,15,-10);
    //glutSolidSphere(1,50,50);
    glPopMatrix();*/

   /* if(rock==true)
  {  for(int i=0;i<=2;i++)
   {
   glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, ID[36]);  ///0,18,-10
     glEnable(GL_TEXTURE_2D);
     glTranslatef(rockx,rocky,0);
     //glTranslatef(15+(i*3.5),3+i,0-(i*1.25));
     glTranslatef(0+(i*5.5),23+i,-10-(i*1.25));
     glScalef(0.7,0.7,0.7);
     GLUquadric *quadrock1;
    quadrock1 = gluNewQuadric();
    gluQuadricTexture(quadrock1, TRUE);
    gluSphere(quadrock1,0.8,100,20);
     glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   }
   for(int i=0;i<=2;i++)
   {
   glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, ID[37]);
     glEnable(GL_TEXTURE_2D);
     glTranslatef(rockx1,rocky,0);
     //glTranslatef(-15-(i*3.5),3+i,0-(i*1.25));
     glTranslatef(-10+(i*3.5),23+i,-10-(i*1.25));
     glScalef(0.7,0.7,0.7);
     GLUquadric *quadrock1;
    quadrock1 = gluNewQuadric();
    gluQuadricTexture(quadrock1, TRUE);
    gluSphere(quadrock1,0.8,100,20);
     glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   }
  }*/


    //rotat();
    //light();
    /*printf("%d\n",Txval);
    printf("%d\n",Tyval);
    printf("%d\n",Tzval);*/

    glFlush();
    glutSwapBuffers();

}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 's':
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;


    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;

    case 'w': //Escape key
         dx = (Cxval - Txval);
         dy = (Cyval - Tyval);
         dz = (Czval- Tzval);
         d = sqrt((dx*dx) + (dy+dy) + (dz*dz));
         eps = 3/d ;
         Txval = (1 - eps) * Txval + eps * Cxval;
         Tyval = (1 - eps) * Tyval + eps * Cyval;
         Tzval = (1 - eps) * Tzval + eps * Czval;

         break;

     case 'q': //Escape key
         dx = (Cxval - Txval);
         dy = (Cyval - Tyval);
         dz = (Czval- Tzval);
         d = sqrt((dx*dx) + (dy+dy) + (dz*dz));
         eps = -3/d;
         Txval = (1 - eps) * Txval + eps * Cxval;
         Tyval = (1 - eps) * Tyval + eps * Cyval;
         Tzval = (1 - eps) * Tzval + eps * Czval;

         break;

    case '-':
        Tzval+=0.2;
        break;

    case '+':
        Tzval-=0.2;
        break;

    case 'u':
        Tyval+=0.2;
        break;

    case 'd':
        Tyval-=0.2;
        break;

    case 'r':
        Txval+=0.2;
        break;

    case 'l':
        Txval-=0.2;
        break;

    case 'o':
        open=!open;
        break;

    case '1':
        lit1=!lit1;
        break;

    case '2':
        lit2=!lit2;
        break;

    case '3':
        lit3=!lit3;
        break;

    case '4':
        lit4=!lit4;
        break;
    case '5':
        lit5=!lit5;
        break;

    case 'z':
        amb=!amb;
        break;
    case 'x':
        dif=!dif;
        break;
    case 'c':
        spec=!spec;
        break;

/*    case 'z':
        sx-=0.2;  ///left
        if(control) Txval=sx;
        break;
    case 'x':
        sx+=0.2; ///right
        if(control) Txval=sx;
        break;
    case 'c':
        sy+=0.2; ///up
        if(control) Tyval=sy;
        break;

    case 'v':
        sy-=0.2; ///down
        if(control) Tyval=sy;
        break;
*/
     case 'b':
        sz+=0.2; ///front
        if(control) Tzval=sz;
        break;

    case 'n':
        sz-=0.2; ///back
        if(control) Tzval=sz;
        break;

    case 'm':
        rm+=0.4; ///rotationX
        axis_x=1.0;
        axis_y=0.0;
        axis_z=0.0;
        if(rm>360)
        { rm= 0;}
        break;

    case 'j':
        rm+=0.4; ///rotationY
        axis_x=0.0;
        axis_y=1.0;
        axis_z=0.0;
        if(rm>360)
        { rm= 0;}
        break;
    case 'k':
        rm+=0.4; ///rotationZ
        axis_x=0.0;
        axis_y=0.0;
        axis_z=1.0;
        if(rm>360)
        { rm= 0;}
        break;

    case '<':
        rm+=0.4; ///rotation -X
        axis_x=-1.0;
        axis_y=0.0;
        axis_z=0.0;
        if(rm>360)
        { rm= 0;}
        break;

    case '>':
        rm+=0.4; ///rotationY
        axis_x=0.0;
        axis_y=-1.0;
        axis_z=0.0;
        if(rm>360)
        { rm= 0;}
        break;
    case '?':
        rm+=0.4; ///rotationZ
        axis_x=0.0;
        axis_y=0.0;
        axis_z=-1.0;
        if(rm>360)
        { rm= 0;}
        break;


    case 'g':
        //control=!control;
        //Txval=5;Tyval=18;Tzval=-10;
        //-2,-10,-10   sx,sy,sz
        //Txval=sx;Tyval=sy;Tzval=sz; //far large near small 7 -10 -15
        Txval=10;Tyval=30;Tzval=-30;
        //Txval=10;Tyval=15;Tzval=30;
        sx=10,sy=18,sz=-15;
        sd = 2;
        break;

    case 'h':
        t=!t;
        a=.13;
        eye[0][0] = Txval;
        eye[0][1] = Tyval;
        eye[0][2] = Tzval;
        eye[0][3] = 1;
        glutPostRedisplay();
        break;

    case 'f':
        rock=!rock;
        if(rock==true)
        {
            rock_falling();
        }
        break;
    case 'a':
        sd =1;
        break;
    case 'y':
        control =!control;
        Txval=sx;Tyval=sy;Tzval=sz;
        break;


    case 27:	// Escape key
        exit(1);
    }
}
void Spaceship_Keys(int key, int xx, int yy)
{

    switch (key) {
        case GLUT_KEY_LEFT :
            sx-=0.2;  ///left
            if(control) Txval=sx;
            break;
        case GLUT_KEY_RIGHT :
            sx+=0.2; ///right
            if(control) Txval=sx;
            break;
        case GLUT_KEY_UP :
             sy+=0.2; ///up
             if(control) Tyval=sy;
             break;
        case GLUT_KEY_DOWN :
             sy-=0.2; ///down
             if(control) Tyval=sy;
             break;
    }

}
void scsToWcs(float sx,float sy, float wcsv[3] )
{

    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    //glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info


    winX = sx;
    winY = (float)viewport[3] - (float)sy;
    winZ = 0;

    //get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    wcsv[0]=worldX;
    wcsv[1]=worldY;
    wcsv[2]=worldZ;


}

void processMouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(flag!=1)
        {
            flag=1;
            clkpt[0].x=x;
            clkpt[0].y=y;
        }


        scsToWcs(clkpt[0].x,clkpt[0].y,wcsClkDn);
        cout<<"\nD: "<<x<<" "<<y<<" wcs: "<<wcsClkDn[0]<<" "<<wcsClkDn[1];
    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (flag==1)
        {
            clkpt[1].x=x;
            clkpt[1].y=y;
            flag=0;
        }
        float wcs[3];
        scsToWcs(clkpt[1].x,clkpt[1].y,wcsClkUp);
        cout<<"\nU: "<<x<<" "<<y<<" wcs: "<<wcsClkUp[0]<<" "<<wcsClkUp[1];

        clikd=!clikd;
    }
}

void animate()
{

    if (bRotate == true)
    {
        theta += 0.3;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if(p1>360)
    {
        p1=0;
    }
    else
    {
        //p1+=0.3;
        p1+=0.3;

    }

    if(p2>360)
    {
        p2=0;
    }
    else
    {
        p2+=0.2;
        //p2+=0.03;
    }

    if(p3>360)
    {
        p3=0;
    }
    else
    {
        p3+=0.1;
       // p3+=0.03;;
    }

    if(p4>360)
    {
        p4=0;
    }
    else
    {
        p4+=0.09;
       // p4+=0.03;
    }

    if(p5>360)
    {
        p5=0;
    }
    else
    {
        p5+=0.08;
        //p5+=0.03;
    }

    if(p6>360)
    {
        p6=0;
    }
    else
    {
        p6+=0.07;
        //p6+=0.03;
    }

    if(p7>360)
    {
        p7=0;
    }
    else
    {
        p7+=0.06;
      // p7+=0.03;
    }

    if(p8>360)
    {
        p8=0;
    }
    else
    {
        p8+=0.05;
    }

     if(open == true)
    {
     //glTranslatef(18,-2.6,5);
        p = 15;
    }
    else
    {
        p=0.0;
    }

    if(rock==true)
   {   //rockx -= 0.1;
       rockx1 -= 0.1;
       //rocky -= 0.1;
       if(rocky<=-20)
       {
           rocky=0.0;
       }
        if(rockx<=-20)
       {
           rockx=0.0;
       }
        if(rockx1<=-3)
       {
           rockx1=3.0;
       }

   }
   if(c_x<=-30)
   {
       c_x=-5;
   }
   else
  {
      c_x-=.01;
  }

    glutPostRedisplay();


}

void LoadTexture(const char*filename, int a)
{
    glGenTextures(1, &ID[a]);
    glBindTexture(GL_TEXTURE_2D, ID[a]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[a]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Final Project");
    refer[0][0]=-4;refer[0][1]=-10;refer[0][2]=-10,refer[0][3]=1;

    LoadTexture("E:\\graphics_lab\\solar_system\\e.bmp",1);
    LoadTexture("E:\\graphics_lab\\solar_system\\sun.bmp",2);
    LoadTexture("E:\\graphics_lab\\solar_system\\jupiter.bmp",3);
    LoadTexture("E:\\graphics_lab\\solar_system\\mars.bmp",4);
    LoadTexture("E:\\graphics_lab\\solar_system\\Saturn.bmp",5);
    LoadTexture("E:\\graphics_lab\\solar_system\\neptune.bmp",6);
    LoadTexture("E:\\graphics_lab\\solar_system\\uranus.bmp",7);
    LoadTexture("E:\\graphics_lab\\solar_system\\mercury1.bmp",8);
    LoadTexture("E:\\graphics_lab\\solar_system\\galaxy3.bmp",9);
    LoadTexture("E:\\graphics_lab\\solar_system\\venus.bmp",10);



    LoadTexture("E:\\graphics_lab\\solar_system\\earthmoon.bmp",11);
    LoadTexture("E:\\graphics_lab\\solar_system\\Satelitte.bmp",12);
    LoadTexture("E:\\graphics_lab\\solar_system\\ship4.bmp",13);
    //LoadTexture("E:\\graphics_lab\\solar_system\\clk2.bmp",14);
    //LoadTexture("E:\\graphics_lab\\solar_system\\clk2.bmp",15);
    LoadTexture("E:\\graphics_lab\\solar_system\\wall2.bmp",16);
    LoadTexture("E:\\graphics_lab\\solar_system\\wall3.bmp",17);
    LoadTexture("E:\\graphics_lab\\solar_system\\wall5.bmp",18);
    LoadTexture("E:\\graphics_lab\\solar_system\\wall4.bmp",19);
    //LoadTexture("E:\\graphics_lab\\solar_system\\wall4.bmp",20);
    LoadTexture("E:\\graphics_lab\\solar_system\\keyboard.bmp",21);
    LoadTexture("E:\\graphics_lab\\solar_system\\nosignal.bmp",22);
    LoadTexture("E:\\graphics_lab\\solar_system\\ss.bmp",23);
    LoadTexture("E:\\graphics_lab\\solar_system\\white.bmp",24);
    LoadTexture("E:\\graphics_lab\\solar_system\\earth2.bmp",25);
    LoadTexture("E:\\graphics_lab\\solar_system\\bar.bmp",26);
    LoadTexture("E:\\graphics_lab\\solar_system\\rocket.bmp",27);
    LoadTexture("E:\\graphics_lab\\solar_system\\nasa3.bmp",28);
    LoadTexture("E:\\graphics_lab\\solar_system\\bin2.bmp",29);
    LoadTexture("E:\\graphics_lab\\solar_system\\sp1.bmp",30);
    LoadTexture("E:\\graphics_lab\\solar_system\\sp2.bmp",31);
    LoadTexture("E:\\graphics_lab\\solar_system\\sp4.bmp",32);
    LoadTexture("E:\\graphics_lab\\solar_system\\usa.bmp",33);
    LoadTexture("E:\\graphics_lab\\solar_system\\n3.bmp",34);
    LoadTexture("E:\\graphics_lab\\solar_system\\w.bmp",35);
    LoadTexture("E:\\graphics_lab\\solar_system\\rock1.bmp",36);
    LoadTexture("E:\\graphics_lab\\solar_system\\rock2.bmp",37);
    LoadTexture("E:\\graphics_lab\\solar_system\\sky.bmp",38);
    LoadTexture("E:\\graphics_lab\\solar_system\\grass1.bmp",39);
    LoadTexture("E:\\graphics_lab\\solar_system\\road.bmp",40);
   // LoadTexture("E:\\graphics_lab\\solar_system\\glass.bmp",41);



    //glutReshapeFunc(resize);
    glutMouseFunc(processMouse);
    glutSpecialFunc(Spaceship_Keys);
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);

    glClearColor(0,0,0,1);


    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    //light();
    printf("WELCOME TO PLANET SAVER!!!!!!!\n");
    printf("Press following keys to experience different features\n");
    printf("Press - for zoom out \n");
    printf("Press + for zoom in \n");
    printf("Press r for moving right \n");
    printf("Press l for moving left \n");
    printf("Press u for moving upwards \n");
    printf("Press d for moving downwards \n\n");

    printf("MOVING SPCESHIP\n");
    printf("Press z for moving left side \n");
    printf("Press x for moving right side \n");
    printf("Press c for moving up side\n");
    printf("Press v for moving down side\n");
    printf("Press b for moving far side\n");
    printf("Press n for moving near side\n");
    printf("Press m for rotating in +X\n");
    printf("Press < for rotating in -X\n");
    printf("Press j for rotating in +Y\n");
    printf("Press > for rotating in -Y\n");
     printf("Press k for rotating in +Z\n");
    printf("Press ? for rotating in -Z\n");

    printf("LIGHTS\n");
    printf("Press 1 for light1 in control room \n");
    printf("Press 2 for light2 in control room \n");
    printf("Press 3 for spot light in control room \n");
    printf("Press 4 for sunlight \n");
    printf("Press 5 for dynamic spaceship light \n\n");



    glutMainLoop();

    return 0;
}

