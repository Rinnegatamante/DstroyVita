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
#include "TGIMain.h"

#include "TGIGlobals.h"

//#include <fstream>

TGIMain::TGIMain(void)
{
	TGIGlobals::theMain = this;

	pSurfaceBackground = NULL;
	bEraseBackground = true;

	/*x0 = y0 = 0;
	width = 320;
	height = 240;*/

	itFirstObjectToQuePasa = listObject.begin();
	nLevelMinToQuePasa = 0;
	nLevelMinFixedObjects = 0;

	//pObjectsMutex = SDL_CreateMutex();

	pSoundBuffer = NULL;
	nSoundLen = 0;

	nFrames = 0;
	lastTick = SDL_GetTicks();

#ifdef GP2X
	bSoundControl = true;
#endif
}

TGIMain::~TGIMain(void)
{

}


bool TGIMain::init()
{
	//init random generator
	srand(SDL_GetTicks()); // a refaire avec un bon seed

	keyHold = 0;

	//sound
	/*SDL_AudioSpec desired, obtained;

	desired.format = AUDIO_S8;
	desired.channels = 1;
	desired.freq = 22050;
	desired.samples = 1024;
	desired.callback = (TGIMain::fill_audio);
	desired.userdata = this;

	SDL_OpenAudio(&desired, &obtained);

	SDL_PauseAudio(0);*/

	
	bRunning = true;
	bPause = false;

	return true;
}
bool TGIMain::exit()
{
	//SDL_DestroyMutex(pObjectsMutex);
	SDL_FillRect(TGIGlobals::pScreen, NULL, 0);
	SDL_Flip(TGIGlobals::pScreen);

	unsigned int i;
	for (i=0;i<vecSurface.size();i++)
	{
		delete vecSurface[i];
	}
	for (i=0;i<vecScreen.size();i++)
	{
		delete vecScreen[i];
	}

	deleteAllObjects();

	if (pSurfaceBackground)
	{
		delete pSurfaceBackground;
	}

	if (TGIGlobals::theMain == this)
		TGIGlobals::theMain = NULL;

	delete this;
	

	return true;
}


void TGIMain::run()
{
	
	bDoingEvents = false;
	bDoingDraw = false;

	Uint32 nLastTick = SDL_GetTicks()-15;
	int nTick, nTickEvent = 0;
	char strText[256];
	int nLastTickDraw = SDL_GetTicks()-30;

	int nEventPerSec = 0;
	int nDrawPerSec = 0;
	int nLastTickEventPerSec = SDL_GetTicks();

	while (bRunning)
	{
/*#ifndef __NDS__
		nTick = SDL_GetTicks() - nLastTick;
		if (nTick >= 15 && !bPause)
		{
			nLastTick = SDL_GetTicks();
			while (nTick >= 15)
			{
				events();
				nEventPerSec++;
				nTick -= 15;
			}
		}
			
		if (bPause)
		{
			nLastTick = SDL_GetTicks();
		}
		draw();	
#else*/
		
		nTick = SDL_GetTicks() - nLastTick;
		if (nTick >= 16 && !bPause)
		{		
			nTickEvent += nTick;
			nLastTick = SDL_GetTicks();
			if (nTickEvent >= 16*3)
			{
				nTickEvent = 16;
			}
			while (nTickEvent >= 16)
			{
				events();
				nEventPerSec++;
				nTickEvent -= 16;
			}
			
		}
		if (bPause)
		{
			nLastTick = SDL_GetTicks();
			nLastTickDraw = SDL_GetTicks();
		}

		nTick = SDL_GetTicks() - nLastTickDraw;
#ifndef __NDS__
		nTick = 31;
#endif
		if (nTick > 30 && !bPause)
		{
			draw();
			nDrawPerSec++;
			nLastTickDraw = SDL_GetTicks();
		}
		
		
		
//#endif

		nTick = SDL_GetTicks() - nLastTickEventPerSec;
		if (nTick > 1000)
		{
			sprintf(strText, "Events=%d draw=%d", nEventPerSec, nDrawPerSec);
			TGIGlobals::Trace(strText);
			nEventPerSec = 0;
			nDrawPerSec = 0;
			nLastTickEventPerSec = SDL_GetTicks();;
		}
		//SDL_Delay(1);
	}

	exit();
}

