/*! \file		Render.h
 *	\brief		Dll que gestiona la geometria que se pinta por pantalla
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef RENDER_H
#define RENDER_H
	
	//////////////////////////
	/*		INCLUDES		*/
	//////////////////////////
	#include "../DatosR/DatosRInterface.h"
	#include "../DatosR/DatosR.h"

	#include <stdio.h>
	#include <conio.h>

	#include <SDL.h>
	#include <SDL_opengl.h>
	#include <IL/il.h>
	#include <IL/ilu.h>
	#include <IL/ilut.h>

	#pragma comment ( lib , "sdl.lib" )
	#pragma comment ( lib , "sdlmain.lib" )

	#pragma comment ( lib , "ilu.lib" )
	#pragma comment ( lib , "ilut.lib" )
	#pragma comment ( lib , "DevIL.lib" )

	//////////////////////////
	/*		FUNCIONES		*/
	//////////////////////////
	BOOL WINAPI DllEntryPoint( HINSTANCE hDll , DWORD fdwReason , LPVOID lpvRserved );
	HRESULT CreateRInterface( HINSTANCE hDLL , DatosRInterface **ppDatosRInterface );
	HRESULT ReleaseRInterface( DatosRInterface **ppDatosRInterface );

	//////////////////////
	/*		CLASSE		*/
	//////////////////////
	/*! \class		Render
	*	\brief		Gestiona la geometria que se pinta por pantalla
	*/
	class Render : public DatosRInterface
	{
		public:
			/*! \fn			Render::Render( void )
			*	\brief		Constructor.
			*	\param		None.
			*	\return		None.
			*/
			Render( void );

			/*! \fn			Render::Render( HINSTANCE hDLL )
			*	\brief		Constructor.	
			*	\param		HINSTANCE hDLL	Para gestionar la instancia de la aplicación.
			*	\return		None.
			*/
			Render( HINSTANCE hDLL );

			/*! \fn			Render::~Render( void )
			*	\brief		Destructor.
			*	\param		None.
			*	\return		None.
			*/
			~Render();

			/*! \fn			HRESULT Render::Init( void )
			*	\brief		Inicializa la dll con las librerias SDL, OpenGL, OpenIL.
			*				\n	y carga las texturas e inicializa las variables de la ventana y escenario.
			*	\param		None.
			*	\return		HRESULT	----------.
			*/
			HRESULT Init( void );

			/*! \fn			int Render::LoadTexture( void )
			*	\brief		Carga una textura.
			*	\param		char *sFileName	Nombre del archivo de la textura.
			*	\return		int	Identificador de textura.
			*/
			int LoadTexture( char *sFileName );

			/*! \fn			bool Render::InitSDL( void )
			*	\brief		Inicializa la libreria SDL.
			*	\param		None.
			*	\return		bool	Booleano de si ha cargado bien o no.
			*/
			bool InitSDL( void );

			/*! \fn			SDL_Surface *Render::InitGL( void )
			*	\brief		Inicializa la libreria OpenGL.
			*	\param		None.
			*	\return		SDL_Surface *	Devuelve si a cargado bien o no.
			*/
			SDL_Surface *InitGL( void );

			/*! \fn			void Render::PintaEnemigo( float fTamaño )
			*	\brief		Pinta a los enemigos	
			*	\param		float fTamaño	Tamaño de los enemigos.
			*	\return		None.
			*/
			void PintaEnemigo( float fTamaño );

			/*! \fn			void Render::PintaNave( int iPlayer )
			*	\brief		Pinta la nave.	
			*	\param		float fTamaño	Número de jugador.
			*	\return		None.
			*/
			void PintaNave( int iPlayer );

			/*! \fn			void Render::PintaBGPintaBG( void )
			*	\brief		Pinta los displays que solo contienen un Back Ground.	
			*	\param		None.
			*	\return		None.
			*/
			void PintaBG( void );

			/*! \fn			void Render::Pinta( void )
			*	\brief		Pinta la geometria que tiene que aparecer en pantalla.	
			*	\param		None.
			*	\return		None.
			*/
			void Pinta( void );
			
			/*! \fn			void Render::LoadTBG( char *nomT )
			*	\brief		Recarga la textura de background, no nos dejava mas memoria i hemos tenido que hacelo así.	
			*	\param		char *nomT.
			*	\return		None.
			*/
			void LoadTBG(char *nomT);
			
			/*! \fn			void Render::PintaSat( float f )
			*	\brief		Pinta los satélites de el modo 1 Player, recive la fuerza para pintar una textura u otra
			*	\param		float f
			*	\return		None.
			*/
			void PintaSat(float f);
			
			/*! \fn			void Render::PintaBala( )
			*	\brief		Pinta los disparos de todos
			*	\param		None.
			*	\return		None.
			*/
			void PintaBala();
			
			/*! \fn			void Render::PintaEscudo( )
			*	\brief		Pinta los escudos de fuerza de todos
			*	\param		None.
			*	\return		None.
			*/
			void PintaEscudo( void );
	};

	typedef class Render *LPRENDER;

#endif