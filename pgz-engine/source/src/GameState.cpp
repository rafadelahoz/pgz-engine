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

#include "GameState.h"

void GameState::init()
{
    // Inicializaci�n de las listas
    entities = new list<Entity*>();
    enabled = new list<Entity*>();
    collidable = new list<Entity*>();
    // Usaremos la funci�n entity_compare para la comparaci�ne entre entidades
    renderable = new list<Entity*>();

    // Inicializaci�n de los buffers
    addedEntitiesBuffer = new list<Entity*>();
    deletedEntitiesBuffer = new list<Entity*>();
    enabledBuffer = new list<Entity*>();
    collidableBuffer = new list<Entity*>();
    renderableBuffer = new list<Entity*>();
}

GameState::GameState(Game* g, int roomw, int roomh)
{
    // Inicializaci�n de estructuras
    init();

    // Almacenamos los par�metros necesarios
    map = NULL;
	game = g;
    this->roomw = roomw;
    this->roomh = roomh;
}

GameState::GameState(Game* g, Map* m, int roomw, int roomh)
{
    // Inicializaci�n de estructuras
    init();

    // Almacenamos los par�metros necesarios
    map = m;
	game = g;
    this->roomw = roomw;
    this->roomh = roomh;
}

GameState::~GameState()
{
    // Borrado de buffers de entidades.
    // Las entidades que contienen ya est�n dentro del GameState porque ser�n
    // borradas directamente de entities.
    delete renderableBuffer;
    delete collidableBuffer;
    delete enabledBuffer;
    delete deletedEntitiesBuffer;

	Entity* tmp;

    // El buffer de entidades a a�adir contiene entidades
    // que no estaban en el GameState, por lo que deben ser borradas expl�citamente.
    list<Entity*>::iterator it;
    for(it = addedEntitiesBuffer->begin(); it != addedEntitiesBuffer->end(); it++)
        if ((*it) != NULL)
        {
			if (!(*it)->persistent)
			{
				tmp = (*it);
				delete tmp;
			}
        }
    delete addedEntitiesBuffer;

    // Borrado de las listas de entidades
    delete renderable;
    delete collidable;
    delete enabled;


    // Borramos todas las entidades del sistema
    for(it = entities->begin(); it != entities->end(); it++)
        if ((*it) != NULL)
        {
            if (!(*it)->persistent)
			{
				tmp = (*it);
				delete tmp;
			}
        }
    delete entities;

    // Borramos el mapa
    if (map != NULL)
        delete map;
}

void GameState::onInit()
{
    // Llama al evento correspondiente de las entidades
    list<Entity*>::iterator it;
    for(it = entities->begin(); it != entities->end(); it++)
        if ((*it) != NULL)
        {
            (*it)->onInitWorld();
        }
}

void GameState::onEnd()
{
    // Llama al evento correspondiente de las entidades
    list<Entity*>::iterator it;
    for(it = entities->begin(); it != entities->end(); it++)
        if ((*it) != NULL)
        {
            (*it)->onEndWorld();
        }
}