#ifndef __NDS__
bool TGIMain::events(void)
{
	register std::list<std::pair<TGIObject*, TGIint> >::iterator itObject; 
	register std::vector<TGIInputMessage>::iterator itMessage;
	register std::vector<TGIInputMessage*>::iterator itCurrentMessage;
	TGIuint16 j;
	SDL_Rect rectSrc;
	rectSrc.x = rectSrc.y = 0;

	int i;
	bool bHere;
	
	//events
	//SDL_PumpEvents();

	SDL_Event ev;
	char strTrace[1000];
	while(SDL_PollEvent(&ev))
	{
		switch(ev.type)
		{
		case SDL_KEYDOWN:
			for (j=0;j<vecInputMessage.size();j++)
			{
				if (vecInputMessage[j].sdlKey == ev.key.keysym.sym)
				{
					vecCurrentMessage.push_back(&(vecInputMessage[j]));
				}
			}
			if (ev.key.keysym.sym == SDLK_ESCAPE)
			{
				stop();
			}

			break;
		case SDL_KEYUP:
			for (i=(TGIint)vecCurrentMessage.size()-1;i>=0;i--)
			{
				if (vecCurrentMessage[i]->sdlKey == ev.key.keysym.sym)
				{
					vecCurrentMessage.erase(vecCurrentMessage.begin()+i);
				}
			}
			break;
		case SDL_JOYAXISMOTION:
			sprintf(strTrace, "axis %d %d %d\n", ev.jaxis.which, ev.jaxis.axis, ev.jaxis.value);
			TGIGlobals::Trace(strTrace);
			if (abs(ev.jaxis.value) < 10000)
			{
				//stops
				for (i=(TGIint)vecCurrentMessage.size()-1;i>=0;i--)
				{
					if (vecCurrentMessage[i]->axisEvent.which == ev.jaxis.which && 
						vecCurrentMessage[i]->axisEvent.axis == ev.jaxis.axis && 
						vecCurrentMessage[i]->axisEvent.value * ev.jaxis.value > 0)
					{
						vecCurrentMessage.erase(vecCurrentMessage.begin() + i);
						break;
					}
				}
			}
			else
			{
				bHere = false;
				//tests if the message is already in the messages list
				for (i=(TGIint)vecCurrentMessage.size()-1;i>=0;i--)
				{
					if (vecCurrentMessage[i]->axisEvent.which == ev.jaxis.which && 
						vecCurrentMessage[i]->axisEvent.axis == ev.jaxis.axis && 
						vecCurrentMessage[i]->axisEvent.value * ev.jaxis.value > 0)
					{
						bHere = true;
						break;
					}
				}
				if (!bHere)
				{
					for (j=0;j<vecInputMessage.size();j++)
					{
						if (vecInputMessage[j].axisEvent.which == ev.jaxis.which && 
							vecInputMessage[j].axisEvent.axis == ev.jaxis.axis && 
							vecInputMessage[j].axisEvent.value * ev.jaxis.value > 0 && 
							abs(ev.jaxis.value) > 10000)
						{
							vecCurrentMessage.push_back(&(vecInputMessage[j]));
						}
					}
				}
			}
			break;
		case SDL_JOYBUTTONDOWN:
			sprintf(strTrace, "button %d %d\n", ev.jbutton.which, ev.jbutton.button);
			TGIGlobals::Trace(strTrace);

#ifdef GP2X
			if (ev.jbutton.button == GP2X_BUTTON_START)
			{
				stop();
			}
#ifndef TGI_NOSOUND
			if (bSoundControl)
			{
				if (ev.jbutton.button == GP2X_BUTTON_VOLUP)
				{
					TGIGlobals::Trace("volup\n");
					Mix_VolumeMusic(Mix_VolumeMusic(-1)+12);
					Mix_Volume(-1, Mix_Volume(-1, -1)+12);
				}
				if (ev.jbutton.button == GP2X_BUTTON_VOLDOWN)
				{
					TGIGlobals::Trace("voldown\n");
					if (Mix_VolumeMusic(-1) < 12)
					{
						Mix_VolumeMusic(0);
						Mix_Volume(-1, 0);
					}
					else
					{
						Mix_VolumeMusic(Mix_VolumeMusic(-1)-12);
						Mix_Volume(-1, Mix_Volume(-1, -1)-12);
					}
				}
			}
#endif
			if (ev.jbutton.button < 8)
			{
				vecGP2XButtonPressed.push_back(ev.jbutton.button);
			}
			else
			{
				for (j=0;j<vecInputMessage.size();j++)
				{
					if (vecInputMessage[j].buttonEvent.which == ev.jbutton.which && 
						vecInputMessage[j].buttonEvent.button == ev.jbutton.button)
					{
						vecCurrentMessage.push_back(&(vecInputMessage[j]));
					}
				}
			}
			//std::cout<<"down:"<<(long)(ev.jbutton.button)<<std::endl;
#else
			for (j=0;j<vecInputMessage.size();j++)
			{
				if (vecInputMessage[j].buttonEvent.which == ev.jbutton.which && 
					vecInputMessage[j].buttonEvent.button == ev.jbutton.button)
				{
					vecCurrentMessage.push_back(&(vecInputMessage[j]));
				}
			}
#endif
			break;
		case SDL_JOYBUTTONUP:
#ifdef GP2X
			if (ev.jbutton.button < 8)
			{
				for (i=vecGP2XButtonPressed.size()-1;i>=0;i--)
				{
					if (vecGP2XButtonPressed[i] == ev.jbutton.button)
					{
						vecGP2XButtonPressed.erase(vecGP2XButtonPressed.begin() + i);
					}
				}
			}
			else
			{
				for (i=(TGIint)vecCurrentMessage.size()-1;i>=0;i--)
				{
					if (vecCurrentMessage[i]->buttonEvent.button == ev.jbutton.button)
					{
						vecCurrentMessage.erase(vecCurrentMessage.begin()+i);
					}
				}
			}
			//vecButtonUp.push_back(ev);
			//std::cout<<"up:"<<(long)(ev.jbutton.button)<<std::endl;
#else
			for (i=(TGIint)vecCurrentMessage.size()-1;i>=0;i--)
			{
				if (vecCurrentMessage[i]->buttonEvent.which == ev.jbutton.which && 
					vecCurrentMessage[i]->buttonEvent.button == ev.jbutton.button)
				{
					vecCurrentMessage.erase(vecCurrentMessage.begin()+i);
				}
			}
#endif
			break;
		case SDL_JOYHATMOTION:
			sprintf(strTrace, "hat %d %d %d\n", ev.jhat.which, ev.jhat.hat, ev.jhat.value);
			TGIGlobals::Trace(strTrace);
			//if (ev.jhat.value == 0)
			{
				//stops movement
				for (i=(TGIint)vecCurrentMessage.size()-1;i>=0;i--)
				{
					if (vecCurrentMessage[i]->hatEvent.which == ev.jhat.which && 
						vecCurrentMessage[i]->hatEvent.hat == ev.jhat.hat && 
						!(vecCurrentMessage[i]->hatEvent.value & ev.jhat.value))
					{
						vecCurrentMessage.erase(vecCurrentMessage.begin() + i);
					}
				}
			}
			//else
			if (ev.jhat.value != 0)
			{
				switch(ev.jhat.value)
				{
				case SDL_HAT_RIGHTUP:
					ev.jhat.value = SDL_HAT_RIGHT;
					break;
				case SDL_HAT_LEFTUP:
					ev.jhat.value = SDL_HAT_UP;
					break;
				case SDL_HAT_RIGHTDOWN:
					ev.jhat.value = SDL_HAT_DOWN;
					break;
				case SDL_HAT_LEFTDOWN:
					ev.jhat.value = SDL_HAT_LEFT;
					break;
				}
				sprintf(strTrace, "->%d\n", ev.jhat.value);
				TGIGlobals::Trace(strTrace);
				//new movement
				for (j=0;j<vecInputMessage.size();j++)
				{
					if (vecInputMessage[j].hatEvent.which == ev.jhat.which && 
						vecInputMessage[j].hatEvent.hat == ev.jhat.hat && 
						vecInputMessage[j].hatEvent.value & ev.jhat.value)
					{
						vecCurrentMessage.push_back(&(vecInputMessage[j]));
					}
				}
			}
			break;
		default:
			break;
		}
	}

	//gp2x stuff
#ifdef GP2X
	GP2XgetDirection(vecGP2XButtonPressed);

	/*sprintf(strTrace, "(");
	std::cout<<strTrace;
	for (i=0;i<vecCurrentMessage.size();i++)
	{
		sprintf(strTrace, "%d", vecCurrentMessage[i]->lId);
		std::cout<<strTrace;
	}
	std::cout<<")\n";*/
	
	
#endif

	bDoingEvents = true;

	//for each object that move (quePasa)
	for (itIndexQuePasa=listObjectToQuePasa.begin();itIndexQuePasa!=listObjectToQuePasa.end();itIndexQuePasa++)
	{
		//handling events
		for (j=0;j<vecCurrentMessage.size();j++)
		{
			(*itIndexQuePasa)->onMessage(vecCurrentMessage[j]);
		}

		(*itIndexQuePasa)->quePasa();
	}
	//itIndexQuePasa = listObjectToQuePasa.begin();

	bDoingEvents = false;

	//delete non autofire input messages
	for (i=(TGIint)vecCurrentMessage.size()-1;i>=0;i--)
	{
		if (!vecCurrentMessage[i]->bAutofire)
		{
			vecCurrentMessage.erase(vecCurrentMessage.begin()+i);
		}
	}

	return true;
}
#else
bool TGIMain::events(void)
{
	scanKeys();
	int i,j;

	u32 keyHeld = keysHeld();
	u32 keyUp, keyDown;

	keyDown = (keyHold ^ keyHeld) & keyHeld;
	keyUp = (keyHold ^ keyHeld) & keyHold;

	keyHold = keyHeld;
 
	if(keyHold & KEY_START)
	{
		stop();
		return false;
	}
	
	std::vector<TGIInputMessage>::iterator it;
	std::vector<TGIInputMessage*>::iterator itCurrent;

	for (i=(TGIint)vecCurrentMessage.size()-1;i>=0;i--)
	{
		if (vecCurrentMessage[i]->sdlKey & keyUp)
		{
			vecCurrentMessage.erase(vecCurrentMessage.begin()+i);
		}
	}

	for (it=vecInputMessage.begin();it!=vecInputMessage.end();it++)
	{
		if (it->sdlKey & keyDown)
		{
			vecCurrentMessage.push_back(&(*it));
		}
	}

	/*char strText[256];
	sprintf(strText, "%d", vecCurrentMessage.size());
	TGIGlobals::Trace(strText);*/

	bDoingEvents = true;

	for (itIndexQuePasa=listObjectToQuePasa.begin();itIndexQuePasa!=listObjectToQuePasa.end();itIndexQuePasa++)
	{
		//handling events
		for (j=0;j<vecCurrentMessage.size();j++)
		{
			(*itIndexQuePasa)->onMessage(vecCurrentMessage[j]);
		}

		(*itIndexQuePasa)->quePasa();
	}

	bDoingEvents = false;

	//delete non autofire input messages
	for (i=(TGIint)vecCurrentMessage.size()-1;i>=0;i--)
	{
		if (!vecCurrentMessage[i]->bAutofire)
		{

			vecCurrentMessage.erase(vecCurrentMessage.begin()+i);
		}
	}
	return true;
}


