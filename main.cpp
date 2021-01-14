//*********************************************************************
//  Minicurso: Computacao Grafica usando OpenGL
//  Autor: Prof. Laurindo de Sousa Britto Neto
//*********************************************************************

/* Inclui os headers do OpenGL, GLU, e GLUT */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>

#include "glm.h"

#define ESC 27

static int eixo_x = 0, eixo_y=0;

GLMmodel * pmodel = NULL;

void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);

void drawModel(void) {

	if (!pmodel) {
		pmodel = glmReadOBJ("porsche.obj");
		if (!pmodel)
			exit(0);
		glmUnitize(pmodel);
		glmFacetNormals(pmodel);//normal do obejeto
		glmVertexNormals(pmodel, 90.0);
	}
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);


}

int main(int argc, char** argv){
    /* inicia o GLUT */
    glutInit(&argc,argv);

    /* inicia o display usando RGB e double-buffering */
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(700,512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Porsche");

    /* Funcao com alguns comandos para a inicializacao do OpenGL; */
    init ();

    /* define as funcões de callback */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

  return 0;
}

/* Funcao com alguns comandos para a inicializacao do OpenGL; */
void init(void){
   // selecionar cor de fundo (preto)
   glClearColor (0.2, 0.2, 0.2, 0.0);
   glEnable(GL_LIGHT0);                   // habilita luz 0
   glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
}

void reshape (int w, int h){
    /* muda para o modo GL_PROJECTION e reinicia a projecção */
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    /* define a zona da janela onde se vai desenhar */
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    /* Define a forma do "viewing volume" para termos               *
     * uma projecção de perspectiva (3D).                           *
     * gluPerpective(angulo,aspecto,ponto_proximo, ponto distante); */
    gluPerspective(60, (float)w/(float)h, 1.0, 20.0);
    gluLookAt(0.0,0.0,5.0, 	// posição da câmera (olho) 
			  0.0,0.0,0.0, 	// centro da cena
			  0.0,1.0,0.0); // direção de cima 
    /* muda para o modo GL_MODELVIEW (não pretendemos alterar a projecção
     * quando estivermos a desenhar a tela) */
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
		case 'x': // sentido anti-horário
			eixo_x = (eixo_x + 5) % 360;
			glutPostRedisplay();
		break;
		case 'X': // sentido horário
			eixo_x = (eixo_x - 5) % 360;
			glutPostRedisplay();
		break;
		case 'y': // sentido anti-horário
			eixo_y = (eixo_y + 5) % 360;
			glutPostRedisplay();
		break;
		case 'Y': // sentido horário
			eixo_y = (eixo_y - 5) % 360;
			glutPostRedisplay();
		break;
		case ESC:
			exit(0);
		break;
		default:
		break;
	}
}

void display(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o Buffer de Cores
    glPushMatrix();
       glRotatef ((GLfloat) eixo_x, 0.0, 1.0, 0.0);
       glRotatef ((GLfloat) eixo_y, 1.0, 0.0, 0.0);
       drawModel(); 
	glPopMatrix();

    /* Troca os buffers, mostrando o que acabou de ser desenhado */
    glutSwapBuffers();
}

