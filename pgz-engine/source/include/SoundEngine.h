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

#ifndef __SOUNDENGINE_H__
#define __SOUNDENGINE_H__


#include "SFML/Audio.hpp"
#include <iostream>
#include <conio.h>

#include "Music.h"
#include "Sound.h"

#include "SoundManager.h"
#include "MusicManager.h"

#include "Logger.h"

class Sound;
class Music;
class MusicManager;
class SoundManager;

using namespace std;


//! Subsistema de sonido que facilita el trabajo con elementos de audio al programador.
/*!
	Es la parte principal en la reproducci�n de sonido, encapsulando la
	librer�a de audio subyaciente.

	Se encarga de trabajar con archivos de m�sica (representados en la clase Music) y
	archivos de sonido (clase Sound). S�lo se prodr� reproducir un archivo de m�sica al
	tiempo, mientras que varios archivos de sonido pueden estar siendo reproducidos
	al mismo tiempo.

	SoundEngine proporciona pues m�todos para manejar la reproducci�n y par�metros tanto
	elementos de sonido como de m�sica.

	\sa Sound
	\sa Music
*/
class SoundEngine
{
	friend class Sound;
	friend class Music;

	private:
		float systemSoundVolume; //Volumen global de sonidos del sistema
		float systemMusicVolume; //Volumen global de m�sica del sistema
		Logger* logger;
		Music* actPlayingMusic; //Almacena la m�sica que se est� reproduciendo en ese momento
		SoundManager* soundManager; //Puntero a SoundManager
		MusicManager* musicManager; //Puntero a MusicManager

		//! Carga el sonido de la ruta especificada.
		/*!
			Si el sonido ya ha sido cargado, SoundEngine se encargar� de devolver el
			mismo puntero con el que se carg�.
			\param path ruta donde se encuentra el sonido a cargar.
			\return Objeto que representa el archivo de sonido especificado.
		*/
		sf::Sound* loadSound(string path);

		//! Carga el archivo de m�sica de la ruta especificada.
		/*!
			Si la pista ya ha sido cargada, MusicEngine se encargar� de devolver el
			mismo puntero con el que se carg�.
			\param path ruta donde se encuentra el archivo de m�sica a cargar.
			\return Objeto que representa el archivo de m�rica especificado.
		*/
		sf::Music* loadMusic(string path);

	public:
		//! Construye el SoundEngine
		/*!
			Preparara las estructuras necesarias para la reproducci�n de sonidos,
			dejando a SoundEngine::init() la inicializaci�n
			de la clase y por tanto de la librer�a de sonido.
		*/
		SoundEngine();

		//! Destructora
		~SoundEngine();

		//! Inicializa los parametros de la clase y rellena las estructuras.
		/*!
			Inicializa el SoundEngine para que pueda realizar su funci�n.
		*/
		bool init();

	/*********************************************************************\
	*	M�todos comunes a todos los tipos de archivos de audio			  *
	\*********************************************************************/

		//! Establece el volumen global de la reproducci�n de sonidos.
		/*!
			Este m�todo modifica el valor del volumen global de sonidos, con el
			cu�l se reproducir�n todos los sonidos en los que no se especifique un
			volumen particular.
			\param soundVolume valor num�rico del nuevo volumen del sistema.
		*/
		void setSoundVolume(float soundVolume);

		//! Obtiene el volumen de sonidos del sistema.
		/*!
			\return Volumen actual de la reproducci�n por defecto de sonidos.
		*/
		float getSoundVolume();

		//! Establece el volumen global de la reproducci�n de pistas de m�sica.
		/*!
			Este m�todo modifica el valor del volumen global de la m�sica, con el
			cu�l se reproducir�n todos las pistas de m�sica en las que no se
			especifique un volumen particular.
			\param musicVolume valor num�rico del nuevo volumen del sistema.
		*/
		void setMusicVolume(float musicVolume);

		//! Obtiene el volumen de pistas de m�sica del sistema.
		/*!
			\return Volumen actual de la reproducci�n por defecto de m�sica.
		*/
		float getMusicVolume();

		//! Detiene todos los sonidos en reproducci�n actualmente.
		void stopAllSounds();

		//! Detiene la m�sica actual en reproducci�n.
		void stopAllMusic();

