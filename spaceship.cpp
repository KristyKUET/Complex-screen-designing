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
extern GLfloat anika;
void material(float clr1, float clr2,float clr3,bool em= false);


void spaceship()
{

    ///cylinder1
    glPushMatrix();
    glTranslatef(-.4,0,0.5);
    glRotated(90,1,0,0);

    glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[31]);
    glEnable(GL_TEXTURE_2D);
    glRotatef(270,1,0,0);
    glScalef(.5,.5,.5);
    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluQuadricTexture(qobj, TRUE);
    gluCylinder(qobj, 1, 1, 4, 50, 50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[32]);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(0,2,0);
    glRotatef(260,1,0,0);
    glutSolidCone(.5,.8,50,50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPopMatrix();

    ///cylinder2
    glPushMatrix();
    glTranslatef(2.3,0,0.5);
    glRotated(90,1,0,0);

    glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[31]);
    glEnable(GL_TEXTURE_2D);
    glRotatef(270,1,0,0);
    glScalef(.5,.5,.5);
    gluCylinder(qobj, 1, 1, 4, 50, 50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1);
    glBindTexture(GL_TEXTURE_2D, ID[32]);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(0,2,0);
    glRotatef(260,1,0,0);
    glutSolidCone(.5,.8,50,50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPopMatrix();


    ///cube
    //glColor3f(1,1,1);
    material(1,1,1);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ID[30]);
    glEnable(GL_TEXTURE_2D);
    glScalef(2,2,.2); //back
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.2,0,0);
    glScalef(.2,2,4); //side1
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,0,0);
    glScalef(.2,2,4); //side2
    drawcube();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,3.8);
    glScalef(2,2,.2); //front
    drawcube();
    glPopMatrix();


    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0,2.1,0);
    glRotatef(90,1,0,0);
    glScalef(2,4,.2); //up
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0,.1,0);
    glRotatef(90,1,0,0);
    glScalef(2,4,.2); //down
    drawcube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1,1,1);
    material(1,1,1);
    //glBindTexture(GL_TEXTURE_2D, ID[32]);
    //glEnable(GL_TEXTURE_2D);
    glTranslatef(1,1,4);
    glRotatef(360,1,0,0);
    glutSolidCone(1.5,1.5,50,50);
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.5,0,0);
    glRotatef(45,0,1,0);
        glPushMatrix();
        //glColor3f(1,0,0);
        material(1,1,1);      ///light cone
        glTranslatef(1,1,0);
        glRotatef(360,1,0,0);
        glutSolidCone(.5,1,50,50);
        glPopMatrix();

        glPushMatrix();
        //glColor3f(1,0,1);
        material(1,1,1);
        glTranslatef(1,1,0);
        //glRotatef(360,1,0,0);
        glutSolidSphere(.4,50,50);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,0,-1.5);
    glRotatef(-45,0,1,0);
        glPushMatrix();
        //glColor3f(1,0,0);       ///light cone
        material(1,1,1);
        glTranslatef(1,1,0);
        glRotatef(360,1,0,0);
        glutSolidCone(.5,1,50,50);
        glPopMatrix();

        glPushMatrix();
        //glColor3f(1,0,1);
        material(1,1,1);
        glTranslatef(1,1,0);
        //glRotatef(360,1,0,0);
        glutSolidSphere(.4,50,50);
        glPopMatrix();
    glPopMatrix();



}