void GameState::_update()
{
    // Iteradores y estructuras que se usar�n
    list<Entity*>::iterator i;
    list<Entity*>::iterator j;

    vector<CollisionPair>::iterator k;
    vector<CollisionPair>* collision_list;

    // ---------------------------------
    // ---------- ON INIT --------------
    // ---------------------------------

    // Realizamos las acciones iniciales de cada entidad
    for(i = enabled->begin(); i != enabled->end(); i++)
        if ((*i) != NULL)
        {
             (*i)->onInitStep();
        }

    // ---------------------------------
    // --------- ON COLLISION ----------
    // ---------------------------------

    // Comprobaci�n de colisiones con el mapa, si existe
    if (map != NULL)
        for(i = collidable->begin(); i != collidable->end(); i++)
            if ((*i) != NULL)
            {
                collision_list = map->getSolids()->collide((*i)->mask);
				if (collision_list != NULL)
				{
					for(k = collision_list->begin(); k != collision_list->end(); k++)
					{
						(*i)->onCollision((*k), NULL);
					}
					delete collision_list;
				}
            }

    // Comprobaci�n de colisiones entre entidades

    // Cada una de las entidades, desde la primera a la pen�ltima,
    for(i = collidable->begin(); i != collidable->end(); i++)
        // con cada de las entidades restantes, desde la segunda a la �ltima
		for(j = collidable->begin(); j != collidable->end(); j++)
		//for(j = i, j++; j != collidable->end(); j++)
        {
            // si ninguna de las entidades es inv�lida, comprobamos la colisi�n
            if ((((*i) != NULL) && ((*j) != NULL)) && (*i) != (*j))
            {
				// Las m�scaras tambi�n deben ser v�lidas
				if ((*i)->mask == NULL || (*j)->mask == NULL)
					continue;

                // Obtenemos una lista de colisi�n y la iteramos
                collision_list = (*i)->mask->collide((*j)->mask);
				if (collision_list != NULL)
				{
					for(k = collision_list->begin(); k != collision_list->end(); k++)
					{
						(*i)->onCollision((*k), (*j));
					}
					// debemos ocuparnos de eliminar la lista una vez usada
					delete collision_list;
				}
            }
        }


    // ---------------------------------
    // ------------ ON STEP ------------
    // ---------------------------------

    // Actualizaci�n principal de las entidades
    for(i = enabled->begin(); i != enabled->end(); i++)
		if ((*i) != NULL && !((*i)->frozen))
        {
            (*i)->_update();
        }

    // Actualizaci�n del gameState, si se desea
    onStep();


    // ---------------------------------
    // --------- ON END STEP -----------
    // ---------------------------------

    // Realizamos las acciones finales de cada entidad
    for(i = enabled->begin(); i != enabled->end(); i++)
    if ((*i) != NULL)
    {
        (*i)->onEndStep();
    }


    // ---------------------------------
    // -- Actualizaci�n de los buffers -
    // ---------------------------------

    // Buffer de entidades a a�adir
	// Almacenamos el tama�o de la lista de renderables
	unsigned int n = renderable->size();

    for(i = addedEntitiesBuffer->begin(); i != addedEntitiesBuffer->end(); i++)
    if ((*i) != NULL)
    {
        _add((*i));
    }
    addedEntitiesBuffer->clear();

	/*// si hemos a�adido elementos, debemos ordenarlos
	if ( n > renderable->size())
		renderable->sort(entity_compare);*/

    // Buffer de entidades a eliminar
    for(i = deletedEntitiesBuffer->begin(); i != deletedEntitiesBuffer->end(); i++)
    if ((*i) != NULL)
    {
        _remove((*i));
    }
    deletedEntitiesBuffer->clear();

    // Buffer de entidades que han alterado su estado enabled.
    // Dependiendo de a qu� valor haya cambiado el estado, se a�adir�n o quitar�n de la correspondiente lista
    for(i = enabledBuffer->begin(); i != enabledBuffer->end(); i++)
    if ((*i) != NULL)
    {
        if ((*i)->enabled)
            add_single(enabled, (*i));
        else
            enabled->remove((*i));
    }
    enabledBuffer->clear();

    // Buffer de entidades que han alterado su estado collidable.
    // Dependiendo de a qu� valor haya cambiado el estado, se a�adir�n o quitar�n de la correspondiente lista
    for(i = collidableBuffer->begin(); i != collidableBuffer->end(); i++)
    if ((*i) != NULL)
    {
        if ((*i)->collidable)
            add_single(collidable, (*i));
        else
            collidable->remove((*i));
    }
    collidableBuffer->clear();

    // Buffer de entidades que han alterado su estado renderable.
	// Almacenamos el tama�o de la lista de renderables
	n = renderable->size();
    // Dependiendo de a qu� valor haya cambiado el estado, se a�adir�n o quitar�n de la correspondiente lista
    for(i = renderableBuffer->begin(); i != renderableBuffer->end(); i++)
    if ((*i) != NULL)
    {
        if ((*i)->visible)
            add_single(renderable, (*i));
        else
            renderable->remove((*i));
    }
    renderableBuffer->clear();
	/*// si hemos a�adido elementos, debemos ordenarlos
	//if ( n > renderable->size())*/
	// Se ordena la lista de renderables
	renderable->sort(entity_compare);
}

