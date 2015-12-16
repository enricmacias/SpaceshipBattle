/*! \file		Satelite.cpp
 *	\brief		Objeto enemigo IA
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "Satelite.h"

Satelite::Satelite()
{
	Vector2D aux;
	aux.setX( 0.0 );
	aux.setY( 0.0 );
	mPos = aux;		
	mVisible = true;
	mRot = 0.0;		
	mVidas = 0;
	mCarga = true;
}

Satelite::~Satelite()
{
}


float Satelite::getTra( void )
{
	return mTra;
}

void Satelite::setPeligro( float xPeligro,  float yPeligro )
{
	mPeligro.setX( xPeligro );
	mPeligro.setY( yPeligro );
}

void Satelite::setTra()
{
	Vector2D aux;
	aux = mVel;
	aux.Normaliza();
	if( aux.getY()>0 )
		mTra = acos(aux.getX());
	else
		mTra = -acos(aux.getX());
	
	mTra = (180*mTra) / 3.1415;	// Ángulo entre dos vectores a1*b1 + a2*b2 / |a|*|b|
}

void Satelite::Reduce( int mult )
{
	mVel.Normaliza();
	mVel.setX(mVel.getX()*mult);
	mVel.setY(mVel.getY()*mult);
}
