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
 
#include <vitasdk.h>
#include "stdafx.h"

#include "DstroyPressFire.h"
#include "DstroyPressFireItem.h"
#include "DstroyGame.h"
#include "DstroyEndGame.h"
#include "DstroyMenuMain.h"


DstroyPressFire::DstroyPressFire()
{
	TGIuint8 i;
	for (i=0;i<4;i++)
	{
		pbReady[i] = false;
	}
}

DstroyPressFire::~DstroyPressFire()
{

}

bool DstroyPressFire::init()
{
	if (!TGIMain::init())
		return false;

	TGIuint8 i;

	TGIGlobals::stopMusic();
#ifdef GP2X
	if (TGIGlobals::bRotateScreen)
	{
		if (DstroyGame::params.nPlayers == 1)
		{
			loadCommands(DstroyGlobals::addResText("commandsgp2xr"));
		}
		else
		{
			loadCommands(DstroyGlobals::addResText("commandsgp2xr2"));
		}
	}
	else
	{
		if (DstroyGame::params.nPlayers == 1)
		{
			loadCommands(DstroyGlobals::addResText("commandsgp2x"));
		}
		else
		{
			loadCommands(DstroyGlobals::addResText("commandsgp2x2"));
		}
	}
#endif

	if (!loadCommands(DstroyGlobals::addConfigText("commands")))
	{
		loadCommands(DstroyGlobals::addResText("commands"));
	}

	TGIInputMessage message;
	message.lId	= 10;
	message.lIdRecipient = 1;
	message.bAutofire = false;
	message.sdlKey = SCE_CTRL_CROSS;
	vecInputMessage.push_back(message);

	DstroyPressFireItem* pItem;
	for (i=0;i<DstroyGame::params.nPlayers;i++)
	{
		pItem = new DstroyPressFireItem;
		pItem->lId = i+1;

		addObject(pItem, 0);
	}

	bEnd = false;
	if (isEndGame())
	{
		bEnd = true;
		TGIGlobals::Trace("Its endGame");
		
		return true;
	}



	TGIuint16 nLevel = 0;

	switch(DstroyGame::params.nMode)
	{
	case GAMEMODE_KILLER:
		for (i=0;i<DstroyGame::params.nPlayers;i++)
		{
			DstroyGame::params.pnBombDuration[i] = 4;
			DstroyGame::params.pnBombs[i] = 3;
			DstroyGame::params.pnFlame[i] = 4;
		}
		
		while (nLevel == 0 || (nLevel >= 31 && nLevel <= 36) || nLevel%6 == 0)
			nLevel = rand()%48+1;
		DstroyGame::params.setLevel(nLevel);
		
		setBackgroundFight(); 
		break;
	case GAMEMODE_FIGHT:
		for (i=0;i<DstroyGame::params.nPlayers;i++)
		{
			DstroyGame::params.pnBombDuration[i] = 4;
			DstroyGame::params.pnBombs[i] = 1;
			DstroyGame::params.pnFlame[i] = 1;
		}
		while (nLevel == 0 || nLevel%6 == 0)
			nLevel = rand()%48+1;
		DstroyGame::params.setLevel(nLevel);
		DstroyGame::params.nDifficulty = 1;
		setBackgroundFight();
		break;
	case GAMEMODE_ADVENTURE:
		setBackgroundAdventure();
		break;
	}

	return true;
}

void DstroyPressFire::setReady(TGIuint16 lId)
{
	pbReady[lId-1] = true;
	/*TGIuint16 i;
	for (i=0;i<DstroyGame::params.nPlayers;i++)
	{	
		if (!bEnd && !pbReady[i])
			return;
		if (bEnd && pbReady[i])
		{
			ttWhenToStop = TGITime::getCurrentTime();
		}
	}*/

	if (bEnd)
	{
		bRunning = false;
		TGIGlobals::stopMusic();
		DstroyMenuMain* pMenu = new DstroyMenuMain;
	}
	else
	{
		ttWhenToStop = TGITime::getCurrentTime();

		//il faut lancer le jeu
		bRunning = false;
		DstroyGame* pGame = new DstroyGame;
	}
}

