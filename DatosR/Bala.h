/*! \file		Bala.h
 *	\brief		Objeto enemigo
 *  \version	1.0
 *  \author		Enric Mac�as L�pez <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef BALA_H
#define BALA_H

#include "Vector2D.h"

/*! \class		Bala
*	\brief		Guarda la informaci�n de un enemigo.
*/
class Bala
{
	private:
		bool		mVisible;	/*!< Si es visible por pantalla o no	*/
		float		mRot;		/*!< �ngulo de rotaci�n					*/
		Vector2D	mPos;		/*!< Posici�n							*/
		Vector2D	mDir;		/*!< Direcci�n							*/

	public:

		/*! \fn			Bala::Bala( void )
		*	\brief		Constructor. Inicializa todas las variables.
		*	\param		None.
		*	\return		None.
		*/
		Bala();

		/*! \fn			Bala::~Bala( void )
		*	\brief		Destructor.
		*	\param		None.
		*	\return		None.
		*/
		~Bala();
		
		/*! \fn			float Bala::getPosX( void )
		*	\brief		Devuelve la posici�n en X.
		*	\param		None.
		*	\return		float	Posici�n Y.
		*/
		float getPosX( void );

		/*! \fn			float Bala::getPosY( void )
		*	\brief		Devuelve la posici�n en Y.
		*	\param		None.
		*	\return		float	Posici�n Y.
		*/
		float getPosY( void );

		/*! \fn			float Bala::getRot( void )
		*	\brief		Devuelve el �ngulo de rotaci�n.
		*	\param		None.
		*	\return		float	�ngulo de rotaci�n.
		*/
		float getRot( void );

		/*! \fn			Vector2D Bala::getPos( void )
		*	\brief		Devuelve la posici�n.
		*	\param		None.
		*	\return		Vector2D	Posici�n.
		*/
		Vector2D getPos( void );

		/*! \fn			bool Bala::getVisible( void )
		*	\brief		Devuelve si el enemigo es visible o no.
		*	\param		None.
		*	\return		bool	Visible o no.
		*/
		bool getVisible( void );

		/*! \fn			Vector2D Bala::getDir( void )
		*	\brief		
		*	\param		None.
		*	\return		bool	Visible o no.
		*/
		Vector2D getDir( void );

		/*! \fn			void Bala::setVisible( bool _b )
		*	\brief		Establece visible a lo que pasa por l�nea de comandos.
		*	\param		bool _b	Visible o no.
		*	\return		None.
		*/
		void setVisible( bool _b );

		/*! \fn			void Bala::setPosX( float _x )
		*	\brief		Establece la posici�n en X.
		*	\param		float _x	Posici�n X.
		*	\return		None.
		*/
		void setPosX( float _x );

		/*! \fn			void Bala::setPosY( float _y )
		*	\brief		Establece la posici�n en Y.
		*	\param		float _y	Posici�n Y.
		*	\return		None.
		*/
		void setPosY( float _y );

		/*! \fn			void Bala::setRot( float _rot )
		*	\brief		Establece el �ngulo de rotaci�n.
		*	\param		float _rot	�ngulo de rotaci�n.
		*	\return		None.
		*/
		void setRot( float _rot );

		/*! \fn			void Bala::setDir( Vector2D _dir )
		*	\brief		
		*	\param		float _rot	�ngulo de rotaci�n.
		*	\return		None.
		*/
		void setDir( float _x , float _y );
};

#endif


