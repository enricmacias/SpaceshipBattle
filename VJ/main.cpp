/*! \file		main.cpp
 *	\brief		Gestiona las 3 dll's para su utilización
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "../DatosI/eNet.h"
#include < windows.h >

#include "../DatosR/DatosR.h"
#include "../DatosE/DatosE.h"
#include "../DatosL/DatosL.h"
#include "../DatosS/DatosS.h"

int main( int argc , char **argv )
{
	//Instanciación de variables
	int Server = 0;
	int iDisplay = 1;
	int iDisplayIni = 1;

	DatosR	*DR;
	DatosE	*DE;
	DatosL	*DL;
	DatosS	*DS;
	eNet	*enet;

	Nave N1,N2;
	std::vector < Satelite > S;
	std::vector < Enemigo > E;

	//Creación de DLL's
	DR = new DatosR( GetModuleHandle( NULL ) );
	DE = new DatosE( GetModuleHandle( NULL ) );
	DL = new DatosL( GetModuleHandle( NULL ) );
	DS = new DatosS( GetModuleHandle( NULL ) );
	enet = new eNet( GetModuleHandle( NULL ) );

	DR->CreateInterface( "Render" );
	DE->CreateInterface( "Eventos" );
	DL->CreateInterface( "Logica" );
	DS->CreateInterface( "Sonido" );
	enet->CreateInterface( "Internet" );

	if( DR->GetInterface() != NULL )
	{
		if( DE->GetInterface() != NULL )
		{
			if( DL->GetInterface() != NULL )
			{
				if( DS->GetInterface() != NULL )
				{
					if( enet->GetInterface() != NULL )
					{
						//Inicializamos la dll Render
						if( !DR->GetInterface()->Init() )
						{
							exit( -1 );
						}

						//Inicializamos la dll Eventos
						if( !DE->GetInterface()->Init() )
						{
							exit( -1 );
						}

						//Inicializamos la dll Logica
						if( !DL->GetInterface()->Init() )
						{
							exit( -1 );
						}
						
						//Inicializamos la dll Sonido
						if( !DS->GetInterface()->Init() )
						{
							exit( -1 );
						}
						
						//Carga de sonidos
						DR->GetInterface()->LoadTBG( "vjintro.jpg" );
						DR->GetInterface()->PintaBG( );
						DS->GetInterface()->LoadSounds( 1 );
						DS->GetInterface()->Play( 1 );
						DS->GetInterface()->Suena();
						DS->GetInterface()->LoadSounds( 2 );
						Sleep(3000);
						
						iDisplay = 2;
						DS->GetInterface()->Play( 2 );
						
						//Pantalla inicial, escoger un jugador o dos
						DR->GetInterface()->LoadTBG( "vjintro1.jpg" );
						while( !DE->GetInterface()->Detecta( iDisplay, Server ) )
						{
							DR->GetInterface()->PintaBG( );
							DS->GetInterface()->Suena();
						}
						if(iDisplay == 3)
						{
							//Selección server o client
							DR->GetInterface()->LoadTBG( "vjintro2.jpg" );
							while( !DE->GetInterface()->Detecta( iDisplay, Server ) )
							{
								DR->GetInterface()->PintaBG( );
								DS->GetInterface()->Suena();
							}
						}
						if(Server == 0)
						{
							N2.setVisible(false);
							DR->GetInterface()->addNave( 2 , N2 );
						}
					
						DE->GetInterface()->InitNave();
						DL->GetInterface()->addServer( Server );
						DR->GetInterface()->addServer( Server );
						DL->GetInterface()->InitPos();
						if(Server == 1)
						{
							E = DL->GetInterface()->getEnem();
							
							enet->GetInterface()->addEnem( E );
							
						}
						if(Server != 0)
						{
							//Inicializamos la dll Internet
							if( !enet->GetInterface()->Init( Server ) )
							{
								exit( -1 );
							}
						}

						//Inicio del juego
						DS->GetInterface()->Play( 3 );
						DR->GetInterface()->LoadTBG( "fons.jpg" );
						//Bucle para mantener el programa en ejecución la variable dira cuando acaba el programa
						while( !DE->GetInterface()->Detecta( iDisplay, Server ) )
						{
							switch(Server)
							{
								case 0: //1 Jugador
									N1 = DE->GetInterface()->getNave( );
									
									DL->GetInterface()->addNave( N1 );
									DL->GetInterface()->Idle(iDisplay);
									N1 = DL->GetInterface()->getNave();
 									E = DL->GetInterface()->getEnem();
									S = DL->GetInterface()->getSat();
									DS->GetInterface()->Suena();
									DR->GetInterface()->addSat( S );
									DR->GetInterface()->addNave( 1 , N1 );
									DR->GetInterface()->addEnem( E );
									DR->GetInterface()->Pinta();

									DE->GetInterface()->addNave( N1 );
									break;
								case 1: //2 jugadores, Server side
									N1 = DE->GetInterface()->getNave( );
									
									DL->GetInterface()->addNave( N1 );
									DL->GetInterface()->addEnem( E );
									DL->GetInterface()->Idle( iDisplay );
									N1 = DL->GetInterface()->getNave();
 									E = DL->GetInterface()->getEnem();
									enet->GetInterface()->addEnem( E );
									enet->GetInterface()->addNave( N1 );
									enet->GetInterface()->Comm( Server );
									E = enet->GetInterface()->getEnem();
									N2 = enet->GetInterface()->getNave();
									DS->GetInterface()->Suena();
									DR->GetInterface()->addNave( 1 , N1 );
									DR->GetInterface()->addNave( 2 , N2 );
									DR->GetInterface()->addEnem( E );
									DR->GetInterface()->Pinta();

									DE->GetInterface()->addNave( N1 );
									break;
								case 2: //2 jugadores, Client side
									N2 = DE->GetInterface()->getNave();
									E = enet->GetInterface()->getEnem();
									enet->GetInterface()->addEnem(E);
									enet->GetInterface()->Comm( Server );
									
									E = enet->GetInterface()->getEnem();
									N1 = enet->GetInterface()->getNave();
									DL->GetInterface()->addNave( N2 );
									
									DL->GetInterface()->addEnem( E ); 
									DL->GetInterface()->Idle(iDisplay);
									N2 = DL->GetInterface()->getNave();
 									E = DL->GetInterface()->getEnem();

									enet->GetInterface()->addEnem( E );
									enet->GetInterface()->addNave( N2 );
									DS->GetInterface()->Suena();
									printf("enem 1X: %f\n", E[0].getPosX());
									printf("enem 2X: %f\n", E[1].getPosX());
									DR->GetInterface()->addNave( 1 , N1 );
									DR->GetInterface()->addNave( 2 , N2 );
									DR->GetInterface()->addEnem( E );
									DR->GetInterface()->Pinta();

									DE->GetInterface()->addNave( N2 );
									break;
							}
						}
						if(iDisplay == 5)
							DR->GetInterface()->LoadTBG( "vjgover.jpg");
						if(iDisplay == 6)
							DR->GetInterface()->LoadTBG( "vjwin.jpg");
						
						while( !DE->GetInterface()->Detecta( iDisplay, Server ) )
						{
							DR->GetInterface()->PintaBG();
							DS->GetInterface()->Suena();
						}
						if(Server == 0)
						{
							if( !enet->GetInterface()->Init( Server ) )
							{
								exit( -1 );
							}
						}
						//Desinicialización de DLL internet eNet
						enet->GetInterface()->deInit( Server );
					}
					//Desinicialización de DLL sonido FMOD
					DS->GetInterface()->DeInit();
				}
			}
		}   
	}

	//Destrucción de DLL's
	delete DL;
	delete DE;
	delete DR;
	delete DS;
	delete enet;

	return 0;
}