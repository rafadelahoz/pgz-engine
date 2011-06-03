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
#ifndef __SOLIDGRID_H__
#define __SOLIDGRID_H__

#include <algorithm>
#include <vector>
#include <stdlib.h>
#include "MaskList.h"
#include "MaskBox.h"
#include "MaskCircle.h"
#include <iostream>
#include <stdio.h>

using namespace std;

//! Miembro de la familia de Mask para comprobar colisiones contra una matriz de elementos
/*!
	Efect�a comprobaciones de colisi�n contra una matriz de elementos de varios tipos.
	Cada celda de la matriz contiene uno de estos elementos,
	que ser�n rectangulares y del mismo tama�o para un mismo SolidGrid,
	aunque dicho tama�o es configurable.

	Los elementos llevan asociado un tipo, que en realidad es un entero positivo.
	- tipo = 0 - la celda est� libre
	- tipo > 0 - la celda contiene un elemento del tipo correspondiente

	Al comprobar colisiones, devuelve el tipo de cada una de las celdas no vac�as
	que partipen en la colisi�n como una cadena de caract�res "solidN",
	siendo N el tipo de la celda.

	Proporciona un m�todo de carga a partir de archivo b�sico, as� como
	la capacidad de proporcionar una matriz de tipos de colisi�n obtenida
	de forma externa.
*/
class SolidGrid : public Mask
{
	private:
		int** grid;		// Matriz que guarda los valores de los s�lidos de la m�scara
		int tileW;		// Ancho de cada posici�n de la matriz
		int tileH;		// Alto de cada posici�n de la matriz
		int colNumber;	// N�mero de columnas de la matriz
		int rowNumber; 	// N�mero de filas de la matriz

		void resizeGrid(int nCol, int nRow); // Redimensiona la matriz
		void deleteGrid();

    public:
		//! Construye el SolidGrid con los par�metros indicados.
		/*!
			Necesitar� las coordenadas de inicio ya que es una m�scara global, sin embargo,
			no tendr� tipo de colisi�n (cada tile tiene su tipo de colisi�n predeterminado).
			\param x Coordenada x de la m�scara global.
			\param y Coordenada y de la m�scara global.
			\param grid Matriz de tipos (NULL para no inicializarla)
			\param tileW Ancho de las celdas de la matriz
			\param tileH Alto de las celdas de la matriz
			\param columns N�mero de columnas de la matriz
			\param rows N�mero de filas de la matriz
		*/
        SolidGrid(int x, int y, int** grid, int tileW, int tileH, int columns, int rows);

		//! Construye el SolidGrid carg�ndolo de archivo por el m�todo por defecto
		/*!
			El m�todo de carga requiere que el archivo que se le pasa tenga el siguiente formato:

			COLUMNAS FILAS
			ANCHOCELDA ALTOCELDA
			TIPO1 TIPO2 TIPO3 ... TIPON

			Siendo N = COLUMNAS x FILAS

			\param fname Nombre de archivo a cargar
		*/
        SolidGrid(string fname);

		//! Destructora
        virtual ~SolidGrid();

		//! Obtiene el ancho de las celdas de la matriz
		/*! \return Ancho de las celdas de la matriz en px */
        int getTileW();

		//! Establece el ancho de las celdas de la matriz
		/*! \param tileW Nuevo ancho de las celdas de la matriz en px */
        void setTileW(int tileW);

		//! Obtiene el alto de las celdas de la matriz
		/*! \return Alto de las celdas de la matriz en px */
        int getTileH();

		//! Establece el alto de las celdas de la matriz
		/*! \param tileH Nuevo alto de las celdas de la matriz en px */
        void setTileH(int tileH);

		//! Obtiene el n�mero de columnas de la matriz
		/*! \return N�mero de columnas de la matriz */
        int getColNumber();

		//! Establece el n�mero de columnas de la matriz
		/*! \param nCol Nuevo n�mero de columnas de la matriz */
        void setColNumber(int nCol);

