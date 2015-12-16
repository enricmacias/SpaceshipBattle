/*! \file		Enemigo.h
 *	\brief		Objeto enemigo
 *  \version	1.0
 *  \author		Enric Mac�as L�pez <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Vector2D.h"

/*! \class		Enemigo
*	\brief		Guarda la informaci�n de un enemigo.
*/
class Enemigo
{
	private:
		Vector2D	mPos;		/*!< Posici�n							*/
		bool		mVisible;	/*!< Si es visible por pantalla o no	*/
		float		mRot;		/*!< �ngulo de rotaci�n					*/
		float		mTama�o;	/*!< Tama�o del enemigo					*/

	public:

		/*! \fn			Enemigo::Enemigo( void )
		*	\brief		Constructor. Inicializa todas las variables.
		*	\param		None.
		*	\return		None.
		*/
		Enemigo();

		/*! \fn			Enemigo::~Enemigo( void )
		*	\brief		Destructor.
		*	\param		None.
		*	\return		None.
		*/
		~Enemigo();

		/*! \fn			float Enemigo::getPosX( void )
		*	\brief		Devuelve la posici�n en X.
		*	\param		None.
		*	\return		float	Posici�n X.
		*/
		float getPosX( void );

		/*! \fn			float Enemigo::getPosY( void )
		*	\brief		Devuelve la posici�n en Y.
		*	\param		None.
		*	\return		float	Posici�n Y.
		*/
		float getPosY( void );

		/*! \fn			float Enemigo::getRot( void )
		*	\brief		Devuelve el �ngulo de rotaci�n.
		*	\param		None.
		*	\return		float	�ngulo de rotaci�n.
		*/
		float getRot( void );

		/*! \fn			float Enemigo::getTama�o( void )
		*	\brief		Devuelve el tama�o del enemigo.
		*	\param		None.
		*	\return		float	Tama�o.
		*/
		float getTama�o( void );

		/*! \fn			Vector2D Enemigo::getPos( void )
		*	\brief		Devuelve la posici�n.
		*	\param		None.
		*	\return		Vector2D	Posici�n.
		*/
		Vector2D getPos( void );

		/*! \fn			bool Enemigo::getVisible( void )
		*	\brief		Devuelve si el enemigo es visible o no.
		*	\param		None.
		*	\return		bool	Visible o no.
		*/
		bool getVisible( void );

		/*! \fn			void Enemigo::setVisible( bool _b )
		*	\brief		Establece visible a lo que pasa por l�nea de comandos.
		*	\param		bool _b	Visible o no.
		*	\return		None.
		*/
		void setVisible( bool _b );

		/*! \fn			void Enemigo::setPosX( float _x )
		*	\brief		Establece la posici�n en X.
		*	\param		float _x	Posici�n X.
		*	\return		None.
		*/
		void setPosX( float _x );

		/*! \fn			void Enemigo::setPosY( float _y )
		*	\brief		Establece la posici�n en Y.
		*	\param		float _y	Posici�n Y.
		*	\return		None.
		*/
		void setPosY( float _y );

		/*! \fn			void Enemigo::setRot( float _rot )
		*	\brief		Establece el �ngulo de rotaci�n.
		*	\param		float _rot	�ngulo de rotaci�n.
		*	\return		None.
		*/
		void setRot( float _rot );

		/*! \fn			void Enemigo::setTama�o( float _tama�o )
		*	\brief		Establece el tama�o del enemigo.
		*	\param		float _tama�o	Tama�o.
		*	\return		None.
		*/
		void setTama�o( float _tama�o );
};

#endif