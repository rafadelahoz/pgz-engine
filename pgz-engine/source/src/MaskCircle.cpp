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

#include "MaskCircle.h"

// Constructora MaskCircle, llamamos a la constructora de Mask con los parametros adecuados
MaskCircle::MaskCircle(int x, int y, float r, string type, int xoffset, int yoffset):Mask(x, y, (int) (2*r), (int) (2*r), type, xoffset, yoffset){
	radius = r;
}

// Destructora por defecto
MaskCircle::~MaskCircle(){
}

vector<CollisionPair>* MaskCircle::collide(Mask* other){
	vector<CollisionPair>* collPairs = Mask::collide(other); // Llamamos al padre para comprobar colisi�n simple de las Masks
	if (collPairs == NULL)			// Comprobamos si hubo colisi�n
		return NULL;				// Si no hubo devolvemos NULL
	else {	// Hubo collisi�n, comprobamos si los elementos internos verdaderamente colisionan
		CollisionPair collPair;			// Preparamos un CollisionPair por si hay colisi�n
		collPair.a = type;
		collPair.b = other->type;

		int xcenter = x + xoffset + (int) radius;
		int ycenter = y + yoffset + (int) radius;

		//--- Colisi�n MaskCircle con MaskCircle ---//
		if (MaskCircle* maskC = dynamic_cast<MaskCircle *> (other)){	// Probamos hacer un cast a MaskCircle
			float collDistance = radius + maskC->radius;	        	// Distancia en la que collisionan las dos circunferencias
			// Centro de la otra m�scara
			int otherXcenter = maskC->x + maskC->xoffset + (int) maskC->radius;
			int otherYcenter = maskC->y + maskC->yoffset + (int) maskC->radius;
			float distance = getDistance(xcenter, otherXcenter, ycenter, otherYcenter);	// Distancia actual entre los las m�scaras
			if (distance < collDistance){		// Hay colisi�n
				collPairs->push_back(collPair);	// Introducimos el par de collisi�n en el vector de colisiones
			}
		}

		//--- Colisi�n MaskCircle con MaskBox ---//
		else if (MaskBox* maskB = dynamic_cast<MaskBox *> (other)){		// Probamos hacer un cast a MaskBox
			float distance = -1.f;	// Guardaremos aqu� la distancia del c�rculo a la esquina del MaskBox

            // Coordenadas desplazadas de la otra m�scara
            int otherEffectiveX = maskB->x + maskB->xoffset;
            int otherEffectiveY = maskB->y + maskB->yoffset;

			// Comprobamos casos en los que la MaskCircle NO est� ubicada perpendicular respecto a los lados de la MaskBox
			if ((xcenter) < (otherEffectiveX)){		// Parte izquierda
				if (ycenter < otherEffectiveY)						// Esquina arriba-izquierda
					distance = getDistance(xcenter, otherEffectiveX, ycenter, otherEffectiveY);
				else if (ycenter > otherEffectiveY + maskB->height)	// Esquina abajo-izquierda
					distance = getDistance(xcenter, otherEffectiveX, ycenter, otherEffectiveY + maskB->height);
			}
			else if (xcenter > otherEffectiveX + maskB->width){	// Parte derecha
				if (ycenter < otherEffectiveY)						// Esquina arriba-derecha
					distance = getDistance(xcenter, otherEffectiveX + maskB->width, ycenter, otherEffectiveY);
				else if (ycenter > otherEffectiveY + maskB->height)	// Esquina abajo-derecha
					distance = getDistance(xcenter, otherEffectiveX + maskB->width, ycenter, otherEffectiveY + maskB->height);
			}
			// Comprobamos si hubo cambio en distance, en cuyo caso tambien comprobamos la colisi�n
			if (distance >= 0 ){
				if (distance < radius) // Si la distancia a la esquina es menor que el radio colisionamos
					collPairs->push_back(collPair);	// Introducimos el par de collisi�n en el vector de colisiones
			}
			// Si no hubo cambio en distance quiere decir que no hemos entrado en ning�n if, por lo que estamos en los casos perpendiculares la m�scara rectangular.
			// La cicunferencia es perpendicular a los lados del MaskBox y por tanto se comporta como un cuadrado de lado 2*radius
			// La colisi�n con el cuadrado de lado 2*radio ya ha sido comprobada en el padre, luego simplemente devolveremos el par de colisi�n.
			else {

                // Preparamos el par con los tipos de la colision
                CollisionPair collPair;
                collPair.a = type;
                collPair.b = maskB->type;
                // Metemos el par en el vector
                collPairs->push_back(collPair);
			}
		}

		//--- Colisi�n MaskCircle con MaskList ---//
		else if (MaskList* maskL = dynamic_cast<MaskList *> (other)){		// Probamos hacer un cast a MaskList
			// Si es una MaskList delegamos el trabajo
			vector<CollisionPair> *auxCollPairs = maskL->collide(this);
			if (auxCollPairs != NULL){
				Mask::flipAll(auxCollPairs);	// Realizamos un flip a los resultados
				vector<CollisionPair>::iterator it;		// Creamos un iterador de CollisionPair
				it = collPairs->end();					// Lo colocamos al final de collPairs
				// A�adimos las colisiones que se hayan producido con MaskList
				collPairs->insert(it, auxCollPairs->begin(), auxCollPairs->end());
				delete auxCollPairs;		// Eliminamos el vector auxiliar
			}
		}

		//--- Colisi�n MaskCircle con SolidGrid ---//
		else if (SolidGrid* grid = dynamic_cast<SolidGrid *> (other)){		// Probamos hacer un cast a SolidGrid
			// Si es una MaskList delegamos el trabajo
			vector<CollisionPair> *auxCollPairs = maskL->collide(this);
			if (auxCollPairs != NULL){
				Mask::flipAll(auxCollPairs); // Realizamos un flip a los resultados
				vector<CollisionPair>::iterator it;		// Creamos un iterador de CollisionPair
				it = collPairs->end();					// Lo colocamos al final de collPairs
				// A�adimos las colisiones que se hayan producido con MaskList
				collPairs->insert(it, auxCollPairs->begin(), auxCollPairs->end());
				delete auxCollPairs;		// Eliminamos el vector auxiliar
			}
		}
	}
	return collPairs;	// Job done! devolvemos los resultados
}