	/*********************************************************************\
	*	M�todos relacionados con la reproducci�n de sonidos				  *
	\*********************************************************************/

		//! Reproduce un sonido especificado en la ruta al volumen dado y con o sin repeticiones.
		/*!
			\param sound sonido a reproducir.
			\param volume Volumen con el que se quiere reproducir. Si no se especifica,
			el sonido se reproducir� con el volumen global de sonidos del sistema.
			\param loop Flag que indica si el sonido se volver� a reproducir tras finalizar o no.
		*/
		void playSound(Sound* sound, float volume = -1.0, bool loop = false);

		//! Elimina un sonido.
		/*!
			Se eliminar� el sonido ya sea solo el link o todo (incluido el buffer) porque 
			nadie m�s lo est� usando.
			\param path ruta del sonido que se quiere eliminar
		*/
		bool deleteSound(string path);

		//! Cambia gradualmente el volumen de un sonido.
		/*!
			\param sound Sonido sobre el que se aplicar� el cambio de volumen.
			\param volume Volumen al que se quiere llegar de manera gradual.
			\param time Tiempo que se tardar� en llegar al volumen especificado.
		*/
		void fadeSound(Sound* sound, float volume, int time);

		//! Indica si se esta reproduciendo un sonido.
		/*!
			\param sound Sonido a comprobar.
			\return Valor booleano indicando si el sonido se est� reproduciendo o no.
		*/
		bool isSoundPlaying(Sound* sound); // true si se est� reproduci�ndose ese sonido

		//! Detiene la reproducci�n de un sonido.
		/*!
			El sonido especificado ser� reproducido. Si se estaba reproduciendo varias
			veces al mismo tiempo, todas las instancias ser�n detenidas.
			\param sound Sonido que se va a detener.
		*/
		void stopSound(Sound* sound);

	/*********************************************************************\
	*	M�todos relacionados con la reproducci�n de pistas de m�sica		  *
	\*********************************************************************/

		//! Reproduce una pista de m�sica especificada en la ruta.
		/*!
			La pista especificada comenzar� su repreoducci�n. Si ya se estaba reproduciendo,
			comenzar� de nuevo desde el principio. Si se encontraba pausada, se reanudar� su reproducci�n.
			Podr� reproducirse con o sin repeticiones.
			\param music Pista de m�sica a reproducir.
			\param volume Volumen con el que se quiere reproducir. Si no se especifica,
			la pista se reproducir� con el volumen global de m�sica del sistema.
			\param loop Flag que indica si la pista de m�ics se volver� a reproducir tras finalizar o no.
		*/
		void playMusic(Music* music, float volume = -1.0, bool loop = true, bool withStop = false);

		//! Elimina una musica.
		/*!
			Se eliminar� la musica ya sea solo el link (virtual) o toda la instancia porque 
			nadie m�s lo est� usando.
			\param path ruta del sonido que se quiere eliminar
		*/
		bool deleteMusic(string path);

		//! Cambia gradualmente el volumen de la pista de m�sica sonando actualmente.
		/*!
			\param volume Volumen al que se quiere llegar de manera gradual.
			\param time Tiempo que se tardar� en llegar al volumen especificado.
		*/
		void fadeMusic(float volume, int time);

		//! Indica si se esta reproduciendo una pista de m�sica.
		/*!
			\param music M�sica a comprobar.
			\return Valor booleano indicando si la pista de m�sica se est� reproduciendo o no.
		*/
		bool isMusicPlaying(Music* music);

		//! Informa si la pista de m�sica actual est� pausada.
		/*!
			\param music M�sica a comprobar.
			\return Valor booleano indicando si la pista de m�sica est� pausada o no.
		*/
		bool isMusicPaused(Music* music);

		//! Pausa la reproducci�n de la pista de m�sica actual.
		void pauseMusic();

		//! Contin�a la reproducci�n de la pista de m�sica actual, si �sta ha sido previamente pausada.
		void resumeMusic();

		//! Detiene la reproducci�n de la pista de m�sica actual.
		void stopMusic();

		//! Cambia el modo de repetici�n de la pista de m�sica actual.
		/*!
			\param loop Valor booleano cuya valor indica si la pista de m�sica actual debe ser reproducida
			tras finalizar (true) o no (false).
		*/
		void setLoop(bool loop);
};

#endif
