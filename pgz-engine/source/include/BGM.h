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
#ifndef __BGM_H__
#define __BGM_H__

#include <string>
#include "SoundEngine.h"
#include "Music.h"

using namespace std;


//! M�sica de fondo de la capa superior del subsistema de audio
/*!
	Envuelve una Music, facilitando su manejo y reproducci�n
	
	Proporciona m�todos para reproducir y controlar bgms
	de forma sencilla y eficaz.
	
	\sa Music
*/
class Bgm
{
	private:
		//! Atributo que encapsula a Music
		Music* music;
		SoundEngine* soundEngine;
		float volume;
		bool playing;
		bool paused;
		bool loop;

	public:
		
		//! Construye la Bgm carg�ndola de un archivo
		/*!
			\param fname Nombre de archivo a cargar
			\param sndEngine Puntero al SoundEngine del sistema
		*/
		Bgm(string fname, SoundEngine *sndEngine);
		
		//! Destruye la Bgm, liberando el archivo cargado
		~Bgm();

		//! Reproduce la Bgm con el volumen indicado
		/*!
			\param volume Volumen de reproducci�n (-1 para volumen por defecto)
		*/
		void play(float volume = -1.f);

		//! Finaliza la reproducci�n
		void stop();

		//! Pausa la reproducci�n en curso
		void pause();

		//! Reanuda la reproducci�n pausada
		void resume();

		//! Informa si la Bgm est� reproduci�ndose actualmente
		bool isPlaying();

		//! Indica si la reproducci�n se repite
		/*!
			\param loop Activa o desactiva la reproducci�n repetida
		*/
		void setLoop(bool loop);

		//! Establece el volumen de reproducci�n
		/*!
			\param volume Volumen de reproducci�n
		*/
		void setVolume (float volume);

		//! Cambia el volumen de reproducci�n vari�ndolo lentamente
		/*!
			\param volume Volumen de reproducci�n
			\param time Tiempo de transici�n
		*/
		void fade (float volume, int time);
};

#endif