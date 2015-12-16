/*! \file		DatosRInterface.cpp
 *	\brief		Guarda los objetos de la dll Render
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "DatosRInterface.h"

DatosRInterface::DatosRInterface()
{
}

DatosRInterface::~DatosRInterface()
{
}

Enemigo DatosRInterface::getEnemigo( int iPos )
{
	return( m_iEnemigos[ iPos ] );
}

void DatosRInterface::addEnem( std::vector < Enemigo > vEnemigos  )
{
	m_iEnemigos = vEnemigos;
}

void DatosRInterface::addNave( int iNave , Nave N )
{
	switch( iNave )
	{
		case 1: N1 = N;
			break;
		case 2: N2 = N;
			break;
	}
}

Nave DatosRInterface::getNave( int iNave )
{
	switch( iNave )
	{
		case 1: return N1;
			break;
		case 2: return N2;
			break;
	}
}

void DatosRInterface::addSat(std::vector < Satelite > _S)
{
	mSat = _S;
}
