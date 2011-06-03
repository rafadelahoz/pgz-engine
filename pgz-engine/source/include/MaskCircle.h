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
#ifndef __MASK_CIRCLE_H__
#define __MASK_CIRCLE_H__

#include "Mask.h"
#include "MaskBox.h"
#include "MaskList.h"
#include "SolidGrid.h"
#include <math.h>

//! M�scara de colisi�n �nica de forma circular.
/*!
	Se trata de un hijo de Mask, representando la m�scara de colisi�n
	de un objeto de forma circular.
*/

class MaskCircle : public Mask
{
	public:

	//! Radio de la m�scara circular.
	float radius;

	//! Construye la m�scara a partir de la posici�n y radio del c�rculo y las dimensiones globales.
	/*!
        La posici�n (x,y) y desplazamiento (xoffset,yoffset) de la m�scara servir�n para representar
        la posici�n de la esquina superior izquierda del cuadrado que envuelve al c�rculo.
		\param x Coordenada x origen de la m�scara.
		\param y Coordenada y origen de la m�scara.
		\param r Radio de la m�scara circular.
        \param type Tipo de colisi�n de la m�scara.
		\param xoffset Coordenada x de desplazamiento la m�scara.
		\param yoffset Coordenada y de desplazamiento la m�scara.
	*/
	MaskCircle(int x, int y, float r, string type, int xoffset = 0, int yoffset = 0);

	//! Destructora
	virtual ~MaskCircle();

	//! Comprueba si la m�scara circular dada colisiona con otra m�scara.
	/*!
		\param other M�scara con la que se comprueba la colisi�n.
		\return Lista de pares de colisi�n entre las 2 m�scaras.
	*/
	vector<CollisionPair>* collide(Mask* other);

	private:

	//! Calcula la distancia de un punto a otro punto.
	/*!
		\param x1 Cordenada x del primer punto.
		\param x2 Cordenada x del segundo punto.
		\param y1 Cordenada y del primer punto.
		\param y2 Cordenada y del segundo punto.
		\return Float con el valor de la distancia entre los puntos.
	*/
	float getDistance (int x1, int x2, int y1, int y2);

	//! Calcula si la circunferencia colisiona con los lados perpendiculares de un rect�ngulo.
	/*!
		\param bx Cordenada x del rect�ngulo.
		\param by Cordenada y del rect�ngulo.
		\param bwidth Ancho del rect�ngulo.
		\param bheigth Alto del rect�ngulo.
		\return bool true si hubo colisi�n, false si no hubo.
	*/
	bool checkBoxCollision(int bx, int by, int bwidth, int bheigth);
};

#endif
