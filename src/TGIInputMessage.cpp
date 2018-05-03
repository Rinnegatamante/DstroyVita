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
#include "TGIInputMessage.h"

#define CURRENT_VERSION 2

TGIInputMessage::TGIInputMessage(void)
{
	reset();
}

TGIInputMessage::~TGIInputMessage(void)
{
}

void TGIInputMessage::reset(void)
{
	axisEvent.which = -1;
	axisEvent.axis = -1;
	buttonEvent.which = -1;
	hatEvent.which = -1;
	buttonEvent.button = -1;
	hatEvent.hat = -1;
	sdlKey = 0;
	strName[0] = 0;
	nAxisDir = 0;
}

bool TGIInputMessage::save(TGIFile& tgiFile)
{
	if (!tgiFile.isOpen())
		return false;

	TGIuint16 order = 255;
	TGIuint16 version = CURRENT_VERSION;

	tgiFile.write((char*)&order, 2);
	tgiFile.write((char*)&version, 2);
	tgiFile.write((char*)&lId, 2);
	tgiFile.write((char*)&lIdRecipient, 2);
	tgiFile.write(strName, 256);
	tgiFile.write((char*)&bAutofire, 1);

	//sdl related
	tgiFile.write((char*)&sdlKey, sizeof(sdlKey));
	//axis
	tgiFile.write((char*)&(axisEvent.axis), sizeof(axisEvent.axis));
	tgiFile.write((char*)&(axisEvent.which), sizeof(axisEvent.which));
	tgiFile.write((char*)&(axisEvent.value), sizeof(axisEvent.value));
	tgiFile.write((char*)&(axisEvent.type), sizeof(axisEvent.type));
	//button
	tgiFile.write((char*)&(buttonEvent.button), sizeof(buttonEvent.button));
	tgiFile.write((char*)&(buttonEvent.which), sizeof(buttonEvent.which));
	tgiFile.write((char*)&(buttonEvent.type), sizeof(buttonEvent.type));
	tgiFile.write((char*)&(buttonEvent.state), sizeof(buttonEvent.state));
	//hat
	tgiFile.write((char*)&(hatEvent.type), sizeof(hatEvent.type));
	tgiFile.write((char*)&(hatEvent.which), sizeof(hatEvent.which));
	tgiFile.write((char*)&(hatEvent.hat), sizeof(hatEvent.hat));
	tgiFile.write((char*)&(hatEvent.value), sizeof(hatEvent.value));

	tgiFile.write((char*)&nAxisDir, sizeof(char));

	return true;
}

