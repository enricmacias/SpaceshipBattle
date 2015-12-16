/*! \file		Bala.cpp
 *	\brief		Objeto enemigo
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "Bala.h"

Bala::Bala()
{
	Vector2D aux;
	aux.setX( 0.0f );
	aux.setY( 0.0f );
	mPos = aux;		
	mDir = aux;		
	mVisible = false;
	mRot = 0.0f;	
}
Bala::~Bala()
{
}

float Bala::getPosX( void )
{
	Vector2D aux = mPos;
	return aux.getX();
}

float Bala::getPosY( void )
{
	Vector2D aux = mPos;
	return aux.getY();
}

float Bala::getRot( void )
{
	return mRot + 45;
}

Vector2D Bala::getPos( void )
{
	return mPos;
}

bool Bala::getVisible( void )
{
	return mVisible;
}

Vector2D Bala::getDir( void )
{
	return mDir;
}

void Bala::setVisible( bool _b )
{
	mVisible = _b;
	
}

void Bala::setPosX( float _x )
{
	mPos.setX( _x );
}

void Bala::setPosY( float _y )
{
	mPos.setY( _y );
}

void Bala::setRot( float _rot )
{
	mRot = _rot;
}

void Bala::setDir( float _x , float _y )
{
	mDir.setVector( _x , _y );
	mDir.Normaliza();
	if( mDir.getY()>0 )
		mRot = acos(mDir.getX());
	else
		mRot = -acos(mDir.getX());
	mRot = (180*mRot) / 3.1415;	// Ángulo entre dos vectores a1*b1 + a2*b2 / |a|*|b|
}