// Distancia de un punto a otro
float MaskCircle::getDistance (int x1, int x2, int y1, int y2){
	return sqrt((float)((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}
/*
bool MaskCircle::checkBoxCollision(int bx, int by, int bwidth, int bheigth){
	int left1 = x;							// L�mite izquierdo circunferencia
    int left2 = bx;							// L�mite izquierdo rect�ngulo
    int right1 = x + width;					// L�mite derecho circunferencia
    int right2 = bx + bwidth;				// L�mite derecho rect�ngulo
    int top1 = y;							// L�mite superior circunferencia
    int top2 = by;							// L�mite superior rect�ngulo
    int bottom1 = y + height;				// L�mite inferior circunferencia
    int bottom2 = by + bheigth;				// L�mite inferior rect�ngulo

	// Vamos comprobando colisiones,
	// Si no hay colisi�n devolvemos NULL
    if (bottom1 < top2)	return false;		// Si la parte inferior de una NO collisiona con la superior de la otra
	if (top1 > bottom2) return false;		// Si la parte superior de una NO collisiona con la inferior de la otra
	if (right1 < left2) return false;		// Si la parte derecha de una NO collisiona con la izquierda de la otra
	if (left1 > right2) return false; 		// Si la parte izquierda de una NO collisiona con la derecha de la otra

	// Si las comprobaciones anteriores fallan entonces las m�scaras colisionan
	return true;
}
*/