#endif

void TGIMain::GP2XgetDirection(std::vector<TGIuint8> vecButtonPressed)
{
#ifdef GP2X
	int i,j;
	
	bool bL, bU, bD, bR, bLU, bLD, bRU, bRD;
	//up
	for (i=vecCurrentMessage.size()-1;i>=0;i--)
	{
		if (vecCurrentMessage[i]->buttonEvent.button < 8)
		{
			vecCurrentMessage.erase(vecCurrentMessage.begin()+i);
		}
	}
	//down
	bL = bU = bD = bR = bLU = bLD = bRU = bRD = false;
	for (i=0;i<vecButtonPressed.size();i++)
	{
		bL = (vecButtonPressed[i] == GP2X_BUTTON_LEFT);
		bU = (vecButtonPressed[i] == GP2X_BUTTON_UP);
		bD = (vecButtonPressed[i] == GP2X_BUTTON_DOWN);
		bR = (vecButtonPressed[i] == GP2X_BUTTON_RIGHT);
		bLU = (vecButtonPressed[i] == GP2X_BUTTON_UPLEFT);
		bLD = (vecButtonPressed[i] == GP2X_BUTTON_DOWNLEFT);
		bRU = (vecButtonPressed[i] == GP2X_BUTTON_UPRIGHT);
		bRD = (vecButtonPressed[i] == GP2X_BUTTON_DOWNRIGHT);
	}
	if ((TGIGlobals::nGP2XmvtMode == 1 && (bL))
		|| (TGIGlobals::nGP2XmvtMode == 2 && (bL || (bLU && !bU)))
		|| (TGIGlobals::nGP2XmvtMode == 3 && (bL || (bLD && !bD))))
	{
		//std::cout<<"DOWN:"<<GP2X_BUTTON_LEFT<<std::endl;
		for (i=0;i<vecInputMessage.size();i++)
		{
			if (vecInputMessage[i].buttonEvent.button == GP2X_BUTTON_LEFT)
				vecCurrentMessage.push_back(&(vecInputMessage[i]));
		}
	}
	if ((TGIGlobals::nGP2XmvtMode == 1 && (bU))
		|| (TGIGlobals::nGP2XmvtMode == 2 && (bU || (bRU && !bR)))
		|| (TGIGlobals::nGP2XmvtMode == 3 && (bU || (bLU && !bL))))
	{
		//std::cout<<"DOWN:"<<GP2X_BUTTON_UP<<std::endl;
		for (i=0;i<vecInputMessage.size();i++)
		{
			if (vecInputMessage[i].buttonEvent.button == GP2X_BUTTON_UP)
				vecCurrentMessage.push_back(&(vecInputMessage[i]));
		}
	}
	if ((TGIGlobals::nGP2XmvtMode == 1 && (bR))
		|| (TGIGlobals::nGP2XmvtMode == 2 && (bR || (bRD && !bD)))
		|| (TGIGlobals::nGP2XmvtMode == 3 && (bR || (bRU && !bU))))
	{
		//std::cout<<"DOWN:"<<GP2X_BUTTON_RIGHT<<std::endl;
		for (i=0;i<vecInputMessage.size();i++)
		{
			if (vecInputMessage[i].buttonEvent.button == GP2X_BUTTON_RIGHT)
				vecCurrentMessage.push_back(&(vecInputMessage[i]));
		}
	}
	if ((TGIGlobals::nGP2XmvtMode == 1 && (bD))
		|| (TGIGlobals::nGP2XmvtMode == 2 && (bD || (bLD && !bL)))
		|| (TGIGlobals::nGP2XmvtMode == 3 && (bD || (bRD && !bR))))
	{
		//std::cout<<"DOWN:"<<GP2X_BUTTON_DOWN<<std::endl;
		for (i=0;i<vecInputMessage.size();i++)
		{
			if (vecInputMessage[i].buttonEvent.button == GP2X_BUTTON_DOWN)
				vecCurrentMessage.push_back(&(vecInputMessage[i]));
		}
	}
#endif
}

