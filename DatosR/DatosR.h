/*! \file		DatosR.h
 *	\brief		Libreria que pide mem�ria para la dll Render
 *  \version	1.0
 *  \author		Enric Mac�as L�pez <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef DATOSR_H
#define DATOSR_H

	#include "DatosRInterface.h"

	/*! \class		DatosR
	*	\brief		Pide mem�ria para la dll Render
	*/
	class DatosR
	{
		private:

			DatosRInterface		*m_pInterface;	/*!< Interfaz que utilizamos para llamar a la dll Render */
			HINSTANCE			 m_hInst;		/*!< Instancia de la ventana							 */
			HMODULE				 m_hDLL;		/*!< Dll que estamos usando para los archivos de parse	 */

		public:

			/*! \fn			DatosR::DatosR( void )
			*	\brief		Constructor.
			*	\param		HINSTANCE hInstance	Instancia de la ventana.
			*	\return		None.
			*/
			DatosR( HINSTANCE hInstance );

			/*! \fn			DatosR::~DatosR( void )
			*	\brief		Destructor. LLama a la funci�n Release.
			*	\param		None
			*	\return		None.
			*/
			~DatosR( void );

			/*! \fn			HRESULT DatosR::CreateInterface( const char *c_achAPI )
			*	\brief		Dependiendo del nombre que le pasemos crea y pide memoria para una DLL 
			*				\n	u otra utilizando la funci�n LoadLibrary. 
			*				\n	Despu�s llamar�a la funci�n CreateInterfacede la DLL utilizando la funci�n GetProcAddress.
			*	\param		const char *c_achAPI	API a crear (Render).
			*	\return		HRESULT	------.
			*/
			HRESULT CreateInterface( const char *c_achAPI );

			/*! \fn			LPDATOSRINTERFACE DatosR::GetInterface( void )
			*	\brief		Devuelve la interfaz.
			*	\param		None.
			*	\return		LPDATOSRINTERFACE	------.
			*/
			LPDATOSRINTERFACE GetInterface( void ){ return m_pInterface; }

			/*! \fn			void DatosR::Release( void )
			*	\brief		Llama a la funci�n ReleaseInterfacede la DLL y luego destruye la DLL.
			*	\param		None.
			*	\return		LPDATOSRINTERFACE	------.
			*/
			void Release( void );
	};

	typedef class DatosR *LPDATOSR;

#endif