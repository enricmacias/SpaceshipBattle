/*! \file		DatosE.cpp
 *	\brief		Libreria que pide memória para la dll Eventos
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "DatosE.h"

DatosE::DatosE( HINSTANCE hInst )
{
   this->m_hInst      = hInst;
   this->m_pInterface = NULL;
   this->m_hDLL       = NULL;
}

DatosE::~DatosE( void )
{ 
	Release(); 
}

HRESULT DatosE::CreateInterface( const char *c_achAPI )
{
	HRESULT				hRes;
	CREATEEINTERFACE	_CreateInterface = 0;

	// Decide which API should be used
	if( strcmp( c_achAPI, "Eventos" ) == 0)
	{
		this->m_hDLL = LoadLibrary( L"Eventos.dll" );
		if( !this->m_hDLL )
		{
			MessageBoxA( NULL , "Loading Eventos.dll from lib failed." , "Error" , MB_OK | MB_ICONERROR );
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
	_CreateInterface = ( CREATEEINTERFACE ) GetProcAddress( this->m_hDLL, "CreateEInterface" );

	if( !_CreateInterface )
	{
		return E_FAIL;
	}

	// Call dll's create function
	hRes = _CreateInterface( m_hDLL , &m_pInterface );
	if( FAILED( hRes ) )
	{
		MessageBoxA( NULL , "CreateEInterface() from lib failed." , "Error" , MB_OK | MB_ICONERROR );
		this->m_pInterface = NULL;
		return E_FAIL;
	}

	return S_OK;
}

void DatosE::Release( void )
{
	RELEASEEINTERFACE	_ReleaseInterface = 0;
	HRESULT				hRes;

	if( this->m_hDLL )
	{
		// Function pointer to dll 'ReleaseEInterface' function
		_ReleaseInterface = ( RELEASEEINTERFACE ) GetProcAddress( this->m_hDLL , "ReleaseEInterface" );
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
