/*! \file		Eventos.h
 *	\brief		Dll que gestiona las órdenes entradas por teclado o ratón
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef EVENTOS_H
#define EVENTOS_H

	//////////////////////////
	/*		INCLUDES		*/
	//////////////////////////
	#include "../DatosE/DatosEInterface.h"
	#include "../DatosE/DatosE.h"

	#include <stdio.h>
	#include <conio.h>

	#include <SDL.h>
	#include <SDL_opengl.h>

	#pragma comment ( lib , "sdl.lib" )
	#pragma comment ( lib , "sdlmain.lib" )

	//////////////////////////
	/*		FUNCIONES		*/
	//////////////////////////
	BOOL WINAPI DllEntryPoint( HINSTANCE hDll , DWORD fdwReason , LPVOID lpvRserved );
	HRESULT CreateEInterface( HINSTANCE hDLL , DatosEInterface **ppDatosEInterface );
	HRESULT ReleaseEInterface( DatosEInterface **ppDatosEInterface );

	//////////////////////
	/*		CLASSE		*/
	//////////////////////
	/*! \class		Eventos
	*	\brief		Gestiona las órdenes entradas por teclado o ratón
	*/
	class Eventos : public DatosEInterface
	{
		public:
			/*! \fn			Eventos::Eventos( void )
			*	\brief		Constructor.
			*	\param		None.
			*	\return		None.
			*/
			Eventos();

			/*! \fn			Eventos::Eventos( HINSTANCE hDLL )
			*	\brief		Constructor.	
			*	\param		HINSTANCE hDLL	Para gestionar la instancia de la aplicación.
			*	\return		None.
			*/
			Eventos( HINSTANCE hDLL );

			/*! \fn			Eventos::~Eventos( void )
			*	\brief		Destructor.
			*	\param		None.
			*	\return		None.
			*/
			~Eventos();

			/*! \fn			HRESULT Eventos::Init( void )
			*	\brief		Inicializa la dll con la libreria SDL.
			*	\param		None.
			*	\return		HRESULT	----------.
			*/
			HRESULT Init( void );

			/*! \fn			bool Render::InitSDL( void )
			*	\brief		Inicializa la libreria SDL.
			*	\param		None.
			*	\return		bool	Booleano de si ha cargado bien o no.
			*/
			bool InitSDL( void );

			/*! \fn			void Eventos::Detecta( void )
			*	\brief		Detecta los eventos que se entran por teclado o ratón.	
			*	\param		None.
			*	\return		bool	Devuelve si tiene que salir del programa o no (bOk, bDone).
			*/
			bool Detecta( int &iDisplay , int& Server );

			/*! \fn			void Eventos::InitNave( void )
			*	\brief		Inicializa la nave en su posición inicial con los parametros correspondientes.	
			*	\param		None.
			*	\return		None.
			*/
			void InitNave( void );

			/*! \fn			Vector2D Eventos::MousePos( void )
			*	\brief		Gestiona la posición del ratón para devolver su posición en la pantalla de juego.	
			*	\param		None.
			*	\return		Vector2D	Posicíón que indica el sitio donde se encuentra el ratón en la pantalla de juego.
			*/
			Vector2D MousePos( void );
	};

	typedef class Eventos *LPEVENTOS;

#endif