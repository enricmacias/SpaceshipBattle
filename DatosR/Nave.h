/*! \file		Nave.h
 *	\brief		Objeto enemigo
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef NAVE_H
#define NAVE_H

#include "Vector2D.h"
#include "Bala.h"
//#include "Math.h"

/*! \class		Enemigo
*	\brief		Guarda la información de un enemigo.
*/
class Nave
{
	protected:
		
		bool		mVisible;	/*!< Si es visible por pantalla o no	*/
		float		mRot;		/*!< Ángulo de rotación					*/
		Vector2D	mPos;		/*!< Posición							*/
		Vector2D	mDir;		/*!< Dirección							*/
		Vector2D	mVel;		/*!< Velocidad							*/
		float		mFuerza;	/*!< Fuerza								*/
		int			mVidas;		/*!< Vidas								*/
		Bala		mBala;		/*!< Bala								*/
		bool		mCarga;		/*!< Carga								*/
		bool		mInmune;	/*!< Inmunidad							*/
		int			mCount;		/*!< Contador interno					*/

	public:

		/*! \fn			Nave::Nave( void )
		*	\brief		Constructor. Inicializa todas las variables.
		*	\param		None.
		*	\return		None.
		*/
		Nave();

		/*! \fn			Nave::~Nave( void )
		*	\brief		Destructor.
		*	\param		None.
		*	\return		None.
		*/
		~Nave();

		/*! \fn			float Nave::getPosX( void )
		*	\brief		Devuelve la posición en X.
		*	\param		None.
		*	\return		float	Posición X.
		*/
		float getPosX( void );

		/*! \fn			float Nave::getPosY( void )
		*	\brief		Devuelve la posición en Y.
		*	\param		None.
		*	\return		float	Posición Y.
		*/
		float getPosY( void );

		/*! \fn			float Nave::getRot( void )
		*	\brief		Devuelve el ángulo de rotación.
		*	\param		None.
		*	\return		float	Ángulo de rotación.
		*/
		float getRot( void );

		/*! \fn			Vector2D Nave::getPos( void )
		*	\brief		Devuelve la posición.
		*	\param		None.
		*	\return		Vector2D	Posición.
		*/
		Vector2D getPos( void );

		/*! \fn			bool Nave::getVisible( void )
		*	\brief		Devuelve si el enemigo es visible o no.
		*	\param		None.
		*	\return		bool	Visible o no.
		*/
		bool getVisible( void );

		/*! \fn			Vector2D Nave::getDir( void )
		*	\brief		
		*	\param		None.
		*	\return		bool	Visible o no.
		*/
		Vector2D getDir( void );

		/*! \fn			Vector2D Nave::getVel( void )
		*	\brief		
		*	\param		None.
		*	\return		bool	Visible o no.
		*/
		Vector2D getVel( void );

		/*! \fn			int Nave::getVidas( void )
		*	\brief		
		*	\param		None.
		*	\return		int	Numero de vidas.
		*/
		int getVidas( void );


		/*! \fn			float Nave::getFuerza( void )
		*	\brief		
		*	\param		None.
		*	\return		bool	Visible o no.
		*/
		float getFuerza( void );

		/*! \fn			void Nave::setVisible( bool _b )
		*	\brief		Establece visible a lo que pasa por línea de comandos.
		*	\param		bool _b	Visible o no.
		*	\return		None.
		*/
		void setVisible( bool _b );

		/*! \fn			void Nave::setPosX( float _x )
		*	\brief		Establece la posición en X.
		*	\param		float _x	Posición X.
		*	\return		None.
		*/
		void setPosX( float _x );

		/*! \fn			void Nave::setPosY( float _y )
		*	\brief		Establece la posición en Y.
		*	\param		float _y	Posición Y.
		*	\return		None.
		*/
		void setPosY( float _y );

		/*! \fn			void Nave::setRot( float _rot )
		*	\brief		Establece el ángulo de rotación.
		*	\param		float _rot	Ángulo de rotación.
		*	\return		None.
		*/
		void setRot( float _rot );

		/*! \fn			void Nave::setDir( Vector2D _dir )
		*	\brief		establece la direccion
		*	\param		float _rot	Ángulo de rotación.
		*	\return		None.
		*/
		void setDir( float _x , float _y );

		/*! \fn			void Nave::setVel( Vector2D _vel )
		*	\brief		establece la velocidad
		*	\param		Vector2D _vel
		*	\return		None.
		*/
		void setVel( Vector2D _vel );

		/*! \fn			void Nave::setFuerza( float _fuerza )
		*	\brief		establece la fuerza
		*	\param		float _rot	Ángulo de rotación.
		*	\return		None.
		*/
		void setFuerza( float _fuerza );

		/*! \fn			void Nave::setVidas( int _iVidas )
		*	\brief		establece las vidas
		*	\param		float _rot	Ángulo de rotación.
		*	\return		None.
		*/
		void setVidas( int _iVidas );
		/*! \fn			void Nave::Stop(  )
		*	\brief		para la nave
		*	\param		None.
		*	\return		None.
		*/
		void Stop( void );
		/*! \fn			bool Nave::getCarga(  )
		*	\brief		devuelve el numero de vidas
		*	\param		None.
		*	\return		boolean.
		*/
		bool getCarga( void ){return mCarga;};
		
		/*! \fn			void Nave::setBala( Bala B )
		*	\brief		establece la bala
		*	\param		Bala B
		*	\return		None.
		*/
		void setBala( Bala B ){mBala = B;};
		
		/*! \fn			void Nave::setCount( int _count )
		*	\brief		establece el contador
		*	\param		int _count 
		*	\return		None.
		*/
		void setCount( int _count );

		/*! \fn			void Nave::setInmune( bool _inmu )
		*	\brief		establece la inmunidad
		*	\param		bool _inmu
		*	\return		None.
		*/
		void setInmune( bool _inmu ){mInmune = _inmu;};
		/*! \fn			void Nave::getInmune( )
		*	\brief		devuelve la inmunidad
		*	\param		None
		*	\return		bool.
		*/
		bool getInmune( void ){return mInmune;};
		
		/*! \fn			int Nave::getCount( )
		*	\brief		devuelve el contador
		*	\param		None
		*	\return		int.
		*/
		int getCount( void ){return mCount;};
		/*! \fn			Bala Nave::getBala( )
		*	\brief		devuelve la bala
		*	\param		None
		*	\return		Bala.
		*/
		Bala getBala( void ){return mBala;};
		/*! \fn			void Nave::setCarga( bool on )
		*	\brief		establece la carga
		*	\param		bool on
		*	\return		None.
		*/
		void setCarga( bool on);
		/*! \fn			void Nave::Dispara(  )
		*	\brief		realiza la acion de disparar
		*	\param		None
		*	\return		None.
		*/
		void Dispara( void );
};

#endif