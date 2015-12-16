/*! \file		DatosEInterface.h
 *	\brief		Guarda los objetos de la dll Eventos
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef DATOSEINTERFACE_H
#define DATOSEINTERFACE_H

	#include <vector>
	#include <windows.h>
	#include <stdio.h>
	#include <string>
	
	#include "../DatosR/Nave.h"
	#include <glut.h>

	#pragma comment ( lib , "opengl32.lib" )
	#pragma comment ( lib , "glu32.lib" )
	#pragma comment ( lib , "glut32.lib" )

	/*! \class		DatosEInterface
	*	\brief		Guarda los ojetos de la dll Eventos
	*/
	class DatosEInterface
	{
		protected:

		HINSTANCE						m_hDLL;			/*!< Para gestionar la instancia de la aplicación		*/
		Nave							N;				/*!< Nave , Jugador 	*/
		int								Server;
		
		public:

			/*! \fn			DatosEInterface::DatosEInterface( void )
			*	\brief		Constructor.
			*	\param		None.
			*	\return		None.
			*/
			DatosEInterface();

			/*! \fn			DatosEInterface::~DatosEInterface( void )
			*	\brief		Destructor.
			*	\param		None.
			*	\return		None.
			*/
			virtual ~DatosEInterface();

			/*! \fn			HRESULT DatosEInterface::Init( void )
			*	\brief		Inicializa la dll con las librerias SDL, OpenGL, OpenIL.
			*				\n	y carga las texturas e inicializa las variables de la ventana y escenario (virutal pura).
			*	\param		None.
			*	\return		HRESULT	----------.
			*/
			virtual HRESULT Init( void ) = 0;

			/*! \fn			void DatosEInterface::Detecta( void )
			*	\brief		Detecta los eventos que se entran por teclado o ratón.	
			*	\param		None.
			*	\return		None.
			*/
			virtual bool Detecta( int &iDisplay , int& Server ) = 0;

			/*! \fn			void DatosEInterface::InitNave( void )
			*	\brief		Inicializa la nave en su posición inicial con los parametros correspondientes.	
			*	\param		None.
			*	\return		None.
			*/
			virtual void InitNave( void ) = 0;

			/*! \fn			void DatosEInterface::updateFuerza( void )
			*	\brief		Actualiza la fuerza que se le aplica a la nave con la tecla espacio.	
			*	\param		None.
			*	\return		None.
			*/
			void updateFuerza( bool bFuerza );

			/*! \fn			void DatosEInterface::addNave( Nave _N )
			*	\brief		Añade una nave en la libreria de la DLL.	
			*	\param		Nave _N Nave a añadir.
			*	\return		None.
			*/
			void addNave( Nave _N );

			/*! \fn			void DatosEInterface::getNave( void )
			*	\brief		Permite sacar la nave que contiene la DLL.	
			*	\param		None.
			*	\return		Nave	Devuelve la nave pedida.
			*/
			Nave getNave( void );

	};

	typedef class DatosEInterface *LPDATOSEINTERFACE;

	/*----------------------------------------------------------------*/
	extern "C" {
		HRESULT CreateEInterface( HINSTANCE hDLL , DatosEInterface **ppDatosEInterface );
		typedef HRESULT( *CREATEEINTERFACE)( HINSTANCE hDLL , DatosEInterface **ppDatosEInterface );
	   
		HRESULT ReleaseEInterface( DatosEInterface **ppDatosEInterface );
		typedef HRESULT( *RELEASEEINTERFACE)( DatosEInterface **ppDatosEInterface );
	}
	/*----------------------------------------------------------------*/

#endif