/*! \file		Enemigo.cpp
 *	\brief		Objeto enemigo
 *  \version	1.0
*  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "Enemigo.h"

Enemigo::Enemigo()
{
	Vector2D aux;
	aux.setX( 0.0f );
	aux.setY( 0.0f );
	mPos = aux;		
	mVisible = true;
	mRot = 0.0f;		
	mTamaño = 1.0f;	
}

Enemigo::~Enemigo()
{
}

float Enemigo::getPosX( void )
{
	Vector2D aux = mPos;
	return aux.getX();
}

float Enemigo::getPosY( void )
{
	Vector2D aux = mPos;
	return aux.getY();
}

float Enemigo::getRot( void )
{
	return mRot;
}

float Enemigo::getTamaño( void )
{
	return mTamaño;
}

Vector2D Enemigo::getPos( void )
{
	return mPos;
}

bool Enemigo::getVisible( void )
{
	return mVisible;
}

void Enemigo::setVisible( bool _b )
{
	mVisible = _b;
}

void Enemigo::setPosX( float _x )
{
	mPos.setX( _x );
}

void Enemigo::setPosY( float _y )
{
	mPos.setY( _y );
}

void Enemigo::setRot( float _rot )
{
	mRot = _rot;
}

void Enemigo::setTamaño( float _tamaño )
{
	mTamaño = _tamaño;
}