void addSingle(list<Entity*>* l, Entity* ent){

	list<Entity*>::iterator i;
	for(i = l->begin(); i != l->end(); i++)
	{
		if ((*i) == ent)
			return;
	}

	l->push_back(ent);
}


bool GameState::add_single(list<Entity*>* l, Entity* ent){

	list<Entity*>::iterator i;
	for(i = l->begin(); i != l->end(); i++)
	{
		if ((*i) == ent)
			return false;
	}

	l->push_back(ent);

	return true;
}

bool GameState::_add(Entity* e)
{
    // Si la imagen no existe no hacemos nada
    if (e != NULL)
    {
		list<Entity*>::iterator it;
		for(it = entities->begin(); it != entities->end(); it++)
			if ((*it) != NULL)
			{
				if ((*it) == e)
					return false;
			}

        // a�adimos la entidad a la lista de entidades
        entities->push_back(e);

        // dependiendo de sus atributos, la a�adimos a las dem�s listas o no.
        if (e->enabled)
            enabled->push_back(e);
        if (e->collidable)
            collidable->push_back(e);
        if (e->visible)
		{
            renderable->push_back(e);
		}

        // se llama al evento de inicio de la entidad
        e->onInit();

		return true;
    }
	else
		return false;
}

void GameState::onStep() {}

void GameState::renderBG() {}

void GameState::renderFG() {}

bool GameState::_remove(Entity* e)
{
    // Si la imagen no existe no hacemos nada
    if (e != NULL)
    {
        // Eliminamos la entidad de las listas
        entities->remove(e);
        enabled->remove(e);
        collidable->remove(e);
        renderable->remove(e);

		enabledBuffer->remove(e);
		addedEntitiesBuffer->remove(e);
		collidableBuffer->remove(e);
		renderableBuffer->remove(e);

        // Borramos la entidad
		if (!e->persistent)
			delete e;
		return true;
    }
	else
		return false;
}

void GameState::onRender()
{
    // Si se desea, se pintar�n elementos por debajo de los dem�s
    renderBG();

    // Si hay mapa, se pinta
    if (map != NULL)
        map->render(0,0);

    list<Entity*>::iterator i;
    // Pintamos todas las entidades visibles
	if (renderable->size() > 0)
		for(i = renderable->begin(); i != renderable->end(); i++)
			if ((*i) != NULL)
			{
				(*i)->onRender();
			}

    // Si se desea, se pintar�n elementos por encima de los dem�s
    renderFG();
}

void GameState::addMap(Map* map)
{
    // si exist�a un mapa, lo borramos y asignamos el nuevo
    if (this->map != NULL)
        delete this->map;

    this->map = map;
}

void GameState::removeMap(bool deleteToo)
{
	if (this->map == NULL)
		return;
	
	if (deleteToo)
		delete this->map;
	this->map = NULL;
};

void GameState::removeAll()
{
    // Borra todos los elementos de la lista
    list<Entity*>::iterator it;
	if (entities->size() > 0)
		for(it = entities->begin(); it != entities->end(); it++)
			if ((*it) != NULL)
			{
				_remove(*it);
			}
}

bool GameState::add(Entity* e)
{
    // a�adimos la entidad al buffer para que se a�ada al final del tick
    if (e != NULL)
    {
        addedEntitiesBuffer->push_back(e);
        return true;
    }
    else
        return false;
}

bool GameState::remove(Entity* e)
{
    // a�adimos la entidad al buffer para que se elimine al final del tick
    if (e != NULL)
    {
		add_single(deletedEntitiesBuffer, e);
        return true;
    }
    else
        return false;
}

void GameState::addList(vector<Entity*>* l)
{
    // a�adimos individualmente cada elemento de la lista
    vector<Entity*>::iterator it;
	if (l->size() > 0)
		for(it = l->begin(); it != l->end(); it++)
			if ((*it) != NULL)
			{
				add(*it);
			}
}

