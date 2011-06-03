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

#include "SpriteMap.h"

//Constructora parametrizada
SpriteMap::SpriteMap(string fname, int nCol, int nRow, GfxEngine* gfxEngine) : Graphic()
{
	//Creo un mapa para las animaciones
	list = new map<string,Anim2D*>();
	//Inicio la animaci�n actual a NULL
	currentAnim = NULL;
	//Creo una imagen a partir de la ruta que me han dado
	img = new Image(fname,gfxEngine);
	// Se indica que la hemos cargado nosotros
	loaded = true;
	//Apunto al subsistema grafico
	this->gfxEngine = gfxEngine;
	//Instancio el logger por si ya existia
	logger = Logger::Instance();
	//Inicializo los parametros genericos
	currentFramesPerStep = 0;
	currentLoop = false;
	frame = 0;
	lastFrame = 0;
	step = 1;
	finished = false;
	//Pongo el numero de filas y columnas al valor correspondiente
	this->nCol = nCol;
	this->nRow = nRow;
}

//Borra el mapa de animaciones con cuidadin
void SpriteMap::deleteAnimMap()
{
	//Creamos un iterador para el map y lo inicializamos
	map< string, Anim2D* >::iterator it = list->begin();
	Anim2D* tmp;
	
	//mientras no hallamos recorrido todas las animaciones
	while (it != list->end())
	{
		//Referenciamos en el temporal la posible animaci�n a borrar
		tmp = it->second;
		it++;
		//Si hay animaci�n asociada en esa posici�n del map, la borramos
		if (tmp)
			delete tmp;
	}
	//Borro el mapa en si
	delete list;
	list = NULL;
}

//Destructora
SpriteMap::~SpriteMap() 
{
	//borro las animaciones
	deleteAnimMap();
	//Si tiene imagen y la he cargado yo la borro
	if (loaded && img != NULL)
		delete img;

	//Logger::DestroyInstance();
}

//A�ade una animaci�n a partir de la direcci�n de la misma
void SpriteMap::addAnim(string name, vector<int>* frameList, int framesPerStep, bool loop)
{
	//Creo la animaci�n y la a�ado a la lista de animaciones
	Anim2D* temp = new Anim2D(name, frameList, framesPerStep, loop);
	list->insert(make_pair(name, temp));
}


//A�ade una animaci�n a partir de una lista de frames
void SpriteMap::addAnim(string name, int* frameList, int numFrames, int framesPerStep, bool loop)
{
	//Creo un vector para guardar la lista de frames
	vector<int>* temp = new vector<int>(numFrames);
	
	//A�ado los frames a la lista
	for (int i = 0; i < numFrames; i++)
		(*temp)[i] = frameList[i];
		
	//Creo la animaci�n y la a�ado a la lista de animaciones
	Anim2D* aux = new Anim2D(name, temp, framesPerStep, loop);
	list->insert(make_pair(name, aux));
}

//A�ade una animaci�n ya creada
void SpriteMap::addAnim(Anim2D* a)
{
	list->insert(make_pair(a->getName(), a));
}

//Avanza al siguiente frame si es necesario si no incrementa el contador de steps transcurridos 
//mostrando este frame
bool SpriteMap::nextFrame() 
{
	//Si se ha alcanzado el n�mero de pasos del juego que hacen falta para cambiar de frame, 
	//reinicio el numero de pasos de juego y aviso de que toca cambiar de frame
	if (step >= currentFramesPerStep) 
	{
		step = 1;
		return true;
	}
	//Si no, aumento el numero de pasos de juego desde el �ltimo cambio de frame, y aviso de que 
	//a�n no toca cambiar
	else 
	{
		step++;
		return false;
	}
}


void SpriteMap::playAnim(string name, bool restart)
{
	// Creamos un iterador para map
	map<string, Anim2D*>::iterator it;
	//Pido que busque la animaci�n solicitada
	it = list->find(name);
	if (it == list->end())
		//Si no est� hemos acabado
		return;
	else
	{
		//Si no hay animaci�n actual o no es la que me piden 
		if (!(currentAnim && (currentAnim->getName() == name)))
		{
			//Copio la nueva en currentAnim
			currentAnim = list->find(name)->second;
			//Copio sus caracteristicas a unas para la animaci�n actual para que, si se desean 
			//cambiar, no se modifiquen los parametros de la animaci�n original
			currentFramesPerStep = currentAnim->getFramesPerStep();
			currentLoop = currentAnim->getLoop();
			//Reseteo los parametros de la animaci�n en curso porque la reproducci�n es nueva
			frame = 0; 
			step = 0;
			finished = false;
		}
		// Si es la actual y quieren que la reseteemos
		else if (restart)
		{
			//Reseteo los parametros de la animaci�n en curso porque la reproducci�n es nueva
			frame = 0; 
			step = 0;
			finished = false;
		}
	}
}
	

