/*! \file		Render.cpp
 *	\brief		Dll que gestiona la geometria que se pinta por pantalla
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "Render.h"

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

HRESULT CreateRInterface( HINSTANCE hDLL , DatosRInterface **ppDatosRInterface )
{
	if( !*ppDatosRInterface )
	{
		*ppDatosRInterface = new Render( hDLL );
		return TRUE;
	}
	return !TRUE;
}

HRESULT ReleaseRInterface( DatosRInterface **ppDatosRInterface )
{
	if( !*ppDatosRInterface )
	{
		return !TRUE;
	}
	delete *ppDatosRInterface;
	*ppDatosRInterface = NULL;
	return TRUE;
}

Render::Render()
{
}
			
Render::Render( HINSTANCE hDLL )
{
	m_hDLL = hDLL;
}
			
Render::~Render()
{
}

bool Render::InitSDL( void )
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

SDL_Surface *Render::InitGL( void )
{
	SDL_Surface *pDrawContext;
	Uint32 flags;

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER , 1 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE , 16 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE , 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE , 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE , 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE , 8 );

	flags = SDL_OPENGL; // | SDL_FULLSCREEN;

	pDrawContext = SDL_SetVideoMode( iWidth , iHeigth , 0 , flags );

	SDL_WM_SetCaption( "The Recolect" , "" );

	glClearColor( 0.0f , 0.0f , 0.0f , 0.0f );

	return pDrawContext;
}

int Render::LoadTexture( char *sFileName )
{
	ILuint iImgId = -1;
	ILuint iTexId = -1;

	// Configurar OpenIL para cada textura
	ilEnable( IL_CONV_PAL ); 
	ilutEnable( ILUT_OPENGL_CONV ); 
	ilutRenderer( ILUT_OPENGL ); 

	//Cargamos la imagen
	ilGenImages( 1 , &iImgId ); 
	ilBindImage( iImgId );

	if( ilLoadImage( ( ILstring ) sFileName ) )
	{
		// He cargado la imagen OK
		glEnable( GL_TEXTURE_2D );

		iTexId = ilutGLBindTexImage();
		ilDeleteImages( 1 , &iImgId );

		glDisable( GL_TEXTURE_2D );
	}
	else
	{
		// NO He cargado la imagen! KO
		printf( "Textura <%s> no cargada\n" , sFileName );
	}

	return iTexId;
}
			
HRESULT Render::Init( void )
{
	bool bOK = true;

	iWidth = 800;
	iHeigth = 800;
	MaxEscenari = 40;

	Server=0;

	//Inicializamos la libreria SDL
	if( !InitSDL() )
	{
		bOK = false;
	}

	//Inicializamos la libreria OpenGL
	if( InitGL() == NULL )
	{
		bOK = false;
	}

	//Inicializamos la libreria OpenIL
	ilInit();

	//Inicializamos texturas
	TexNau		= LoadTexture( "nau.png"		);
	TexNauOn	= LoadTexture( "nauOn.png"		);
	TexAste		= LoadTexture( "asteroide.png"	);
	TexEnem		= LoadTexture( "enem.png"		);
	TexEnemOn	= LoadTexture( "enemon.png"		);
	TexLaser	= LoadTexture( "Laser.png"		);
	TexEsc		= LoadTexture( "Esc.png"		);	
	
	//TexAux		= LoadTexture( "Fons.png"	);
	if( bOK )
		return TRUE;
	else
		return !TRUE;
}

void Render::LoadTBG(char *nomT)
{
	TexBG   = NULL;
	TexBG	= LoadTexture( nomT );
}

void Render::PintaNave( int iPlayer )
{
	glEnable( GL_TEXTURE_2D );

	switch( iPlayer )
	{
		case 1:
			//dependiendo de la aceleración de la nave se pinta con los motores On o Off
			if(N1.getFuerza() > 0)
				glBindTexture( GL_TEXTURE_2D , TexNauOn );
			else
				glBindTexture( GL_TEXTURE_2D , TexNau );
			break;
		case 2:
			//para una posible imagen diferente de nave
			if(N2.getFuerza() > 0)
				glBindTexture( GL_TEXTURE_2D , TexNauOn );
			else
				glBindTexture( GL_TEXTURE_2D , TexNau );
			break;
	}

	glEnable( GL_BLEND );
	
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

	glColor3f( 1.0f , 1.0f , 1.0f );

	glPushMatrix();
		glBegin( GL_QUADS );
			
			glTexCoord2f( 0.0f , 1.0f );
			glVertex3f( -1.0f , -1.0f , 0.0f );

			glTexCoord2f( 0.0f , 0.0f );
			glVertex3f( -1.0f , 1.0f , 0.0f );

			glTexCoord2f( 1.0f , 0.0f );
			glVertex3f( 1.0f , 1.0f , 0.0f );

			glTexCoord2f( 1.0f , 1.0f );
			glVertex3f( 1.0f , -1.0f , 0.0f );

		glEnd();
	glPopMatrix();

	glDisable( GL_BLEND );

	glDisable( GL_TEXTURE_2D );
}
void Render::PintaEscudo( )
{
	glEnable( GL_TEXTURE_2D );

	glBindTexture( GL_TEXTURE_2D , TexEsc );

	glEnable( GL_BLEND );
	
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

	glColor3f( 1.0f , 1.0f , 1.0f );

	glPushMatrix();
		glBegin( GL_QUADS );
			
			glTexCoord2f( 0.0f , 1.0f );
			glVertex3f( -1.0f , -1.0f , 0.0f );

			glTexCoord2f( 0.0f , 0.0f );
			glVertex3f( -1.0f , 1.0f , 0.0f );

			glTexCoord2f( 1.0f , 0.0f );
			glVertex3f( 1.0f , 1.0f , 0.0f );

			glTexCoord2f( 1.0f , 1.0f );
			glVertex3f( 1.0f , -1.0f , 0.0f );

		glEnd();
	glPopMatrix();

	glDisable( GL_BLEND );

	glDisable( GL_TEXTURE_2D );
}

void Render::PintaBala()
{
	glEnable( GL_TEXTURE_2D );

	glBindTexture( GL_TEXTURE_2D , TexLaser );

	glEnable( GL_BLEND );
	
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

	glColor3f( 1.0f , 1.0f , 1.0f );

	glPushMatrix();
		glBegin( GL_QUADS );
			
			glTexCoord2f( 0.0f , 1.0f );
			glVertex3f( -0.4f , -0.4f , 0.0f );

			glTexCoord2f( 0.0f , 0.0f );
			glVertex3f( -0.4f , 0.4f , 0.0f );

			glTexCoord2f( 1.0f , 0.0f );
			glVertex3f( 0.4f , 0.4f , 0.0f );

			glTexCoord2f( 1.0f , 1.0f );
			glVertex3f( 0.4f , -0.4f , 0.0f );

		glEnd();
	glPopMatrix();

	glDisable( GL_BLEND );

	glDisable( GL_TEXTURE_2D );
}

void Render::PintaSat(float f)
{
	glEnable( GL_TEXTURE_2D );

	if(f > 0)
		glBindTexture( GL_TEXTURE_2D , TexEnemOn );
	else
		glBindTexture( GL_TEXTURE_2D , TexEnem );

	glEnable( GL_BLEND );
	
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

	glColor3f( 1.0f , 1.0f , 1.0f );

	glPushMatrix();
		glBegin( GL_QUADS );
			
			glTexCoord2f( 0.0f , 1.0f );
			glVertex3f( -1.0f , -1.0f , 0.0f );

			glTexCoord2f( 0.0f , 0.0f );
			glVertex3f( -1.0f , 1.0f , 0.0f );

			glTexCoord2f( 1.0f , 0.0f );
			glVertex3f( 1.0f , 1.0f , 0.0f );

			glTexCoord2f( 1.0f , 1.0f );
			glVertex3f( 1.0f , -1.0f , 0.0f );

		glEnd();
	glPopMatrix();

	glDisable( GL_BLEND );

	glDisable( GL_TEXTURE_2D );
}

void Render::PintaEnemigo( float fTamaño )
{
	glEnable( GL_TEXTURE_2D );

	glBindTexture( GL_TEXTURE_2D , TexAste );

	glEnable( GL_BLEND );
	
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

	glColor3f( 1.0f , 1.0f , 1.0f );

	glPushMatrix();
		glBegin( GL_QUADS );
			
			glTexCoord2f( 0.0f , 1.0f );
			glVertex3f( -fTamaño , -fTamaño , 0.0f );

			glTexCoord2f( 0.0f , 0.0f );
			glVertex3f( -fTamaño , fTamaño , 0.0f );

			glTexCoord2f( 1.0f , 0.0f );
			glVertex3f( fTamaño , fTamaño , 0.0f );

			glTexCoord2f( 1.0f , 1.0f );
			glVertex3f( fTamaño , -fTamaño , 0.0f );

		glEnd();
	glPopMatrix();

	glDisable( GL_BLEND );

	glDisable( GL_TEXTURE_2D );
}



void Render::Pinta( void )
{
	char *cChar;
	Enemigo enem;
	float left, right, up, down;
	float min, max;
	float posX, posY;
	min = - 25;
	max = 25;
	Satelite S;

	if(Server == 2)
	{
		posX = N2.getPos().getX();
		posY = N2.getPos().getY();
	}
	else
	{
		posX = N1.getPos().getX();
		posY = N1.getPos().getY();
	}

	left = posX - 15;
	right = posX + 15;
	up = posY + 15;
	down = posY - 15;

	glClearColor( 0.0f , 0.0f , 0.0f , 0.0f );
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	glViewport( 0 , 0 , ( GLsizei ) ( iWidth ) , ( GLsizei ) ( iHeigth ) );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	if(posX < min)
	{
		left = -MaxEscenari;
		right = left + 30;
	}
	if(posY < min)
	{
		down = -MaxEscenari;
		up = down + 30;
	}
	if(posX > max)
	{	
		right = MaxEscenari;
		left = right - 30;
	}
	if(posY > max)
	{	
		up = MaxEscenari;
		down = up - 30;
	}
	glOrtho( left, right, down, up , -100.0 , 100.0 );
	//glOrtho( -MaxEscenari , MaxEscenari , -MaxEscenari , MaxEscenari , -100.0 , 100.0 );

	gluLookAt( 0.0f , 0.0f , 100.0f , 0.0f , 0.0f , 0.0f , 0.0f , 1.0f , 0.0f );

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D , TexBG );	
	glColor3f( 1.0f , 1.0f , 1.0f );

	glPushMatrix();
		glBegin( GL_QUADS );
			
			glTexCoord2f( 0.0f , 1.0f );
			glVertex3f( -MaxEscenari , -MaxEscenari , 0.0f );

			glTexCoord2f( 0.0f , 0.0f );
			glVertex3f( -MaxEscenari , MaxEscenari , 0.0f );

			glTexCoord2f( 1.0f , 0.0f );
			glVertex3f( MaxEscenari , MaxEscenari , 0.0f );

			glTexCoord2f( 1.0f , 1.0f );
			glVertex3f( MaxEscenari , -MaxEscenari , 0.0f );

		glEnd();
	glPopMatrix();

	glDisable( GL_TEXTURE_2D );

	if (N1.getVisible())
	{
		glPushMatrix();
			glTranslatef( N1.getPosX() , N1.getPosY() , 0.0f );
			glRotatef( N1.getRot() , 0.0f , 0.0f , 1.0f );
			PintaNave( 1 );
			if(N1.getInmune())
				PintaEscudo();
		glPopMatrix();
		if (N1.getBala().getVisible())
		{
			glPushMatrix();
				glTranslatef( N1.getBala().getPosX() , N1.getBala().getPosY() , 0.0f );
				glRotatef( N1.getBala().getRot() , 0.0f , 0.0f , 1.0f );
				PintaBala();
			glPopMatrix();
		}
	}

	if (N2.getVisible())
	{
		glPushMatrix();
			glTranslatef( N2.getPosX() , N2.getPosY() , 0.0f );
			glRotatef( N2.getRot() , 0.0f , 0.0f , 1.0f );
			PintaNave( 2 );
			if(N2.getInmune())
				PintaEscudo();
		glPopMatrix();
		if (N2.getBala().getVisible())
		{
			glPushMatrix();
				glTranslatef( N2.getBala().getPosX() , N2.getBala().getPosY() , 0.0f );
				glRotatef( N2.getBala().getRot() , 0.0f , 0.0f , 1.0f );
				PintaBala();
			glPopMatrix();
		}
	}
	for( int i=0 ; i < mSat.size(); i++ )
	{
		if (mSat[i].getVisible())
		{
			glPushMatrix();
				glTranslatef( mSat[i].getPosX() , mSat[i].getPosY() , 0.0f );
				glRotatef( mSat[i].getRot() , 0.0f , 0.0f , 1.0f );
				PintaSat(mSat[i].getFuerza());
				if(mSat[i].getInmune())
					PintaEscudo();
			glPopMatrix();
			if (mSat[i].getBala().getVisible())
			{
				glPushMatrix();
					glTranslatef( mSat[i].getBala().getPosX() , mSat[i].getBala().getPosY() , 0.0f );
					glRotatef( mSat[i].getBala().getRot() , 0.0f , 0.0f , 1.0f );
					PintaBala();
				glPopMatrix();
			}
		}
	}
	
	for( int i=0 ; i < m_iEnemigos.size(); i++ )
	{
		enem = getEnemigo( i );
		if (enem.getVisible())
		{
			glPushMatrix();
				glTranslatef( enem.getPosX() , enem.getPosY() , 0.0f );
				glRotatef( enem.getRot() , 0.0f , 0.0f  , 1.0f );
				PintaEnemigo( enem.getTamaño() );
			glPopMatrix();
		}
	}
	//un recuadro informativo de la vidas que quedan imagen del personage i velocidad actual

	//glEnable( GL_TEXTURE_2D );

	//glBindTexture( GL_TEXTURE_2D , iTextureId15 );

	//glEnable( GL_BLEND );
	//
	//glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

	//glColor3f( 1.0f , 1.0f , 1.0f );

	//glPushMatrix();
	//	glBegin( GL_QUADS );
	//		
	//		glTexCoord2f( 0.0f , 1.0f );
	//		glVertex3f( left , down , 0.0f );

	//		glTexCoord2f( 0.0f , 0.0f );
	//		glVertex3f( left , up , 0.0f );

	//		glTexCoord2f( 1.0f , 0.0f );
	//		glVertex3f( right , up , 0.0f );

	//		glTexCoord2f( 1.0f , 1.0f );
	//		glVertex3f( right , down , 0.0f );

	//	glEnd();
	//glPopMatrix();

	//glDisable( GL_BLEND );

	//glDisable( GL_TEXTURE_2D );
	SDL_GL_SwapBuffers();
}

void Render::PintaBG( void )
{
	glClearColor( 0.0f , 0.0f , 0.0f , 0.0f );
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	
	glViewport( 0 , 0 , ( GLsizei ) ( iWidth ) , ( GLsizei ) ( iHeigth ) );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glOrtho( -MaxEscenari , MaxEscenari , -MaxEscenari , MaxEscenari , -100.0 , 100.0 );

	gluLookAt( 0.0f , 0.0f , 100.0f , 0.0f , 0.0f , 0.0f , 0.0f , 1.0f , 0.0f );
	
	glEnable( GL_TEXTURE_2D );
	
	glBindTexture( GL_TEXTURE_2D , TexBG );
			
	glColor3f( 1.0f , 1.0f , 1.0f );

	glPushMatrix();
		glBegin( GL_QUADS );
			
			glTexCoord2f( 0.0f , 1.0f );
			glVertex3f( -MaxEscenari , -MaxEscenari , 0.0f );

			glTexCoord2f( 0.0f , 0.0f );
			glVertex3f( -MaxEscenari , MaxEscenari , 0.0f );

			glTexCoord2f( 1.0f , 0.0f );
			glVertex3f( MaxEscenari , MaxEscenari , 0.0f );

			glTexCoord2f( 1.0f , 1.0f );
			glVertex3f( MaxEscenari , -MaxEscenari , 0.0f );

		glEnd();
	glPopMatrix();

	glDisable( GL_TEXTURE_2D );

	SDL_GL_SwapBuffers();
}
