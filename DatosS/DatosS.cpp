/*! \file		DatosS.cpp
 *	\brief		Libreria que pide memória para la dll Sonido
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "DatosS.h"

DatosS::DatosS( HINSTANCE hInst )
{
   this->m_hInst      = hInst;
   this->m_pInterface = NULL;
   this->m_hDLL       = NULL;
}

DatosS::~DatosS( void )
{ 
	Release(); 
}

HRESULT DatosS::CreateInterface( const char *c_achAPI )
{
	HRESULT			hRes;
	CREATESINTERFACE _CreateInterface = 0;

	// Decide which API should be used
	if( strcmp( c_achAPI, "Sonido" ) == 0)
	{
		this->m_hDLL = LoadLibrary( L"Sonido.dll" );
		if( !this->m_hDLL )
		{
			MessageBoxA( NULL , "Loading Sonido.dll from lib failed." , "Error" , MB_OK | MB_ICONERROR );
			return E_FAIL;
		}
	}
	else
	{
		std::string sBuffer;
		sBuffer.assign( "API '");
		sBuffer.append( c_achAPI );
		sBuffer.append( "' not yet supported." );
		MessageBoxA( NULL , sBuffer.c_str() , "Error" , MB_OK | MB_ICONERROR );
		return E_FAIL;
	}

	// Function pointer to dll's 'CreateParserInterface' function
	_CreateInterface = ( CREATESINTERFACE ) GetProcAddress( this->m_hDLL, "CreateSInterface" );

	if( !_CreateInterface )
	{
		return E_FAIL;
	}

	// Call dll's create function
	hRes = _CreateInterface( m_hDLL , &m_pInterface );
	if( FAILED( hRes ) )
	{
		MessageBoxA( NULL , "CreateSInterface() from lib failed." , "Error" , MB_OK | MB_ICONERROR );
		this->m_pInterface = NULL;
		return E_FAIL;
	}

	return S_OK;
}

void DatosS::Release( void )
{
	RELEASESINTERFACE _ReleaseInterface = 0;
	HRESULT          hRes;

	if( this->m_hDLL )
	{
		// Function pointer to dll 'ReleaseInterface' function
		_ReleaseInterface = ( RELEASESINTERFACE ) GetProcAddress( this->m_hDLL , "ReleaseSInterface" );
	}

	// Call dll's release function
	if( this->m_pInterface )
	{
		hRes = _ReleaseInterface( &m_pInterface );
		if( FAILED( hRes ) )
		{
			this->m_pInterface = NULL;
		}
	}
}
