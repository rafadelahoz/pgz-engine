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
#ifndef __MASK_LIST_H__
#define __MASK_LIST_H__

#include "Mask.h"
#include "MaskBox.h"
#include "MaskCircle.h"

//! Lista de m�scaras de colisi�n
/*!
	Se trata de un hijo de Mask, representando la m�scara de colisi�n
	de un objeto en varias partes.
*/

class MaskList : public Mask
{
	public:

	//! Lista de las m�scaras de colisi�n que contiene.
	vector<Mask*>* masks;

	//! Construye la m�scara a partir de una lista de m�scaras y las dimensiones globales.
	/*!
		\param x Coordenada x origen de la m�scara.
		\param y Coordenada y origen de la m�scara.
		\param width Ancho global de la m�scara.
		\param height Alto global de la m�scara.
		\param type Tipo de colisi�n de la m�scara.
		\param m Lista de m�scaras ya creada.
		\param xoffset Coordenada x de desplazamiento la m�scara.
		\param yoffset Coordenada y de desplazamiento la m�scara.
	*/
	MaskList(int x, int y, int width, int height, string type, vector<Mask*>* m, int xoffset = 0, int yoffset = 0);

	//! Destructora
	virtual ~MaskList();

	//! Comprueba si la m�scara dada colisiona con otra m�scara.
	/*!
		Hace uso del m�todo de la clase padre para comprobar si cada
		una de las m�scaras de su lista colisiona con la m�scara other.

		\param other M�scara con la que se comprueba la colisi�n.
		\return Lista de pares de colisi�n entre las 2 m�scaras.
	*/
	vector<CollisionPair>* collide(Mask* other);

    void setXY(int x, int y);

	private:

	//! M�todo privado para concatenar vectores de CollisionPair
	/*!
		\param fromVect vector del cual sacamos datos.
		\param toVect vector al que concatenamos datos.
	*/
	void concatVect(vector<CollisionPair> *fromVect, vector<CollisionPair> *toVect);
};

#endif
