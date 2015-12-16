/*! \file		Internet.cpp
 *	\brief		Dll que gestiona la conexión del juego
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/
#include "Internet.h"

BOOL WINAPI DllEntryPoint( HINSTANCE hDll, DWORD fdwReason, LPVOID lpvReserved )
{
	switch( fdwReason )
	{
		// called when we attach to the DLL
		case DLL_PROCESS_ATTACH:
			/* dll init/setup stuff */
		break;

		case DLL_PROCESS_DETACH:
			/* dll shutdown/release stuff */
		break;

		default:
		break;
	}
   
	return TRUE;
}

HRESULT CreateeNetInterface( HINSTANCE hDLL , eNetInterface **ppeNetInterface )
{
	if( !*ppeNetInterface )
	{
		*ppeNetInterface = new Internet( hDLL );
		return TRUE;
	}
	return !TRUE;
}

HRESULT ReleaseeNetInterface( eNetInterface **ppeNetInterface )
{
	if( !*ppeNetInterface )
	{
		return !TRUE;
	}
	delete *ppeNetInterface;
	*ppeNetInterface = NULL;
	return TRUE;
}

Internet::Internet()
{
}
			
Internet::Internet( HINSTANCE hDLL )
{
	m_hDLL = hDLL;
}
			
Internet::~Internet()
{
}

bool Internet::InitServer( void )
{
	// Creación del Server
	bool OK=true;
	ENetAddress Address;
	Address.host = ENET_HOST_ANY;

	printf( "Port de connexio: " );
	gets( acPort );
	if( acPort[ 0 ] != 0 )
	{
	    Address.port = atoi( acPort );
	}
	else
	{
	    Address.port = 1234;
	}

    pServer_Client = enet_host_create( &Address , 1 , 0 , 0 );

    if( pServer_Client == NULL )
    {
        printf( "[Error   ] An error occurred while trying to create an ENet server host.\n" );
        OK = false;
	}
	else
	{
		bool connectat = false;
		printf("Esperando cliente...\n");
		while( !connectat )
		{
			enet_host_service( pServer_Client , &event , 1000 );
			if(event.type == ENET_EVENT_TYPE_CONNECT)
			{
				printf( "Cliente conectado\n" , event.peer->address.host, event.peer->address.port );
				event.peer->data = "Client information";
				pPeer = event.peer;
				connectat = true;
			}
		}

		char aux[100];
		char Info[2048];

		int i=0;
		strcpy( Info , "" );
		for( int iEnem=0;iEnem< m_iEnemigosOut.size();iEnem++)
		{
			strcat( Info , itoa(m_iEnemigosOut[iEnem].getPosX() * 1000,aux,10));
			strcat( Info , "@" );
			strcat( Info , itoa(m_iEnemigosOut[iEnem].getPosY() * 1000,aux,10));
			strcat( Info , "@" );
			strcat( Info , itoa(m_iEnemigosOut[iEnem].getRot() * 1000,aux,10));
			strcat( Info , "@" );
			strcat( Info , itoa(m_iEnemigosOut[iEnem].getTamaño() * 1000,aux,10));
			strcat( Info , "@" );
			strcat( Info , itoa(m_iEnemigosOut[iEnem].getVisible() * 1000,aux,10));
			strcat( Info , "#" );
		}

		ENetPacket *pPacket = enet_packet_create( Info , strlen( Info ) + 1 , ENET_PACKET_FLAG_RELIABLE );	
		enet_peer_send( pPeer , 0 , pPacket );
	}
	return OK;
}