int TGIMain::threadDrawing(void* pp)
{
	TGIMain* pMain = (TGIMain*)pp;

	//SDL_WaitThread((SDL_Thread*)pp, NULL);

	while(pMain->bRunning)
	{
		SDL_Delay(100);
		if (pMain->bPause)
			continue;
		if (TGIGlobals::theMain)
			TGIGlobals::theMain->draw();
		
	}

	return 0;
}

void TGIMain::draw(void)
{
	SDL_Rect rectSrc, rectDest;
	TGISprite* pSprite;
	TGIuint16 i;

	if (!bRunning)
		return;


	if (pSurfaceBackground)
	{
		SDL_BlitSurface(pSurfaceBackground->pSurface, NULL, TGIGlobals::pScreen, NULL);
	}
	else if (bEraseBackground)
	{
		SDL_FillRect(TGIGlobals::pScreen, NULL, SDL_MapRGB(TGIGlobals::pScreen->format, 0, 0, 0));
	}

	bDoingDraw = true;
	for (itIndexQuePasa=listObjectToChangeSprite.begin();itIndexQuePasa!=listObjectToChangeSprite.end();itIndexQuePasa++)
	{
		(*itIndexQuePasa)->doChangeSprite();

	}
	
	for (i=0;i<vecScreen.size();i++)
	{
		vecScreen[i]->drawScreen(this);
	}	

	for (itIndexQuePasa=listFixedObject.begin();itIndexQuePasa!=listFixedObject.end();itIndexQuePasa++)
	{
		pSprite = (*itIndexQuePasa)->doChangeSprite();
			
		rectSrc.x = pSprite->x;
		rectSrc.y = pSprite->y;
		rectSrc.w = pSprite->w;
		rectSrc.h = pSprite->h;
		
		rectDest.x = (*itIndexQuePasa)->X()*TGIGlobals::nSpriteSize;
		rectDest.y = (*itIndexQuePasa)->Y()*TGIGlobals::nSpriteSize;
		rectDest.w = pSprite->w;
		rectDest.h = pSprite->h;

		if (TGIGlobals::bRotateScreen)
		{
			rectDest.x = TGIGlobals::screenWidth - rectDest.x - 1 - rectDest.w;
			rectDest.y = TGIGlobals::screenHeight - rectDest.y - 1 - rectDest.h;
		}

	
		SDL_BlitSurface(pSprite->pTGISurface->pSurface, &rectSrc, TGIGlobals::pScreen, &rectDest);
	}

	bDoingDraw = false;

	/*for (itIndexQuePasa=listObject.begin();itIndexQuePasa!=listObject.end();itIndexQuePasa++)
	{
		if (itIndexQuePasa->first->bFixedOnScreen)
		{
			pSprite = itIndexQuePasa->first->doChangeSprite();
			
			rectSrc.x = pSprite->x;
			rectSrc.y = pSprite->y;
			rectSrc.w = pSprite->w;
			rectSrc.h = pSprite->h;
			
			rectDest.x = itIndexQuePasa->first->X()*TGIGlobals::nSpriteSize;
			rectDest.y = itIndexQuePasa->first->Y()*TGIGlobals::nSpriteSize;
			rectDest.w = pSprite->w;
			rectDest.h = pSprite->h;

			if (TGIGlobals::bRotateScreen)
			{
				rectDest.x = TGIGlobals::screenWidth - rectDest.x - 1 - rectDest.w;
				rectDest.y = TGIGlobals::screenHeight - rectDest.y - 1 - rectDest.h;
			}

		
			SDL_BlitSurface(pSprite->pTGISurface->pSurface, &rectSrc, TGIGlobals::pScreen, &rectDest);
		}
	}*/

	//SDL_mutexV(pObjectsMutex);

	//fps

	/*nFrames++;
	
	if (SDL_GetTicks() - lastTick > 500)
	{
		static char strFPS[256];
		lastTick = SDL_GetTicks();
		//std::cout<<"FPS:"<<nFrames*2<<std::endl;
		sprintf(strFPS, ("FPS:%03d\n"), nFrames*2);
		nFrames = 0;
		TGIGlobals::Trace(strFPS);
		
	}*/
	/*len = (TGIint)(strlen(strFPS)-1);
	rectDest.w = 8;
	rectDest.h = 10;
	rectDest.y = 1; 
	rectDest.x = 20;
	while (len != -1)
	{
		rectNumber.x = (strFPS[len]-48)*8;
		SDL_BlitSurface(pSurfaceNumbers, &rectNumber, TGIGlobals::pScreen, &rectDest);
		rectDest.x -= 9;
		len--;
	}*/
	SDL_Flip(TGIGlobals::pScreen); 
}

