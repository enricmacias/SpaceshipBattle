/*! \file		Logica.cpp
 *	\brief		Dll que gestiona la lógica del juego
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "Logica.h"

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

HRESULT CreateLInterface( HINSTANCE hDLL , DatosLInterface **ppDatosLInterface )
{
	if( !*ppDatosLInterface )
	{
		*ppDatosLInterface = new Logica( hDLL );
		return TRUE;
	}
	return !TRUE;
}

HRESULT ReleaseLInterface( DatosLInterface **ppDatosLInterface )
{
	if( !*ppDatosLInterface )
	{
		return !TRUE;
	}
	delete *ppDatosLInterface;
	*ppDatosLInterface = NULL;
	return TRUE;
}

Logica::Logica()
{
}
			
Logica::Logica( HINSTANCE hDLL )
{
	m_hDLL = hDLL;
}
			
Logica::~Logica()
{
}
			
HRESULT Logica::Init( void )
{
	return TRUE;
}
void Logica::InitPos( void )
{
	int MaxEscenari = 40;
	//Inicializamos posiciones enemigos
	srand( time( NULL ) );
	float tamanyo;
	float Xpos, Ypos;
	Satelite S;

	if(Server == 0)
	{
		for( float i=0 ; i < 6; i++ )
		{
			S.setPosX (rand()% ( 2*MaxEscenari ) - MaxEscenari);
			S.setPosY (rand()% ( 2*MaxEscenari ) - MaxEscenari);
			S.setVidas( 2 );
			mSat.push_back( S );
		}
	}
	if(Server != 2)
	{
		for( float i=0 ; i < 30 ; i++ )
		{
			tamanyo = rand()%15;
			tamanyo = tamanyo/10;
			tamanyo += 0.3;
			posiciona(Xpos, Ypos, tamanyo, MaxEscenari);
			addEnemigo( Xpos, Ypos , rand()%360 , tamanyo);
		}
	}
}

void Logica::Idle( int &iDisplay )
{
	Solver(1, 0);
	if(Server == 0)
	{
		iDisplay = 6;
		for( int i=0 ; i < mSat.size(); i++ )
		{
			if(mSat[i].getVisible())
			{
				iDisplay = 4;
				Piensa(i);
				Solver(2 , i);
			}
		}
	}
	Colisiona();
}
void Logica::posiciona ( float &x, float &y , float tamanyo, int MaxEscenari)
{
	x = rand()% ( 2*MaxEscenari ) - MaxEscenari;
	y = rand()% ( 2*MaxEscenari ) - MaxEscenari;
	Vector2D dist;
	float aux;
	tamanyo = tamanyo/2;
	for( int i=0 ; i < m_iEnemigos.size(); i++ )
	{
		dist.setX( m_iEnemigos[ i ].getPos().getX() - x);
		dist.setY( m_iEnemigos[ i ].getPos().getY() - y);
		aux = dist.getModulo();
		if( aux < m_iEnemigos[ i ].getTamaño() + tamanyo )
		{
			posiciona ( x, y, tamanyo, MaxEscenari);
		}
	}
}