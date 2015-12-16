/*! \file		Enemigo.h
 *	\brief		Objeto enemigo
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Vector2D.h"

/*! \class		Enemigo
*	\brief		Guarda la información de un enemigo.
*/
class Enemigo
{
	private:
		Vector2D	mPos;		/*!< Posición							*/
		bool		mVisible;	/*!< Si es visible por pantalla o no	*/
		float		mRot;		/*!< Ángulo de rotación					*/
		float		mTamaño;	/*!< Tamaño del enemigo					*/

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
		*	\brief		Devuelve la posición en X.
		*	\param		None.
		*	\return		float	Posición X.
		*/
		float getPosX( void );

		/*! \fn			float Enemigo::getPosY( void )
		*	\brief		Devuelve la posición en Y.
		*	\param		None.
		*	\return		float	Posición Y.
		*/
		float getPosY( void );

		/*! \fn			float Enemigo::getRot( void )
		*	\brief		Devuelve el ángulo de rotación.
		*	\param		None.
		*	\return		float	Ángulo de rotación.
		*/
		float getRot( void );

		/*! \fn			float Enemigo::getTamaño( void )
		*	\brief		Devuelve el tamaño del enemigo.
		*	\param		None.
		*	\return		float	Tamaño.
		*/
		float getTamaño( void );

		/*! \fn			Vector2D Enemigo::getPos( void )
		*	\brief		Devuelve la posición.
		*	\param		None.
		*	\return		Vector2D	Posición.
		*/
		Vector2D getPos( void );

		/*! \fn			bool Enemigo::getVisible( void )
		*	\brief		Devuelve si el enemigo es visible o no.
		*	\param		None.
		*	\return		bool	Visible o no.
		*/
		bool getVisible( void );

		/*! \fn			void Enemigo::setVisible( bool _b )
		*	\brief		Establece visible a lo que pasa por línea de comandos.
		*	\param		bool _b	Visible o no.
		*	\return		None.
		*/
		void setVisible( bool _b );

		/*! \fn			void Enemigo::setPosX( float _x )
		*	\brief		Establece la posición en X.
		*	\param		float _x	Posición X.
		*	\return		None.
		*/
		void setPosX( float _x );

		/*! \fn			void Enemigo::setPosY( float _y )
		*	\brief		Establece la posición en Y.
		*	\param		float _y	Posición Y.
		*	\return		None.
		*/
		void setPosY( float _y );

		/*! \fn			void Enemigo::setRot( float _rot )
		*	\brief		Establece el ángulo de rotación.
		*	\param		float _rot	Ángulo de rotación.
		*	\return		None.
		*/
		void setRot( float _rot );

		/*! \fn			void Enemigo::setTamaño( float _tamaño )
		*	\brief		Establece el tamaño del enemigo.
		*	\param		float _tamaño	Tamaño.
		*	\return		None.
		*/
		void setTamaño( float _tamaño );
};

#endif