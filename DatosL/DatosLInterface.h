/*! \file		DatosLInterface.h
 *	\brief		Guarda los objetos de la dll Lógica
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef DATOSLINTERFACE_H
#define DATOSLINTERFACE_H

	#include <vector>
	#include <windows.h>
	#include <stdio.h>
	#include <string>

	#include "../DatosR/Satelite.h"
	#include "../DatosR/Bala.h"
	#include "../DatosR/Enemigo.h"

	/*! \class		DatosLInterface
	*	\brief		Guarda los ojetos de la dll Lógica
	*/
	class DatosLInterface
	{
		protected:

			HINSTANCE						m_hDLL;			/*!< Para gestionar la instancia de la aplicación		*/
			Nave							N;				/*!< Nave que tratamos									*/
			std::vector < Satelite >		mSat;			/*!< Vector para guardar los satelites					*/
			std::vector < Enemigo >			m_iEnemigos;	/*!< Vector para guardar los enemigos					*/
			int								Server;			/*!< Define nuestra funcion respecto a internet			*/
		public:

			/*! \fn			DatosLInterface::DatosLInterface( void )
			*	\brief		Constructor.
			*	\param		None.
			*	\return		None.
			*/
			DatosLInterface();

			/*! \fn			DatosLInterface::~DatosLInterface( void )
			*	\brief		Destructor.
			*	\param		None.
			*	\return		None.
			*/
			virtual ~DatosLInterface();

			/*! \fn			HRESULT DatosLInterface::Init( void )
			*	\brief		Inicializa la dll. (virtual pura)
			*	\param		None.
			*	\return		HRESULT	----------.
			*/
			virtual HRESULT Init( void ) = 0;

			/*! \fn			void DatosLInterface::Idle( void )
			*	\brief		Controla la lógica del juego.	(virtual pura)
			*	\param		None.
			*	\return		None.
			*/
			virtual void Idle( int &iDisplay ) = 0;
			
			/*! \fn			void DatosLInterface::InitPos( void )
			*	\brief		Inicializa las posiciones	(virtual pura)
			*	\param		None.
			*	\return		None.
			*/
			virtual void InitPos( void ) = 0;

			/*! \fn			void DatosRInterface::addEnemigo( float x , float y , float rot , float tamaño )
			*	\brief		Añade un enemigo al vector de enemigos. (virtual pura)
			*	\param		float x			Posición x del enemigo.
			*	\param		float y			Posición y del enemigo.
			*	\param		float rot		Angulo de rotación del enemigo.
			*	\param		float tamaño	Tamaño del enemigo.
			*	\return		None.
			*/
			void addEnemigo( float x , float y , float rot , float tamaño );

			/*! \fn			std::vector < Enemigo > DatosLInterface::getEnem( void )
			*	\brief		devuelve el vector de asteroides
			*	\param		None.
			*	\return		std::vector < Enemigo >.
			*/
			std::vector < Enemigo > getEnem( void );
			
			/*! \fn			void DatosLInterface::addNave(  Nave _n )
			*	\brief		añade la nave a memoria
			*	\param		Nave _n 
			*	\return		none
			*/
			void addNave( Nave _n ){ N = _n; };
			
			/*! \fn			void DatosLInterface::addSat( std::vector < Satelite > _s )
			*	\brief		añade el vector de satelites a memoria
			*	\param		std::vector < Satelite > _s
			*	\return		none
			*/
			void addSat( std::vector < Satelite > _s ){ mSat = _s; };
			
			/*! \fn			void DatosLInterface::addEnem( std::vector < Enemigo > _e )
			*	\brief		añade el vector de satelites a memoria
			*	\param		 std::vector < Enemigo > _e
			*	\return		none
			*/
			void addEnem( std::vector < Enemigo > _e ){ m_iEnemigos = _e; };
			
			/*! \fn			sNave DatosLInterface::getNave( void )
			*	\brief		devuelve ela nave
			*	\param		None.
			*	\return		Nave
			*/
			Nave getNave( void ) { return N; };
			
			/*! \fn			td::vector < Satelite >  DatosLInterface::getSat( void )
			*	\brief		devuelve el vector de satelites
			*	\param		None.
			*	\return		td::vector < Satelite > 
			*/
			std::vector < Satelite > getSat(void){return mSat;};
			
			/*! \fn			void DatosLInterface::addServer(  int _Server )
			*	\brief		añade el entero Server a memoria
			*	\param		int _Server
			*	\return		none
			*/
			void addServer( int _Server ){ Server = _Server; };
			
			/*! \fn			void DatosLInterface::Solver( int inum , int i )
			*	\brief		calcula el desplazamiento de los objetos
			*	\param		int inum , int i
			*	\return		none
			*/
			void Solver( int inum , int i);
			
			/*! \fn			Bala DatosLInterface::BSolver( Bala B )
			*	\brief		calcula el desplazamiento de las balas
			*	\param		Bala B
			*	\return		Bala
			*/
			Bala BSolver( Bala B );
			
			/*! \fn			void DatosLInterface::Piensa(int i )
			*	\brief		les dice a los satelites que tienen que hacer
			*	\param		int i
			*	\return		none
			*/
			void Piensa( int i );
			
			/*! \fn			void DatosLInterface::Colisiona()
			*	\brief		calcula las colisiones
			*	\param		none
			*	\return		none
			*/
			void Colisiona( void );
			
			/*! \fn			void DatosLInterface::posiciona( float &x, float &y, float tamanyo, int MaxEscenari )
			*	\brief		calcula nuevas posiciones para los asteroides aleatoria y recursivamente (virtual)
			*	\param		loat &x, float &y, float tamanyo, int MaxEscenari
			*	\return		none
			*/
			virtual void posiciona(float &x, float &y, float tamanyo, int MaxEscenari) = 0;
	};

	typedef class DatosLInterface *LPDATOSLINTERFACE;

	/*----------------------------------------------------------------*/
	extern "C" {
		HRESULT CreateLInterface( HINSTANCE hDLL , DatosLInterface **ppDatosLInterface );
		typedef HRESULT( *CREATELINTERFACE)( HINSTANCE hDLL , DatosLInterface **ppDatosLInterface );
	   
		HRESULT ReleaseLInterface( DatosLInterface **ppDatosLInterface );
		typedef HRESULT( *RELEASELINTERFACE)( DatosLInterface **ppDatosLInterface );
	}
	/*----------------------------------------------------------------*/

#endif