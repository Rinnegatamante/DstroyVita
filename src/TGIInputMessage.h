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
#pragma once

#include "TGIGlobals.h"
#include "TGIFile.h"

/* TGIInputMessage

	messages to objects
	it has the ID of the destination object, and an ID
	other data can be use for a specific platform (key ID for the system...)

*/

class TGIInputMessage
{
public:
	TGIInputMessage(void);
public:
	~TGIInputMessage(void);

	//destination object (has to be in the TGIMain vector)
	TGIuint16 lIdRecipient;
	//ID of the message (platform independent!)
	TGIuint16 lId;
	//if the message is sent when the button is keeped pressed
	TGIuint8 bAutofire;
	//name
	char strName[256];

	//SDL related
	TGIlong sdlKey;
	SDL_JoyAxisEvent axisEvent;
	SDL_JoyButtonEvent buttonEvent;
	SDL_JoyHatEvent hatEvent;
	char nAxisDir;

	/* TODO

	init function

	*/
	bool save(TGIFile& file);
	bool load(TGIFile& file);
public:
	bool autoFill(void);
public:
	void reset(void);
};
