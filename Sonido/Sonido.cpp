/*! \file		Sonido.cpp
 *	\brief		Dll que gestiona el sonido del juego
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/

#include "Sonido.h"

BOOL WINAPI DllEntryPoint( HINSTANCE hDll, DWORD fdwReason, LPVOID lpvReserved )
{
	switch( fdwReason )
	{
		// called when we attach to the DLL
		case DLL_PROCESS_ATTACH:
			/* dll init/setup stuff */
		break;

		case DLL_PROCESS_DETACH:
			/* dll shutdown/release stuff */
		break;

		default:
		break;
	}
   
	return TRUE;
}

HRESULT CreateSInterface( HINSTANCE hDLL , DatosSInterface **ppDatosSInterface )
{
	if( !*ppDatosSInterface )
	{
		*ppDatosSInterface = new Sonido( hDLL );
		return TRUE;
	}
	return !TRUE;
}

HRESULT ReleaseSInterface( DatosSInterface **ppDatosSInterface )
{
	if( !*ppDatosSInterface )
	{
		return !TRUE;
	}
	delete *ppDatosSInterface;
	*ppDatosSInterface = NULL;
	return TRUE;
}

Sonido::Sonido()
{
}
			
Sonido::Sonido( HINSTANCE hDLL )
{
	m_hDLL = hDLL;
}
			
Sonido::~Sonido()
{
}

void Sonido::ERRCHECK(FMOD_RESULT gResult)
{
    if (gResult != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", gResult, FMOD_ErrorString(gResult));
        exit(-1);
    }
}

void Sonido::LoadSounds( int iDisplay )
{
	FMOD::Sound* Sonido;
	switch( iDisplay )
	{
		case 1:
			gResult = gSystem->createSound("../Musica/Display1.mp3", FMOD_SOFTWARE | FMOD_2D, 0, &Sonido);
			ERRCHECK(gResult);
			vgSounds.push_back( Sonido );
			break;

		case 2:
			gResult = gSystem->createSound("../Musica/Display2.mp3", FMOD_SOFTWARE | FMOD_2D, 0, &Sonido);
			ERRCHECK(gResult);
			vgSounds.push_back( Sonido );

			gResult = gSystem->createSound("../Musica/Display4.mp3", FMOD_SOFTWARE | FMOD_2D, 0, &Sonido);
			ERRCHECK(gResult);
			vgSounds.push_back( Sonido );

			gResult = gSystem->createSound("../Musica/Disparo.mp3", FMOD_SOFTWARE | FMOD_2D, 0, &Sonido);
			ERRCHECK(gResult);
			vgSounds.push_back( Sonido );
			break;
	}
}
			
HRESULT Sonido::Init( void )
{
	// Channels initialization
	vgChannels.push_back(0);
	vgChannels.push_back(0);
	vgChannels.push_back(0);

	// Create a System object and initialize.
    gResult = FMOD::System_Create(&gSystem);
    ERRCHECK(gResult);
    
    gResult = gSystem->getVersion(&gVersion);
    ERRCHECK(gResult);

    if (gVersion < FMOD_VERSION)
    {
        printf("Error!  You are using an old gVersion of FMOD %08x.  This program requires %08x\n", gVersion, FMOD_VERSION);
        return false;
    }
    
    gResult = gSystem->getNumDrivers(&gNumdrivers);
    ERRCHECK(gResult);

    if (gNumdrivers == 0)
    {
        gResult = gSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
        ERRCHECK(gResult);
    }
    else
    {
        gResult = gSystem->getDriverCaps(0, &gCaps, 0, 0, &gSpeakermode);
        ERRCHECK(gResult);

        gResult = gSystem->setSpeakerMode(gSpeakermode);       // Set the user selected speaker mode.
        ERRCHECK(gResult);

        if (gCaps & FMOD_CAPS_HARDWARE_EMULATED)             // The user has the 'Acceleration' slider set to off!  This is really bad for latency!.
        {                                                   // You might want to warn the user about this.
            gResult = gSystem->setDSPBufferSize(1024, 10);
            ERRCHECK(gResult);
        }

        gResult = gSystem->getDriverInfo(0, gName, 256, 0);
        ERRCHECK(gResult);

        if (strstr(gName, "SigmaTel"))                       // Sigmatel sound devices crackle for some reason if the format is PCM 16bit.  PCM floating point output seems to solve it.
        {
            gResult = gSystem->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR);
            ERRCHECK(gResult);
        }
    }

    gResult = gSystem->init(100, FMOD_INIT_NORMAL, 0);
    if (gResult == FMOD_ERR_OUTPUT_CREATEBUFFER)             // Ok, the speaker mode selected isn't supported by this soundcard.  Switch it back to stereo.
    {
        gResult = gSystem->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
        ERRCHECK(gResult);
            
        gResult = gSystem->init(100, FMOD_INIT_NORMAL, 0);    // ... and re-init.
        ERRCHECK(gResult);
	}

	return TRUE;
}

void Sonido::Play( int iSonido )
{
	bool paused;
	switch( iSonido )
	{
		case 1:
			gResult = gSystem->playSound(FMOD_CHANNEL_FREE, vgSounds[0], false, &vgChannels[0]);
            ERRCHECK(gResult);
			break;
		case 2:
			vgChannels[0]->getPaused(&paused);
            vgChannels[0]->setPaused(!paused);
			gResult = gSystem->playSound(FMOD_CHANNEL_FREE, vgSounds[1], false, &vgChannels[0]);
            ERRCHECK(gResult);
			break;
		case 3:
			vgChannels[1]->getPaused(&paused);
            vgChannels[1]->setPaused(!paused);
			gResult = gSystem->playSound(FMOD_CHANNEL_FREE, vgSounds[2], false, &vgChannels[0]);
            ERRCHECK(gResult);
			break;
		case 4:
			break;
		case 5:
			break;
	}
}

void Sonido::Suena( void )
{
	gSystem->update();
}

void Sonido::DeInit( void )
{
    // Shut down
    gResult = vgSounds[0]->release();
    ERRCHECK(gResult);
    gResult = vgSounds[1]->release();
    ERRCHECK(gResult);
    gResult = vgSounds[2]->release();
    ERRCHECK(gResult);
	gResult = vgSounds[3]->release();
    ERRCHECK(gResult);

    gResult = gSystem->close();
    ERRCHECK(gResult);
    gResult = gSystem->release();
    ERRCHECK(gResult);
}