//Reporoduce una animaci�n cambiando sus parametros por otros
void SpriteMap::playAnim(string name, int framesPerStep, bool loop, bool restart)
{
	//Llamo a playAnim(name) para que haga la parte de reproducir una nueva animaci�n
	playAnim(name, restart);
	
	//Actualizo los parametros de la animaci�n actual para los framesPerStep y la repetici�n
	currentFramesPerStep = framesPerStep;
	currentLoop = loop;
}

//Reproduce una animaci�n modificando sus parametros antiguos en cierta medida
void SpriteMap::playAnim(string name, float frameRate, bool loop, bool restart)
{
	//Llamo a playAnim(name) para que haga la parte de reproducir una nueva animaci�n
	playAnim(name, restart);

	//Actualizo los parametros de la animaci�n actual para los framesPerStep y la repetici�n
	currentFramesPerStep = (int) (currentAnim->getFramesPerStep()/frameRate);
	currentLoop = loop;
}

//Detiene la reproducci�n de una animaci�n
void SpriteMap::stopAnim()
{
	//Si existe animaci�n actual fija como �ltimo frame el acutal
	if (currentAnim)
	{
		lastFrame = currentAnim->getFrameList()->at(frame);
	}
}

//Se ejecuta en cada paso del juego y su tarea es cambiar de frame si fuese necesario y mantener
//la animaci�n actual en reproducci�n hasta que finalice y no deba repetirse
void SpriteMap::update()
{
	//Si existe animaci�n, no est� finalizada y toca cambiar de frame
	if (currentAnim && !finished && nextFrame())
	{
		//Cambio de frame y compruebo si he llegado al final
		frame++;
		if (frame >= currentAnim->getFrameCount()) 
		{
			//Si he llegado al final compruebo si tiene repetici�n
			if (!currentLoop) 
			{
				//Si no la tiene marco la animaci�n actual como finalizada, reinicio los steps del 
				//juego desde el �ltimo cambio de frame, pongo el �ltimo frame usado como lastFrame
				//y indico que n�mero fue el ultimo frame reproducido
				finished = true;
				step = 1;
				lastFrame = currentAnim->getFrameList()->at((currentAnim->getFrameCount())-1);
				frame = currentAnim->getFrameCount()-1;
			}
			//Si tiene repetici�n reinicio el frame y dejo que siga
			else frame = 0;
		}
	}
}
	
// Dibuja el spriteMap sobre la pantalla
void SpriteMap::render(int x, int y) 
{
	//Calculo el ancho y el alto de cada tile
	int w = img->getWidth() / nCol;
	int h = img->getHeigth() / nRow;
	
	//Si hay animaci�n actual
	if (currentAnim) 
	{
		//Calculo la posici�n en la imagen del frame actual
		int posnum = currentAnim->getFrameList()->at(frame);
		//La paso a coordenadas cartesianas
		pair<int,int> pos = numToXY(posnum);
		//Renderizo la parte de la imagen que va desde (pos.first*w, pos.second*h), es decir, 
		//la esquina superior izquierda del frame, hasta (pos.first*w + w, pos.second*h +h), 
		//es decir la esquina inferior derecha del frame a dibujar, en la posici�n (x,y) de la
		//imagen por defecto
		gfxEngine->renderPartExt(img, x+originX, y+originY, pos.first*w, pos.second*h, w, h, *color, alpha, scaleH, scaleV, rotation, NULL, originX, originY);
	}
}

//Convierte un n�mero en una coordenada
pair<int,int> SpriteMap::numToXY(int num)
{
	return make_pair(num % nCol, num / nCol);
}

//Convierte una coordenada en un n�mero
int SpriteMap::XYToNum(int x, int y)
{
	return x*nCol+y;
}

//Cambia la imagen del SpriteMap
void SpriteMap::setImage(Image* img)
{
	// Si tenemos imagen y la hemos cargado nosotros, hay que borrarla
	if (loaded && img != NULL)
		delete img;
	// En cualquier caso, la imagen actual no la hemos cargado nosotros y debe borrarse fuera
	this->img = img;
	loaded = false;
}

//Devuelve la imagen de un spriteMap
Image* SpriteMap::getImage()
{
	return img;
}

//Dice si hay animaci�n reproduciendose y si la hay, cual
string SpriteMap::getCurrentAnim()
{
	//Si existe la animaci�n devuelvo el nombre
	if (currentAnim) 
		return currentAnim->getName(); 
	//Si no, digo que no hay animaci�n en curso
	else 
		return "none";
}

//Devuelve si la animaci�n ha finalizado
bool SpriteMap::animFinished()
{
	return finished;
};

int SpriteMap::getCurrentFrame()
{
	return frame;
};

int SpriteMap::getWidth()
{
	if (img != NULL)
		return img->getWidth() / nCol;
	else
		return 0;
};

int SpriteMap::getHeight()
{
	if (img != NULL)
		return img->getHeigth() / nRow;
	else
		return 0;
}