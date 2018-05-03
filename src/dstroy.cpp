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
	save.create(DstroyGlobals::addResText("commandsnds"), true);

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

	/*message.reset();
	message.lId	= left;
	message.lIdRecipient = 2;
	message.buttonEvent.button = GP2X_BUTTON_B;
	message.buttonEvent.which = 0;
	strncpy(message.strName, "LEFT", 256);
	message.bAutofire = true;
	message.save(save);

	message.reset();
	message.lId	= right;
	message.lIdRecipient = 2;
	message.buttonEvent.button = GP2X_BUTTON_A;
	message.buttonEvent.which = 0;
	strncpy(message.strName, "RIGHT", 256);
	message.bAutofire = true;
	message.save(save);

	message.reset();
	message.lId	= up;
	message.lIdRecipient = 2;
	message.buttonEvent.button = GP2X_BUTTON_X;
	message.buttonEvent.which = 0;
	strncpy(message.strName, "UP", 256);
	message.bAutofire = true;
	message.save(save);

	message.reset();
	message.lId	= down;
	message.lIdRecipient = 2;
	message.buttonEvent.button = GP2X_BUTTON_Y;
	message.buttonEvent.which = 0;
	strncpy(message.strName, "DOWN", 256);
	message.bAutofire = true;
	message.save(save);

	message.reset();
	message.lId	= 10;
	message.lIdRecipient = 2;
	message.buttonEvent.button = GP2X_BUTTON_SELECT;
	message.buttonEvent.which = 0;
	strncpy(message.strName, "FIRE", 256);
	message.bAutofire = false;
	message.save(save);*/

/*	message.reset();
	message.sdlKey = 0;
	message.axisEvent.which = -1;
	message.hatEvent.which = -1;
	message.buttonEvent.which = -1;

	message.reset();
	message.lIdRecipient = 3;
	message.lId = left;
	message.bAutofire = true;
	strncpy(message.strName, "LEFT", 256);
	message.save(save);
	message.lId = right;
	strncpy(message.strName, "RIGHT", 256);
	message.save(save);
	message.lId = up;
	strncpy(message.strName, "UP", 256);
	message.save(save);
	message.lId = down;
	strncpy(message.strName, "DOWN", 256);
	message.save(save);
	message.lId = 10;
	message.bAutofire = false;
	strncpy(message.strName, "FIRE", 256);
	message.save(save);

	message.reset();
	message.lIdRecipient = 4;
	message.lId = left;
	message.bAutofire = true;
	strncpy(message.strName, "LEFT", 256);
	message.save(save);
	message.lId = right;
	strncpy(message.strName, "RIGHT", 256);
	message.save(save);
	message.lId = up;
	strncpy(message.strName, "UP", 256);
	message.save(save);
	message.lId = down;
	strncpy(message.strName, "DOWN", 256);
	message.save(save);
	message.lId = 10;
	message.bAutofire = false;
	strncpy(message.strName, "FIRE", 256);
	message.save(save);*/

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

	//DstroyGlobals::convertLevels();
	//return 0;
	//createCommandsFromScratch();
	//return 0;
/*#ifdef __NDS__

	powerON(POWER_ALL);  
	videoSetMode(MODE_0_2D | DISPLAY_BG0_ACTIVE);
	vramSetBankA(VRAM_A_MAIN_BG);
	BG0_CR = BG_MAP_BASE(31);
	BG_PALETTE[255] = RGB15(31,31,31);
	consoleInitDefault((u16*)SCREEN_BASE_BLOCK(31), (u16*)CHAR_BASE_BLOCK(0), 16);
	if (!fatInitDefault())  
	{
		TGIGlobals::Trace("Unable to initialize media device!");
		return false;
	}

	WaitForVblank();
	WaitForVblank();

	

#endif*/

	TGIGlobals::Trace("starting...");

	DstroyOptions options;
	options.load();

	bool bFullScreen = false;
	int nSpriteSize = 1;
	bool bRotateScreen = false;
/*	int i;
	for (i=1;i<argc;i++)
	{
		if (strcmp(argv[i], "-fs") == 0)
		{
			bFullScreen = true;
		}
		if (strcmp(argv[i], "-ds") == 0)
		{
			nSpriteSize = 2;
		}
	}*/

	bFullScreen = options.bFullScreen;
	if (options.bDoubleSize)
		nSpriteSize = 2;
	bRotateScreen = options.bRotateScreen;

#ifdef GP2X
	TGIGlobals::nGP2XmvtMode = options.nGP2XmvtMode;
#endif

	TGIGlobals::init(320, 240, nSpriteSize, bFullScreen, bRotateScreen);
#ifndef TGI_NONET
	SDLNet_Init();
#endif

	/*if (argc == 2 && argv[1][0] == 's')
	{
		DstroyMenuNetServer* pMenu = new DstroyMenuNetServer;
		pMenu->init();
		pMenu->run();

		return 0;
		//return server();
	}
	if (argc == 3 && argv[1][0] == 'c')
	{
		return client(argv[2]);
	}*/
	
	/*DstroyGame::params.cstrFile = argv[1];
	DstroyGame::params.setMode(GAMEMODE_FIGHT);
	DstroyGame::params.nPlayers = 4;

	DstroyGame* game = new DstroyGame;
	game->init();
	game->run();

	return 0;*/

/*	for (i=1;i<argc;i++)
	{
		if (strcmp(argv[i], "-fs") != 0 && strcmp(argv[i], "-ds") != 0)
		{
			DstroyGame::params.cstrFile = argv[1];
			DstroyGame::params.setMode(GAMEMODE_FIGHT);
			DstroyGame::params.nPlayers = 4;

			DstroyGame* game = new DstroyGame;
			game->init();
			game->run();

			return 0;
		}
	}*/

	/*DstroyGame::params.nPlayers = 1;
	DstroyGame::params.nDifficulty = 1;
	DstroyGame::params.setLevel(2);
	
	DstroyGame::params.setMode(GAMEMODE_ADVENTURE);
	
	DstroyGame::params.pnLives[0] = 5;
	DstroyGame::params.pnBombDuration[0] = 4;
	DstroyGame::params.pnBombs[0] = 20;
	DstroyGame::params.pnFlame[0] = 10;


	DstroyGame* game = new DstroyGame;
	game->init();
	game->run();

	return 0;*/
#ifndef __NDS__
	DstroyTitle* pTitle = new DstroyTitle;
#else
	DstroyMenuMain* pTitle = new DstroyMenuMain;
#endif
	//
	//DstroyMenuGP2XCommands* pMenu = new DstroyMenuGP2XCommands;
	while (TGIGlobals::theMain)
	{
		TGIGlobals::theMain->init();
		TGIGlobals::theMain->run();
	}


	TGIGlobals::exit();

#ifdef GP2X
	chdir("/usr/gp2x");
	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif 

	return 0;
}