bool Internet::InitClient( void )
{
	//Crear un cliente

	bool OK=true;
    pServer_Client = enet_host_create( NULL , 1 , 57600 / 8 , 14400 / 8 );

    if( pServer_Client == NULL )
    {
        printf( "[Error   ] An error occurred while trying to create an ENet client host.\n" );
        OK = false;
    }
	else
	{
		//Conectar al Server
		ENetAddress Address;

		/* Connect to some.server.net:1234. */
		printf( "Direccio IP: " );
		gets( acAddress );
		if( acAddress[ 0 ] != 0 )
		{
			enet_address_set_host( &Address, acAddress );
		}
		else
		{
			enet_address_set_host( &Address, "127.0.0.1" );
		}

		printf( "Port de connexio: " );
		gets( acPort );
		if( acPort[ 0 ] != 0 )
		{
			Address.port = atoi( acPort );
		}
		else
		{
			Address.port = 1234;
		}

		
		/* Initiate the connection, allocating the two channels 0 and 1. */
		pPeer = enet_host_connect( pServer_Client , &Address , 2 );    
	    
		if( pPeer == NULL )
		{
			printf( "[Error   ] No available peers for initiating an ENet connection.\n" );
			OK = false;
		}
	    
		/* Wait up to 5 seconds for the connection attempt to succeed. */
		if( enet_host_service( pServer_Client , &event , 5000 ) > 0 && event.type == ENET_EVENT_TYPE_CONNECT )
		{
			printf( "[System  ] Connection to %s:%s succeeded.\n" , acAddress , acPort );
		}
		else
		{
			enet_peer_reset( pPeer );

			printf( "Connection to %s:%s failed.\n" , acAddress , acPort );
		}              
		
		bool connectat = false;
		char *aux, *aux2, *value;
		char* enem[40];
		int i=0;

		while( !connectat )
		{
			enet_host_service( pServer_Client , &event , 1000 );
			if(event.type == ENET_EVENT_TYPE_RECEIVE)
			{
				aux = (char*) event.packet->data;
				aux2 = strtok( aux , "#" );
				while( aux2!=NULL )
				{
					enem[i] = aux2;
					aux2 = strtok( NULL , "#" );
					i++;
				}

				for(int j=0;j<i;j++)
				{
					Enemigo e;
					value = strtok( enem[j] , "@" );
					e.setPosX( (atoi(value)/1000) );
					value = strtok( NULL , "@" );
					e.setPosY( (atoi(value)/1000) );
					value = strtok( NULL , "@" );
					e.setRot( (atoi(value)/1000) );
					value = strtok( NULL , "@" );
					e.setTamaño( (atoi(value)/1000) );
					value = strtok( NULL , "@" );
					e.setVisible( (atoi(value)/1000) );
					value = strtok( NULL , "@" );

					m_iEnemigosIn.push_back( e );
				}				
				enet_packet_destroy( event.packet );
				connectat = true;
			}
		}
	}
	return OK;
}
			
HRESULT Internet::Init( int Server )
{
	bool OK;

	// Inicialiciación de eNet
	if( enet_initialize() != 0 )
	{
		printf( "[Error   ] An error occurred while initializing ENet.\n" );
		return EXIT_FAILURE;
	}

	switch ( Server )
	{
		case 1: OK = InitServer();
			break;
		case 2: OK = InitClient();
			break;
	}
	return OK;
}

void Internet::ServerSend()
{
	char aux[100];
	char Info[2048];

	strcpy( Info , "" );
	for( int iEnem=0;iEnem< m_iEnemigosOut.size();iEnem++)
	{
		strcat( Info , itoa(m_iEnemigosOut[iEnem].getVisible() * 1000,aux,10));
		strcat( Info , "#" );
	}
	strcat( Info , "%" );
	strcat( Info , itoa( NOut.getPosX() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getPosY() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getRot() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getVisible() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getInmune() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getBala().getPosX() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getBala().getPosY() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getBala().getRot() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getBala().getVisible() * 1000,aux,10));
	strcat( Info , "%" );

	ENetPacket *pPacket = enet_packet_create( Info , strlen( Info ) + 1 , ENET_PACKET_FLAG_RELIABLE );	
	enet_peer_send( pPeer , 0 , pPacket );
}

void Internet::ClientSend()
{
	char aux[100];
	char Info[2048];

	strcpy( Info , "" );
	printf("------------------> %d\n", m_iEnemigosOut.size());
	for( int iEnem=0;iEnem< m_iEnemigosOut.size();iEnem++)
	{
		strcat( Info , itoa(m_iEnemigosOut[iEnem].getVisible() * 1000,aux,10));
		strcat( Info , "#" );
	}
	strcat( Info , "%" );

	strcat( Info , itoa( NOut.getPosX() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getPosY() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getRot() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getVisible() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getInmune() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getBala().getPosX() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getBala().getPosY() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getBala().getRot() * 1000,aux,10));
	strcat( Info , "@" );
	strcat( Info , itoa( NOut.getBala().getVisible() * 1000,aux,10));
	strcat( Info , "%" );

	ENetPacket *pPacket = enet_packet_create( Info , strlen( Info ) + 1 , ENET_PACKET_FLAG_RELIABLE );	
	enet_peer_send( pPeer , 0 , pPacket );

	printf("Envio enem: %s", Info);
}