void GameState::removeList(vector<Entity*>* l)
{
    // eliminamos individualmente cada elemento de la lista
    vector<Entity*>::iterator it;
	if (l->size() > 0)
		for(it = l->begin(); it != l->end(); it++)
			if ((*it) != NULL)
			{
				remove(*it);
			}
}

void GameState::changedRenderable(Entity* e)
{
    // a�adimos la entidad al buffer para que se efect�e el cambio al final del tick
    if (e != NULL)
        renderableBuffer->push_back(e);
}

void GameState::changedCollidable(Entity*e)
{
    // a�adimos la entidad al buffer para que se efect�e el cambio al final del tick
    if (e != NULL)
        collidableBuffer->push_back(e);
}

void GameState::changedEnabled(Entity*e)
{
    // a�adimos la entidad al buffer para que se efect�e el cambio al final del tick
    if (e != NULL)
        enabledBuffer->push_back(e);
}

vector<Entity*>* GameState::getType(std::string type)
{
    // Creamos la lista que contendr� el resultado
    vector<Entity*>* l = new vector<Entity*>();

    list<Entity*>::iterator i;
    // A�adiremos a la lista todas las entidades cuyo tipo coincida con el dado
	if (entities->size() > 0)
		for(i = entities->begin(); i != entities->end(); i++)
			if ((*i) != NULL)
			{
				if ((*i)->type == type)
					l->push_back(*i);
			}
    return l;
}


bool GameState::collide_mask(Mask* m)
{
    vector<CollisionPair>* collision_list;

    // Comprobamos si la m�scara choca con el SolidGrid
    if (map != NULL)
    {
        collision_list = map->getSolids()->collide(m);
        // si no ha devuelto una lista (NULL), no nos molestamos
        if (collision_list != NULL)
            // si ha devuelto una lista y adem�s contiene elementos, devolvemnos falso
            if (collision_list->size() != 0)
            {
                delete collision_list;
                return false;
            }
    }

    // Comprobamos si la m�scara choca con las entidades
    list<Entity*>::iterator i = entities->begin();
    while (i != entities->end())
    {
        collision_list = (*i)->mask->collide(m);
        // si no ha devuelto una lista (NULL), no nos molestamos
        if (collision_list != NULL)
            // si ha devuelto una lista y adem�s contiene elementos, devolvemnos falso
            if (collision_list->size() != 0)
            {
                delete collision_list;
                return false;
            }
       i++;
    }

    // Si no ha colisionado con ning�n elemento, entonces es que la posici�n est� libre
    return true;
}


bool GameState::collide_entity(Entity* e)
{
    vector<CollisionPair>* collision_list;

	if (e->mask != NULL)
	{
		// Comprobamos si la entidad choca con el SolidGrid
		if (map != NULL)
		{
			collision_list = map->getSolids()->collide(e->mask);
			// si no ha devuelto una lista (NULL), no nos molestamos
			if (collision_list != NULL)
			{
				// si ha devuelto una lista y adem�s contiene elementos, devolvemnos falso
				if (collision_list->size() != 0)
				{
					delete collision_list;
					return false;
				}
				delete collision_list;
			}
		}

		// Comprobamos si la entidad choca con las entidades
		list<Entity*>::iterator i = entities->begin();
		while (i != entities->end())
		{
			if (((*i) != NULL && ( (*i) != e)) && ((*i)->solid))
				if ((*i)->mask != NULL)
				{

					collision_list = (*i)->mask->collide(e->mask);
					// si no ha devuelto una lista (NULL), no nos molestamos
					if (collision_list != NULL)
					{
						// si ha devuelto una lista y adem�s contiene elementos, devolvemnos falso
						if (collision_list->size() != 0)
						{
							delete collision_list;
							return false;
						}
						delete collision_list;
					}
				}
			i++;
		}

		// Si no ha colisionado con ning�n elemento, entonces es que la posici�n est� libre
		return true;
	}
	else
		return false;
}


