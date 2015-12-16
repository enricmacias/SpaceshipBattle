/*! \file		Logica.h
 *	\brief		Dll que gestiona la lógica del juego
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef RENDER_H
#define RENDER_H
	
	//////////////////////////
	/*		INCLUDES		*/
	//////////////////////////
	#include "../DatosL/DatosLInterface.h"
	#include "../DatosL/DatosL.h"

	#include "time.h"
	#include <stdio.h>
	#include <conio.h>
	#include <math.h>

	//////////////////////////
	/*		FUNCIONES		*/
	//////////////////////////
	BOOL WINAPI DllEntryPoint( HINSTANCE hDll , DWORD fdwReason , LPVOID lpvRserved );
	HRESULT CreateLInterface( HINSTANCE hDLL , DatosLInterface **ppDatosLInterface );
	HRESULT ReleaseLInterface( DatosLInterface **ppDatosLInterface );

	//////////////////////
	/*		CLASSE		*/
	//////////////////////
	/*! \class		Lógica
	*	\brief		Gestiona la lógica del juego
	*/
	class Logica : public DatosLInterface
	{
		public:
			/*! \fn			Logica::Logica( void )
			*	\brief		Constructor.
			*	\param		None.
			*	\return		None.
			*/
			Logica( void );

			/*! \fn			Logica::Logica( HINSTANCE hDLL )
			*	\brief		Constructor.	
			*	\param		HINSTANCE hDLL	Para gestionar la instancia de la aplicación.
			*	\return		None.
			*/
			Logica( HINSTANCE hDLL );

			/*! \fn			Logica::~Logica( void )
			*	\brief		Destructor.
			*	\param		None.
			*	\return		None.
			*/
			~Logica();

			/*! \fn			HRESULT Logica::Init( void )
			*	\brief		Inicializa la dll.
			*	\param		None.
			*	\return		HRESULT	----------.
			*/
			HRESULT Init( void );

			/*! \fn			void Logica::Idle( void )
			*	\brief		Trabaja la lógica del juego.	
			*	\param		None.
			*	\return		None.
			*/
			void Idle( int &iDisplay );
			
			/*! \fn			void Logica::InitPos( void )
			*	\brief		Inicializa las posiciones.	
			*	\param		None.
			*	\return		None.
			*/
			void InitPos( void );

			/*! \fn			void Logica::InitPos( void )
			*	\brief		Inicializa las posiciones para que no se solapen los asteroides.	
			*	\param		None.
			*	\return		None.
			*/
			void posiciona(float &x, float &y, float tamanyo, int MaxEscenari);
	};

	typedef class Logica *LPLOGICA;

#endif