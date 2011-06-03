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
#ifndef __MASK_H__
#define __MASK_H__

#include <string>
#include <vector>

using namespace std;

//! Par de colisi�n que representa los tipos de colisi�n que se han producido.
struct CollisionPair {
	//! Tipo de colisi�n de la m�scara A en la colisi�n.
	string a;
	//! Tipo de colisi�n de la m�scara B en la colisi�n.
	string b;
};


//! M�scara de colisi�n abstracta capaz de comprobar colisiones con otras m�scaras.
/*!
	Una m�scara es un elemento abstracto que representa la estructura f�sica
	de una entidad y su delimitaci�n a la hora de calcular su contacto con otras entidades.

	Contiene adem�s una etiqueta editable que definir� qu� tipo de colisi�n posee
	la m�scara, �til a la hora de calcular colisiones. Esta etiqueta ser� una cadena
	de caracteres y deber� ser constru�da por el programador.
*/
class Mask
{
	public:

	//! Valor de la anchura de las dimensiones globales de la m�scara de colisi�n.
	/*!
		Toda m�scara hija estar� envuelta en una m�scara abstracta global.
		Debe ser colocada cuidadosamente, ya que dos m�scaras no colisionan
		si sus m�scaras globales no est�n en contacto, aunque sus
		correspondientes m�scaras internas s� colisionen.
	*/
	int width;

	//! Valor de la altura de las dimensiones globales de la m�scara de colisi�n.
	/*!
		Toda m�scara hija estar� envuelta en una m�scara abstracta global.
		Debe ser colocada cuidadosamente, ya que dos m�scaras no colisionan
		si sus m�scaras globales no est�n en contacto, aunque sus
		correspondientes m�scaras internas s� colisionen.
	*/
	int height;

	//! Coordenada x de posici�n origen de la m�scara.
	int x;
	//! Coordenada y de posici�n origen de la m�scara.
	int y;

	//! Coordenada x de desplazamiento de la m�scara con respecto a la posici�n original.
	int xoffset;
	//! Coordenada y de desplazamiento de la m�scara con respecto a la posici�n original.
	int yoffset;

	//! Tipo de colisi�n de la m�scara.
	string type;

	//! Construye la m�scara a partir de una anchura y altura globales dadas.
	/*!
		\param x Coordenada x origen de la m�scara.
		\param y Coordenada y origen de la m�scara.
		\param width Ancho de la m�scara.
		\param height Alto de la m�scara.
		\param type Tipo de colisi�n de la m�scara.
		\param xoffset Coordenada x de desplazamiento la m�scara.
		\param yoffset Coordenada y de desplazamiento la m�scara.
	*/
	Mask(int x, int y, int width, int height, string type, int xoffset = 0, int yoffset = 0);

	//! Destructora
	virtual ~Mask();

	//! Comprueba si la m�scara dada colisiona con otra m�scara.
	/*!
		\param other M�scara con la que se comprueba la colisi�n.
		\return Lista de pares de colisi�n entre las 2 m�scaras.
	*/
	virtual vector<CollisionPair>* collide(Mask* other);

    //! Actualiza la posici�n de la m�scara con las nuevas coordenadas, teniendo en cuenta el desplazamiento
	/*!
		\param x Coordenada x destino.
		\param y Coordenada y destino.
	*/
	virtual void setXY(int x, int y);

	//! Devuelve la posici�n x de la m�scara teniendo en cuenta el desplazamiento.
	/*!
		\return Coordenada x real de la m�scara.
	*/
	int posX();

	//! Devuelve la posici�n y de la m�scara teniendo en cuenta el desplazamiento.
	/*!
		\return Coordenada y real de la m�scara.
	*/
	int posY();

	//! Invierte todos los pares de collisi�n contenidos en un vector de CollisionPair.
	/*!
		\param vect Vector de CollisionPair cuyos componentes queremos invertir.
	*/
	vector<CollisionPair>* flipAll (vector<CollisionPair>* vect);
};

#endif