bool TGIMain::deleteObject(TGIObject* pObject, bool bDelete)
{
	register std::list<std::pair<TGIObject*, TGIint> >::iterator itObject; 
	register std::list<TGIObject*>::iterator itObject2; 
	bool bAfter = false;

	if (bDoingEvents && !listObjectToQuePasa.empty() && pObject == *itIndexQuePasa)
		itIndexQuePasa--;
	if (bDoingDraw && !listObjectToChangeSprite.empty() && pObject == *itIndexQuePasa)
		itIndexQuePasa--;

	for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
	{
		
		if (itObject->first == pObject)
		{
			if (pObject->bDoChangeSprite)
			{
				//we must delete the object from listObjectToChangeSprite
				for (itObject2=listObjectToChangeSprite.begin();itObject2!=listObjectToChangeSprite.end();itObject2++)
				{
					if (*itObject2 == pObject)
					{
						listObjectToChangeSprite.erase(itObject2);
						break;
					}
				}
			}
			if (itObject->second >= nLevelMinToQuePasa)
			{
				//delete from listObjectToQuePasa
				for (itObject2=listObjectToQuePasa.begin();itObject2!=listObjectToQuePasa.end();itObject2++)
				{
					if (*itObject2 == pObject)
					{
						listObjectToQuePasa.erase(itObject2);
						break;
					}
				}
			}
			if (itObject->second >= nLevelMinFixedObjects)
			{
				//delete from listObjectToQuePasa
				for (itObject2=listFixedObject.begin();itObject2!=listFixedObject.end();itObject2++)
				{
					if (*itObject2 == pObject)
					{
						listFixedObject.erase(itObject2);
						break;
					}
				}
			}
				
			if (bDelete)
				delete pObject;
			listObject.erase(itObject);
						
			return true;
		}
		/*if (itObject->first == *itIndexQuePasa)
			bAfter = true;*/
	}
	
	return false;
}

