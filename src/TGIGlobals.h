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

#ifdef _DEBUG
#define _TGI_DEBUG
#endif

//standard types
#define TGIint int
#define TGIlong long
#define TGIchar char
#define TGIdouble double
#define TGIuint8 Uint8
#define TGIuint16 Uint16
#define TGIuint32 Uint32

#ifdef WIN32
#define DESKTOP
#endif
#ifdef LINUX
#define DESKTOP
#endif
#ifdef MACOSX
#define DESKTOP
#endif


//standard direction enum
enum Direction { left=1, right=2, up=3, down=4, stand=0 };

#include <string>
#include <vector>
#include <list>
#include <iostream>

//SDL related
#include <SDL.h>
#include <SDL_thread.h>

#ifndef TGI_NOSOUND
#ifndef __NDS__
#include "SDL_mixer.h"
#else
#include "file2res.h"
#endif
#endif

#ifndef TGI_NONET
#include <SDL_net.h>
#endif

//#ifdef GP2X
#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (4)
#define GP2X_BUTTON_LEFT            (2)
#define GP2X_BUTTON_RIGHT           (6)
#define GP2X_BUTTON_UPLEFT          (1)
#define GP2X_BUTTON_UPRIGHT         (7)
#define GP2X_BUTTON_DOWNLEFT        (3)
#define GP2X_BUTTON_DOWNRIGHT       (5)
#define GP2X_BUTTON_CLICK           (18)
#define GP2X_BUTTON_A               (12)
#define GP2X_BUTTON_B               (13)
#define GP2X_BUTTON_X               (15)
#define GP2X_BUTTON_Y               (14)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_START           (8)
#define GP2X_BUTTON_SELECT          (9)
#define GP2X_BUTTON_VOLUP           (16)
#define GP2X_BUTTON_VOLDOWN         (17)
//#endif

#define GP2X_MVT_MODE1 1
#define GP2X_MVT_MODE2 2
#define GP2X_MVT_MODE3 3

#ifdef __NDS__
#include <nds.h>
#include <maxmod9.h>
#endif

class TGIMain;

class TGIGlobals
{
public:
	TGIGlobals(void);
	~TGIGlobals(void);

	/** write data to the console - whatever the console looks like :)
	*/
	static void Trace(std::string strMessage, ...);
	//static pt to the ONLY main that can exists at a time
	static TGIMain* theMain;
	
	//initiate graphics
	static bool init(TGIint screenWidth, TGIint screenHeight, TGIuint8 nSpriteSize, bool bFullScreen, bool bRotateScreen);
	static TGIint screenWidth;
	static TGIint screenHeight;
	static TGIuint8 nSpriteSize;
	static bool bRotateScreen;
	//exit program
	static bool exit(void);

	//endianness convertion
	static void endianConvert(TGIuint16 order, void* pData, TGIuint16 nLen);

	//music
	static bool playMusic(std::string cstrFile, TGIuint16 nRepeat=0, TGIuint16 nRepeatPos=0);
	static bool stopMusic(void);

	//SDL related
	static SDL_Surface* pScreen;
#ifndef TGI_NOSOUND
#ifndef __NDS__
	static Mix_Music *pMusic;
	static TGIuint16 nRepeatPos;
	static TGIuint16 nRepeat;
	static void music_finished();
#else
	static int nMusicRes;
#endif
#endif
	//joysticks opened
	static std::vector<SDL_Joystick*> vecJoystick;
#ifdef GP2X
	static TGIuint8 nGP2XmvtMode;
#endif

	
	
};
