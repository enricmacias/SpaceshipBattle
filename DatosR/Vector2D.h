/*! \file		Vector2D.h
 *	\brief		Objeto Vector2D para tratar información que necesita de dos coordenadas
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

/*! \class		Vector2D
*	\brief		Clase para tratar variables que necessiten de dos coordenadas para definir-se.
*/
class Vector2D
{
	private:
		float mModulo;			/*!< Módulo			*/
		float mX;				/*!< Componente X	*/
		float mY;				/*!< Componente Y	*/
	
	public:

		/*! \fn			Vector2D::Vector2D( void )
		*	\brief		Constructor. Inicializa todas las variables.
		*	\param		None.
		*	\return		None.
		*/
		Vector2D( void );

		/*! \fn			Vector2D::Vector2D( void )
		*	\brief		Constructor. Inicializa las variables con la información pasada por linia de comandos.
		*	\param		float _x	Coordenada X.
		*	\param		float _y	Coordenada Y.
		*	\return		None.
		*/
		Vector2D( float _x , float _y );

		/*! \fn			Vector2D::~Vector2D( void )
		*	\brief		Destructor.
		*	\param		None.
		*	\return		None.
		*/
		~Vector2D( void );
		
		/*! \fn			float Vector2D::getModulo( void )
		*	\brief		Devuelve el Modulo.
		*	\param		None.
		*	\return		float	Modulo.
		*/
		float getModulo( void );

		/*! \fn			void Vector2D::Normaliza( void )
		*	\brief		Normaliza el vector.
		*	\param		None.
		*	\return		None.
		*/
		void Normaliza( void );

		/*! \fn			void Vector2D::operator=( Vector2D vct )
		*	\brief		Implementación del operador =.
		*	\param		Vector2D vct	Vector.
		*	\return		None.
		*/
		void operator=( Vector2D vct );

		/*! \fn			void Vector2D::operator=( Vector2D vct )
		*	\brief		Implementación del operador +.
		*	\param		Vector2D vct	Vector.
		*	\return		Vector2D		Vector.
		*/
		Vector2D *operator-( Vector2D vct );

		/*! \fn			void Vector2D::operator=( Vector2D vct )
		*	\brief		Implementación del operador -.
		*	\param		Vector2D vct	Vector.
		*	\return		Vector2D		Vector.
		*/
		Vector2D *operator+( Vector2D vct );

		/*! \fn			void Vector2D::setX( float _x )
		*	\brief		Establece la coordenada X.
		*	\param		float _x	Coordenada X.
		*	\return		None.
		*/
		void setX( float _x );

		/*! \fn			void Vector2D::setY( float _y )
		*	\brief		Establece la coordenada Y.
		*	\param		float _y	Coordenada Y.
		*	\return		None.
		*/
		void setY( float _y );

		/*! \fn			void Vector2D::setVector( float _x , float _y )
		*	\brief		Establece un vector x , y.
		*	\param		float _x	Coordenada X.
		*	\param		float _y	Coordenada Y.
		*	\return		None.
		*/
		void setVector( float _x , float _y );

		/*! \fn			float Vector2D::getX( void )
		*	\brief		Devuelve la coordenada X.
		*	\param		None.
		*	\return		float	Coordenada X.
		*/
		float getX( void );

		/*! \fn			float Vector2D::getY( void )
		*	\brief		Devuelve la coordenada Y.
		*	\param		None.
		*	\return		float	Coordenada Y.
		*/
		float getY( void );

};

#endif