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

#ifndef _MUSICMANGER_H_
#define _MUSICMANGER_H_

#include <map>
#include "MusicManagerItem.h"
#include "Music.h"

class Music;

class MusicManagerItem;

//! Mantiene la colecci�n de m�sicas en memoria.
/*!
	Dentro de un mismo juego distintos elementos pueden compartir
	un mismo archivo de audio musical. Este elemento
	no deber�a cargarse varias veces en memoria,
	sino compartirse entre todos con el consecuente ahorro.
	
	De esta tarea se encarga MusicManager, que mantiene la lista
	de sonidos cargados en memoria de forma transparente al programador.

	Se asegura de que las m�sicas cargadas desde disco a memoria
	se mantienen sin duplicados y que se eliminan las que no se 
	necesiten, mediante un contador de enlaces asociado a cada
	m�sica.
	
	Proporciona funcionalidad para comprobar si una m�sica ya
	est� cargada, obtenerla en tal caso o a�adir una nueva entrada
	en otro caso.
*/
class MusicManager {
	private:
		//! Mapa de m�sicas enlazadas por nombre de archivo fuente
		map<std::string,MusicManagerItem*>* list;

	public:
		//! Instancia el MusicManager
		MusicManager();
		
		//! Destruye el MusicManager
		~MusicManager();
		
		//! Comprueba si la m�sica obtenida a partir del archivo fname ya est� cargada.
		/*!
			Este m�todo tiene un coste computacional reducido (el mapa se indexa por nombre de archivo)
			\param fname Nombre de archivo fuente
			\return true si la m�sica ya ha sido cargada
		*/
		bool isLoaded(std::string fname);
		
		//! Obtiene una m�sica almacenada en el manager
		/*!
			\param fname Nombre de archivo fuente solicitado
			\return Puntero a la m�sica cargada en memoria
		*/
		sf::Music* getMusic(std::string fname);
		
		//! A�ade una nueva m�sica a la lista
		/*!
			\param fname Nombre de archivo fuente
			\param music Puntero a la m�sica
			\return false si la m�sica o el fname ya estaban en memoria
		*/
		bool setMusic(std::string fname, sf::Music* music);
		
		//! Elimina una entrada de la lista
		/*!
			Elimina la entrada de la lista y tambi�n la m�sica de memoria
			\param fname Nombre de archivo fuente
			\return true si se ha eliminado correctamente
		*/
		bool remove(std::string fname);
};

#endif // _SURFACEMANAGER_H_