#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "diagramaDegraus.h"

Diagrama::Diagrama()
{
}
Diagrama::Diagrama(int screenHeight, int screenWidth )
{

   for(int i = 0; i < 6; i++ )
   {
      desenha.push_back(false);
   }

   largura = (screenWidth - (screenWidth/6)) /( binario.size() + 2 );
   altura  = screenHeight/(binario.size()+2);
}
void Diagrama::Render( int screenWidth, int screenHeight )
{

   CV::translate(0, 0);
   for(int i = 0; i < binario.size()+1; i++)
   {
      CV::color(1,0,0);
      CV::line(((i+1) * largura) + screenWidth/6, 0, ((i+1) * largura) + screenWidth/6, screenHeight);
   }
   CV::rectFill(screenWidth/6, (screenHeight/2 + 1), screenWidth, (screenHeight/2 - 1));

   CV::translate(screenWidth/6, screenHeight/2);

   for(int i = 0; i < coords.size()-1; i++)
   {
      printf("\n%.2f %.2f", coords[i].x, coords[i].y);

      CV::color(0,0,0);
      CV::rectFill( ( (coords[i].x   * largura ) - 1), ( (coords[i].y   * altura ) - 1),
                    ( (coords[i+1].x * largura ) + 1), ( (coords[i+1].y * altura ) + 1) );
   }

   printf("\n\n");
   CV::translate(0,0);
   CV::color(1,0,0);
   CV::circleFill(screenWidth/6,screenHeight/2,5,25);
   CV::circleFill(screenWidth-3,screenHeight/2,5,25);

}
void Diagrama::modify_Dimensoes( int screenWidth, int screenHeight )
{
   largura = (screenWidth - (screenWidth/6)) /( binario.size() + 2 );
   altura  = screenHeight/(binario.size()+2);
}
void Diagrama::config_Entrada( int screenWidth, int screenHeight, int index )
{
   switch(index)
   {
      case 0: desenha_NRZI         ( screenWidth, screenHeight );
         break;
      case 1: desenha_NRZL         ( screenWidth, screenHeight );
         break;
      case 2: desenha_AMI          ( screenWidth, screenHeight );
         break;
      case 3: desenha_Pseudo       ( screenWidth, screenHeight );
         break;
      case 4: desenha_Manchester   ( screenWidth, screenHeight );
         break;
      case 5: desenha_ManchesterDif( screenWidth, screenHeight );
         break;
   }
}
void Diagrama::desenha_NRZI( int screenWidth, int screenHeight )
{

   int y = 1;
   int i = 0;
   coords.clear();

   for( i = 0; i < binario.size(); i++)
   {

      if(i == 0)
      {
         coords.push_back(Vector2(0,0));
         coords.push_back(Vector2(i+1,0));
         coords.push_back(Vector2(i+1, y));
         if(binario.size() == 1)
            coords.push_back(Vector2(i+2, y));
      }
      else{
         if(binario[i] != 0)
         {
            coords.push_back(Vector2(i+1, y));
            coords.push_back(Vector2(i+1, y*-1));
            y = y * -1;
         }
         else
            coords.push_back(Vector2(i+1, y));
      }
   }
   if(binario.size() > 0)
   {
      coords.push_back(Vector2(i+1, y));
      coords.push_back(Vector2(i+1, 0));
      coords.push_back(Vector2(screenWidth,0));
   }
}
void Diagrama::desenha_NRZL( int screenWidth, int screenHeight )
{
   int y;
   coords.clear();
   if(binario[0])
      y = -1;
   else
      y = 1;
   int i = 0;

   for( i = 0; i < binario.size(); i++)
   {

      if(i == 0)
      {
         coords.push_back(Vector2(0,0));
         coords.push_back(Vector2(i+1,0));
         coords.push_back(Vector2(i+1, y));
         if(binario.size() == 1)
            coords.push_back(Vector2(i+2, y));
      }
      else
      {
         if(binario[i] != binario[i-1])
         {
            coords.push_back(Vector2(i+1, y));
            coords.push_back(Vector2(i+1, y*-1));
            y = y * -1;
         }
         else
            coords.push_back(Vector2(i+1, y));
      }
   }
   if(binario.size() > 0)
   {
      coords.push_back(Vector2(i+1, y));
      coords.push_back(Vector2(i+1, 0));
      coords.push_back(Vector2(screenWidth,0));
   }
}
void Diagrama::desenha_AMI(int screenWidth, int screenHeight)
{

   int y = -1;
   int i = 0;
   coords.clear();

   for( i = 0; i < binario.size(); i++)
   {

      if(i == 0)
      {
         coords.push_back(Vector2(0,0));
         if(binario[0])
         {
            coords.push_back(Vector2(i+1,0));
            coords.push_back(Vector2(i+1,y));
         }
         else
         {
            coords.push_back(Vector2(i+1,0));
         }
      }

      else
      {
         switch(binario[i])
         {
            case 0:
               if(binario[i] != binario[i-1])
               {
                  coords.push_back(Vector2(i+1,y));
                  coords.push_back(Vector2(i+1,0));
               }
               else
               {
                  coords.push_back(Vector2(i+1,0));
               }
               break;
            case 1:
               if(binario[i] != binario[i-1])
               {
                  coords.push_back(Vector2(i+1,0));
                  y = y * -1;
                  coords.push_back(Vector2(i+1,y));
               }
               else
               {
                  coords.push_back(Vector2(i+1,y));
                  y = y * -1;
                  coords.push_back(Vector2(i+1,y));
               }
               break;
         }
      }
   }
   if(binario.size() > 0)
   {
      if(binario[i-1])
         coords.push_back(Vector2(i+1, y));
      coords.push_back(Vector2(i+1, 0));
      coords.push_back(Vector2(screenWidth,0));
   }

}
void Diagrama::desenha_Pseudo( int screenWidth, int screenHeight)
{

   int y = 1;
   int i = 0;
   coords.clear();

   for( i = 0; i < binario.size(); i++)
   {

      if(i == 0)
      {
         coords.push_back(Vector2(0,0));
         if(!binario[0]){
            coords.push_back(Vector2(i+1,0));
            coords.push_back(Vector2(i+1,y));
         }
         else
         {
            coords.push_back(Vector2(i+1,0));
         }
      }

      else{
         switch(binario[i])
         {
            case 0:
               if(binario[i] != binario[i-1])
               {
                  coords.push_back(Vector2(i+1,0));
                  y = y * -1;
                  coords.push_back(Vector2(i+1,y));
               }
               else
               {
                  coords.push_back(Vector2(i+1,y));
                  y = y * -1;
                  coords.push_back(Vector2(i+1,y));
               }
               break;
            case 1:
               if(binario[i] != binario[i-1])
               {
                  coords.push_back(Vector2(i+1,y));
                  coords.push_back(Vector2(i+1,0));
               }
               else
               {
                  coords.push_back(Vector2(i+1,0));
               }
               break;
         }
      }
   }
   if(binario.size() > 0)
   {
      if(!binario[i-1])
         coords.push_back(Vector2(i+1, y));
      coords.push_back(Vector2(i+1, 0));
      coords.push_back(Vector2(screenWidth,0));
   }

}
void Diagrama::desenha_Manchester( int screenWidth , int screenHeight )
{

   int y = 0;
   coords.clear();
   int i = 0;

   if(binario[0])
      y = -1;
   else
      y = 1;

   for( i = 0 ; i < binario.size() ; i++)
   {

      if(i == 0)
      {
         coords.push_back(Vector2(0,0));
         coords.push_back(Vector2(i+1,0));
         coords.push_back(Vector2(i+1, y));
      }
      else
      {
         if(binario[i] == binario[i-1])
         {
            y = y * -1;
            coords.push_back(Vector2(i+1, y));
         }
      }
         coords.push_back(Vector2(i+1.5, y));
         y = y * -1;
         coords.push_back(Vector2(i+1.5, y));
         coords.push_back(Vector2(i+2, y));
   }

   if(binario.size() > 0)
   {
      coords.push_back(Vector2(i+1, 0));
      coords.push_back(Vector2(screenWidth,0));
   }
}
void Diagrama::desenha_ManchesterDif( int screenWidth , int screenHeight )
{

   int y = 0;
   coords.clear();
   int i = 0;

   if(!binario[0])
      y = -1;
   else
      y = 1;

   for( i = 0 ; i < binario.size() ; i++)
   {

      if(i == 0)
      {
         coords.push_back(Vector2(0,0));
         coords.push_back(Vector2(i+1,0));
         coords.push_back(Vector2(i+1, y));
      }
      else{
         if(!binario[i])
         {
            y = y * -1;
            coords.push_back(Vector2(i+1, y));
         }
      }
         coords.push_back(Vector2(i+1.5, y));
         y = y * -1;
         coords.push_back(Vector2(i+1.5, y));
         coords.push_back(Vector2(i+2, y));
   }

   if(binario.size() > 0)
   {
      coords.push_back(Vector2(i+1, 0));
      coords.push_back(Vector2(screenWidth,0));
   }

}
void Diagrama::select_Desenho( int index, int tamanho )
{
   for (int i = 0; i < tamanho; i++)
      desenha[i] = false;
   desenha[index] = true;
}