bool TGIMain::addObject(TGIObject* pObject, TGIint nDepth)
{
	register std::list<std::pair<TGIObject*, TGIint> >::iterator itObject; 
	std::pair<TGIObject*, TGIint> pair;
	pair.first = pObject;
	pair.second = nDepth;

	if (nDepth >= nLevelMinToQuePasa)
	{
		listObjectToQuePasa.push_back(pObject);
		if (listObjectToQuePasa.size() == 1)
		{
			itIndexQuePasa = listObjectToQuePasa.begin();
		}

	}
	if (pObject->bFixedOnScreen)
	{
		
		listFixedObject.push_back(pObject);
	}
	if (pObject->bDoChangeSprite)
	{
		listObjectToChangeSprite.push_back(pObject);
	}

	if (listObject.empty())
	{
		listObject.push_back(pair);
		//itFirstObjectToQuePasa = listObject.begin();
		//itFirstObjectFixed = listObject.begin();

		return true;
	}

	for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
	{
		if (nDepth <= itObject->second)
		{
			listObject.insert(itObject, pair);
			
			return true;
		}
	}

	listObject.push_back(pair);
	return true;
}

/*TGIObject* TGIMain::getObject(TGIint nIndex)
{
	//return listObject[nIndex].first;
	return NULL;
}*/

