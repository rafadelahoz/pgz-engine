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
#ifndef __MUSICMANAGERITEM_H__
#define __MUSICMANAGERITEM_H__

#include "Music.h"

class Music;

//! Elemento b�sico del MusicManager
/*!
	Dentro de un mismo juego distintos elementos pueden compartir
	un mismo archivo de audio musical. Este elemento
	no deber�a cargarse varias veces en memoria,
	sino compartirse entre todos con el consecuente ahorro.
	
	De esta tarea se encarga MusicManager, que mantiene la lista
	de sonidos cargados en memoria de forma transparente al programador.

	MusicManagerItem es el elemento b�sico de esta lista.
	Relaciona un elemento de la clase Music (m�sica) con el n�mero de elementos que la utilizan
	para poder liberarla cuando no sea necesaria, asegurando que no
	se elimina mientras alguien la est� utilizando.

	\sa MusicManager
	\sa Music
*/
class MusicManagerItem
{

private:
	//! N�mero de enlaces actuales a la m�sica encapsulada
	unsigned int links;
	//! M�sica (Music encapsulada)
	sf::Music* music;

public:
	//! Construye el MusicManagerItem para la m�sic music
	/*!
		Inicializa el contador de enlaces a 0.
		\param music M�sica encapsulada
	*/
	MusicManagerItem(sf::Music* music);

	//! A�ade un nuevo enlace a la m�sica
	void link();
	
	//! Elimina un enlace a la m�sica
	/*!
		\return true si la m�sica puede borrarse porque el n�mero de enlaces es 0.
	*/
	bool unlink(); // true si debe borrarse
	
	//! Obtiene la m�sica encapsulada
	/*!
		\return Puntero a la m�sica encapsulada
	*/
	sf::Music* getMusic();
	
	//! Devuelve el n�mero de enlaces actual a la m�sica
	/*!
		\return N�mero de enlaces actuales
	*/
	int getLinks();
};

#endif