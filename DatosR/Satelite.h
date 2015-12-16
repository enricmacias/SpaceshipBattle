/*! \file		Satelite.h
 *	\brief		Objeto enemigo IA
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef SATELITE_H
#define SATELITE_H

#include "Nave.h"
//#include "Math.h"

/*! \class		Enemigo IA
*	\brief		Guarda la información de un enemigo.
*/
class Satelite : public Nave
{
	private:
		float		mTra;		/*!< Ángulo de trayectoria				*/
		Vector2D	mPeligro;	/*!< Ávector peligro					*/

	public:

		/*! \fn			Satelite::Satelite( void )
		*	\brief		Constructor. Inicializa todas las variables.
		*	\param		None.
		*	\return		None.
		*/
		Satelite();

		/*! \fn			Satelite::~Satelite( void )
		*	\brief		Destructor.
		*	\param		None.
		*	\return		None.
		*/
		~Satelite();

		/*! \fn			void Satelite::setTra( void )
		*	\brief		Establece la trayectoria.
		*	\param		None.
		*	\return		None
		*/
		void setTra();
		/*! \fn			void Satelite::Reduce(  int mult  )
		*	\brief		Reduce la velocidad a mult
		*	\param		int mult 
		*	\return		None
		*/
		void Reduce( int mult );
		/*! \fn			Vector2D Satelite::getPeligro( )
		*	\brief		devuelve el vector peligro
		*	\param		none
		*	\return		Vector2D
		*/
		Vector2D getPeligro( void ){ return mPeligro;};
		/*! \fn			void Satelite::getPeligro( float xPeligro, float yPeligro  )
		*	\brief		establece el vector peligro
		*	\param		float xPeligro, float yPeligro 
		*	\return		none
		*/
		void setPeligro( float xPeligro, float yPeligro );
		
		/*! \fn			void Satelite::getPeligro(  )
		*	\brief		defvuelve la trayectoria
		*	\param		None 
		*	\return		float
		*/
		float getTra( void );
};

#endif