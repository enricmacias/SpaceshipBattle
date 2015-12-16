/*! \file		DatosE.h
 *	\brief		Libreria que pide memória para la dll Eventos
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef DATOSE_H
#define DATOSE_H

	#include "DatosEInterface.h"

	/*! \class		DatosE
	*	\brief		Pide memória para la dll Eventos
	*/
	class DatosE
	{
		private:

			DatosEInterface		*m_pInterface;	/*!< Interfaz que utilizamos para llamar a la dll Eventos */
			HINSTANCE			 m_hInst;		/*!< Instancia de la ventana							 */
			HMODULE				 m_hDLL;		/*!< Dll que estamos usando para los archivos de parse	 */

		public:
			
			/*! \fn			DatosE::DatosE( void )
			*	\brief		Constructor.
			*	\param		HINSTANCE hInstance	Instancia de la ventana.
			*	\return		None.
			*/
			DatosE( HINSTANCE hInstance );

			/*! \fn			DatosE::~DatosE( void )
			*	\brief		Destructor. LLama a la función Release.
			*	\param		None
			*	\return		None.
			*/
			~DatosE( void );

			/*! \fn			HRESULT DatosE::CreateInterface( const char *c_achAPI )
			*	\brief		Dependiendo del nombre que le pasemos crea y pide memoria para una DLL 
			*				\n	u otra utilizando la función LoadLibrary. 
			*				\n	Después llamará la función CreateInterfacede la DLL utilizando la función GetProcAddress.
			*	\param		const char *c_achAPI	API a crear (Render).
			*	\return		HRESULT	------.
			*/
			HRESULT CreateInterface( const char *c_achAPI );

			/*! \fn			LPDATOSRINTERFACE DatosE::GetInterface( void )
			*	\brief		Devuelve la interfaz.
			*	\param		None.
			*	\return		LPDATOSRINTERFACE	------.
			*/
			LPDATOSEINTERFACE GetInterface( void ){ return m_pInterface; }

			/*! \fn			void DatosE::Release( void )
			*	\brief		Llama a la función ReleaseInterfacede la DLL y luego destruye la DLL.
			*	\param		None.
			*	\return		LPDATOSRINTERFACE	------.
			*/
			void Release( void );
	};

	typedef class DatosE *LPDATOSE;

#endif