void DstroyPressFire::setBackgroundFight(void)
{
	TGIuint8 i;

	TGISurface* pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("s1.pcx"), true);
	setBackground(pSurface);
	pSurface = NULL;

	pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("s2.pcx"), true);
	font.setSurface(pSurface);
	pSurface = NULL;



	for (i=0;i<4;i++)
	{
		font.importLetter('0', false, 1, 8+39*i, 30, 32);
		font.importLetter('1', false, 32, 8+39*i, 17, 32);
		font.importLetter('2', false, 51, 8+39*i, 80-51, 32);
		font.importLetter('3', false, 82, 8+39*i, 111-82, 32);
		font.importLetter('4', false, 113, 8+39*i, 142-113, 32);
		font.importLetter('5', false, 144, 8+39*i, 173-144, 32);
		font.importLetter('6', false, 175, 8+39*i, 204-175, 32);
		font.importLetter('7', false, 206, 8+39*i, 235-206, 32);
		font.importLetter('8', false, 237, 8+39*i, 266-237, 32);
		font.importLetter('9', false, 268, 8+39*i, 297-268, 32);
	}
	font.importLetter('a', false, 1, 173, 79-1, 238-173);
	font.importLetter('b', false, 82, 173, 79-1, 238-173);

	char strText[5];

	sprintf(strText, "%d", DstroyGame::params.pnWins[0]);
	font.writeText(strText, 71, 36, TAcenter,0, NULL);

	sprintf(strText, "%d", DstroyGame::params.pnWins[1]);
	font.writeText(strText, 248, 170, TAcenter, 1, NULL);

	if (DstroyGame::params.nPlayers > 2)
	{
		sprintf(strText, "%d", DstroyGame::params.pnWins[2]);
		font.writeText(strText, 248, 36, TAcenter, 2, NULL);
	}
	else
	{
		font.writeText("b", 210, 20, TAleft,0,  NULL);
	}
	if (DstroyGame::params.nPlayers > 3)
	{
		sprintf(strText, "%d", DstroyGame::params.pnWins[3]);
		font.writeText(strText, 71, 170, TAcenter, 3, NULL);
	}
	else
	{
		font.writeText("a", 33, 154, TAleft,0, NULL);
	}

}

void DstroyPressFire::setBackgroundAdventure(void)
{
	TGISurface* pSurface = new TGISurface;

	switch (DstroyGame::params.nPlayers)
	{
	case 1:
		pSurface->loadImage(DstroyGlobals::addResText("pf1.pcx"), true);
		break;
	case 2:
		pSurface->loadImage(DstroyGlobals::addResText("pf2.pcx"), true);
		break;
	case 3:
		pSurface->loadImage(DstroyGlobals::addResText("pf3.pcx"), true);
		break;
	case 4:
		pSurface->loadImage(DstroyGlobals::addResText("pf4.pcx"), true);
		break;
	}

	setBackground(pSurface);
}

void DstroyPressFire::stop(void)
{
	bRunning = false;
	setReady(0);
}

