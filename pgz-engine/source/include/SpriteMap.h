/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//	  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once
#ifndef __SPRITEMAP_H__
#define __SPRITEMAP_H__

#include <map>
#include <utility>

#include "Anim2D.h"
#include "GfxEngine.h"
#include "Image.h"
#include "Graphic.h"
#include "Logger.h"


using namespace std;


// Funci�n invocada por alguna clase de forma autom�tica al cumplirse una condici�n
//typedef void (*CallBack) ();


//! Miembro de la familia de Graphic que representa un elemento grafico animado.
/*!
	Almacena un archivo de imagen que contiene los frames
	que forman las animaciones del elemento ordenadas en forma
	de matriz. 
	Se indica el tama�o de un frame y mediante Anim2D se crean las animaciones
	indicando los frames que las componen.
	
	\sa Anim2D
*/
class SpriteMap : public Graphic {
	private:
		//! Atributos de la clase SpriteMap.
		/*!
			\param list contiene la tabla de animaciones del spriteMap.
			\param currentAnim contiene la animaci�n en ejecuci�n.
			\param img contiene la imagen cargada.
			\param cbFunc puntero a funci�n CallBack().
			\param gfxEngine contiene la informaci�n de gestion de los graficos.
			\param logger instancia del log de trabajo.
			\param currentframesPerStep n�mero de steps que se ejecutar� cada frame en la animaci�n actual.
			\param currentLoop indica si la animaci�n actual ha de repetirse o no.
			\param frame frame actual en la animaci�n en ejecuci�n (de 0 a frameCount-1).
			\param lastFrame sprite en el que termina la �ltima animaci�n ejecutada (de 0 a nCol*nRow-1).
			\param step pasos del juego ejecutados desde la �ltima actualizaci�n de la animaci�n en curso.
			\param nCol n�mero de columnas del spriteMap.
			\param nRow n�mero de filas del spriteMap.
			\param finished indica si la animaci�n actual ha terminado.
		*/

		map<string,Anim2D*>* list;
		Anim2D* currentAnim; 
		Image* img; 
		// Indica si la imagen se ha cargado en el SpriteMap y debe borrarse
		bool loaded;
		//CallBack cbFunc;  
		GfxEngine* gfxEngine;

		Logger* logger;
		
		int currentFramesPerStep;
		bool currentLoop;
		int frame; 
		int lastFrame;  
		int step; 
		int nCol;
		int nRow;
		bool finished;
				
		//! borra el spriteMap
		void deleteAnimMap();
		
		//!Convierte un entero en una coordenada bidimensional (x,y)
		/*!
			\param num entero a convertir en coordenada.
			\return la coordenada bidimensional en un tipo pair
		*/
		pair<int,int> numToXY(int num);

		//!Convierte una coordenada bidimensional (x,y) en un entero
		/*!
			\param x coordenada x a convertir en  entero.
			\param y coordenada y a convertir en  entero.
			\return el entero equivalente a la coordenada de entrada
		*/
		int XYToNum(int x, int y);
		
		//!Indica si existe un nuevo frame o se trata del �ltimo de la animaci�n
		/*!
			\return true si hay m�s sprites detras del actual, falso si es el �ltimo
		*/
		bool nextFrame();
		
	public:

		//! Construye un SpriteMap con los par�metros indicados
		/*!
			\param fname Nombre de archivo de imagen a cargar
			\param nCol N�mero de columnas de la imagen
			\param nRow N�mero de filas de la imagen
			\param gfxEngine Puntero al subsistema grafico
			
			\sa GfxEngine
		*/
		SpriteMap(string fname, int nCol, int nRow, GfxEngine* gfxEngine = NULL);

		//! Destruye el SpriteMap, liberando sus animaciones
		~SpriteMap();
		
		//! A�ade una animaci�n a partir de un vector de frames
		/*!
			\param name Nombre de la animaci�n
			\param frameList Vector con los frames de la animaci�n
			\param framesPerStep Frames de juego a que dura cada paso de la animaci�n
			\param loop Indica si la animaci�n ha de repetirse o no.
		*/
		void addAnim(string name, vector<int>* frameList, int framesPerStep, bool loop);

		//! A�ade una animaci�n a a partir de una array de frames
		/*!
			\param name Nombre de la animaci�n
			\param frameList Array con los frames de la animaci�n
			\param numFrames N�mero de frames de la animaci�n
			\param framesPerStep Frames de juego a que dura cada paso de la animaci�n
			\param loop Indica si la animaci�n ha de repetirse o no.
		*/
		void addAnim(string name, int* frameList, int numFrames, int framesPerStep, bool loop);

		//! A�ade una animaci�n a partir de una Anim2D ya construida
		/*!
			\param a Animaci�n a a�adir
			\sa Anim2D
		*/
		void addAnim(Anim2D* a);
		
		//! Cambia la imagen que utiliza el SpriteMap
		/*!
			\param img Nueva imagen para el SpriteMap
			\sa Image
		*/
		void setImage(Image* img);

		//! Obtiene la imagen del SpriteMap
		/*!
			\return Imagen img del spriteMap
			\sa Image
		*/
		Image* getImage();
		
		//! Reproduce una animaci�n
		/*!
			\param name nombre de la animaci�n a reproducir
			\param restart indica, si la animaci�n es la animaci�n en curso, si debe volver a empezar o no.
		*/
		void playAnim(string name, bool restart = false);

		//! Reproduce una animaci�n a la velocidad indicada
		/*!
			\param name Nombre de la animaci�n a reproducir
			\param framesPerStep Pasos de juego que dura cada frame
			\param loop Indica si la animaci�n ha de repetirse o no
			\param restart indica, si la animaci�n es la animaci�n en curso, si debe volver a empezar o no.
		*/
		void playAnim(string name, int framesPerStep, bool loop, bool restart = false);

		//! Reproduce una animaci�n indicando la velocidad como un porcentaje de la velocidad por defecto
		/*!
			\param name Nombre de la animaci�n a reproducir
			\param frameRate Porcentaje [0..1] respecto a la velocidad original
			\param loop Indica si la animaci�n ha de repetirse o no
			\param restart indica, si la animaci�n es la animaci�n en curso, si debe volver a empezar o no.
		*/
		void playAnim(string name, float frameRate, bool loop, bool restart = false);

		//! Detiene la animaci�n en curso.
		void stopAnim();
		
		//! Actualiza el estado de la animaci�n
		/*!
			Debe llamarse cada paso del juego
		*/
		void update();

		//! Renderiza el frame actual del SpriteMap en la posici�n indicada
		/*!
			\param x Coordenada x 
			\param y Coordenada y
		*/
		void render(int x, int y);

		//! Obtiene el nombre de la animaci�n actual
		/*!
			\return Nombre de la animaci�n que se est� reproduciendo ("none" si no la hay)
		*/
		string getCurrentAnim();

		//! Indica si la animaci�n actual ha finalizado
		/*!
			\return True si ha finalizado, false en caso contrario
		*/
		bool animFinished();

		//! Obtiene el frame actual
		int getCurrentFrame();

		//! Obtiene el ancho de un frame
		int getWidth();
		int getHeight();
};

#endif