bool GameState::place_free(int x, int y, Entity* e)
{
    // s�lo comprobamos colisi�n si la m�scara existe y es collidable
    if (e != NULL)
        if (e->collidable)
        {
            // Movemos la entidad de forma temporal a la posici�n x,y
            int tmpx = e->mask->x;
            int tmpy = e->mask->y;
            e->mask->x = x;
            e->mask->y = y;

            // Calculamos si colisiona o no con el resto de elementos del GameState
            bool free = collide_entity(e);

            // Devolvemos la entidad a su posici�n
            e->mask->x = tmpx;
            e->mask->y = tmpy;

            return free;
        }
        else
            return true;
    else
        return false;
}

bool GameState::position_free(int x, int y)
{
    // Creamos una m�scara auxiliar que representa un pixel
    Mask* m = new MaskBox(x, y, 0, 0, "test");

    // Llamamos al m�todo que comprueba si una m�scara puede colocarse en una posici�n
    bool free = collide_mask(m);

    // Liberamos la m�scara auxiliar
    delete m;

    return free;
}

bool GameState::collides(Entity* a, Entity* b)
{
    // s�lo comprobamos colisi�n si las m�scaras existen y son collidable
    if ((a != NULL) && (b != NULL))
    {
        if (a->collidable && b->collidable)
        {
            vector<CollisionPair>* collision_list;
            collision_list = a->mask->collide(b->mask);
            // si no ha devuelto una lista (NULL), no nos molestamos
            if (collision_list != NULL)
            {
                // si ha devuelto una lista y adem�s contiene elementos, colisionan
                if (collision_list->size() != 0)
                {
                    delete collision_list;
                    return true;
                }
				delete collision_list;
            }
        }
    }
    return false;
}

Entity* GameState::place_meeting(int x, int y, Entity* e, std::string type)
{
    // si la entidad dada es inv�lida, no hacemos nada
    if ((e != NULL) && (e->mask != NULL))
    {
		// Se almacena la posici�n de la m�scara
		int xtemp = e->mask->x, ytemp = e->mask->y;

		// y se lleva a la nueva
		e->mask->x = x, e->mask->y = y;

        vector<CollisionPair>* collision_list;
        list<Entity*>::iterator i = entities->begin();
        // Comprobamos colisi�n con cada una de las entidades con las que puede chocar
        while (i != entities->end())
        {
            if (((*i) != e) && ((*i)->mask != NULL))
            {
				// El tipo debe ser correcto o any
				if (type == "any" || (*i)->mask->type == type)
				{
					collision_list = (*i)->mask->collide(e->mask);
					// si no ha devuelto una lista (NULL), no nos molestamos
					if (collision_list != NULL)
					{
						// si ha devuelto una lista y adem�s contiene elementos, devolvemnos la entidad
						if (collision_list->size() != 0)
						{
							delete collision_list;

							// Se devuelve a la posici�n antigua
							e->mask->x = xtemp;
							e->mask->y = ytemp;

							return (*i);
						}
						delete collision_list;
					}
				}
            }
			i++;
        }

		// Se devuelve a la posici�n antigua
		e->mask->x = xtemp;
		e->mask->y = ytemp;
    }

	

    return NULL;
}

vector<Entity*>* GameState::enclosedEntities(Mask* mask, std::string type)
{
    vector<Entity*>* l = new vector<Entity*>();

    // si la m�scara dada es inv�lida, no hacemos nada
    if (mask != NULL)
    {
        vector<CollisionPair>* collision_list;
        list<Entity*>::iterator i = entities->begin();
        // Comprobamos colisi�n con cada una de las entidades con las que puede chocar
        while (i != entities->end())
        {
            if (((*i) != NULL) && ((*i)->mask != NULL))
			{
				collision_list = (*i)->mask->collide(mask);
				// si no ha devuelto una lista (NULL), no nos molestamos
				if (collision_list != NULL)
				{
					// si ha devuelto una lista y adem�s contiene elementos, devolvemnos la entidad
					if ((collision_list->size() != 0) && (*i)->type == type)
					{
						delete collision_list;
						l->push_back(*i);
					}
					delete collision_list;
				}
			}
            i++;
        }
    }

    return l;
}

