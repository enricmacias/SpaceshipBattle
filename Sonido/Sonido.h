/*! \file		Sonido.h
 *	\brief		Dll que gestiona el sonido del juego
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef RENDER_H
#define RENDER_H
	
	//////////////////////////
	/*		INCLUDES		*/
	//////////////////////////
	#include "../DatosS/DatosSInterface.h"
	#include "../DatosS/DatosS.h"

	#include "time.h"
	#include <stdio.h>
	#include <conio.h>
	#include <math.h>

	//////////////////////////
	/*		FUNCIONES		*/
	//////////////////////////
	BOOL WINAPI DllEntryPoint( HINSTANCE hDll , DWORD fdwReason , LPVOID lpvRserved );
	HRESULT CreateSInterface( HINSTANCE hDLL , DatosSInterface **ppDatosSInterface );
	HRESULT ReleaseSInterface( DatosSInterface **ppDatosSInterface );

	//////////////////////
	/*		CLASSE		*/
	//////////////////////
	/*! \class		Sonido
	*	\brief		Gestiona el sonido del juego
	*/
	class Sonido : public DatosSInterface
	{
		public:
			/*! \fn			Sonido::Sonido( void )
			*	\brief		Constructor.
			*	\param		None.
			*	\return		None.
			*/
			Sonido( void );

			/*! \fn			Sonido::Sonido( HINSTANCE hDLL )
			*	\brief		Constructor.	
			*	\param		HINSTANCE hDLL	Para gestionar la instancia de la aplicación.
			*	\return		None.
			*/
			Sonido( HINSTANCE hDLL );

			/*! \fn			Sonido::~Sonido( void )
			*	\brief		Destructor.
			*	\param		None.
			*	\return		None.
			*/
			~Sonido();

			/*! \fn			void DatosSInterface::ERRCHECK(FMOD_RESULT gResult)
			*	\brief		Comprueba que toda la ejecución no de ningún error.
			*	\param		FMOD_RESULT gResult		Si se produce error esta variable ser verà afectada.
			*	\return		None.
			*/
			void ERRCHECK(FMOD_RESULT gResult);

			/*! \fn			HRESULT Sonido::Init( void )
			*	\brief		Inicializa la dll.
			*	\param		None.
			*	\return		HRESULT	----------.
			*/
			HRESULT Init( void );

			/*! \fn			void DatosSInterface::LoadSounds( int iDisplay )
			*	\brief		Carga los sonidos de la aplicación.
			*	\param		int iDisplay	Si es 1 cargarà el primer sonido para la carga, si es dos todos los demás.
			*	\return		None.
			*/
			void LoadSounds( int iDisplay );

			/*! \fn			void DatosSInterface::Play( int iSonido )
			*	\brief		Pone a play el sonido correspondiente a la variable iSonido.
			*	\param		int iSonido		Determina que sonido reproducir.
			*	\return		None.
			*/
			void Play( int iSonido );

			/*! \fn			void DatosSInterface::Suena( void )
			*	\brief		Permite que las canciones no dejen de sonar.
			*	\param		None.
			*	\return		None.
			*/
			void Suena( void );

			/*! \fn			void DatosSInterface::DeInit( void )
			*	\brief		Desinicializa la dll.
			*	\param		None.
			*	\return		None.
			*/
			void DeInit( void );
	};

	typedef class Sonido *LPSONIDO;

#endif