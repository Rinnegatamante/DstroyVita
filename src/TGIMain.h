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
#include "TGIObject.h"
#include "TGIInputMessage.h"
#include "TGIScreen.h"
#include "TGISound.h"
#include "SDL_thread.h"

/* TGIMain :
	main class for a game
	contains all the graphics & sounds

	you should derive this class and change:
		init() to fill the data:
			surface vector, 
			object list, 
			screen vector,
			nLevelMinToQuePasa (not needed, but better for performance)
			input message vector
		events() to add globals events (conditions for exit...)

		run() & exit() can be also be changed

	ALWAYS create the class with TGIMain *pMain = new TGIMAIN
	This class autodestructs itself in the exit()

	in the constructor, the class set the TGIGlobals::theMain
	so you can't have more than ONE TGIMain at a time

	good way to use multiple TGIMain:
	in a main() function:

	DstroyMenuMain* pMenu = new DstroyMenuMain;
	while (TGIGlobals::theMain)
	{
		TGIGlobals::theMain->init();
		TGIGlobals::theMain->run();
	}

	exit() sets TGIGlobals::theMain to NULL if TGIGlobals::theMain == this
	so you can instanciate a new TGIMain during an event and send a stop() message to change the TGIMain

*/

class TGIMain
{	
private:
	//for fps
	int nFrames;
	Uint32 lastTick;

	//vector containing all the TGIObjects in the game
	std::list<std::pair<TGIObject*, TGIint> > listObject;
	
	std::list<TGIObject*> listObjectToChangeSprite;
	std::list<TGIObject*> listObjectToQuePasa;
	std::list<TGIObject*> listFixedObject;

	//TGIScreens (for multiplayer on the same screen): there must be at least ONE!
	std::vector<TGIScreen*> vecScreen;

	

	//current index in the cycle "events" and in the cycle "draw"
	//TGIuint16 nIndexQuePasa;
	std::list<TGIObject*>::iterator itIndexQuePasa;
	bool bDoingEvents;
	bool bDoingDraw;
	//std::list<std::pair<TGIObject*, TGIint> >::iterator itIndexQuePasa;
	//index of the first object to quePasa (calculated with nLevelMinToQuePasa)
	std::list<std::pair<TGIObject*, TGIint> >::iterator itFirstObjectToQuePasa;
	std::list<std::pair<TGIObject*, TGIint> >::iterator itFirstObjectFixed;

	//SDL related
	//thread for drawing
	//SDL_Thread* pThreadDraw;
	//mutex for the thread
	//SDL_mutex* pObjectsMutex;
	//audio data
	Uint8 *pSoundBuffer;
	Sint32 nSoundLen;
	
	//gp2x sutff
#ifdef GP2X
	std::vector<Uint8> vecGP2XButtonPressed;
	bool bSoundControl;
#endif
	//nds stuff
	uint32_t keyHold;
	
	
	TGISurface* pSurfaceBackground;
	
protected:
	bool bEraseBackground;
	//for reuse ervey time needed
	//std::list<std::pair<TGIObject*, TGIint> >::iterator itObject; 
	//TGISurfaces for the game
	std::vector<TGISurface*> vecSurface;
	//the main stops if bRunning is set to false (and waits for the thread to terminate)
	bool bRunning;
	//minimum level of objects to quePasa() them 
	//in order to not send useless messages to the background
	TGIuint16 nLevelMinToQuePasa;
	TGIuint16 nLevelMinFixedObjects;
	//TGIInputMessages in the game
	std::vector<TGIInputMessage> vecInputMessage;
	//current input messages
	std::vector<TGIInputMessage*> vecCurrentMessage;

	//pause the game
	bool bPause;

public:
	TGIMain(void);
	virtual ~TGIMain(void);
		
	//virtual functions
	virtual bool init();
	virtual bool exit();
	virtual void run();
	//function called by run()
	virtual bool events(void);

	//stops the game (bRunning -> false)
	virtual void stop(void);

	//thread for drawing
	static int threadDrawing(void* pp);
	//play a music
	bool playMusic(std::string cstrFile, TGIuint16 nRepeat=0);

	//objects...
	virtual bool deleteObject(TGIObject* pObject, bool bDelete=true);
	virtual bool addObject(TGIObject* pObject, TGIint nDepth);
	//TGIObject* getObject(TGIint nIndex);
	TGIuint16 getObjectCount(void);
	TGIint getObjectDepth(TGIObject* pObject);
	bool deleteAllObjects(void);

	inline std::list<std::pair<TGIObject*, TGIint> >::iterator getFirstObject()
	{
		return listObject.begin();
	}
	inline std::list<std::pair<TGIObject*, TGIint> >::iterator getFirstObjectToQuePasa()
	{
		return itFirstObjectToQuePasa;
	}
	inline std::list<std::pair<TGIObject*, TGIint> >::iterator getEndObject()
	{
		return listObject.end();
	}

	//add a screen
	void addScreen(TGIint x , TGIint y , TGIint w , TGIint h, TGIint xmin, TGIint ymin, TGIint xmax, TGIint ymax, TGIObject* pCenterObject, TGIint x0=0, TGIint y0=0);
	
public:
	virtual bool loadCommands(std::string cstrFile);
public:
	virtual bool saveCommands(std::string cstrFile);
public:
	bool setBackground(TGISurface* pSurface);
public:
	bool stopMusic(void);
public:
	bool isMusicPlaying(void);
	void draw(void);
public:
	void GP2XgetDirection(std::vector<TGIuint8> vecButtonPressed);
};
