/*! \file		eNetInterface.h
 *	\brief		Guarda los objetos de la dll Internet
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef ENETINTERFACE_H
#define ENETINTERFACE_H
	
	#include <stdio.h>
	#include <stdlib.h>

	#include <conio.h>
	#include <vector>
	
	#include "../DatosR/Nave.h"
	#include "../DatosR/Enemigo.h"
	#include "../DatosR/Satelite.h"

	#include <enet/enet.h>
	#pragma comment ( lib , "eNetProject.lib" )
	#pragma comment ( lib , "ws2_32.lib" )
	#pragma comment ( lib , "WINMM.lib" )
	
	/*! \class		eNetInterface
	*	\brief		Guarda los ojetos de la dll Internet
	*/
	class eNetInterface
	{
		protected:
	
		HINSTANCE						m_hDLL;				/*!< Para gestionar la instancia de la aplicación		*/
		char							acPort[ 256 ];		/*!< Cadena con la información del puerto				*/
		char							acAddress[ 256 ];	/*!< Cadena con la información de la direcciónIP		*/
		ENetPeer						*pPeer;				/*!< Cliente al que se esta conectado					*/
		ENetHost						*pServer_Client;	/*!< Host al que se está conectado						*/
		ENetEvent						event;				/*!< Detecta los eventos que se dan en el envio			*/
		std::vector < Enemigo >			m_iEnemigosOut;		/*!< Vector de enemigos saliente, para enviar			*/
		std::vector < Enemigo >			m_iEnemigosIn;		/*!< Vector de enemigos entrante, recibidos				*/
		std::vector < Satelite >		m_iSateliteOut;		/*!< Vector de satelites saliente, para enviar			*/
		std::vector < Satelite >		m_iSateliteIn;		/*!< Vector de satelites entrante, recibidos			*/
		Nave							NOut, NIn;			/*!< Naves, NOut para enviar, NIn la recibida			*/

		public:

			/*! \fn			eNetInterface::eNetInterface( void )
			*	\brief		Constructor.
			*	\param		None.
			*	\return		None.
			*/
			eNetInterface();

			/*! \fn			eNetInterface::~eNetInterface( void )
			*	\brief		Destructor.
			*	\param		None.
			*	\return		None.
			*/
			virtual ~eNetInterface();

			/*! \fn			HRESULT eNetInterface::Init( void )
			*	\brief		Inicializa la dll con la libreria eNet.
			*	\param		None.
			*	\return		HRESULT	----------.
			*/
			virtual HRESULT Init( int Server ) = 0;

			/*! \fn			void eNetInterface::deInit( int Server )
			*	\brief		Desinicializa la libreria eNet según la variable Server.
			*	\param		int Server Indica si se tiene que ejecutar código de server(1) o de client(2).
			*	\return		None.
			*/
			virtual void deInit( int Server ) = 0;
			
			/*! \fn			void eNetInterface::Comm( int Server )
			*	\brief		Gestiona la comunicación entre un server i un client.
			*	\param		None.
			*	\return		int Server Indica si se tiene que ejecutar código de server(1) o de client(2).
			*/
			virtual void Comm( int Server ) = 0;

			/*! \fn			void eNetInterface::addEnem( std::vector < Enemigo > EnemigosOut )
			*	\brief		Añade los enemigos en la libreria de la DLL.	
			*	\param		std::vector < Enemigo > EnemigosOut	Vector a inserir para enviarlos.
			*	\return		None.
			*/
			void addEnem( std::vector < Enemigo > EnemigosOut );

			/*! \fn			void eNetInterface::addSat( std::vector < Satelite > SateliteOut )
			*	\brief		Añade los satélites en la libreria de la DLL para enviarlos.	
			*	\param		std::vector < Satelite > SateliteOut	Vector a inserir.
			*	\return		None.
			*/
			void addSat( std::vector < Satelite > SateliteOut  );

			/*! \fn			std::vector < Enemigo > EnemigosOut eNetInterface::addEnem( void )
			*	\brief		Devuelve los enemigos llegados del otro cliente de la DLL.	
			*	\param		None.
			*	\return		std::vector < Enemigo > EnemigosOut	Vector pedido.
			*/
			std::vector < Enemigo > getEnem( void );

			/*! \fn			void eNetInterface::getNave( void )
			*	\brief		Permite sacar la nave que contiene la DLL.	
			*	\param		None.
			*	\return		Nave	Devuelve la nave pedida.
			*/
			Nave getNave( void ) { return NIn; };

			/*! \fn			std::vector < Satelite > SateliteOut eNetInterface::addSat( void )
			*	\brief		Devuelve los satelites llegados del otro cliente de la DLL.
			*	\param		None.
			*	\return		std::vector < Satelite > SateliteOut	Vector pedido.
			*/
			std::vector < Satelite > getSat( void ) { return m_iSateliteIn; }

			/*! \fn			void eNetInterface::addNave( Nave _N )
			*	\brief		Añade una nave en la libreria de la DLL.	
			*	\param		Nave _N Nave a añadir.
			*	\return		None.
			*/
			void addNave( Nave _N ) { NOut = _N; };
	};

	typedef class eNetInterface *LPENETINTERFACE;

	/*----------------------------------------------------------------*/
	extern "C" {
		HRESULT CreateeNetInterface( HINSTANCE hDLL , eNetInterface **ppeNetInterface );
		typedef HRESULT( *CREATEENETINTERFACE)( HINSTANCE hDLL , eNetInterface **ppeNetInterface );
	   
		HRESULT ReleaseeNetInterface( eNetInterface **ppeNetInterface );
		typedef HRESULT( *RELEASEENETINTERFACE)( eNetInterface **ppeNetInterface );
	}
	/*----------------------------------------------------------------*/

#endif