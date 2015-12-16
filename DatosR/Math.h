/*! \file		Math.h
 *	\brief		
 *  \version	1.0
 *  \author		Andres Fernandez <andresf@salleurl.edu> & Pau Moreno Font <pmfont@salle.url.edu> - DTM La Salle - Barcelona
 *  \date		November 24th, 2008
*/

#ifndef MATH
#define MATH

	#define DTOR	0.0174532925					/*!< 	Use it for convert Degrees to Radians.	*/
	#define RTOD    57.2957795						/*!< 	Use it for convert Radians to Degrees.	*/
	#define TWOPI   6.283185307179586476925287		/*!< 	Two times PI.							*/
	#define PI      3.141592653589793238462643		/*!< 	PI.										*/
	#define PID2    1.570796326794896619231322		/*!< 	Half PI.								*/

	#define CROSSPROD( p1 , p2 , p3 ) p3.Set( p1.GetY() * p2.GetZ() - p1.GetZ() * p2.GetY() , p1.GetZ() * p2.GetX() - p1.GetX() * p2.GetZ() , p1.GetX() * p2.GetY() - p1.GetY() * p2.GetX() );	/*!< 	Do the Vectorial product between p1 and p2 , and set the result in P3.	*/
	#define ABS( x ) ( x < 0 ? -( x ) : ( x ) )								/*!< 	Absolut value of X.				*/
	#define MIN( x , y ) ( x < y ? x : y )									/*!< 	Minium value between x and y.	*/
	#define MAX( x , y ) ( x > y ? x : y )									/*!< 	Maxium value between x and y.	*/
	#define SIGN( x ) ( x < 0 ? ( -1 ) : 1)									/*!< 	Returns the sign of x.			*/
	#define MODULUS( p ) ( sqrt( p.x * p.x + p.y * p.y + p.z * p.z ) )		/*!< 	Returns the length of a vector.	*/

#endif