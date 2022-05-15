#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"

extern unsigned int ID[100];
void drawcube();
extern bool open;
extern GLfloat p;
void material(float clr1, float clr2,float clr3,bool em=false);
void f1()
{

    //glColor3f(0.804, 0.361, 0.361); //Y
    //material(0.391, 0.144, 0.144, 0.804, 0.361, 0.361,60);
    //glColor3f(1,1,1);
    material(1,1,1);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[18]);
    glEnable(GL_TEXTURE_2D);
    glTranslated(-15.2,-2,-22);
    glRotated(28,0,1,0);
    glScaled(7,15,0.5);     /// background wall2
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //glColor3f(0.863, 0.078, 0.235); //g
    // material(0.345, 0.031, 0.094,0.863, 0.078, 0.235,60);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[18]);
    glEnable(GL_TEXTURE_2D);
    glTranslated(2.4,-2,-25);
    glRotated(-28,0,1,0);
    glScaled(7.5,15,0.5);     /// background wall3
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void wall()
{

    //glColor3f(0.847, 0.749, 0.847);
    //material(0.339, 0.299, 0.339,0.847, 0.749, 0.847,60);
    //glColor3f(1,1,1);
    material(1,1,1);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[16]);
    glEnable(GL_TEXTURE_2D);
                            ///floor
    glScaled(50,2,30);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


}
void second_floor()
{
    glPushMatrix();
    glTranslatef(-22,35,-25); ///ceiling of 2nd floor
    wall();
    glPopMatrix();


    glPushMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[17]);        ///middle wall of 2nd floor
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-22,19,-22);
    glScalef(50,16,0.5);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //glColor3f(1.000, 0.627, 0.478);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[17]);
    glEnable(GL_TEXTURE_2D);
    glTranslated(-20,16.8,-21.5);    ///sidewall floor 2
    glRotated(90,0,0,1);
    glScaled(19.3,2,26.64);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[17]);
    glEnable(GL_TEXTURE_2D);
    glTranslated(28,16.8,-25);     ///sidewall floor2
    glRotated(90,0,0,1);
    glScaled(19.3,2,30);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[34]);        ///nasa logo
    glEnable(GL_TEXTURE_2D);
    //glTranslatef(6,19,5);
    glTranslatef(26,19,5);
    glRotated(180,0,1,0);
    glScalef(20,16.3,1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[33]);        ///usa flag
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-4,19,5);
    glRotatef(90,0,0,1);
    glScalef(16.5,16,1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[35]);        ///
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-4,19,5);
    glScalef(10,16.3,3);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


}
void room()
{

    glPushMatrix();
    glTranslated(0,0,0);
    glScalef(1.35,1.35,1);      ///wall
    f1();
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[19]);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-12,-2.6,-25);
    glScalef(15,20,0.5);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //glColor3f(1.000, 0.627, 0.478);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[17]);
    glEnable(GL_TEXTURE_2D);
    glTranslated(-20,-2.5,-21.5);    ///sidewall 1
    glRotated(90,0,0,1);
    glScaled(19.3,2,26.64);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //glColor3f(1.000, 0.627, 0.478);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[17]);
    glEnable(GL_TEXTURE_2D);
    glTranslated(14.1,-2.5,-21.5);     ///sidewall 2
    glRotated(90,0,0,1);
    glScaled(19.3,2,26.64);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[17]);
    glEnable(GL_TEXTURE_2D);
    glTranslated(28,-2.5,-25);    ///sidewall 3
    glRotated(90,0,0,1);
    glScaled(19.3,2,30);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[17]);        ///middle wall room2
    glEnable(GL_TEXTURE_2D);
    glTranslatef(13,-2.6,-25);
    glScalef(15,20,0.5);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(p,0,0);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[17]);        ///door
    glEnable(GL_TEXTURE_2D);
    glTranslatef(13,-2.6,5);
    glScalef(15,20,0.5);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-22,16.8,-25); ///ceiling
    wall();
    glPopMatrix();

    glPushMatrix();
    second_floor();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-22,-4.5,-25);   ///floor
    wall();
    glPopMatrix();

}

