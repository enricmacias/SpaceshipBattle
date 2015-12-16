/*! \file		DatosEInterface.cpp
 *	\brief		Guarda los objetos de la dll Eventos
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/


#include "DatosEInterface.h"

DatosEInterface::DatosEInterface()
{
}

DatosEInterface::~DatosEInterface()
{
}

void DatosEInterface::updateFuerza(bool bFuerza)
{
	if(bFuerza)
		N.setFuerza(1.0);
	else
	{
		if(N.getFuerza() > 0)
			N.setFuerza(N.getFuerza()-0.018);
	}
}

void DatosEInterface::addNave( Nave _N )
{
	N = _N;
}

Nave DatosEInterface::getNave( )
{
	return N;
}