#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "Botao.h"
#include "gl_canvas2d.h"
#include "diagramaDegraus.h"

using namespace std;

int screenWidth = 1200, screenHeight = 600;
int mouseX, mouseY;
Diagrama diagrama;
Botao botao[7];

void render()
{

   diagrama.modify_Dimensoes( screenWidth, screenHeight );

   botao[6].modifica_Label( diagrama.binario );
   botao[6].modifica_Binario( screenWidth, screenHeight );

   for( int i = 0; i < 6; i++ )
   {
      botao[i].modifica_Botao(screenWidth, screenHeight, i);
      botao[i].Render(screenWidth);
   }

   CV::color(0.25,0.25,0.25);
   CV::rectFill((screenWidth/6)-1, 0, (screenWidth/6)+1, screenHeight);

   for(int i = 0; i < 6; i++)
   {
      if(diagrama.desenha[i])
      {
         diagrama.config_Entrada( screenWidth, screenHeight, i );
         if(diagrama.binario.size() > 0)
            diagrama.Render( screenWidth, screenHeight );
      }
   }
   CV::translate(0,0);
   botao[6].Render(screenWidth);
}
void keyboard(int key)
{
   if( key == 48 )
      diagrama.binario.push_back(0);
   if( key == 49 ){
      diagrama.binario.push_back(1);
   }
   if( key == 8 && (diagrama.binario.size() > 0))
      diagrama.binario.pop_back();
}
void keyboardUp(int key)
{

}
void mouse(int button, int state, int wheel, int direction, int x, int y)
{

   mouseX = x;
   mouseY = y;

   if(state == 0)
   {
      for(int i = 0; i < 6; i++ )
      {
         if( botao[i].Colidiu(mouseX, mouseY) )
            diagrama.select_Desenho( i, 6 );
      }
   }
}
int main(void)
{

   botao[0] = Botao(screenWidth/24, 1*screenHeight/7, screenWidth/10, screenHeight/20,     "NRZ-I");
   botao[1] = Botao(screenWidth/24, 2*screenHeight/7, screenWidth/10, screenHeight/20,     "NRZ-L");
   botao[2] = Botao(screenWidth/24, 3*screenHeight/7, screenWidth/10, screenHeight/20,       "AMI");
   botao[3] = Botao(screenWidth/24, 4*screenHeight/7, screenWidth/10, screenHeight/20,   "Pseudo.");
   botao[4] = Botao(screenWidth/24, 5*screenHeight/7, screenWidth/10, screenHeight/20,"Manchester");
   botao[5] = Botao(screenWidth/24, 6*screenHeight/7, screenWidth/10, screenHeight/20,"Manch. Dif.");

   botao[6] = Botao(screenWidth/6, 0, screenWidth, screenHeight/20);

   diagrama = Diagrama( screenHeight, screenWidth );
   CV::init(&screenWidth, &screenHeight, "T1 Comunicação de dados Leonardo Piekala e Anthony Silva");
   CV::run();
}