TGIuint16 TGIMain::getObjectCount(void)
{
	return (TGIuint16)listObject.size();
}


void TGIMain::addScreen(TGIint x , TGIint y , TGIint w , TGIint h, TGIint xmin, TGIint ymin, TGIint xmax, TGIint ymax, TGIObject* pCenterObject, TGIint x0, TGIint y0)
{
	TGIScreen* screen = new TGIScreen; 

	screen->rectLimit.x = xmin*TGIGlobals::nSpriteSize;
	screen->rectLimit.y = ymin*TGIGlobals::nSpriteSize;
	screen->rectLimit.w = (xmax-w)*TGIGlobals::nSpriteSize;
	screen->rectLimit.h = (ymax-h)*TGIGlobals::nSpriteSize;

	screen->pCenterObject = pCenterObject;


/*	if (TGIGlobals::bRotateScreen)
	{
		screen->rectDest.x = (TGIGlobals::screenWidth - x - w)*TGIGlobals::nSpriteSize;
		screen->rectDest.y = (TGIGlobals::screenHeight - y - h)*TGIGlobals::nSpriteSize;
		screen->rectDest.w = w*TGIGlobals::nSpriteSize;
		screen->rectDest.h = h*TGIGlobals::nSpriteSize;	
	}
	else*/
	{
		screen->rectDest.x = x*TGIGlobals::nSpriteSize;
		screen->rectDest.y = y*TGIGlobals::nSpriteSize;
		screen->rectDest.w = w*TGIGlobals::nSpriteSize;
		screen->rectDest.h = h*TGIGlobals::nSpriteSize;
	}

	screen->rectSrc.x = 0;
	screen->rectSrc.y = 0;
	screen->rectSrc.w = w*TGIGlobals::nSpriteSize;
	screen->rectSrc.h = h*TGIGlobals::nSpriteSize;

	screen->x0 = x0*TGIGlobals::nSpriteSize;
	screen->y0 = y0*TGIGlobals::nSpriteSize;

	vecScreen.push_back(screen);

	screen = NULL;
}

