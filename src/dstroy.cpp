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
// dstroy.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"


#include "DstroyNetServer.h"
#include "DstroyNetClient.h"

#include "TGIGlobals.h"
#include "DstroyGame.h" 
#include "DstroyTitle.h"
#include "DstroyIntro.h"
#include "DstroyOptions.h"
#include "DstroyMenuAdventure.h"
#include "PadTest.h"
#include "DstroyMenuGP2XCommands.h"
#include "DstroyMenuMain.h"
#include "DstroyMenuNetServer.h"

#include "TGIInputMessage.h"
#include <SDL_image.h>

#include "TGIFile.h"

#include <string.h>


void createCommandsFromScratch()
{
	TGIFile save;
	save.create(DstroyGlobals::addResText("commands"), true);

	TGIInputMessage message;

	message.reset();
	message.lId	= left;
	message.lIdRecipient = 1;
	message.axisEvent.which = 0;
	message.axisEvent.axis = 0;
	message.nAxisDir = -1;
	message.bAutofire = true;
	strncpy(message.strName, "PLAYER1 LEFT", 256);
	message.save(save);

	message.reset();
	message.lId	= right;
	message.lIdRecipient = 1;
	message.axisEvent.which = 0;
	message.axisEvent.axis = 0;
	message.nAxisDir = 1;
	message.bAutofire = true;
	strncpy(message.strName, "PLAYER1 RIGHT", 256);
	message.save(save);

	message.reset();
	message.lId	= up;
	message.lIdRecipient = 1;
	message.axisEvent.which = 0;
	message.axisEvent.axis = 0;
	message.nAxisDir = -1;
	message.bAutofire = true;
	strncpy(message.strName, "PLAYER1 UP", 256);
	message.save(save);

	message.reset();
	message.lId	= down;
	message.lIdRecipient = 1;
	message.axisEvent.which = 0;
	message.axisEvent.axis = 0;
	message.nAxisDir = +1;
	message.bAutofire = true;
	strncpy(message.strName, "PLAYER1 DOWN", 256);
	message.save(save);

	message.reset();
	message.lId	= 10;
	message.lIdRecipient = 1;
	message.buttonEvent.button = 0;
	message.buttonEvent.which = 0;
	message.bAutofire = false;
	strncpy(message.strName, "PLAYER1 FIRE", 256);
	message.save(save);

	save.close();
}

int server()
{
	DstroyNetServer server;
	int i;

	server.open(666);

	while (1)
	{
		if (server.receivePacketWaitingConnect())
		{
			printf("New clients list : \n");
			for (i=0;i<server.vecClientName.size();i++)
			{
				printf("\t%s\n", server.vecClientName[i].c_str());
			}
		}
		SDL_Delay(100);
	}

	return 0;
}

int client(char* strName)
{
	DstroyNetClient client;
	client.setName(strName);

	client.connect("naroin", 666);
	SDL_Delay(15000);
	client.deconnect();

	return 0;
}

int main(int argc, char* argv[])
{
	DstroyGlobals::init();

	TGIGlobals::Trace("starting...");

	DstroyOptions options;
	options.load();

	bool bFullScreen = false;
	int nSpriteSize = 1;
	bool bRotateScreen = false;

	bFullScreen = options.bFullScreen;
	if (options.bDoubleSize)
		nSpriteSize = 2;
	bRotateScreen = options.bRotateScreen;

	TGIGlobals::init(320, 240, nSpriteSize, bFullScreen, bRotateScreen);
#ifndef TGI_NONET
	SDLNet_Init();
#endif

#ifndef __NDS__
	DstroyTitle* pTitle = new DstroyTitle;
#else
	DstroyMenuMain* pTitle = new DstroyMenuMain;
#endif

	while (TGIGlobals::theMain)
	{
		TGIGlobals::theMain->init();
		TGIGlobals::theMain->run();
	}


	TGIGlobals::exit();

	return 0;
}

