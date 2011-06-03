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

#ifndef __MAP_H__
#define __MAP_H__

#include "TileMap.h"
#include "SolidGrid.h"
#include "GfxEngine.h"

using namespace std;

//! Representa un mapa basado en tiles, tanto su parte g�fica como su parte de colisiones.
/*!
	Encapsula un TileMap para la parte gr�fica y un SolidGrid para la parte de colisiones.
	
	Proporciona m�todos para modificar las propiedades de las clases que encapsula y
	m�todos de carga, as� como uno de actualizaci�n y otro de renderizado, todos virtuales.
	
	Para una mayor comodidad, se puede derivar una clase de Map, sobreescribir los
	m�todos que interesen (por ejemplo el de carga) y pas�rsela al GameState pertinente
	para que la mantenga de forma autom�tica.
	
	La forma com�n de trabajar con Map es:
	- Instanciar el Map con el tama�o de tile deseado
	- Indicar al Map el tileset que debe utilizar mediante Map::setTileset().
	- Cargar el mapa:
		- Con el m�todo por defecto
		- De forma externa al Map, pas�ndoselo luego mediante Map::setSolids() y Map::setTiles()
	- Mantener actualizado el mapa con Map::update()
	- Renderizar el mapa cuando corresponda con Map::render();
	
	\sa GameState
	\sa TileMap
	\sa SolidGrid
*/

class Map
{
	protected:
		//! Atributos de la clase SpriteMap.
		/*!
			\param tileMap aspecto gr�fico de un mapa de tiles
			\param solidGrid matriz de s�lidos de un mapa de tiles
		*/
		TileMap* tileMap;
		SolidGrid* solidGrid;
	
    public:

		//! Construye el Map con el ancho y alto de tile indicados
		/*!
			\param tileW Ancho de los tiles del mapa
			\param tileH Alto de los tiles del mapa
			\param gfxEngine Puntero al GfxEngine del sistema
		*/
		Map(int tileW, int tileH, GfxEngine* gfxEngine);

		//! Destruye el Map
        virtual ~Map();

		//! Carga el la parte de colisiones del mapa con el m�todo por defecto
		/*!
			\param fname Nombre del archivo a cargar
		*/
		virtual void loadSolids(string fname);
		
		//! Devuelve el contenido de la parte de colisiones del Map.
		virtual SolidGrid* getSolids();

		//! Establece el contenido de la parte de colisiones del Map.
		/*!
			\param solids Array con los tipos de las celdas
		*/
		virtual void setSolids(int x, int y, int** solids, int columns, int rows);
		
		//! Establece el tileset que utilizar� el mapa
		/*!
			\param fname Nombre de archivo del tileset
		*/
		virtual void setTileset(string fname);

		//! Establece el tileset que utilizar� el mapa
		/*!
			\param tset Referencia al objeto tileset
		*/
		virtual void setTileset(TileSet* tset);
		
		//! Carga el la parte de gr�ficos del mapa con el m�todo por defecto
		/*!
			\param fname Nombre del archivo a cargar
		*/
		virtual void loadTiles(string fname);
		
		//! Establece el contenido de la parte de gr�ficos del Map.
		/*!
			\param tiles Array con los tiles
		*/
		virtual void setTiles(int** tiles, int columns, int rows);

		//! Obtiene de la imagen del mapa ya constru�do.
		/*!
			\return la imagen del mapa
		*/
		Image* getMapImage();

		//! Establece de uno de los tiles del mapa
		/*!
			\param x contiene la coordenada x del tile que deseamos cambiar
			\param y contiene la coordenada y del tile que queremos cambiar
			\param tile contiene el tile del tileSet asignado al mapa que vamos a colocar en la posici�n indicada del mapa
		*/
		void setTile(int x, int y, int tile);

		//! Carga el mapa completo (gr�ficos y colisiones) con el m�todo por defecto
		/*!
			\param fname Nombre del archivo a cargar
		*/
		virtual void loadMap(string fname);

		//! Actualiza la imagen y el estado de los s�lidos del Map
		virtual void update();
		
		//! Muestra el mapa en la posici�n indicada
		/*!
			\param x Posici�n horizontal
			\param y Posici�n vertical
		*/
        virtual void render(int x, int y);

		//! Obtiene el tileset actual del mapa
		/*! \return Tileset actual */
        virtual TileSet* getTileset();
};

#endif // MAP_H
