/*! \file		Internet.h
 *	\brief		Dll que gestiona la conexi�n del juego
 *  \version	1.0
 *  \author		Enric Mac�as L�pez <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
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
	*	\brief		Gestiona la conexi�n del juego
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
			*	\param		HINSTANCE hDLL	Para gestionar la instancia de la aplicaci�n.
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
			*	\return		bool	Booleano de si se ha hecho bien la inicializaci�n o no.
			*/
			bool InitServer( void );

			/*! \fn			bool Internet::InitClient( void )
			*	\brief		Inicializa la libreria eNet para un client.
			*	\param		None.
			*	\return		bool	Booleano de si se ha hecho bien la inicializaci�n o no.
			*/
			bool InitClient( void );

			/*! \fn			void Internet::deInit( int Server )
			*	\brief		Desinicializa la libreria eNet seg�n la variable Server.
			*	\param		int Server Indica si se tiene que ejecutar c�digo de server(1) o de client(2).
			*	\return		None.
			*/
			void deInit( int Server );

			/*! \fn			void Internet::Comm( int Server )
			*	\brief		Gestiona la comunicaci�n entre un server i un client.
			*	\param		None.
			*	\return		int Server Indica si se tiene que ejecutar c�digo de server(1) o de client(2).
			*/
			void Comm( int Server );

			/*! \fn			void Internet::CreuaEnem( void )
			*	\brief		Genera un vector de enemigos que contiene la informaci�n de los dos lados (server i client).
			*	\param		None.
			*	\return		None.
			*/
			void CreuaEnem( void  );

			/*! \fn			void Internet::ServerSend( void )
			*	\brief		Funci�n que env�a el paquete con informaci�n al client.
			*	\param		None.
			*	\return		None.
			*/
			void ServerSend( void );

			/*! \fn			void Internet::ServerClient( void )
			*	\brief		Funci�n que env�a el paquete con informaci�n al server.
			*	\param		None.
			*	\return		None.
			*/
			void ClientSend( void );

			/*! \fn			void Internet::ServerReceive( void )
			*	\brief		Funci�n que recive el paquete de informaci�n del client.
			*	\param		ENetEvent event	Variable que contiene informaci�n sobre el paquete recibido.
			*	\return		None.
			*/
			void ServerReceive( ENetEvent event );

			/*! \fn			void Internet::ClientReceive( void )
			*	\brief		Funci�n que recive el paquete de informaci�n del client.
			*	\param		ENetEvent event	Variable que contiene informaci�n sobre el paquete recibido.
			*	\return		None.
			*/
			void ClientReceive( ENetEvent event );

			/*! \fn			void Internet::ExtraeEnemigos( char* aux )
			*	\brief		Extrae la informaci�n de los enemigos.
			*	\param		char* aux	Cadena que contiene la informaci�n a desfragmentar.
			*	\return		None.
			*/
			void ExtraeEnemigos( char* aux );

			/*! \fn			void Internet::ExtraeNave( char* aux )
			*	\brief		Extrae la informaci�n de la nave.
			*	\param		char* aux	Cadena que contiene la informaci�n a desfragmentar.
			*	\return		None.
			*/
			void ExtraeNave( char* aux );
	};

	typedef class Internet *LPINTERNET;

#endif