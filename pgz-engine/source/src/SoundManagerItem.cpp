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

#include "SoundManagerItem.h"


//! Construye el SoundManagerItem para el m�sic sound
/*!
	Inicializa el contador de enlaces a 0.
	\param sound Sonido encapsulado
*/
SoundManagerItem::SoundManagerItem(sf::SoundBuffer* soundBuf){
	// Enlazamos el sonido
	this->soundBuffer = soundBuf;
	// contador de enlaces a 1
	links = 1;
}

//! A�ade un nuevo enlace al sonido
void SoundManagerItem::link(){
	this->links++; // incrementamos el n� de enlaces
}
	
//! Elimina un enlace al sonido
/*!
	\return true si el sonido puede borrarse porque el n�mero de enlaces es 0.
*/
bool SoundManagerItem::unlink(){
	this->links--; // decrementamos el n�mero de enlaces
	return (this->links == 0); // Si el n� de enlaces es 0 se puede eliminar
} // true si debe borrarse
	
//! Obtiene el sonido encapsulado
/*!
	\return Puntero a el sonido encapsulado
*/
sf::SoundBuffer* SoundManagerItem::getSoundBuffer(){
	return this->soundBuffer;
}
	
//! Devuelve el n�mero de enlaces actual al sonido
/*!
	\return N�mero de enlaces actuales
*/
int SoundManagerItem::getLinks(){
	return this->links;
};