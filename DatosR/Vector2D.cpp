/*! \file		Vector2D.cpp
 *	\brief		Objeto Vector2D para tratar información que necesita de dos coordenadas
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "Vector2D.h"

Vector2D::Vector2D( void )
{
	mX = 0.0f;
	mY = 0.0f;
	mModulo = 0.0f;
}

Vector2D::Vector2D( float _x , float _y )
{
	mX = _x;
	mY = _y;
	mModulo = sqrt( ( mX*mX ) + ( mY*mY ) );
}

Vector2D::~Vector2D( void )
{
}

float Vector2D::getModulo( void )
{
	mModulo = sqrt( (double) ( mX*mX ) + ( mY*mY ) );

	return mModulo;
}

void Vector2D::Normaliza( void )
{
	mModulo = sqrt( (double) ( mX*mX ) + ( mY*mY ) );

	if( mModulo != 0 )
	{
		mX = mX/mModulo;
		mY = mY/mModulo;
	}
}

float Vector2D::getX()
{
	return mX;
}

float Vector2D::getY()
{
	return mY;
}

void Vector2D::setX( float _x )
{
	mX = _x;
}

void Vector2D::setY( float _y )
{
	mY = _y;
}

void Vector2D::setVector( float _x , float _y )
{
	mX = _x;
	mY = _y;
	mModulo = getModulo();
}

void Vector2D::operator=( Vector2D vct )
{
	mX = vct.getX();
	mY = vct.getY();
}

Vector2D *Vector2D::operator-( Vector2D vct )
{
	return( new Vector2D( mX - vct.getX() , mY - vct.getY() ) );
}

Vector2D *Vector2D::operator+(Vector2D vct)
{
	return( new Vector2D( mX - vct.getX() , mY - vct.getY() ) );
}