void Internet::ExtraeEnemigos( char* aux )
{
	char *aux2, *value, *enem[40];
	int i=0;
	std::vector < Enemigo > m_iEnemAux;

	aux2 = strtok( aux , "#" );
	while( aux2!=NULL )
	{
		enem[i] = aux2;
		aux2 = strtok( NULL , "#" );
		printf( "cadena de asteroides: %s\n" , enem[i] );
		i++;
	}
	for(int j=0;j<i;j++)
	{
		Enemigo e;
		value = strtok( enem[j] , "@" );
		e.setVisible( (atoi(value)/1000) );
		value = strtok( NULL , "@" );

		m_iEnemAux.push_back( e );
	}
	for(int j=0;j<i;j++)
	{
		m_iEnemigosIn[j].setVisible( m_iEnemAux[j].getVisible());
	}
	
	//CreuaEnem();
}

void Internet::ExtraeNave( char* aux )
{
	char* value;

	value = strtok( aux , "@" );
	NIn.setPosX( (atoi(value)/1000) );
	value = strtok( NULL , "@" );
	NIn.setPosY( (atoi(value)/1000) );
	value = strtok( NULL , "@" );
	NIn.setRot( (atoi(value)/1000) );
	value = strtok( NULL , "@" );
	NIn.setVisible( (atoi(value)/1000) );
	value = strtok( NULL , "@" );
	NIn.setInmune( (atoi(value)/1000) );
	value = strtok( NULL , "@" );
	NIn.getBala().setPosX( (atoi(value)/1000) );
	value = strtok( NULL , "@" );
	NIn.getBala().setPosY( (atoi(value)/1000) );
	value = strtok( NULL , "@" );
	NIn.getBala().setRot( (atoi(value)/1000) );
	value = strtok( NULL , "@" );
	NIn.getBala().setVisible( (atoi(value)/1000) );
	value = strtok( NULL , "@" );
}

void Internet::ServerReceive(ENetEvent event)
{
	char *aux, *aux2, *value;
	char *objecte[5], *enem[40], *sat[40];
	int i=0, j;
	std::vector < Enemigo > m_iEnemigosAux;

	aux = (char*) event.packet->data;
	aux2 = strtok( aux , "%" );
	while( aux2!=NULL )
	{
		objecte[i] = aux2;
		aux2 = strtok( NULL , "%" );
		i++;
	}
	
	//Extracción enemigos
	j=0;
	aux2 = strtok( objecte[0] , "#" );
	while( aux2!=NULL )
	{
		enem[j] = aux2;
		aux2 = strtok( NULL , "#" );
		j++;
	}
	for(int k=0;k<j;k++)
	{
		Enemigo e;
		value = strtok( enem[k] , "@" );
		e.setVisible( (atoi(value)/1000) );
		value = strtok( NULL , "@" );

		m_iEnemigosAux.push_back( e );
	}
	for(int k=0;k<j;k++)
	{
		m_iEnemigosIn[k].setVisible( m_iEnemigosAux[k].getVisible());
	}
	
	//CreuaEnem();

	ExtraeNave( objecte[1] );
}

void Internet::ClientReceive(ENetEvent event)
{
	char *aux, *aux2;
	char *objecte[5];
	int i=0, j=0;

	aux = (char*) event.packet->data;
	aux2 = strtok( aux , "%" );
	while( aux2!=NULL )
	{
		objecte[i] = aux2;
		
		aux2 = strtok( NULL , "%" );
		i++;

	}

	ExtraeEnemigos( objecte[0] );
	ExtraeNave( objecte[1] );
}

void Internet::CreuaEnem( void  )
{
	for( int i=0 ; i < m_iEnemigosOut.size() ; i++ )
	{
		if (m_iEnemigosIn[ i ].getVisible() && m_iEnemigosOut[ i ].getVisible())
		{
			m_iEnemigosOut[ i ] = m_iEnemigosIn[ i ];
		}
		else
		{
			m_iEnemigosOut[ i ].setVisible(false);
		}
	}
}

void Internet::Comm(int Server)
{	
	while( enet_host_service( pServer_Client , &event , 200 )> 0)
	{
		if( Server == 1 )
			ServerSend();
		else
			ClientSend();
		
		switch( event.type )
		{
			case ENET_EVENT_TYPE_RECEIVE:
				if( Server == 1 )
					ServerReceive(event);
				else
					ClientReceive(event);
				
				enet_packet_destroy( event.packet );
				break;
				
	       
			case ENET_EVENT_TYPE_DISCONNECT:
				printf( "Client desconnectat\n", event.peer->data );

				/* Reset the peer's client information. */
				event.peer->data = NULL;
		}
		
	}
}

void Internet::deInit( int Server )
{
	switch( Server )
	{
		case 1: enet_host_destroy( pServer_Client );
			enet_deinitialize();
			break;
		case 2:enet_deinitialize();
			break;
	}
}