		//! Obtiene el n�mero de filas de la matriz
		/*! \return N�mero de filas de la matriz*/
        int getRowNumber();

		//! Establece el n�mero de filas de la matriz
		/*! \param nRow Nuevo n�mero de filas de la matriz */
        void setRowNumber(int nRow);

		//! Obtiene la coordenada X de la posici�n de la esquina superior izquiera del SolidGrid.
		/*! \return coordenada X de la posici�n de la esquina superior izquiera del SolidGrid */
		int getXPos();

		//! Establece la coordenada X de la posici�n de la esquina superior izquiera del SolidGrid.
		/*! \param xp Nueva coordenada X de la posici�n de la esquina superior izquiera del SolidGrid */
		void setXPos(int xp);

		//! Obtiene la coordenada Y de la posici�n de la esquina superior izquiera del SolidGrid.
		/*! \return coordenada Y de la posici�n de la esquina superior izquiera del SolidGrid */
		int getYPos();

		//! Establece la coordenada Y de la posici�n de la esquina superior izquiera del SolidGrid.
		/*! \param yp Nueva coordenada Y de la posici�n de la esquina superior izquiera del SolidGrid */
		void setYPos(int yp);

		//! Obtiene el tipo de una celda de la matriz
		/*!
			La celda se especifica por su columna y su fila
			\param i Columna de la celda
			\param j Fila de la celda
			\return Tipo de la celda (i, j)
		*/
        int getCell(int i, int j);

		//! Establece el tipo de una celda de la matriz
		/*!
			La celda se especifica por su columna y su fila
			\param i Columna de la celda
			\param j Fila de la celda
			\param type Tipo que tendr� la celda
		*/
        void setCell(int i, int j, int type);

		//! Obtiene el tipo de la celda de la matriz que contiene el punto (x, y)
		/*!
			La posici�n del punto se especifica en px.
			\param x Coordenada x del punto
			\param y Coordenada y del punto
			\return Tipo de la celda que contiene a (x, y)
		*/
        int getPosition(int x, int y);

		//! Establece el tipo de la celda de la matriz que contiene el punto (x, y)
		/*!
			La posici�n del punto se especifica en px.
			\param x Coordenada x del punto
			\param y Coordenada y del punto
			\param type Tipo que tendr� la celda
		*/
        void setPosition(int x, int y, int type);

		//! Obtiene la columna de la celda que contiene el punto de coordenada horizontal x
		/*!
			El valor de x se especifica en px
			\param x Coordenada horizontal del punto a comprobar
			\return Columna de la celda que contiene a x.
		*/
        int getColumn(int x);

		//! Obtiene la fila de la celda que contiene el punto de coordenada vertical y
		/*!
			El valor de y se especifica en px
			\param y Coordenada vertical del punto a comprobar
			\return Columna de la celda que contiene a y.
		*/
        int getRow(int y);

		//! Comprueba si una m�scara colisiona con el SolidGrid
		/*!
			Devuelve los tantos pares de colisi�n como celdas
			no vac�as colisionen con la m�scara indicada.
			\param other M�scara contra la que se comprueba la colisi�n.
			\return Lista de pares de colisi�n entre las 2 m�scaras.
			\sa CollisionPair
		*/
		vector<CollisionPair>* collide(Mask* other);

		//! Comprueba si la posici�n indicada est� dentro del SolidGrid
		/*!
			\param x Coordenada horizontal
			\param y Coordenada vertical
			\return true si la posici�n indicada est� dentro del SolidGrid
		*/
		bool isPointInbounds(int x, int y);

		//! Comprueba si la m�scara indicada est� dentro del SolidGrid
		/*!
			\param mask M�scara a comprobar
			\return true si la m�scara indicada est� dentro del SolidGrid
		*/
		bool isMaskInbounds(Mask* mask);
};

#endif // SOLIDGRID_H
