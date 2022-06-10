#ifndef DIAGRAMADEGRAUS_H_INCLUDED
#define DIAGRAMADEGRAUS_H_INCLUDED

#include <vector>
#include "gl_canvas2d.h"
#include "Vector2.h"

class Diagrama
{

   public:std::vector<int> binario;
   int largura;
   int altura;
   public: std::vector<bool> desenha;
   public: std::vector<Vector2> coords;

public:

   Diagrama();

   Diagrama( int screenHeight, int screenWidth );

   void Render( int screenWidth, int screenHeight );

   void modify_Dimensoes( int screenWidth, int screenHeight );

   void config_Entrada( int screenWidth, int screenHeight, int index );

   void desenha_NRZI( int screenWidth, int screenHeight );

   void desenha_NRZL( int screenWidth, int screenHeight );

   void desenha_AMI(int screenWidth, int screenHeight);

   void desenha_Pseudo( int screenWidth, int screenHeight);

   void desenha_Manchester( int screenWidth , int screenHeight );

   void desenha_ManchesterDif( int screenWidth , int screenHeight );

   void select_Desenho( int index, int tamanho );
};

#endif // DIAGRAMADEGRAUS_H_INCLUDED
