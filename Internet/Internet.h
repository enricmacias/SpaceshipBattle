/*! \file		Internet.h
 *	\brief		Dll que gestiona la conexión del juego
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef INTERNET_H
#define INTERNET_H
	
	//////////////////////////
	/*		INCLUDES		*/
	//////////////////////////
	#include "../DatosI/eNetInterface.h"
	#include "../DatosI/eNet.h"

	#include <stdio.h>
	#include <stdlib.h>
	#include <conio.h>
	#include <vector>

	//////////////////////////
	/*		FUNCIONES		*/
	//////////////////////////
	BOOL WINAPI DllEntryPoint( HINSTANCE hDll , DWORD fdwReason , LPVOID lpvRserved );
	HRESULT CreateeNetInterface( HINSTANCE hDLL , eNetInterface **ppeNetInterface );
	HRESULT ReleaseeNetInterface( eNetInterface **ppeNetInterface );

	//////////////////////
	/*		CLASSE		*/
	//////////////////////
	/*! \class		Internet
	*	\brief		Gestiona la conexión del juego
	*/
	class Internet : public eNetInterface
	{
		public:
			/*! \fn			Internet::Internet( void )
			*	\brief		Constructor.
			*	\param		None.
			*	\return		None.
			*/
			Internet( void );

			/*! \fn			Internet::Internet( HINSTANCE hDLL )
			*	\brief		Constructor.	
			*	\param		HINSTANCE hDLL	Para gestionar la instancia de la aplicación.
			*	\return		None.
			*/
			Internet( HINSTANCE hDLL );

			/*! \fn			Internet::~Internet( void )
			*	\brief		Destructor.
			*	\param		None.
			*	\return		None.
			*/
			~Internet();

			/*! \fn			HRESULT Internet::Init( void )
			*	\brief		Inicializa la dll.
			*	\param		None.
			*	\return		HRESULT	----------.
			*/
			HRESULT Init( int Server );
			
			/*! \fn			bool Internet::InitServer( void )
			*	\brief		Inicializa la libreria eNet para un server.
			*	\param		None.
			*	\return		bool	Booleano de si se ha hecho bien la inicialización o no.
			*/
			bool InitServer( void );

			/*! \fn			bool Internet::InitClient( void )
			*	\brief		Inicializa la libreria eNet para un client.
			*	\param		None.
			*	\return		bool	Booleano de si se ha hecho bien la inicialización o no.
			*/
			bool InitClient( void );

			/*! \fn			void Internet::deInit( int Server )
			*	\brief		Desinicializa la libreria eNet según la variable Server.
			*	\param		int Server Indica si se tiene que ejecutar código de server(1) o de client(2).
			*	\return		None.
			*/
			void deInit( int Server );

			/*! \fn			void Internet::Comm( int Server )
			*	\brief		Gestiona la comunicación entre un server i un client.
			*	\param		None.
			*	\return		int Server Indica si se tiene que ejecutar código de server(1) o de client(2).
			*/
			void Comm( int Server );

			/*! \fn			void Internet::CreuaEnem( void )
			*	\brief		Genera un vector de enemigos que contiene la información de los dos lados (server i client).
			*	\param		None.
			*	\return		None.
			*/
			void CreuaEnem( void  );

			/*! \fn			void Internet::ServerSend( void )
			*	\brief		Función que envía el paquete con información al client.
			*	\param		None.
			*	\return		None.
			*/
			void ServerSend( void );

			/*! \fn			void Internet::ServerClient( void )
			*	\brief		Función que envía el paquete con información al server.
			*	\param		None.
			*	\return		None.
			*/
			void ClientSend( void );

			/*! \fn			void Internet::ServerReceive( void )
			*	\brief		Función que recive el paquete de información del client.
			*	\param		ENetEvent event	Variable que contiene información sobre el paquete recibido.
			*	\return		None.
			*/
			void ServerReceive( ENetEvent event );

			/*! \fn			void Internet::ClientReceive( void )
			*	\brief		Función que recive el paquete de información del client.
			*	\param		ENetEvent event	Variable que contiene información sobre el paquete recibido.
			*	\return		None.
			*/
			void ClientReceive( ENetEvent event );

			/*! \fn			void Internet::ExtraeEnemigos( char* aux )
			*	\brief		Extrae la información de los enemigos.
			*	\param		char* aux	Cadena que contiene la información a desfragmentar.
			*	\return		None.
			*/
			void ExtraeEnemigos( char* aux );

			/*! \fn			void Internet::ExtraeNave( char* aux )
			*	\brief		Extrae la información de la nave.
			*	\param		char* aux	Cadena que contiene la información a desfragmentar.
			*	\return		None.
			*/
			void ExtraeNave( char* aux );
	};

	typedef class Internet *LPINTERNET;

#endif