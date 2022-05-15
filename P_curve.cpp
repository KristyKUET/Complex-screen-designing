#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"

void star()
{

    glPushMatrix();
    glTranslatef(0,5,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(1.5,0,.5);
    glVertex3f(0,2,.5);
    glVertex3f(-1.5,0,.5);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,5,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-2,-2,.5);
    glVertex3f(-4,0,.5);
    glVertex3f(-2,0,.5);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,5,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(2,-2,.5);
    glVertex3f(4,0,.5);
    glVertex3f(2,0,.5);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.5,7,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(2,-2,.5);
    glVertex3f(0,-4,.5);
    glVertex3f(3,-4.5,.5);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5,7,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-2,-2,.5);
    glVertex3f(0,-4,.5);
    glVertex3f(-3,-4.5,.5);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.01,5.1,.5);
    glBegin(GL_POLYGON);
    glVertex2f(1.4,0);
    glVertex2f(-1.4,0);
    glVertex2f(0,-2);
    glEnd();
    glPopMatrix();

}