void monitor(int x)
{
    glPushMatrix();
    //glColor3f(0,0,0);
    material(0,0,0);
    glScalef(3,1.5,.2);
    drawcube();
    glPopMatrix();

    glPushMatrix();
        //glColor3f(1,1,1);
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[x]);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(0.3,0.2,0.2);
    glScalef(2.5,1.15,.2); ///screen
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    //glColor3f(0,0,0);
    material(0,0,0);
    glTranslatef(1.38,-0.5,0);
    glScalef(.4,.6,.2);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0,0,0);
    material(0,0,0);
    glTranslatef(0.8,-.6,1);
    glRotatef(-90,1,0,0);
    glScalef(1.5,1.5,.2);
    drawcube();
    glPopMatrix();
}
void PC()
{
    glPushMatrix();
    //glColor3f(0.184, 0.310, 0.310);
    material(0.184, 0.310, 0.310);
    glTranslatef(4,-.6,0);
    glScalef(1,2,1);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0,0,0);
    material(0,0,0);
    glTranslatef(4.1,1,.95);
    glScalef(.2,.1,.1);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0,0,0);
    material(0,0,0);
    glTranslatef(4.4,1,.95);
    glScalef(.2,.1,.1);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0,0,0);
    material(0,0,0);
    glTranslatef(4.8,1.05,.95);
    glutSolidSphere(.1,50,50);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0,0,0);
    material(0,0,0);
    glTranslatef(4.1,.6,0.96);
    glScalef(.8,.2,.1);
    drawcube();
    glPopMatrix();

}
void chair()
{
    glPushMatrix();
    //glColor3f(0.753, 0.753, 0.753);
    material(0.753, 0.753, 0.753);
    glScalef(1.5,1,.3); //upperportion
    drawcube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.184, 0.310, 0.310);
    material(0.184, 0.310, 0.310);
    glTranslatef(.6,-1,0);
    glScalef(.3,1,.3);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.184, 0.310, 0.310);
    material(0.184, 0.310, 0.310);
    glTranslatef(-.1,-0.95,0); //handle1
    glRotatef(30,1,0,0);
    glScalef(.1,.8,.2);
    drawcube();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-.16,-0.3,.4);
    glScalef(.3,.2,1);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,-0.95,0); //handle2
    glRotatef(30,1,0,0);
    glScalef(.1,.8,.2);
    drawcube();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.4,-0.3,.4);
    glScalef(.3,.2,1);
    drawcube();
    glPopMatrix();


    glPushMatrix();
    //glColor3f(0.412, 0.412, 0.412);
    material(0.412, 0.412, 0.412);
    glTranslatef(-0.2,-1,0); //seat
    glScalef(2,.1,2);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.184, 0.310, 0.310);
    material(0.184, 0.310, 0.310);
    glTranslatef(-.1,-2.5,0); //leg left
    glScalef(.2,1.5,.2);
    drawcube();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-.1,-2.5,1.5);
    glScalef(.2,1.5,.2);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,-2.5,0);       //leg right
    glScalef(.2,1.5,.2);
    drawcube();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5,-2.5,1.5);
    glScalef(.2,1.5,.2);
    drawcube();
    glPopMatrix();


}
void table()
{

    glPushMatrix();
    //glColor3f(0.863, 0.863, 0.863);
    material(0.863, 0.863, 0.863);
    glScalef(6,.3,4.5); //base
    drawcube();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.275, 0.510, 0.706);
    material(0.275, 0.510, 0.706);
    glTranslatef(0,.2,-.1); //upper part
    glScalef(6,2,1);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3,-2,0); //leg left
    glScalef(.3,2,.3);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3,-2,2.5);
    glScalef(.3,2,.3);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.5,-2,0); //leg right
    glScalef(.3,2,.3);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.5,-2,2.5);
    glScalef(.3,2,.3);
    drawcube();
    glPopMatrix();
}

void dustbin()
{
    ///cylinder
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[29]);
    glEnable(GL_TEXTURE_2D);
    //glTranslatef(0,-4,2);
    glRotatef(270,1,0,0);
    //glColor3f(0.467, 0.533, 0.600);
    //glColor3f(1, 1, 1);
    material(1, 1, 1);
    glScalef(.5,.5,.5);
    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluQuadricTexture(qobj, TRUE);
    gluCylinder(qobj, 0.8, 0.8, 3, 50, 50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.184, 0.310, 0.310);
    material(0.184, 0.310, 0.310);
    glTranslatef(0,1.6,0);
    glScalef(.5,.2,.5);
    glutSolidSphere(1,50,50);
    glPopMatrix();

}

