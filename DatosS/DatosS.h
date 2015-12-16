/*! \file		DatosS.h
 *	\brief		Libreria que pide mem�ria para la dll Sonido
 *  \version	1.0
 *  \author		Enric Mac�as L�pez <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef DATOSS_H
#define DATOSS_H

	#include "DatosSInterface.h"

	/*! \class		DatosS
	*	\brief		Pide mem�ria para la dll Sonido
	*/
	class DatosS
	{
		private:

			DatosSInterface		*m_pInterface;	/*!< Interfaz que utilizamos para llamar a la dll Sonido */
			HINSTANCE			 m_hInst;		/*!< Instancia de la ventana							 */
			HMODULE				 m_hDLL;		/*!< Dll que estamos usando para los archivos de parse	 */

		public:

			/*! \fn			DatosS::DatosS( void )
			*	\brief		Constructor.
			*	\param		HINSTANCE hInstance	Instancia de la ventana.
			*	\return		None.
			*/
			DatosS( HINSTANCE hInstance );

			/*! \fn			DatosS::~DatosS( void )
			*	\brief		Destructor. LLama a la funci�n Release.
			*	\param		None
			*	\return		None.
			*/
			~DatosS( void );

			/*! \fn			HRESULT DatosS::CreateInterface( const char *c_achAPI )
			*	\brief		Dependiendo del nombre que le pasemos crea y pide memoria para una DLL 
			*				\n	u otra utilizando la funci�n LoadLibrary. 
			*				\n	Despu�s llamar�a la funci�n CreateInterfacede la DLL utilizando la funci�n GetProcAddress.
			*	\param		const char *c_achAPI	API a crear (Sonido).
			*	\return		HRESULT	------.
			*/
			HRESULT CreateInterface( const char *c_achAPI );

			/*! \fn			LPDATOSSINTERFACE DatosS::GetInterface( void )
			*	\brief		Devuelve la interfaz.
			*	\param		None.
			*	\return		LPDATOSSINTERFACE	------.
			*/
			LPDATOSSINTERFACE GetInterface( void ){ return m_pInterface; }

			/*! \fn			void DatosS::Release( void )
			*	\brief		Llama a la funci�n ReleaseInterface de la DLL y luego destruye la DLL.
			*	\param		None.
			*	\return		LPDATOSSINTERFACE	------.
			*/
			void Release( void );
	};

	typedef class DatosS *LPDATOSS;

#endif