bool TGIInputMessage::load(TGIFile& tgiFile)
{
	if (!tgiFile.isOpen())
		return false;

	if (tgiFile.eof())
		return false;

	TGIuint16 order;
	TGIuint16 version;

	tgiFile.read((char*)&order, 2);
	tgiFile.read((char*)&version, 2);
	TGIGlobals::endianConvert(order, &version, sizeof(version));
	tgiFile.read((char*)&lId, 2);
	TGIGlobals::endianConvert(order, &lId, sizeof(lId));
	tgiFile.read((char*)&lIdRecipient, 2);
	TGIGlobals::endianConvert(order, &lIdRecipient, sizeof(lIdRecipient));
	tgiFile.read(strName, 256);
	tgiFile.read((char*)&bAutofire, 1);

	if (tgiFile.eof())
		return false;

	//sdl related
	tgiFile.read((char*)&sdlKey, sizeof(sdlKey));
	TGIGlobals::endianConvert(order, &sdlKey, sizeof(sdlKey));
	//axis
	tgiFile.read((char*)&(axisEvent.axis), sizeof(axisEvent.axis));
	TGIGlobals::endianConvert(order, &axisEvent.axis, sizeof(axisEvent.axis));
	tgiFile.read((char*)&(axisEvent.which), sizeof(axisEvent.which));
	TGIGlobals::endianConvert(order, &axisEvent.which, sizeof(axisEvent.which));
	tgiFile.read((char*)&(axisEvent.value), sizeof(axisEvent.value));
	TGIGlobals::endianConvert(order, &axisEvent.value, sizeof(axisEvent.value));
	tgiFile.read((char*)&(axisEvent.type), sizeof(axisEvent.type));
	TGIGlobals::endianConvert(order, &axisEvent.type, sizeof(axisEvent.type));
	//button
	tgiFile.read((char*)&(buttonEvent.button), sizeof(buttonEvent.button));
	TGIGlobals::endianConvert(order, &buttonEvent.button, sizeof(buttonEvent.button));
	tgiFile.read((char*)&(buttonEvent.which), sizeof(buttonEvent.which));
	TGIGlobals::endianConvert(order, &buttonEvent.which, sizeof(buttonEvent.which));
	tgiFile.read((char*)&(buttonEvent.type), sizeof(buttonEvent.type));
	TGIGlobals::endianConvert(order, &buttonEvent.type, sizeof(buttonEvent.type));
	tgiFile.read((char*)&(buttonEvent.state), sizeof(buttonEvent.state));
	TGIGlobals::endianConvert(order, &buttonEvent.state, sizeof(buttonEvent.state));
	//hat
	tgiFile.read((char*)&(hatEvent.type), sizeof(hatEvent.type));
	TGIGlobals::endianConvert(order, &hatEvent.type, sizeof(hatEvent.type));
	tgiFile.read((char*)&(hatEvent.which), sizeof(hatEvent.which));
	TGIGlobals::endianConvert(order, &hatEvent.which, sizeof(hatEvent.which));
	tgiFile.read((char*)&(hatEvent.hat), sizeof(hatEvent.hat));
	TGIGlobals::endianConvert(order, &hatEvent.hat, sizeof(hatEvent.hat));
	tgiFile.read((char*)&(hatEvent.value), sizeof(hatEvent.value));
	TGIGlobals::endianConvert(order, &hatEvent.value, sizeof(hatEvent.value));

	if (version >= 2)
	{
		tgiFile.read((char*)&nAxisDir, sizeof(char));
	}

	return true;
}

bool TGIInputMessage::autoFill(void)
{
	bool bFound = false;

	reset();

	SDL_Event ev;
	SDL_PumpEvents();
	while(SDL_PollEvent(&ev))
	{

	};
	SDL_Delay(500);

	
	while (!bFound)
	{
		SDL_Delay(1);
		//SDL_PumpEvents();

		
		while(SDL_PollEvent(&ev))
		{
			switch(ev.type)
			{
			case SDL_KEYDOWN:
				sdlKey = ev.key.keysym.sym;
				bFound = true;
				break;
			case SDL_KEYUP:
				break;
			case SDL_JOYAXISMOTION:
#ifdef DESKTOP
				if (abs(ev.jaxis.value) > 10000)
#endif
#ifdef __NDS__
				if (abs(ev.jaxis.value) > 5)
#endif
				{
					axisEvent = ev.jaxis;
					bFound = true;
					if (ev.jaxis.value > 0)
						nAxisDir  = 1;
					else
						nAxisDir = -1;
				}			
				break;
			case SDL_JOYBUTTONDOWN:
				buttonEvent = ev.jbutton;
				bFound = true;
				break;
			case SDL_JOYBUTTONUP:
				break;
			case SDL_JOYHATMOTION:
				hatEvent = ev.jhat;
				bFound = true;
				break;
			default:
				break;
			}
		}
	}

	switch (hatEvent.value)
	{
	case SDL_HAT_RIGHTUP:
		hatEvent.value = SDL_HAT_RIGHT;
		break;
	case SDL_HAT_LEFTUP:
		hatEvent.value = SDL_HAT_UP;
		break;
	case SDL_HAT_RIGHTDOWN:
		hatEvent.value = SDL_HAT_DOWN;
		break;
	case SDL_HAT_LEFTDOWN:
		hatEvent.value = SDL_HAT_LEFT;
		break;
	}

	SDL_Delay(200);

	return true;
}