void control_room()
{
    glPushMatrix();
    glScalef(.5,.5,.5);
    room();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[11]);        ///middle wall picture
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-5.5,0.5,-12);
    glScalef(6.5,7,0.1);
    //glRotatef(90,0,0,1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[13]);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-9.5,6,-11); ///side wall picture
    glScalef(3.2,5,0.1);
    glRotatef(-90,0,0,1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[27]);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-10.8,2.5,-4); ///rocket
    glScalef(1,5,2);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();




    glPushMatrix();
    //glColor3f(1,1,1);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[14]);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-9.1,7.5,-11); ///clk
    glScalef(2.5,1,0.1);
    glRotatef(-90,0,0,1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[12]);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(2,2,-10.5); ///side wall
    glScalef(3.5,4,0.1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

     glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[28]);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(5.5,3.5,-4); ///NASA
    glScalef(.5,2,2);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[15]); ///clk
    glEnable(GL_TEXTURE_2D);
    glTranslatef(2.2,7.5,-10.5);
    glScalef(2.5,1,0.1);
    glRotatef(-90,0,0,1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glScalef(.8,.8,.5);         ///desktop1
    glTranslatef(0,.5,-12);

    glPushMatrix();
    glScalef(1,1,.5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,-2,0);
    glScalef(1,1,.5);
    dustbin();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,.8,.8);
    glScalef(.8,.8,.8);
    PC();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,.8,1);
    glScalef(.8,.8,.5);
    monitor(24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.6,.8,1);
    glScalef(.8,.8,.5);
    monitor(24);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glScalef(.8,.8,.5);         ///desktop2
    glTranslatef(-11,.5,-12);

    glPushMatrix();
    glScalef(1,1,.5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,.8,.8);
    glScalef(.8,.8,.8);
    PC();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,.8,1);
    glScalef(.8,.8,.5);
    monitor(24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.6,.8,1);
    glScalef(.8,.8,.5);
    monitor(24);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glScalef(.7,.7,.5);         ///desktop3
    glTranslatef(0.5,.5,-7);

    glPushMatrix();
    glScalef(1,1,.5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,-2,-0.5); ///dustbin
    glScalef(1,1,.5);
    dustbin();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,.8,.8);
    glScalef(.8,.8,.8);
    PC();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,.8,1);
    glScalef(.8,.8,.5);
    monitor(24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.6,.8,1);
    glScalef(.8,.8,.5);
    monitor(24);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glScalef(.8,.8,.5);         ///desktop4
    glTranslatef(-11,.5,-7);

    glPushMatrix();
    glScalef(1,1,.5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,.8,.8);
    glScalef(.8,.8,.8);
    PC();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,.8,1);
    glScalef(.8,.8,.5);
    monitor(24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.6,.8,1);
    glScalef(.8,.8,.5);
    monitor(24);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glScalef(.8,.8,.5);         ///desktop5
    glTranslatef(0.5,.5,-3);

    glPushMatrix();
    glScalef(1,1,.5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,-2,1); ///dustbin
    glScalef(1,1,.5);
    dustbin();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,.8,.8);
    glScalef(.8,.8,.8);
    PC();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,.8,1);
    glScalef(.8,.8,.5);
    monitor(26);
    glPopMatrix();

     glPushMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[21]); ///keyboard
    glEnable(GL_TEXTURE_2D);
    glTranslatef(1.5,.5,2);
    glRotated(90,1,0,0);
    glScalef(1.5,.5,.1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.6,.8,1);
    glScalef(.8,.8,.5);
    monitor(25);
    glPopMatrix();
     glPushMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[21]); ///keyboard
    glEnable(GL_TEXTURE_2D);
    glTranslatef(3.8,.5,2);
    glRotated(90,1,0,0);
    glScalef(1.5,.5,.1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glScalef(.8,.8,.5);         ///desktop6
    glTranslatef(-11,.5,-3);

    glPushMatrix();
    glScalef(1,1,.5);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,.8,.8);
    glScalef(.8,.8,.8);
    PC();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,.8,1);
    glScalef(.8,.8,.5);
    monitor(22);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[21]); ///keyboard
    glEnable(GL_TEXTURE_2D);
    glTranslatef(4.4,0.4,2);
    glRotated(90,1,0,0);
    glScalef(1.5,.5,.1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.6,.8,1);
    glScalef(.8,.8,.5);
    monitor(23);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[21]); ///keyboard
    glEnable(GL_TEXTURE_2D);
    glTranslatef(1.6,0.4,2);
    glRotated(90,1,0,0);
    glScalef(1.5,.5,.1);
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopMatrix();




    glPushMatrix();
    glTranslatef(-7,.8,1);      ///chair row 3
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5,.8,1);
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.1,.8,1);
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.6,.8,1);
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,.8,-1);      ///chair row 2
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5,.8,-1);
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.1,.8,-1);
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.6,.8,-1);
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,.8,-4);      ///chair row 1
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5,.8,-4);
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.1,.8,-4);
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.6,.8,-4);
    glRotatef(180,0,1,0);
    glScalef(.6,.8,.5);
    chair();
    glPopMatrix();

}
