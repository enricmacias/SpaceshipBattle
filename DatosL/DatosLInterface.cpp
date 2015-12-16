/*! \file		DatosLInterface.cpp
 *	\brief		Guarda los objetos de la dll Lógica
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "DatosLInterface.h"

DatosLInterface::DatosLInterface()
{
}

DatosLInterface::~DatosLInterface()
{
}

std::vector < Enemigo > DatosLInterface::getEnem()
{
	return m_iEnemigos;
}

void DatosLInterface::addEnemigo( float x , float y , float rot , float tamaño )
{
	Enemigo enem;

	//Llenamos el objeto con la información pasada por línea de comandos
	enem.setPosX( x );
	enem.setPosY( y );
	enem.setRot( rot );
	enem.setTamaño( tamaño );

	//Añadimos el enemigo en el vector
	m_iEnemigos.push_back( enem );
}

void DatosLInterface::Piensa( int i )
{
	Vector2D dist;
	Vector2D peligro;
	float aux, auxP;
	float desviacio;
	float distpeligro = 1000;
	int proxim = 0, Pond = 1;

	dist.setX( mSat[i].getPos().getX() - N.getPos().getX());
	dist.setY( mSat[i].getPos().getY() - N.getPos().getY());
	aux = dist.getModulo();
	
	if( aux < 25)
	{
		mSat[i].setDir(N.getPos().getX(), N.getPos().getY());
		if( mSat[i].getVel().getModulo() < 2)
		{
			mSat[i].setFuerza(0.5);
		}
		else
		{
			mSat[i].Reduce(2);
			mSat[i].setFuerza(0);
		}
		mSat[i].setTra();
		desviacio = mSat[i].getTra() - mSat[i].getRot();
		if(desviacio > 5 || desviacio < 5)
		{
			mSat[i].setFuerza(1);
			if( mSat[i].getVel().getModulo() < 2)
				mSat[i].Reduce(2);
		}
		else
		{
			if(aux > 10)
			{
				mSat[i].setFuerza(1);
				if( mSat[i].getVel().getModulo() < 2)
				mSat[i].Reduce(2);
			}
		}
		if(aux < 9)
		{
			if(mSat[i].getCarga())
				mSat[i].Dispara();
		}
		if(aux < 6)
		{
			mSat[i].setFuerza(0);
			mSat[i].Reduce(0.5);
		}
		for( int j=0 ; j < m_iEnemigos.size(); j++ )
		{
			if( m_iEnemigos[ j ].getVisible() )
			{
				peligro.setX( m_iEnemigos[j].getPos().getX() - mSat[i].getPos().getX());
				peligro.setY( m_iEnemigos[j].getPos().getY() - mSat[i].getPos().getY());
				auxP = peligro.getModulo();
				if(auxP < distpeligro)
				{
					distpeligro = auxP;
					proxim = i;
				}
			}
		}
		peligro.setX( (m_iEnemigos[proxim].getPos().getX() - mSat[i].getPos().getX()));
		peligro.setY( (m_iEnemigos[proxim].getPos().getY() - mSat[i].getPos().getY()));
		mSat[i].setPeligro( - peligro.getX(), - peligro.getY());
		if(mSat[i].getPeligro().getModulo() < 2)
		{
			mSat[i].setDir(mSat[i].getPeligro().getX(), mSat[i].getPeligro().getY());
			mSat[i].Reduce(0.9);
			mSat[i].setFuerza(2);
		}	
		else
		{
			if(mSat[i].getPeligro().getModulo() < 4)
			{
				mSat[i].setDir(mSat[i].getDir().getX() + mSat[i].getPeligro().getX(), mSat[i].getDir().getY() + mSat[i].getPeligro().getY());
				mSat[i].Reduce(1.5);
				mSat[i].setFuerza(1);
			}
		}
	}
	else
	{
		mSat[i].Reduce(0.5);
	}
	if(N.getBala().getVisible())
	{
		peligro.setX( mSat[i].getPos().getX() - N.getBala().getPos().getX());
		peligro.setY( mSat[i].getPos().getY() - N.getBala().getPos().getY());
		
		if( peligro.getModulo() < 4 )
		{
			mSat[i].setDir( peligro.getY(), peligro.getX());
			mSat[i].Reduce(2);
			mSat[i].setFuerza(4);
		}
	}
}

void DatosLInterface::Solver( int inum, int i )
{
	float MAX_ESCENARI = 40;
	float pasoIntegracion = 0.05;
	float borde = MAX_ESCENARI/5;
	Vector2D Vaux;
	Vector2D Daux;
	float PosX, PosY;
	float Faux;
	Bala _b;

	if(Server == 0)
		pasoIntegracion = 0.04;
	else
		pasoIntegracion = 0.05;
	
	switch (inum)
	{
		case 1:
			Vaux = N.getVel();
			PosX = N.getPosX();
			PosY = N.getPosY();
			Faux = N.getFuerza();
			Daux = N.getDir();
			break;
		case 2:
			Vaux = mSat[i].getVel();
			PosX = mSat[i].getPosX();
			PosY = mSat[i].getPosY();
			Faux = mSat[i].getFuerza();
			Daux = mSat[i].getDir();
			break;
	}
	
	float VauxX = Vaux.getX();
	float VauxY = Vaux.getY();

	//Si casi estamos fuera del escenario
	if( PosX < -(MAX_ESCENARI - borde) ) 
	{
		VauxX = VauxX/1.03;
	}

	if( PosX > (MAX_ESCENARI - borde ) )
	{
		VauxX = VauxX/1.03;
	}

	if( PosY < -(MAX_ESCENARI - borde) ) 
	{
		VauxY = VauxY/1.03;
	}
	
	if( PosY > (MAX_ESCENARI - borde) )
	{
		VauxY = VauxY/1.03;
	}
	
	////Si estamos fuera del escenario
	if( ( PosX < -(MAX_ESCENARI) ) || ( PosX > (MAX_ESCENARI) ) )
	{
		Vaux.setVector( -VauxX , VauxY );
	}

	if( ( PosY < -(MAX_ESCENARI) ) || ( PosY > (MAX_ESCENARI) ) )
	{
		Vaux.setVector( VauxX , -VauxY );
	}

	//Si estamos dentro del escenario
	if( ( PosX > -MAX_ESCENARI ) && ( PosX < MAX_ESCENARI ) && ( PosY > -MAX_ESCENARI ) && ( PosY < MAX_ESCENARI ) )
	{
		VauxX += pasoIntegracion * Faux * Daux.getX();
		VauxY += pasoIntegracion * Faux * Daux.getY();
		
		Vaux.setVector( VauxX , VauxY );
	}
	
	PosX += pasoIntegracion * VauxX;
	PosY += pasoIntegracion * VauxY;

	switch (inum)
	{
		case 1:
			N.setVel( Vaux );
			N.setPosX( PosX );
			N.setPosY( PosY );
			if (N.getBala().getVisible())
			{
				_b = BSolver(N.getBala());
				N.setBala(_b);
			}
			else
				N.setCarga(true);
			if (N.getInmune())
				N.setCount(N.getCount() - 1);
			break;
		case 2:
			mSat[i].setVel( Vaux );
			mSat[i].setPosX( PosX );
			mSat[i].setPosY( PosY );
			if (mSat[i].getBala().getVisible())
			{
				_b = BSolver(mSat[i].getBala());
				mSat[i].setBala(_b);
			}
			else
				mSat[i].setCarga(true);
			if (mSat[i].getInmune())
				mSat[i].setCount(mSat[i].getCount() - 1);
			break;
	}
}

Bala DatosLInterface::BSolver( Bala B )
{
	float MAX_ESCENARI = 40;
	float pasoIntegracion = 0.05;
	Vector2D aux;
	float auxX, auxY;

	//Si estamos dentro del escenario
	if( ( B.getPosX() > -MAX_ESCENARI ) && ( B.getPosX() < MAX_ESCENARI ) && ( B.getPosY() > -MAX_ESCENARI ) && ( B.getPosY() < MAX_ESCENARI ) )
	{
		aux = B.getPos();
		auxX = aux.getX();
		auxY = aux.getY();

		auxX += pasoIntegracion * 3 * B.getDir().getX();
		auxY += pasoIntegracion * 3 * B.getDir().getY();

		B.setPosX( auxX );
		B.setPosY( auxY );
	}
	else
	{
		B.setVisible(false);
	}
	return B;
}

void DatosLInterface::Colisiona( void )
{
	float aux = 0;
	float auxB = 0;
	Vector2D dist;
	Vector2D distB;
	
	for( int i=0 ; i < m_iEnemigos.size(); i++ )
	{
		if( m_iEnemigos[ i ].getVisible() )
		{
			dist.setX( m_iEnemigos[ i ].getPos().getX() - N.getPos().getX());
			dist.setY( m_iEnemigos[ i ].getPos().getY() - N.getPos().getY());
			aux = dist.getModulo();
			
			if( aux < m_iEnemigos[ i ].getTamaño()*1.7 && !(N.getInmune()))
			{
				N.setVidas(N.getVidas() - 1);
				N.Stop();
				N.setInmune(true);
				N.setCount(100);
				m_iEnemigos[ i ].setVisible( false );
			}
			
			if(N.getBala().getVisible())
			{
				distB.setX( m_iEnemigos[ i ].getPos().getX() - N.getBala().getPos().getX());
				distB.setY( m_iEnemigos[ i ].getPos().getY() - N.getBala().getPos().getY());
				auxB = distB.getModulo();
				if( auxB < m_iEnemigos[ i ].getTamaño() )
				{
					N.getBala().setVisible(false);
					N.setCarga(true);
					m_iEnemigos[ i ].setVisible( false );
				}
			}
			if(Server == 0)
			{
				for( int j=0 ; j < mSat.size(); j++ )
				{
					dist.setX( m_iEnemigos[ i ].getPos().getX() - mSat[j].getPos().getX());
					dist.setY( m_iEnemigos[ i ].getPos().getY() - mSat[j].getPos().getY());
					aux = dist.getModulo();
					if( aux < m_iEnemigos[ i ].getTamaño() && !(mSat[j].getInmune()))
					{
						mSat[j].setVidas(mSat[j].getVidas() - 1);
						if (mSat[j].getVidas() < 1)
							mSat[j].setVisible(false);
						mSat[j].Stop();
						mSat[j].setInmune(true);
						mSat[j].setCount(100);
						m_iEnemigos[ i ].setVisible( false );
					}
					if(mSat[j].getBala().getVisible())
					{
						distB.setX( m_iEnemigos[ i ].getPos().getX() - mSat[j].getBala().getPos().getX());
						distB.setY( m_iEnemigos[ i ].getPos().getY() - mSat[j].getBala().getPos().getY());
						auxB = distB.getModulo();
						if( auxB < m_iEnemigos[ i ].getTamaño() )
						{
							mSat[j].getBala().setVisible(false);
							mSat[j].setCarga(true);
							m_iEnemigos[ i ].setVisible( false );
						}
					}
					if(mSat[j].getBala().getVisible() && !(N.getInmune()))
					{
						distB.setX( N.getPos().getX() - mSat[j].getBala().getPos().getX());
						distB.setY( N.getPos().getY() - mSat[j].getBala().getPos().getY());
						auxB = distB.getModulo();
						if( auxB < 1 )
						{
							mSat[j].getBala().setVisible(false); 
							mSat[j].setCarga(true);
							N.setVidas(N.getVidas() -1);
							N.Stop();
							N.setInmune(true);
							N.setCount(100);
						}
					}
					if(N.getBala().getVisible() && !(mSat[j].getInmune()))
					{
						distB.setX( mSat[j].getPos().getX() - N.getBala().getPos().getX());
						distB.setY( mSat[j].getPos().getY() - N.getBala().getPos().getY());
						auxB = distB.getModulo();
						if( auxB < 1 )
						{
							N.getBala().setVisible(false); 
							N.setCarga(true);
							mSat[j].setVidas(mSat[j].getVidas() -1);
							if (mSat[j].getVidas() < 1)
									mSat[j].setVisible(false);
							mSat[j].Stop();
							mSat[j].setInmune(true);
							mSat[j].setCount(100);
						}
					}
				}
			}
		}
	}
	
}
