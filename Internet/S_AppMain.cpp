#include "S_AppMain.h"

int main( int iArgCounter , char **ppArgValues )
{
	char acPort[ 256 ] , acActiveConnections[ 256 ];
	int iActiveConnections;

	// Initialize
	// ----------------------------------------------------------------------------------
	if( enet_initialize() != 0 )
	{
		printf( "[Error   ] An error occurred while initializing ENet.\n" );
		return EXIT_FAILURE;
	}

	// Create a server
	// ----------------------------------------------------------------------------------
	ENetAddress Address;
	ENetHost *pServer;

	/* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */

	Address.host = ENET_HOST_ANY;
    /* Bind the server to port 1234. */

	printf( "[Question] Type the port to be listening on: " );
	gets( acPort );
	if( acPort[ 0 ] != 0 )
	{
	    Address.port = atoi( acPort );
	}
	else
	{
	    Address.port = 1234;
	}


	printf( "[Question] Number of active connections: " );
	gets( acActiveConnections );
	if( acActiveConnections[ 0 ] != 0 )
	{
		iActiveConnections = atoi( acActiveConnections );
	}
	else
	{
		iActiveConnections = 1234;
	}


    pServer = enet_host_create( &Address				/* the address to bind the server host to */, 
		                         iActiveConnections		/* allow up to 32 clients and/or outgoing connections */,
                                 0						/* assume any amount of incoming bandwidth */,
                                 0						/* assume any amount of outgoing bandwidth */);

    if( pServer == NULL )
    {
        printf( "[Error   ] An error occurred while trying to create an ENet server host.\n" );
        exit( EXIT_FAILURE );
    }

	// Manage events
	// ----------------------------------------------------------------------------------
    ENetEvent event;
	std::vector <ENetPeer *> vPeers;
	
	while( true )
	{
		if( kbhit() )
		{
			char asMessage[ 2048 ];
			// Send message to the server
			// ----------------------------------------------------------------------------------
			gets( asMessage );

			for( int iCounter = 0 ; iCounter < vPeers.size() ; iCounter ++ )
			{
				/* Create a reliable packet of size 7 containing "packet\0" */
				ENetPacket *pPacket = enet_packet_create( asMessage , strlen( asMessage ) + 1 , ENET_PACKET_FLAG_RELIABLE );

				/* Send the packet to the peer over channel id 3. */
				/* One could also broadcast the packet by         */
				/* enet_host_broadcast (host, 3, packet);         */
				enet_peer_send( vPeers[ iCounter ] , 0 , pPacket );
	    
				/* One could just use enet_host_service() instead. */
				//enet_host_flush (host);
			}
		}

		/* Wait up to 1000 milliseconds for an event. */
		while( enet_host_service( pServer , &event , 1000 ) > 0 )
		{
			switch( event.type )
			{
				case ENET_EVENT_TYPE_CONNECT:
					printf( "[Message ] A new client connected from %x:%u.\n"
						, event.peer->address.host
						, event.peer->address.port );

					/* Store any relevant client information here. */
					event.peer->data = "Client information";
					vPeers.push_back( event.peer );
					//pPeer = event.peer;
				break;

				case ENET_EVENT_TYPE_RECEIVE:
					printf( "[Message ] A packet of length %u containing %s was received from %s on channel %u.\n"
						, event.packet->dataLength
						, event.packet->data
						, event.peer->data
						, event.channelID );

					for( int iCounter = 0 ; iCounter < vPeers.size() ; iCounter ++ )
					{
						ENetPacket *pPacket = enet_packet_create( event.packet->data , strlen( ( char * ) event.packet->data ) + 1 , ENET_PACKET_FLAG_RELIABLE );
						enet_peer_send( vPeers[ iCounter ] , 0 , pPacket );
			    
						/* One could just use enet_host_service() instead. */
						//enet_host_flush (host);
					}

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
	enet_host_destroy( pServer );
	enet_deinitialize();
}