#include "C_AppMain.h"

int main( int iArgCounter , char **ppArgValues )
{
	char acPort[ 256 ] , acAddress[ 256 ];

	// Initialize
	// ----------------------------------------------------------------------------------
	if( enet_initialize() != 0 )
	{
		printf( "[Error   ] An error occurred while initializing ENet.\n" );
		return EXIT_FAILURE;
	}

	// Create a client
	// ----------------------------------------------------------------------------------
	ENetHost *pClient;

    pClient = enet_host_create( NULL		/* create a client host */,
								1			/* only allow 1 outgoing connection */,
								57600 / 8	/* 56K modem with 56 Kbps downstream bandwidth */,
								14400 / 8	/* 56K modem with 14 Kbps upstream bandwidth */);

    if( pClient == NULL )
    {
        printf( "[Error   ] An error occurred while trying to create an ENet client host.\n" );
        exit( EXIT_FAILURE );
    }


	// Connect to the server
	// ----------------------------------------------------------------------------------
    ENetEvent event;
    ENetPeer *pPeer;
	ENetAddress Address;

    /* Connect to some.server.net:1234. */
	printf( "[Question] Type the address to connect to: " );
	gets( acAddress );
	if( acAddress[ 0 ] != 0 )
	{
		enet_address_set_host( &Address, acAddress );
	}
	else
	{
		enet_address_set_host( &Address, "127.0.0.1" );
	}

	printf( "[Question] Type the port to connect to: " );
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
    pPeer = enet_host_connect( pClient , &Address , 2 );    
    
    if( pPeer == NULL )
    {
       printf( "[Error   ] No available peers for initiating an ENet connection.\n" );
       exit( EXIT_FAILURE );
    }
    
    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if( enet_host_service( pClient , &event , 5000 ) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT )
    {
		printf( "[System  ] Connection to %s:%s succeeded.\n" , acAddress , acPort );
    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset( pPeer );

		printf( "Connection to %s:%s failed.\n" , acAddress , acPort );
    }

	printf( "[Commands] [quit]: Exits   Any other to chat\n" );

	bool bEnd = false;
	// Manage events
	// ----------------------------------------------------------------------------------
	while( !bEnd )
	{
		if( kbhit() )
		{
			char asMessage[ 2048 ];
			// Send message to the server
			// ----------------------------------------------------------------------------------
			gets( asMessage );

			if( strcmp( asMessage , "quit" ) == 0 )
			{
				enet_peer_disconnect( &pClient->peers[ 0 ] , 0 );
				bEnd = true;
			}
			else
			{
				/* Create a reliable packet of size 7 containing "packet\0" */
				ENetPacket *pPacket = enet_packet_create( asMessage , strlen( asMessage ) + 1 , ENET_PACKET_FLAG_RELIABLE );

				/* Send the packet to the peer over channel id 3. */
				/* One could also broadcast the packet by         */
				/* enet_host_broadcast (host, 3, packet);         */
				enet_peer_send( pPeer , 0 , pPacket );
	    
				/* One could just use enet_host_service() instead. */
				//enet_host_flush (host);
			}
		}

		/* Wait up to 1000 milliseconds for an event. */
		while( enet_host_service( pClient , &event , 1000 ) > 0 )
		{
			switch( event.type )
			{
				case ENET_EVENT_TYPE_CONNECT:
					printf( "[Message ] A new client connected from %x:%u.\n"
						, event.peer->address.host
						, event.peer->address.port );

					/* Store any relevant client information here. */
					event.peer->data = "Client information";
				break;

				case ENET_EVENT_TYPE_RECEIVE:
					printf( "[Message ] A packet of length %u containing %s was received from %s on channel %u.\n"
						, event.packet->dataLength
						, event.packet->data
						, event.peer->data
						, event.channelID );

					/* Clean up the packet now that we're done using it. */
					enet_packet_destroy( event.packet );
				break;
	           
				case ENET_EVENT_TYPE_DISCONNECT:
					printf( "[Message ] %s disconected.\n"
						, event.peer->data );

					/* Reset the peer's client information. */
					event.peer->data = NULL;
			}
		}
	}

	// Deinitialize
	// ----------------------------------------------------------------------------------
	enet_deinitialize();
}