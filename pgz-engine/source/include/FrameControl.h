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
#ifndef __FRAMECONTROL_H__
#define __FRAMECONTROL_H__

// Clase "Window" de SFML en la que se apoya FrameControl
#include "SFML\Window.hpp"
#include <algorithm>

#include "Logger.h"

using namespace std;

//! Controla los frames por segundo que dibuja el juego.
/*! Permite imponer un l�mite a los FPS, 
	obtener la media de FPS a la que se est� ejecutando el juego
	y obtener la duraci�n del �ltimo frame.
*/
class FrameControl
{
	private:

		// Instancia de Logger
		Logger* logger;

		// L�mite de fps (0 = sin l�mite)
		int fpsLimit;
		// Media de fps
		int fps;
		// Puntero a la ventana que gestiona
		sf::Window* window;
		// Tiempos de los �ltimos 10 frames del juego
		float frame_time[10];
		// Posici�n de la duraci�n del �ltimo frame a�adido
		int last_frame;
		// Cu�ntos frames han sido ejecutados (hasta 10)
		int n_frames;

	public:
		//! Instancia el controlador de frames.
		/*!
			\param fpsLimit L�mite de los FPS (0 para deshabilitarlo).
		*/
		FrameControl(int fpsLimit = 0);
		//! Destructora por defecto
		~FrameControl();
		
		//! Inicializa el control de FPS. Debe llamarse despu�s de la constructora.
		bool init(sf::Window* window, bool reboot = false);
		
		//! Establece el l�mite de los FPS.
		/*!
			\param fpsLimit L�mite de los FPS (0 para deshabilitarlo).
		*/
		void setFPSLimit(int fpsLimit = 0);
		
		//! Obtiene el l�mite establecido para los FPS (No los FPS medios reales)
		/*!
			\return L�mite establecido para los FPS.
		*/
		int getFPSLimit();
		
		//! Obtiene la media de FPS a la que se est� ejecutando el juego
		/*
			\return Media de FPS.
		*/
		int getFramesPerSecond();
		
		//! Obtiene la duraci�n del �ltimo frame.
		/*
			Calculada a partir de la diferencia de tiempos de los dos �ltimos frames.
			\return Duraci�n del �ltimo frame.
		*/
		int getDelay();

		// Obtiene el valor de la duraci�n del frame en cada paso del juego
		// y actualiza el valor de la media de fps en consecuencia
		// Debe llamarse en cada paso del juego
		void update();
};

#endif