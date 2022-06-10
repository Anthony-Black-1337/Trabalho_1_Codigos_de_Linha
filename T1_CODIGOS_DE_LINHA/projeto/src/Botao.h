#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "gl_canvas2d.h"
#include <vector>

class Botao
{
  float altura, largura, x, y;
  char label[100];
  float r, g, b;

public:

    Botao()
    {
    }
    Botao(float _x, float _y, float _larg, float _alt, char *_label)
    {
         altura  = _alt;
         largura = _larg;
         x = _x;
         y = _y;
         strcpy(label, _label);
         r = 0.50;
         g = 0.50;
         b = 0.50;
  }
    void modifica_Label( std::vector<int> binario)
    {
          char palavra[binario.size()+1];
          for( int i = 0; i < binario.size(); i++)
          {
             if( binario[i] == 0)
             {
                palavra[i] = '0';
                palavra[i+1] = '\0';
             }
             else
             {
                palavra[i] = '1';
                palavra[i+1] = '\0';
             }
          }
          strcpy(label, palavra);
    }
    Botao(float _x, float _y, float _larg, float _alt)
    {
         altura  = _alt;
         largura = _larg;
         x = _x;
         y = _y;
         r = 0.75;
         g = 0.75;
         b = 0.75;
  }
    void modifica_Binario  ( int screenWidth, int screenHeight )
    {
       x = screenWidth/6;
       y = 0;
       largura = screenWidth - (screenWidth/6);
       altura = screenHeight/20;
       r = 0.25;
       g = 0.25;
       b = 0.25;
    }
    void Render(int screenWidth)
    {
          CV::color(r, g, b);
          CV::rectFill(x, y, x + largura, y + altura);
          CV::color(1, 1, 1);
          if(strlen(label) > 0)
             CV::text( ( x + (largura/2) - ( strlen(label)* 5 ) ) , (y + altura/2) - 4, label); //escreve o label do botao mais ou menos ao centro.
  }
    bool Colidiu(int mx, int my)
    {
          if( mx >= x && mx <= (x + largura) && my >= y && my <= (y + altura) )
          {
              return true;
          }
          return false;
  }
    void modifica_Botao( int screenWidth, int screenHeight, int i )
    {
      x       = screenWidth/24;
      y       = (i+1)*screenHeight/7;
      altura  = screenHeight/20;
      largura = screenWidth/10;
    }
};

#endif
