/*! \file		DatosRInterface.h
 *	\brief		Guarda los objetos de la dll Render
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef DATOSRINTERFACE_H
#define DATOSRINTERFACE_H

	#include <vector>
	#include <windows.h>
	#include <stdio.h>
	#include <string>

	#include "Enemigo.h"
	#include "Satelite.h"
	#include <glut.h>

	#pragma comment ( lib , "opengl32.lib" )
	#pragma comment ( lib , "glu32.lib" )
	#pragma comment ( lib , "glut32.lib" )

	/*! \class		DatosRInterface
	*	\brief		Guarda los ojetos de la dll Render
	*/
	class DatosRInterface
	{
		protected:

			HINSTANCE						m_hDLL;			/*!< Para gestionar la instancia de la aplicación		*/

			GLint							TexBG;			/*!< Id de Textura Back Ground							*/
			GLint							TexNau;			/*!< Id de Textura Nave									*/
			GLint							TexNauOn;		/*!< Id de Textura Nave acelerando						*/
			GLint							TexAste;		/*!< Id de Textura Asteroide							*/
			GLint							TexEnem;		/*!< Id de Textura Satélite								*/
			GLint							TexEnemOn;		/*!< Id de Textura Satélite acelerando					*/
			GLint							TexLaser;		/*!< Id de Textura Laser								*/
			GLint							TexEsc;			/*!< Id de Textura Escudo de fuerza						*/
			
			unsigned int					iWidth;			/*!< Altura de la ventana	*/
			unsigned int					iHeigth;		/*!< Anchura de la ventana	*/
			int								MaxEscenari;	/*!< Medida MAX frustrum	*/
			int								Server;			/*!< Medida MAX frustrum	*/
			

			std::vector < Enemigo >			m_iEnemigos;	/*!< Vector para guardar los enemigos					*/
			Nave							N1;				/*!< Nave 1 , Jugador 1									*/
			Nave							N2;				/*!< Nave 2 , Jugador 2									*/
			std::vector < Satelite >		mSat;			/*!< Vector de Satelites								*/


		public:

			/*! \fn			DatosRInterface::DatosRInterface( void )
			*	\brief		Constructor.
			*	\param		None.
			*	\return		None.
			*/
			DatosRInterface();

			/*! \fn			DatosRInterface::~DatosRInterface( void )
			*	\brief		Destructor.
			*	\param		None.
			*	\return		None.
			*/
			virtual ~DatosRInterface();

			/*! \fn			HRESULT DatosRInterface::Init( void )
			*	\brief		Inicializa la dll con las librerias SDL, OpenGL, OpenIL.
			*				\n	y carga las texturas e inicializa las variables de la ventana y escenario (virutal pura).
			*	\param		None.
			*	\return		HRESULT	----------.
			*/
			virtual HRESULT Init( void ) = 0;
			
			/*! \fn			void DatosRInterface::PintaBG( void )
			*	\brief		Pinta en los casos que solo hay Back Ground (virtual pura).	
			*	\param		None.
			*	\return		None.
			*/
			virtual void PintaBG( void ) = 0;

			/*! \fn			void DatosRInterface::Pinta( void )
			*	\brief		Pinta la geometria que tiene que aparecer en pantalla (virtual pura).	
			*	\param		None.
			*	\return		None.
			*/
			virtual void Pinta( void ) = 0;

			/*! \fn			Enemigo DatosRInterface::getEnemigo( int iPos )
			*	\brief		Devuelve el enemigo solicitado	
			*	\param		int iPos	Posición en el vector de enemigos.
			*	\return		Enemigo		Enemigo pedido.
			*/
			Enemigo getEnemigo( int iPos );
			
			/*! \fn			void DatosRInterface::LoadTBG( char *nomT )
			*	\brief		Caraga la textura de BackGround(virtual pura).	
			*	\param		char *nomT.
			*	\return		None.
			*/
			virtual void LoadTBG(char *nomT) = 0;
			
			/*! \fn			void DatosRInterface::addEnem( std::vector < Enemigo > vEnemigos )
			*	\brief		anyade el vector de enemigos a memoria	
			*	\param		std::vector < Enemigo > vEnemigos 	vector de enemigos.
			*	\return		None.
			*/
			void addEnem( std::vector < Enemigo > vEnemigos );
			
			/*! \fn			void DatosRInterface::addNave( int iNave , Nave N )
			*	\brief		anyade la nave a memoria
			*	\param		int iNave , Nave N	nave e indicador.
			*	\return		None.
			*/
			void addNave( int iNave , Nave N );
			
			/*! \fn			void DatosRInterface::addServer( int _Ser)
			*	\brief		anyade la variable Server a memoria	
			*	\param		int _Ser 
			*	\return		None.
			*/
			void addServer( int _Ser ){Server = _Ser;};;
			
			/*! \fn			Nave DatosRInterface::getNave( int iNave )
			*	\brief		devuelve la nave de memoria
			*	\param		int Nave
			*	\return		Nave.
			*/
			Nave getNave( int iNave );
			
			/*! \fn			void DatosRInterface::addSat( std::vector < Satelite > _S )
			*	\brief		anyade el vector Satelites
			*	\param		std::vector < Satelite > _S.
			*	\return		None.
			*/
			void addSat(std::vector < Satelite > _S);
	};

	typedef class DatosRInterface *LPDATOSRINTERFACE;

	/*----------------------------------------------------------------*/
	extern "C" {
		HRESULT CreateRInterface( HINSTANCE hDLL , DatosRInterface **ppDatosRInterface );
		typedef HRESULT( *CREATERINTERFACE)( HINSTANCE hDLL , DatosRInterface **ppDatosRInterface );
	   
		HRESULT ReleaseRInterface( DatosRInterface **ppDatosRInterface );
		typedef HRESULT( *RELEASERINTERFACE)( DatosRInterface **ppDatosRInterface );
	}
	/*----------------------------------------------------------------*/

#endif