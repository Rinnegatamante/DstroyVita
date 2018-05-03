/*
 * Dstroy, a remake of the bomberman-like DOS game from Fully Bugged Software
 * Copyright (C) Michael Doguet
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#include "stdafx.h"
#include "TGIGlobals.h"

#include <iostream>
#include <string>

#include "TGIMain.h"

#include <vitasdk.h>

TGIMain* TGIGlobals::theMain = NULL;
SDL_Surface* TGIGlobals::pScreen = NULL;
TGIint TGIGlobals::screenWidth = 0;
TGIint TGIGlobals::screenHeight = 0;
bool TGIGlobals::bRotateScreen = false;
#ifndef TGI_NOSOUND
#ifndef __NDS__
Mix_Music* TGIGlobals::pMusic = NULL;
TGIuint16 TGIGlobals::nRepeat = 0;
TGIuint16 TGIGlobals::nRepeatPos = 0;
#else
int TGIGlobals::nMusicRes = -1;
#endif //__NDS__
#endif
std::vector<SDL_Joystick*> TGIGlobals::vecJoystick;
TGIuint8 TGIGlobals::nSpriteSize = 2;
#ifdef GP2X
TGIuint8 TGIGlobals::nGP2XmvtMode = 1;
#endif

TGIGlobals::TGIGlobals(void)
{
}

TGIGlobals::~TGIGlobals(void)
{
}

void LOG2FILE(const char *format, ...) {
	__gnuc_va_list arg;
	int done;
	va_start(arg, format);
	char msg[512];
	done = vsprintf(msg, format, arg);
	va_end(arg);
	int i;
	sprintf(msg, "%s\n", msg);
	FILE* log = fopen("ux0:/data/dstroy.log", "a+");
	if (log != NULL) {
		fwrite(msg, 1, strlen(msg), log);
		fclose(log);
	}
}

void TGIGlobals::Trace(std::string strMessage, ...)
{
	//a refaire
#ifdef _TGI_DEBUG
	LOG2FILE("%s",strMessage.c_str());
#endif

}

bool TGIGlobals::init(TGIint screenWidth, TGIint screenHeight, TGIuint8 nSpriteSize, bool bFullScreen, bool bRotateScreen)
{
 	TGIGlobals::nSpriteSize = nSpriteSize;
	TGIGlobals::bRotateScreen = bRotateScreen;

	TGIGlobals::screenWidth = screenWidth;
	TGIGlobals::screenHeight = screenHeight;



	//SDL init
	TGIint err  = 0;
#ifndef __NDS__
	err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
#endif

	if (err < 0)
	{ 
		TGIGlobals::Trace("Cant initiate SDL: %s\n", SDL_GetError()); 
		return false;
	}
	TGIGlobals::Trace("SDL initiated");

	TGIGlobals::nSpriteSize = 2;
	TGIGlobals::screenWidth = 320;
	TGIGlobals::screenHeight = 240;

	scePowerSetArmClockFrequency(444);
	scePowerSetBusClockFrequency(222);
	scePowerSetGpuClockFrequency(222);
	scePowerSetGpuXbarClockFrequency(166);
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
	
	TGIGlobals::pScreen = SDL_SetVideoMode(TGIGlobals::screenWidth*nSpriteSize, TGIGlobals::screenHeight*nSpriteSize, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (pScreen == NULL)
	{
		TGIGlobals::Trace("Error while initializing screen\n");
		return false;
	}
	SDL_SetVideoModeScaling(0, 0, 960, 544);
	
	//joysticks
	int nJoys = SDL_NumJoysticks() - 1;
	SDL_Joystick* pJoy;
	for (;nJoys>=0;nJoys--)
	{
		pJoy = SDL_JoystickOpen(nJoys);
		if (pJoy)
		{
			vecJoystick.push_back(pJoy);
		}
	}
	//sound
#ifndef TGI_NOSOUND
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	int n;
	n = Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 128);
	Mix_HookMusicFinished(music_finished);
#endif

	SDL_ShowCursor(0);

	return true;
}

bool TGIGlobals::exit(void)
{
#ifndef TGI_NOSOUND
#ifndef __NDS__
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
#endif
#endif

	
	for (TGIuint16 i=0;i<vecJoystick.size();i++)
	{
		SDL_JoystickClose(vecJoystick[i]);
	}

	SDL_Quit();

	return true;
}


void TGIGlobals::endianConvert(TGIuint16 order, void* pData, TGIuint16 nLen)
{
	if (order == 255)
	{
		//no need to convert
		return;
	}

	TGIint i;
	TGIuint8 t;
	for (i=nLen/2-1;i>=0;i--)
	{
		t = ((TGIuint8*)pData)[i];
		((TGIuint8*)pData)[i] = ((TGIuint8*)pData)[nLen-i-1];
		((TGIuint8*)pData)[nLen-i-1] = t;
	}
}


bool TGIGlobals::playMusic(std::string cstrFile, TGIuint16 nRepeat, TGIuint16 nRepeatPos)
{
#ifndef TGI_NOSOUND
	char strDebug[256];
	sprintf(strDebug, "playMusic:%s", cstrFile.c_str());
	TGIGlobals::Trace(strDebug);
	TGIGlobals::stopMusic();

#ifndef __NDS__
	TGIGlobals::pMusic = Mix_LoadMUS(cstrFile.c_str());
	if (!TGIGlobals::pMusic)
		return false;
	TGIGlobals::nRepeatPos = nRepeatPos;
	TGIGlobals::nRepeat = nRepeat - 1;

	return Mix_PlayMusic(TGIGlobals::pMusic, 1) == 0;
#else
	nMusicRes = file2res(cstrFile.c_str());
	sprintf(strDebug, "ressource=%d", nMusicRes);
	TGIGlobals::Trace(strDebug);
		
	mmLoad(nMusicRes);
	mmStart( nMusicRes, MM_PLAY_LOOP );
#endif

#endif
	return false;
}

bool TGIGlobals::stopMusic(void)
{
#ifndef TGI_NOSOUND
#ifndef __NDS__
	if (TGIGlobals::pMusic)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(TGIGlobals::pMusic);
		TGIGlobals::pMusic = NULL;
	}
#else
	//maxmod
	if (nMusicRes != -1)
	{
		if (mmActive())
		{
			mmStop( );
		}
		mmUnload(nMusicRes);

		nMusicRes = -1;
	}
#endif
#endif
	return true;
}
#ifndef TGI_NOSOUND
#ifndef __NDS__
void TGIGlobals::music_finished()
{

	if (nRepeat == 0)
		return;
	if (nRepeat > 0)
		nRepeat--;

	
	Mix_PlayMusic(TGIGlobals::pMusic, 1);
	Mix_PauseMusic();
	Mix_SetMusicPosition(nRepeatPos);
	Mix_ResumeMusic();

}
#endif
#endif
