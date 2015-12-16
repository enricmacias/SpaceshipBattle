/*! \file		DatosL.h
 *	\brief		Libreria que pide memória para la dll Lógica
 *  \version	1.0
*  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef DATOSL_H
#define DATOSL_H

	#include "DatosLInterface.h"

	/*! \class		DatosL
	*	\brief		Pide memória para la dll Lógica
	*/
	class DatosL
	{
		private:

			DatosLInterface		*m_pInterface;	/*!< Interfaz que utilizamos para llamar a la dll Lógica */
			HINSTANCE			 m_hInst;		/*!< Instancia de la ventana							 */
			HMODULE				 m_hDLL;		/*!< Dll que estamos usando para los archivos de parse	 */

		public:

			/*! \fn			DatosL::DatosL( void )
			*	\brief		Constructor.
			*	\param		HINSTANCE hInstance	Instancia de la ventana.
			*	\return		None.
			*/
			DatosL( HINSTANCE hInstance );

			/*! \fn			DatosL::~DatosL( void )
			*	\brief		Destructor. LLama a la función Release.
			*	\param		None
			*	\return		None.
			*/
			~DatosL( void );

			/*! \fn			HRESULT DatosL::CreateInterface( const char *c_achAPI )
			*	\brief		Dependiendo del nombre que le pasemos crea y pide memoria para una DLL 
			*				\n	u otra utilizando la función LoadLibrary. 
			*				\n	Después llamaráa la función CreateInterfacede la DLL utilizando la función GetProcAddress.
			*	\param		const char *c_achAPI	API a crear (Render).
			*	\return		HRESULT	------.
			*/
			HRESULT CreateInterface( const char *c_achAPI );

			/*! \fn			LPDATOSRINTERFACE DatosL::GetInterface( void )
			*	\brief		Devuelve la interfaz.
			*	\param		None.
			*	\return		LPDATOSRINTERFACE	------.
			*/
			LPDATOSLINTERFACE GetInterface( void ){ return m_pInterface; }

			/*! \fn			void DatosL::Release( void )
			*	\brief		Llama a la función ReleaseInterface de la DLL y luego destruye la DLL.
			*	\param		None.
			*	\return		LPDATOSRINTERFACE	------.
			*/
			void Release( void );
	};

	typedef class DatosL *LPDATOSL;

#endif