/*! \file		eNet.h
 *	\brief		Libreria que pide mem�ria para la dll Internet
 *  \version	1.0
 *  \author		Enric Mac�as L�pez <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef ENET_H
#define ENET_H

	#include "eNetInterface.h"

	/*! \class		eNet
	*	\brief		Pide mem�ria para la dll Internet
	*/
	class eNet
	{
		private:

			eNetInterface		*m_pInterface;	/*!< Interfaz que utilizamos para llamar a la dll Internet */
			HINSTANCE			 m_hInst;		/*!< Instancia de la ventana							 */
			HMODULE				 m_hDLL;		/*!< Dll que estamos usando para los archivos de parse	 */

		public:
			
			/*! \fn			eNet::eNet( void )
			*	\brief		Constructor.
			*	\param		HINSTANCE hInstance	Instancia de la ventana.
			*	\return		None.
			*/
			eNet( HINSTANCE hInstance );

			/*! \fn			eNet::~eNet( void )
			*	\brief		Destructor. LLama a la funci�n Release.
			*	\param		None
			*	\return		None.
			*/
			~eNet( void );

			/*! \fn			HRESULT eNet::CreateInterface( const char *c_achAPI )
			*	\brief		Dependiendo del nombre que le pasemos crea y pide memoria para una DLL 
			*				\n	u otra utilizando la funci�n LoadLibrary. 
			*				\n	Despu�s llamar� la funci�n CreateInterfacede la DLL utilizando la funci�n GetProcAddress.
			*	\param		const char *c_achAPI	
			*	\return		HRESULT	------.
			*/
			HRESULT CreateInterface( const char *c_achAPI );

			/*! \fn			LPENETINTERFACE eNet::GetInterface( void )
			*	\brief		Devuelve la interfaz.
			*	\param		None.
			*	\return		LPENETINTERFACE	------.
			*/
			LPENETINTERFACE GetInterface( void ){ return m_pInterface; }

			/*! \fn			void eNet::Release( void )
			*	\brief		Llama a la funci�n ReleaseInterface de la DLL y luego destruye la DLL.
			*	\param		None.
			*	\return		------.
			*/
			void Release( void );
	};

	typedef class eNet *LPENET;

#endif