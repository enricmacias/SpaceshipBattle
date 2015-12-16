/*! \file		DatosSInterface.h
 *	\brief		Guarda los objetos de la dll Sonido
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef DATOSSINTERFACE_H
#define DATOSSINTERFACE_H

	#include <vector>
	#include <windows.h>
	#include <stdio.h>
	#include <string>
	#include <conio.h>
	#include <math.h>

	#include "api/inc/fmod.hpp"
	#include "api/inc/fmod_errors.h"

	#pragma comment ( lib , "fmodex_vc.lib" )

	#define    INTERFACE_UPDATETIME    50      // 50ms update for interface
	#define    DISTANCEFACTOR          1.0f    // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.

	/*! \class		DatosSInterface
	*	\brief		Guarda los ojetos de la dll Sonido
	*/
	class DatosSInterface
	{
		protected:

			HINSTANCE						m_hDLL;			/*!< Para gestionar la instancia de la aplicación		*/
			FMOD::System					*gSystem;		/*!< Gestiona el sistema conjunto de FMOD				*/
			std::vector < FMOD::Sound* >	vgSounds;		/*!< Vector que guarda los sonidos						*/
			std::vector < FMOD::Channel* >	vgChannels;		/*!< Vector que guarda los canales						*/
			FMOD_RESULT						gResult;		/*!< Variable de control de errores de FMOD				*/
			int								gNumdrivers;	/*!< Numero de drivers targeta sonido					*/
			unsigned int					gVersion;		/*!< Guarda la version de FMOD que se utiliza			*/
			FMOD_SPEAKERMODE				gSpeakermode;	/*!< Guarda el modo utilizado de altavoz				*/
			FMOD_CAPS						gCaps;			/*!< Caps												*/
			char							gName[256];		/*!< Nombre												*/

		public:

			/*! \fn			DatosSInterface::DatosSInterface( void )
			*	\brief		Constructor.
			*	\param		None.
			*	\return		None.
			*/
			DatosSInterface();

			/*! \fn			DatosSInterface::~DatosSInterface( void )
			*	\brief		Destructor.
			*	\param		None.
			*	\return		None.
			*/
			virtual ~DatosSInterface();

			/*! \fn			HRESULT DatosSInterface::Init( void )
			*	\brief		Inicializa la dll.
			*	\param		None.
			*	\return		HRESULT	----------.
			*/
			virtual HRESULT Init( void ) = 0;

			/*! \fn			void DatosSInterface::LoadSounds( int iDisplay )
			*	\brief		Carga los sonidos de la aplicación.
			*	\param		int iDisplay	Si es 1 cargarà el primer sonido para la carga, si es dos todos los demás.
			*	\return		None.
			*/
			virtual void LoadSounds( int iDisplay ) = 0;

			/*! \fn			void DatosSInterface::Play( int iSonido )
			*	\brief		Pone a play el sonido correspondiente a la variable iSonido.
			*	\param		int iSonido		Determina que sonido reproducir.
			*	\return		None.
			*/
			virtual void Play( int iSonido ) = 0;

			/*! \fn			void DatosSInterface::Suena( void )
			*	\brief		Permite que las canciones no dejen de sonar.
			*	\param		None.
			*	\return		None.
			*/
			virtual void Suena( void ) = 0;

			/*! \fn			void DatosSInterface::DeInit( void )
			*	\brief		Desinicializa la dll.
			*	\param		None.
			*	\return		None.
			*/
			virtual void DeInit( void ) = 0;
	};

	typedef class DatosSInterface *LPDATOSSINTERFACE;

	/*----------------------------------------------------------------*/
	extern "C" {
		HRESULT CreateSInterface( HINSTANCE hDLL , DatosSInterface **ppDatosSInterface );
		typedef HRESULT( *CREATESINTERFACE)( HINSTANCE hDLL , DatosSInterface **ppDatosSInterface );
	   
		HRESULT ReleaseSInterface( DatosSInterface **ppDatosSInterface );
		typedef HRESULT( *RELEASESINTERFACE)( DatosSInterface **ppDatosSInterface );
	}
	/*----------------------------------------------------------------*/

#endif