void GameState::moveToContact(int x, int y, Entity* e)
{
    int incremento;

	// Si el destino es la posici�n, no hay que hacer nada
	if (x == e->x && y == e->y) return;

    // Almacenamos las coordenadas de la m�scara
    int maskx = e->mask->x;
    int masky = e->mask->y;

    // Inversa de la pendiente, 1/m
    float m;

    // Coordenadas que almacenar�n el desplazamiento de la entidad
    float tmpx;
    float tmpy;

    // Si est� a mayor distancia horizontal que vertical, acercaremos la entidad a las coordenadas destino
    // aumentando de 1 en 1 la coordenada x para ganar precisi�n, y la coordenada y aumentar� en el correspondiente valor del vector direcci�n.
    if (maskx != x && abs(maskx - x) >= abs(masky - y))
    {
        // m = pendiente = incremento de y / incremento de x
        m = ((float) (masky - y)) / ((float) (maskx - x));

        // Si la coordinada destino es menor que la origen, debemos retroceder
        if (maskx >= x)
            incremento = -1;
        // Si no, debemos avanzar
        else
            incremento = +1;

        tmpx = 0;
        tmpy = 0;

        // Aproximamos la entidad a las coordenadas destino a trav�s del vector que une las coordenadas iniciales y las finales
        // Por tales, el valor de y ser� el valor de x por el valor de la pendiente (calculado en m).
        /*
            incremento de y / incremento de x = m = tmpy / tmpx
            tmpy = tmpx * y
        */
        // Si hay una entidad obstruyendo el camino, se saldr� del bucle, almacenando en (tmpx, tmpy) el desplazamiento a realizar
        while ((tmpx != (x - maskx)) && place_free(maskx + (int) tmpx, masky + (int) tmpy, e))
        {
            tmpx += incremento;
            tmpy = tmpx*m;
        }

		// Retrocedemos al �ltimo punto en el que no hubo colisi�n
		tmpx -= incremento;
		tmpy = tmpx*m;

        // Desplazamos tanto la entidad como la m�scara
        e->mask->x += (int) tmpx;
        e->mask->y += (int) tmpy;
        e->x += (int) tmpx;
        e->y += (int) tmpy;
    }
    // Si por el contrario est� a mayor distancia vertical que horizontal, acercaremos la entidad a las coordenadas destino
    // aumentando de 1 en 1 la coordenada y para ganar precisi�n, y la coordenada x aumentar� en el correspondiente valor del vector direcci�n.
    else if (masky != y)
    {
        // m = 1 / pendiente = 1 (incremento de y / incremento de x ) = incremento de x / incremento de y
        m = ((float) (maskx - x)) / ((float) (masky - y));

        // Si la coordinada destino es menor que la origen, debemos retroceder
        if (masky >= y)
            incremento = -1;
        // Si no, debemos avanzar
        else
            incremento = +1;

        tmpx = 0;
        tmpy = 0;

        // Aproximamos la entidad a las coordenadas destino a trav�s del vector que une las coordenadas iniciales y las finales
        // Por tales, el valor de x ser� el valor de yx por el valor de la inversa de la pendiente (calculado en m).
        /*
            incremento de y / incremento de x = pendiente = tmpy / tmpx
            tmpx = tmpy / pendiente = tmpy * m
        */
        // Si hay una entidad obstruyendo el camino, se saldr� del bucle, almacenando en (tmpx, tmpy) el desplazamiento a realizar
        /*while ((tmpy != (y - masky)) && place_free(maskx + (int) tmpx, masky + (int) tmpy, e))
        {
            tmpy += incremento;
            tmpx = tmpy*m;
        }*/

		while ((tmpy != (y - masky)) && place_free(maskx + (int) tmpx, masky + (int) tmpy, e))
        {
            tmpy += incremento;
            tmpx = tmpy*m;
        }

		// Retrocedemos al �ltimo punto en el que no hubo colisi�n
		tmpy -= incremento;
		tmpx = tmpy*m;

        // Desplazamos tanto la entidad como la m�scara
        e->mask->x += (int) tmpx;
        e->mask->y += (int) tmpy;
        e->x += (int) tmpx;
        e->y += (int) tmpy;
    }
}

bool GameState::entity_compare(Entity* a, Entity* b)
{
	// Una entidad va antes que otra si su profundidad es menor
    return a->depth < b->depth;
};
