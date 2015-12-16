/*! \file		eNetInterface.cpp
 *	\brief		Guarda los objetos de la dll Internet
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "eNetInterface.h"

eNetInterface::eNetInterface()
{
}

eNetInterface::~eNetInterface()
{
}

void eNetInterface::addEnem( std::vector < Enemigo > EnemigosOut  )
{
	m_iEnemigosOut = EnemigosOut;
	m_iEnemigosIn = EnemigosOut;
}

void eNetInterface::addSat( std::vector < Satelite > SateliteOut  )
{
	m_iSateliteOut = SateliteOut;
}

std::vector < Enemigo > eNetInterface::getEnem( void  )
{
	return m_iEnemigosIn;
}