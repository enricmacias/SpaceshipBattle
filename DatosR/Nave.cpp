/*! \file		Nave.cpp
 *	\brief		Objeto enemigo
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "Nave.h"

Nave::Nave()
{
	Vector2D aux;
	aux.setX( 0.0 );
	aux.setY( 0.0 );
	mPos = aux;		
	mVisible = true;
	mRot = 0.0;		
	mVidas = 0;
	mInmune = true;
	mCount = 100;
	mCarga = true;
}

Nave::~Nave()
{
}

float Nave::getPosX( void )
{
	Vector2D aux = mPos;
	return aux.getX();
}

float Nave::getPosY( void )
{
	Vector2D aux = mPos;
	return aux.getY();
}

float Nave::getRot( void )
{
	return mRot;
}

Vector2D Nave::getPos( void )
{
	return mPos;
}

bool Nave::getVisible( void )
{
	return mVisible;
}

Vector2D Nave::getDir( void )
{
	return mDir;
}

Vector2D Nave::getVel( void )
{
	return mVel;
}

float Nave::getFuerza( void )
{
	return mFuerza;
}

int Nave::getVidas( void )
{
	return mVidas;
}

void Nave::setVisible( bool _b )
{
	mVisible = _b;
	if(_b == false)
		mBala.setVisible(false);
}

void Nave::setPosX( float _x )
{
	mPos.setX( _x );
}

void Nave::setPosY( float _y )
{
	mPos.setY( _y );
}

void Nave::setRot( float _rot )
{
	mRot = _rot;
}

void Nave::setDir( float _x , float _y )
{
	mDir.setVector( _x - mPos.getX() , _y - mPos.getY() );
	mDir.Normaliza();
	if( mDir.getY()>0 )
		mRot = acos(mDir.getX());
	else
		mRot = -acos(mDir.getX());
	mRot = (180*mRot) / 3.1415;	// Ángulo entre dos vectores a1*b1 + a2*b2 / |a|*|b|
}

void Nave::setVel( Vector2D _vel )
{
	mVel.setX(_vel.getX());
	mVel.setY(_vel.getY());
}

void Nave::setFuerza( float _fuerza )
{
	mFuerza = _fuerza;
}

void Nave::setVidas( int _iVidas )
{
	mVidas = _iVidas;
}

void Nave::Stop( void )
{
	Vector2D aux;
	aux.setX(0);
	aux.setY(0);

	mVel = aux;
	mFuerza = 0.0;
}
void Nave::Dispara( void )
{
	mCarga = false;
	mBala.setVisible(true);
	mBala.setPosX(mPos.getX());
	mBala.setPosY(mPos.getY());
	mBala.setDir(mDir.getX(), mDir.getY());

}
void Nave::setCarga( bool on)
{
	mCarga = on;
	if(!on)
	{
		mBala.setVisible(on);
	}
}
void Nave::setCount( int _count )
{
	if (_count < 1)
	{
		mInmune = false;
	}
	else
		mCount = _count;
}
