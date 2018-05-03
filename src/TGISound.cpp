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
#include "TGISound.h"

TGISound::TGISound(void)
{
#ifndef TGI_NOSOUND
#ifndef __NDS__
	sample = NULL;
#else
	se.id = -1;
#endif
#endif
}

TGISound::~TGISound(void)
{
#ifndef TGI_NOSOUND
#ifndef __NDS__
	//sdl
	if (sample)
	{
		Mix_FreeChunk(sample);
	}
	
#else
	//maxmod
	if (se.id != (unsigned int)-1)
	{
		char strDebug[256];
		sprintf(strDebug, "Unloading wav %d...", se.id);
		TGIGlobals::Trace(strDebug);
		mmUnloadEffect( se.id );
		TGIGlobals::Trace("WAV unloaded");
	}
#endif 
#endif
}

bool TGISound::loadFile(std::string cstrFile)
{
#ifndef TGI_NOSOUND
	TGIGlobals::Trace("Loading wav...");
#ifndef __NDS__
	sample = Mix_LoadWAV(cstrFile.c_str());
	return (sample != NULL);
#else
	int nRes = file2res(cstrFile.c_str());
	if (nRes < 0)
	{
		TGIGlobals::Trace("ERROR : WAV not loaded");
		return false;
	}
	mmLoadEffect( nRes );
	se.id = nRes;
	se.rate = (int)(1.0f * (1<<10));
	se.handle = 0;
	se.volume = 255;
	se.panning = 128;

	TGIGlobals::Trace("WAV loaded");

	return true;
#endif

	
#endif
}

bool TGISound::play()
{
#ifndef TGI_NOSOUND
#ifndef __NDS__
	int n = Mix_PlayChannel(-1, sample, 0);
	if (n<0)
	{
		TGIGlobals::Trace(Mix_GetError());
		return false;
	}
	return true;
#else
	mmEffectEx(&se);
	return true;
#endif
#endif
}