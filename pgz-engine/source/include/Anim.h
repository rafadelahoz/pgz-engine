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

#ifndef __ANIM_H__
#define __ANIM_H__

#include <string>
using namespace std;

//! Anim es el elemento de animaci�n de mayor alto nivel.
/*!
	De �l derivar�n los distintos tipos de animaciones con que pueda trabajar el programador.
*/
class Anim {
	protected:
		//! Atributo de la clase anim.
		/*!
			\param _name nombre de la animaci�n.
		*/
		string name;
	public:

		//! Construye una animaci�n indicando su nombre
		/*! \param name Nombre de la animaci�n */
		Anim(string name){};
		//! Destruye la animaci�n
		virtual ~Anim(){};
		
		//! Obtiene el nombre de la animaci�n
		/*!
			\return Nombre de la animaci�n
		*/
		virtual string getName(){return  NULL;};
};

#endif