TGIint TGIMain::getObjectDepth(TGIObject* pObject)
{
	/*for (TGIint i=0;i<getObjectCount();i++)
	{
		if (listObject[i].first == pObject)
			return listObject[i].second;
	}*/

	return 0;
}

void TGIMain::stop(void)
{
	//stops the run
	bRunning = false;
}

bool TGIMain::deleteAllObjects(void)
{
	/*unsigned int i;
	for (i=0;i<listObject.size();i++)
	{
		delete listObject[i].first;
	}*/

	register std::list<std::pair<TGIObject*, TGIint> >::iterator itObject; 

	for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
	{
		delete itObject->first;
	}	

	listObject.clear();
	listObjectToChangeSprite.clear();
	listObjectToQuePasa.clear();
	listFixedObject.clear();
	itFirstObjectToQuePasa = listObject.begin();

	return true;
}

bool TGIMain::playMusic(std::string cstrFile, TGIuint16 nRepeat)
{
	return TGIGlobals::playMusic(cstrFile, nRepeat);
}

bool TGIMain::loadCommands(std::string cstrFile)
{
	TGIFile tgiFile;
	tgiFile.openRead(cstrFile.c_str(), true);
	if (!tgiFile.isOpen())
		return false;

	vecInputMessage.clear();

	TGIInputMessage message;
	while (message.load(tgiFile))
	{
#ifdef GP2X
		if (message.buttonEvent.button == GP2X_BUTTON_VOLUP || message.buttonEvent.button == GP2X_BUTTON_VOLDOWN)
		{
			TGIGlobals::Trace("sound control disabled\n");
			bSoundControl = false;
		}
#endif
		vecInputMessage.push_back(message);
	}	
	tgiFile.close();

	return true;
}

bool TGIMain::saveCommands(std::string cstrFile)
{
	TGIFile tgiFile;
	if (!tgiFile.create(cstrFile.c_str(), true))
		return false;

	for (TGIuint16 i=0;i<vecInputMessage.size();i++)
	{
		vecInputMessage[i].save(tgiFile);
	}
	return true;
}

bool TGIMain::setBackground(TGISurface* pSurface)
{
	if (pSurfaceBackground)
	{
		delete pSurfaceBackground;
		pSurfaceBackground = NULL;
	}

	pSurfaceBackground = pSurface;

	return true;
}

bool TGIMain::stopMusic(void)
{
	TGIGlobals::stopMusic();

	return true;
}

bool TGIMain::isMusicPlaying(void)
{
#ifndef TGI_NOSOUND
	//return (TGIGlobals::pMusic != NULL);
#endif
	return false;
}