bool DstroyPressFire::isEndGame(void)
{
	TGIuint8 i,j;

	if (DstroyGame::params.nMode == GAMEMODE_ADVENTURE)
	{
		if (DstroyGame::params.nLevel > 48)
		{
			return true;
		}
			

		for (i=0;i<DstroyGame::params.nPlayers;i++)
		{
			if (DstroyGame::params.pnLives[i] != 0)
			{
				return false;
			}
		}
		TGISurface* pSurface = new TGISurface;
		pSurface->loadImage(DstroyGlobals::addResText("go.pcx"), true);
		setBackground(pSurface);
		pSurface = NULL;

		playMusic(DstroyGlobals::addResText("over.mod"), 1);

		ttWhenToStop = TGITime::getCurrentTime();
		ttWhenToStop += 20000;

		return true;
	}
	else
	{
		
		for (i=0;i<DstroyGame::params.nPlayers;i++)
		{
			if (DstroyGame::params.pnWins[i] >= DstroyGame::params.nWins)
			{
				char strText[20][256];

				TGISurface* pSurface = new TGISurface;
				pSurface->setInvisibleColor(0, 0, 0);
				pSurface->loadImage(DstroyGlobals::addResText("l1.pcx"));
				
				font.setSurface(pSurface);
				font.importFixedFont(true, 0, 8*7, 320, 8*7, 8, 8);

				pSurface = new TGISurface;
				switch (i+1)
				{
				case 1:
					sprintf(strText[0], "BRAVO BOODIES BLEU!");
					sprintf(strText[1], " ");
					sprintf(strText[2], "TU VIENS D'ANEANTIR TES");
					sprintf(strText[3], "ADVERSAIRES AVEC UN");
					sprintf(strText[4], "COURAGE ET UNE");
					sprintf(strText[5], "DETERMINATION QUI N'ONT");
					sprintf(strText[6], "AUCUN EGAL DANS");
					sprintf(strText[7], "L'UNIVERS! TU ES PROMU");
					sprintf(strText[8], "AU RANG DE PRINCE DES");
					sprintf(strText[9], "BOODIES, CHAMPION ET");
					sprintf(strText[10], "GRAND MAITRE DES");
					sprintf(strText[11], "TOURNOIS. TOUS LES");
					sprintf(strText[12], "AUTRES BOODIES TE");
					sprintf(strText[13], "DOIVENT RESPECT ET");
					sprintf(strText[14], "OBEISSANCE...JUSQU'A");
					sprintf(strText[15], "LA PROCHAINE PARTIE!");
					pSurface->loadImage(DstroyGlobals::addResText("f1.pcx"));
					break;
				case 2:
					sprintf(strText[0], "BRAVO BOODIES JAUNE!");
					sprintf(strText[1], " ");
					sprintf(strText[2], "CES LARVES QUI TE");
					sprintf(strText[3], "SERVAIENT D'ADVERSAIRES");
					sprintf(strText[4], "ONT ETE REMISES A LEUR");
					sprintf(strText[5], "PLACE, ANEANTIS PAR TA");
					sprintf(strText[6], "MAITRISE DU COMBAT ET");
					sprintf(strText[7], "DE LA RUSE DANS");
					sprintf(strText[8], "L'ARENE! LES AUTRES");
					sprintf(strText[9], "BOODIES TE PROCLAMENT");
					sprintf(strText[10], "MAITRE TOUT PUISSANT...");
					sprintf(strText[11], "JUSQU'A TA PROCHAINE");
					sprintf(strText[12], "DEFAITE!");
					sprintf(strText[13], " ");
					sprintf(strText[14], " ");
					sprintf(strText[15], " ");
					pSurface->loadImage(DstroyGlobals::addResText("f2.pcx"));
					break;
				case 3:
					sprintf(strText[0], "BRAVO BOODIES VERT!");
					sprintf(strText[1], " ");
					sprintf(strText[2], "C'EST LORS DES GRANDES");
					sprintf(strText[3], "BATAILLES QUE L'ON");
					sprintf(strText[4], "RECONNAIT LES HEROS! LE");
					sprintf(strText[5], "PEUPLE BOODIES EST EN");
					sprintf(strText[6], "ADMIRATION DEVANT TON");
					sprintf(strText[7], "ECRASANTE VICTOIRE SUR");
					sprintf(strText[8], "TES ADVERSAIRES. TON");
					sprintf(strText[9], "TITRE DE MAITRE DES");
					sprintf(strText[10], "TOURNOIS NE SE CONTESTE");
					sprintf(strText[11], "AUCUNEMENT... MAIS");
					sprintf(strText[12], "ATTIRE DEJA DE NOUVEAUX");
					sprintf(strText[13], "PRETENDANTS!");
					sprintf(strText[14], " ");
					sprintf(strText[15], " ");
					pSurface->loadImage(DstroyGlobals::addResText("f3.pcx"));
					break;
				case 4:
					sprintf(strText[0], "BRAVO BOODIES ROUGE!");
					sprintf(strText[1], " ");
					sprintf(strText[2], "TA VICTOIRE EST DEJA");
					sprintf(strText[3], "ACCLAMEE A TRAVERS TOUT");
					sprintf(strText[4], "LE PAYS, ET LE PEUPLE");
					sprintf(strText[5], "CHANTE DES LOUANGES EN");
					sprintf(strText[6], "TON HONNEUR. TES");
					sprintf(strText[7], "ADVERSAIRES ONT ETE");
					sprintf(strText[8], "RIDICULISES MAIS");
					sprintf(strText[9], "PREPARENT DEJA LEUR");
					sprintf(strText[10], "REVANCHE!");
					sprintf(strText[11], " ");
					sprintf(strText[12], " ");
					sprintf(strText[13], " ");
					sprintf(strText[14], " ");
					sprintf(strText[15], " ");
					pSurface->loadImage(DstroyGlobals::addResText("f4.pcx"));
					break;
				}
				setBackground(pSurface);

				for (j=0;j<16;j++)
				{
					font.writeText(strText[j], 100, 20+j*12, TAcenter, 0, NULL);
				}

				playMusic(DstroyGlobals::addResText("win.mod"), 1);

				ttWhenToStop = TGITime::getCurrentTime();
				ttWhenToStop += 20000;

				return true;
			}
		}
	}


	return false;
}

bool DstroyPressFire::events(void)
{
	/*if (bEnd && TGITime::getCurrentTime() > ttWhenToStop)
	{
		bRunning = false;
		DstroyMenuMain* pMenu = new DstroyMenuMain;
	}*/
	if (DstroyGame::params.nLevel > 48)
	{
		bRunning = false;
		DstroyEndGame* pMenu = new DstroyEndGame;
	}

	return TGIMain::events();
}
