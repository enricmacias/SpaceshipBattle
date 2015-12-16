/*! \file		Eventos.cpp
 *	\brief		Dll que gestiona las órdenes entradas por teclado o ratón
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/
#include "Eventos.h"

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

HRESULT CreateEInterface( HINSTANCE hDLL , DatosEInterface **ppDatosEInterface )
{
	if( !*ppDatosEInterface )
	{
		*ppDatosEInterface = new Eventos( hDLL );
		return TRUE;
	}
	return !TRUE;
}

HRESULT ReleaseEInterface( DatosEInterface **ppDatosEInterface )
{
	if( !*ppDatosEInterface )
	{
		return !TRUE;
	}
	delete *ppDatosEInterface;
	*ppDatosEInterface = NULL;
	return TRUE;
}

Eventos::Eventos()
{
}
			
Eventos::Eventos( HINSTANCE hDLL )
{
	m_hDLL = hDLL;
}
			
Eventos::~Eventos()
{
}

bool Eventos::InitSDL( void )
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "ERROR CON LA INICIALIZACION DE LA SDL: %s\n" , SDL_GetError() );

		return false;
	}
	else
	{
		SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY , SDL_DEFAULT_REPEAT_INTERVAL );

		return true;
	}
}
			
HRESULT Eventos::Init( void )
{
	bool bOK = true;

	//Inicializamos la libreria SDL
	if( !InitSDL() )
	{
		bOK = false;
	}
	//Inicializamos vidas naves
	N.setVidas( 3 );

	if( bOK )
		return TRUE;
	else
		return !TRUE;
}

bool Eventos::Detecta( int &iDisplay, int &Ser )
{
	SDL_Event event;
	bool bDone = false;
	bool bFuerza = false;
	Vector2D mouseP;

	mouseP = MousePos();
	N.setDir( mouseP.getX() , mouseP.getY() );
	
	if( SDL_PollEvent( &event ) )
	{
		switch( event.type )
		{
			case SDL_QUIT:
				bDone = true;
				break;

			case SDL_KEYDOWN:
				switch( event.key.keysym.sym )
				{
					case SDLK_1: 
						if (iDisplay == 3)
						{
							Ser = 1;
							bDone = true;
						}
						if (iDisplay == 2)
						{
							Ser = 0;
							iDisplay = 4;
							bDone = true;
						}
						break;
					case SDLK_2: 
						if (iDisplay == 3)
						{
							Ser = 2;
							bDone = true;
						}
						if (iDisplay == 2)
						{
							iDisplay = 3;
							bDone = true;
						}
						break;
					case SDLK_q: bDone = true;
						break;
					case SDLK_SPACE:
						switch( iDisplay )
						{
							case 4:	bFuerza = true;
								break;
							case 5: bDone = true;
								break;
							case 6: bDone = true;
								break;
						}
						break;
				}
				break;

			case SDL_MOUSEMOTION: 
				break;
			case SDL_MOUSEBUTTONDOWN: 
				if (iDisplay == 4)
				{
					if(N.getCarga())
						N.Dispara();
				}
				break;
		}
		Server = Ser;
	}
	updateFuerza(bFuerza);

	if (N.getVidas() < 1 && iDisplay == 4)
	{
		iDisplay = 5;
		bDone = true;
	}
	return bDone;
}

Vector2D Eventos::MousePos( void )
{
	int mX, mY;
	GLfloat winX, winY;
	GLdouble posX=0, posY=0, posZ=0;
	int state;
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	Vector2D mPos;

	state = SDL_GetMouseState( &mX , &mY );
	
	glGetIntegerv(GL_VIEWPORT, viewport);

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	winX = (float) mX;
	winY = (float)viewport[3] - (float)mY;

	gluUnProject( winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);

	mPos.setX( (float) posX );
	mPos.setY( (float) posY );

	return( mPos );
}
void Eventos::InitNave( )
{
	//Inicializamos posicones naves
	switch(Server)
	{
		case 0:
			N.setPosX( 0.0 );
			N.setPosY( 0.0 );
			break;
		case 1:
			N.setPosX( 17.0 );
			N.setPosY( 0.0 );
			break;
		case 2:
			N.setPosX( -17.0 );
			N.setPosY( 0.0 );
			break;
	}
}