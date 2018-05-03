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
#include "DstroyGame.h"

#include "DstroyMenuMain.h"
#include "DstroyMenuAdventure.h"

#include "DstroyFloor.h"
#include "DstroyItem.h"
#include "DstroyWall.h"
#include "DstroyPlayer.h"
#include "DstroyMonster.h"
#include "DstroyBomb.h"

#include "DstroyMenuPause.h"
#include "DstroyPressFire.h"

#include <string.h>
#include <vitasdk.h>

typedef struct DstroyMapItem
{
	int classId;
	int nSprite;

} DstroyMapItem;

DstroyGameParams DstroyGame::params;

DstroyGame::DstroyGame(void)
{
	bFinishedGame = false;
	matrixGame = NULL;
	TGIint i;
	for (i=0;i<4;i++)
	{
		pTextLives[i] = NULL;
	}
	nCurrentMonsterToThink = 0;

	nSpriteSize = 16;
}

DstroyGame::~DstroyGame(void)
{
	if (matrixGame)
	{
		delete [] matrixGame;
	}
}

bool DstroyGame::loadB(std::string cstrFile)
{
	unsigned int i,j,k,l;
	TGISurface* pSurface = NULL;
	TGISprite sprite;

	//players
	pSurface = new TGISurface;
	pSurface->setInvisibleColor(0, 0, 0);
	pSurface->loadImage(cstrFile, true);
	
	vecSurface.push_back(pSurface);

	sprite.setSurface(vecSurface[vecSurface.size()-1]);

	k=0;
	l=0;
	while(k!=4)
	{
		pdsPlayer[l] = new DstroyPlayer;
		pdsPlayer[l]->lId = l+1;
		pdsPlayer[l]->bAlive = false;
		pdsPlayer[l]->bVisible = false;
		for (i=0;i<3;i++)
		{
			for (j=0;j<18;j++)
			{
				sprite.setPlacement(j*nSpriteSize, (i+k*3)*nSpriteSize, nSpriteSize, nSpriteSize);
				pdsPlayer[l]->addSprite(sprite);
			}
		}
		switch(k)
		{
		case 0: k=2;break;
		case 1: k=3;break;
		case 2: k=1;break;
		case 3: k=4;break;
		}
		l++;
	}

	return true;
}

bool DstroyGame::loadM(std::string cstrFile)
{
	unsigned int i,j;
	TGISurface* pSurface = NULL;
	TGISprite sprite;

	pSurface = new TGISurface;
	pSurface->setInvisibleColor(0, 0, 0);
	pSurface->loadImage(cstrFile);
	
	vecSurface.push_back(pSurface);

	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	
	//monster 1
	for (i=0;i<3;i++)
	{
		for (j=0;j<18;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			dsMonsterStandard1.addSprite(sprite);
		}
	}
	//monster 2
	for (i=3;i<6;i++)
	{
		for (j=0;j<18;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			dsMonsterStandard2.addSprite(sprite);
		}
	}
	//bonus
	for (i=7;i<11;i++)
	{
		for (j=0;j<16;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			dsBonusStandard.addSprite(sprite);
		}
	}
	dsBonusStandard.bVisible = false;

	return true;
}

bool DstroyGame::loadE(std::string cstrFile)
{
	unsigned int i,j;
	TGISurface* pSurface = NULL;
	TGISprite sprite;

	pSurface = new TGISurface;
	pSurface->setInvisibleColor(0, 0, 0);
	pSurface->loadImage(cstrFile);
	
	vecSurface.push_back(pSurface);

	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	
	//bombs
	for (i=0;i<1;i++)
	{
		for (j=0;j<9;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			dsBombStandard.addSprite(sprite);
		}
	}
	sprite.setPlacement(0, 8*nSpriteSize, nSpriteSize, nSpriteSize);
	dsBombStandard.addSprite(sprite); //la remote

	//explosions
	for (i=1;i<6;i++)
	{
		for (j=0;j<17;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			dsExplosionStandard.addSprite(sprite);
		}
	}
	dsExplosionStandard.bVisible = true;

	//teleporting players
	for (i=6;i<8;i++)
	{
		for (j=0;j<9;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			dsTeleportingStandard.addSprite(sprite);
		}
	}

	return true;
}

bool DstroyGame::loadG(std::string cstrFile, TGIuint8 nWallNo, std::vector<DstroyItem*>& vecToMakeMap)
{
	unsigned int i,j;
	TGISurface* pSurface = NULL;
	TGISprite sprite;

	pSurface = new TGISurface;
	pSurface->loadImage(cstrFile);
	vecSurface.push_back(pSurface);
	sprite.setSurface(vecSurface[vecSurface.size()-1]);

	DstroyFloor* pFloor = NULL;
	pFloor = new DstroyFloor;
	for (i=0;i<1;i++)
	{
		for (j=0;j<20;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			pFloor->addSprite(sprite);
		}
	}
	vecToMakeMap.push_back(pFloor);

	//CLASSID_NO
	DstroyWall* pWall = NULL;
	pWall = new DstroyWall;
	pWall->classId = CLASSID_NO;
	i=1;
	{
		for (j=0;j<nWallNo;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			pWall->addSprite(sprite);
		}
	}
	vecToMakeMap.push_back(pWall);

	//CLASSID_WALL
	pWall = NULL;
	pWall = new DstroyWall;
	i=1;
	{
		for (j=nWallNo;j<20;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			pWall->addSprite(sprite);
		}
	}
	vecToMakeMap.push_back(pWall);

	//soft wall
	for (i=2;i<8;i++)
	{
		for (j=0;j<20;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			dsSoftWallStandard.addSprite(sprite);
		}
	}
	dsSoftWallStandard.bVisible = true;

	//nests
	i=8;
	{
		for (j=0;j<8;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			dsNestOutStandard.addSprite(sprite);
		}
	}
	i=9;
	{
		for (j=0;j<8;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			dsNestCreatorStandard.addSprite(sprite);
		}
	}
	i=10;
	{
		for (j=0;j<8;j++)
		{
			sprite.setPlacement(j*nSpriteSize, i*nSpriteSize, nSpriteSize, nSpriteSize);
			dsNestCreatorStandard.addSprite(sprite);
			dsNestOutStandard.addSprite(sprite);
		}
	}

	/*dsNestCreatorStandard.init(NESTTYPE_CREATOR, 1, 30000);
	dsNestOutStandard.init(NESTTYPE_OUT);*/

	return true;
}

bool DstroyGame::init()
{
	int i;

	if (!TGIMain::init())
		return false;

	bEraseBackground = false;
	
	options.load();

	TGISurface* pSurface;
	pSurface = new TGISurface;
	pSurface->setInvisibleColor(0, 0, 0);
	pSurface->loadImage(DstroyGlobals::addResText("l1.pcx"));
	
	font.setSurface(pSurface);
	font.importFixedFont(true, 0, 8*7, 320, 8*7, 8, 8);


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

	loadCommands(DstroyGlobals::addConfigText("commands"));

	TGIInputMessage message;
	message.lId	= up;
	message.lIdRecipient = 1;
	message.bAutofire = true;
	message.sdlKey = SCE_CTRL_UP;
	vecInputMessage.push_back(message);

	message.lId	= down;
	message.lIdRecipient = 1;
	message.sdlKey = SCE_CTRL_DOWN;
	vecInputMessage.push_back(message);

	message.lId	= left;
	message.lIdRecipient = 1;
	message.sdlKey = SCE_CTRL_LEFT;
	vecInputMessage.push_back(message);

	message.lId	= right;
	message.lIdRecipient = 1;
	message.sdlKey = SCE_CTRL_RIGHT;
	vecInputMessage.push_back(message);

	message.lId	= 10;
	message.lIdRecipient = 1;
	message.bAutofire = false;
	message.sdlKey = SCE_CTRL_CROSS;
	vecInputMessage.push_back(message);

	nLevelMinToQuePasa = 3;
	nLevelMinFixedObjects = 0;

	loadMap(DstroyGame::params.cstrFile);
	
/*	TGIInputMessage tricheMessage;
	tricheMessage.lId = 20;
	tricheMessage.lIdRecipient = 1;
	tricheMessage.sdlKey = SDLK_TAB;

	this->vecInputMessage.push_back(tricheMessage);*/

	

	createPlayers();

	soundXtraLife.loadFile(DstroyGlobals::addResText("xtralife.wav"));
	soundBomb.loadFile(DstroyGlobals::addResText("bombe.wav"));
	soundFlame.loadFile(DstroyGlobals::addResText("flamme.wav"));
	

	soundBoom.loadFile(DstroyGlobals::addResText("boom.wav"));
	
	soundChange.loadFile(DstroyGlobals::addResText("change.wav"));
	subTypeSound[BONUSS_CHANGE] = &soundChange;
	soundControl.loadFile(DstroyGlobals::addResText("control.wav"));
	subTypeSound[BONUSS_CONTROL] = &soundControl;
	soundCross.loadFile(DstroyGlobals::addResText("cross.wav"));
	subTypeSound[BONUSS_CROSS] = &soundCross;
	soundCrossFire.loadFile(DstroyGlobals::addResText("crossfir.wav"));
	subTypeSound[BONUSS_CROSSFIRE] = &soundCrossFire;
	soundDropBomb.loadFile(DstroyGlobals::addResText("dropbomb.wav"));
	subTypeSound[BONUSS_DROPBOMB] = &soundDropBomb;
	soundFastBomb.loadFile(DstroyGlobals::addResText("fastbomb.wav"));
	subTypeSound[BONUSS_FASTBOMB] = &soundFastBomb;
	soundFreeze.loadFile(DstroyGlobals::addResText("freeze.wav"));
	subTypeSound[BONUSS_FREEZE] = &soundFreeze;
	soundMonsterFreeze.loadFile(DstroyGlobals::addResText("mstr-frz.wav"));
	subTypeSound[BONUSS_MONSTERFREEZE] = &soundMonsterFreeze;
	soundMonsterSpeed.loadFile(DstroyGlobals::addResText("mstr-spd.wav"));
	subTypeSound[BONUSS_MONSTERSPEED] = &soundMonsterSpeed;
	soundRemote.loadFile(DstroyGlobals::addResText("remote.wav"));
	subTypeSound[BONUSS_REMOTE] = &soundRemote;
	soundReverse.loadFile(DstroyGlobals::addResText("reverse.wav"));
	subTypeSound[BONUSS_REVERSE] = &soundReverse;
	soundShadow.loadFile(DstroyGlobals::addResText("shadow.wav"));
	subTypeSound[BONUSS_SHADOW] = &soundShadow;
	soundShield.loadFile(DstroyGlobals::addResText("shield.wav"));
	subTypeSound[BONUSS_SHIELD] = &soundShield;
	soundSlow.loadFile(DstroyGlobals::addResText("slow.wav"));
	subTypeSound[BONUSS_SLOW] = &soundSlow;
	soundSlowBomb.loadFile(DstroyGlobals::addResText("slowbomb.wav"));
	subTypeSound[BONUSS_SLOWBOMB] = &soundSlowBomb;
	soundExplosion.loadFile(DstroyGlobals::addResText("xplosion.wav"));
	subTypeSound[BONUSS_EXPLOSION] = &soundExplosion;
	soundNextLevel.loadFile(DstroyGlobals::addResText("next-lvl.wav"));
	subTypeSound[BONUSS_NEXTLEVEL] = &soundNextLevel;
	soundMonster.loadFile(DstroyGlobals::addResText("monster.wav"));
	subTypeSound[BONUSS_MONSTER] = &soundMonster;
	soundSwap.loadFile(DstroyGlobals::addResText("swap.wav"));
	subTypeSound[BONUSS_SWAP] = &soundSwap;
	soundTransfert.loadFile(DstroyGlobals::addResText("transfer.wav"));
	subTypeSound[BONUSS_TRANSFERT] = &soundTransfert;
	soundReversePlayer.loadFile(DstroyGlobals::addResText("rvrs-plr.wav"));
	subTypeSound[BONUSS_REVERSEPLAYER] = &soundReversePlayer;

	//reserves
	for (i=0;i<25;i++)
	{
		reserveBomb.add(new DstroyBomb(dsBombStandard));
	}
	for (i=0;i<100;i++)
	{
		reserveExplosion.add(new DstroyExplosion(dsExplosionStandard));
	}

	

	//bonusNextLevel();
	
	return true;
}
bool DstroyGame::loadMap(std::string strMap)
{
	TGIFile tgiFile;

	tgiFile.openRead(strMap.c_str(), true);
	if (!tgiFile.isOpen())
		return false;

	TGIGlobals::Trace("map ouverte.");

	TGIuint8 n8;
	TGIuint16 nIA1=1, nIA2=0, nIA3=0, n16;
	TGIuint16 nWidth=0, nHeight=0;
	TGIuint16 version, order;
	//probabilités
	TGIuint8 nProbaBloc = 85;

	TGIuint16 nxPlayer[4];
	TGIuint16 nyPlayer[4];

	DstroyMapItem* pMap = NULL;

	TGIuint16 j;
	TGIuint16 i, k;

	TGIuint8 nLevel;

	char strMusic[256];
	char strB[256], strE[256], strG[256], strM[256], strTrunk[256];
	TGIuint8 nWallNo;

	TGIuint8 nNest;
	TGIuint16 nxNestCreator[256];
	TGIuint16 nyNestCreator[256];
	TGIuint16 nxNestOut[256];
	TGIuint16 nyNestOut[256];
	TGIuint16 nNestPeriodicity[256];
	TGIuint8 nNestLife[256];
	TGIuint8 nNestMonsterType[256];
	TGIuint8 nNestMonsterLife[256];
	TGIuint8 nNestMonsterIA[256];
	TGIuint8 nNestMaxMonster[256];
 
	//copy from DStroyMap :

	//order 
	tgiFile.read((char*)&order, 2);
	//version
	tgiFile.read((char*)&version, 2);
	if (version >= 1)
	{
		//width
		tgiFile.read((char*)&nWidth, 2);
		//height
		tgiFile.read((char*)&nHeight, 2);

		pMap = new DstroyMapItem[nWidth * nHeight];

		//players
		for (i=0;i<4;i++)
		{
			tgiFile.read((char*)&(nxPlayer[i]), 2);
			tgiFile.read((char*)&(nyPlayer[i]), 2);
		}
		//reserved
		char reserved[16];
		tgiFile.read(reserved, 16);
		//monsters
		if (version <= 2)
		{
			tgiFile.read((char*)&n16, 2);
			tgiFile.read((char*)&n16, 2);
		}

		if (version >= 2)
		{
			tgiFile.read((char*)&nLevel, 1);
			if (version < 3)
			{

				switch (nLevel)
				{
				case 1:
					strncpy(strMusic, ("1strage.mod"), 256);
					strncpy(strB, ("b1.pcx"), 256);
					strncpy(strE, ("e1.pcx"), 256);
					strncpy(strM, ("m1.pcx"), 256);
					strncpy(strG, ("g1.pcx"), 256);
					nWallNo = 1;
					break;
				case 2:
					strncpy(strMusic, ("middle.mod"), 256);
					strncpy(strB, ("b2.pcx"), 256);
					strncpy(strE, ("e2.pcx"), 256);
					strncpy(strM, ("m2.pcx"), 256);
					strncpy(strG, ("g2.pcx"), 256);
					nWallNo = 1;
					break;
				case 3:
					strncpy(strMusic, ("nabots.mod"), 256);
					strncpy(strB, ("b5.pcx"), 256);
					strncpy(strE, ("e5.pcx"), 256);
					strncpy(strM, ("m5.pcx"), 256);
					strncpy(strG, ("g5.pcx"), 256);
					nWallNo = 1;
					break;
				case 4:
					strncpy(strMusic, ("water.mod"), 256);
					strncpy(strB, ("b3.pcx"), 256);
					strncpy(strE, ("e3.pcx"), 256);
					strncpy(strM, ("m3.pcx"), 256);
					strncpy(strG, ("g3.pcx"), 256);
					nWallNo = 10;
					break;
				case 5:
					strncpy(strMusic, ("theworks.mod"), 256);
					strncpy(strB, ("b4.pcx"), 256);
					strncpy(strE, ("e4.pcx"), 256);
					strncpy(strM, ("m4.pcx"), 256);
					strncpy(strG, ("g4.pcx"), 256);
					nWallNo = 3;
					break;
				case 6:
					strncpy(strMusic, ("farwest.mod"), 256);
					strncpy(strB, ("b7.pcx"), 256);
					strncpy(strE, ("e7.pcx"), 256);
					strncpy(strM, ("m7.pcx"), 256);
					strncpy(strG, ("g7.pcx"), 256);
					nWallNo = 20;
					break;
				case 7:
					strncpy(strMusic, DstroyGlobals::addResText("haloween.mod"), 256);
					strncpy(strB, DstroyGlobals::addResText("b8.pcx"), 256);
					strncpy(strE, DstroyGlobals::addResText("e8.pcx"), 256);
					strncpy(strM, DstroyGlobals::addResText("m8.pcx"), 256);
					strncpy(strG, DstroyGlobals::addResText("g8.pcx"), 256);
					nWallNo = 1;
					break;
				case 8:
					strncpy(strMusic, DstroyGlobals::addResText("techno.mod"), 256);
					strncpy(strB, DstroyGlobals::addResText("b6.pcx"), 256);
					strncpy(strE, DstroyGlobals::addResText("e6.pcx"), 256);
					strncpy(strM, DstroyGlobals::addResText("m6.pcx"), 256);
					strncpy(strG, DstroyGlobals::addResText("g6.pcx"), 256);
					nWallNo = 1;
					break;
				default:
					return false;
				}
			}
		}
		if (version >= 3)
		{
			tgiFile.read(strB, 256);
			makeLower(strB);
			tgiFile.read(strE, 256);
			makeLower(strE);
			tgiFile.read(strG, 256);
			makeLower(strG);
			tgiFile.read(strM, 256);
			makeLower(strM);
			tgiFile.read(strMusic, 256);
			makeLower(strMusic);

			if (version >= 5)
			{
				tgiFile.read((char*)&nMusicRepeat, 2);
			}
			else
			{
				nMusicRepeat = 0;
			}


			/*tgiFile.read(strTrunk, 256);
			tgiFile.read(strTrunk, 256);
			tgiFile.read(strTrunk, 256);
			tgiFile.read(strTrunk, 256);
			tgiFile.read(strTrunk, 256);*/

			/*strncpy(strMusic, DstroyGlobals::addResText("1strage.mod"), 256);
			strncpy(strB, DstroyGlobals::addResText("b1.pcx"), 256);
			strncpy(strE, DstroyGlobals::addResText("e1.pcx"), 256);
			strncpy(strM, DstroyGlobals::addResText("m1.pcx"), 256);
			strncpy(strG, DstroyGlobals::addResText("g1.pcx"), 256);*/


			tgiFile.read((char*)&nWallNo, 1);

			for (i=0;i<4;i++)
			{
				if (i <= DstroyGame::params.nDifficulty)
				{
					if (version < 4)
					{
						tgiFile.read((char*)&n16, 2);
						tgiFile.read((char*)&n16, 2);
					}
					tgiFile.read((char*)&nIA1, 2);
					tgiFile.read((char*)&nIA2, 2);
					tgiFile.read((char*)&nIA3, 2);

					tgiFile.read((char*)&nNest, 1);
					for (j=0;j<nNest;j++)
					{
						tgiFile.read((char*)&nxNestCreator[j], 2);
						TGIGlobals::endianConvert(order, &(nxNestCreator[j]), 2);
						tgiFile.read((char*)&nyNestCreator[j], 2);
						TGIGlobals::endianConvert(order, &(nyNestCreator[j]), 2);
						tgiFile.read((char*)&nxNestOut[j], 2);
						TGIGlobals::endianConvert(order, &(nxNestOut[j]), 2);
						tgiFile.read((char*)&nyNestOut[j], 2);
						TGIGlobals::endianConvert(order, &(nyNestOut[j]), 2);
						tgiFile.read((char*)&nNestPeriodicity[j], 2);
						TGIGlobals::endianConvert(order, &(nNestPeriodicity[j]), 2);
						tgiFile.read((char*)&nNestLife[j], 1);
						tgiFile.read((char*)&nNestMonsterType[j], 1);
						if (version >= 4)
						{
							tgiFile.read((char*)&nNestMonsterLife[j], 1);
							tgiFile.read((char*)&nNestMonsterIA[j], 1);
							tgiFile.read((char*)&nNestMaxMonster[j], 1);
						}
					}

					tgiFile.read((char*)&nProbaBloc, 1);
				}
				else
				{
					if (version < 4)
					{
						tgiFile.read((char*)&n16, 2);
						tgiFile.read((char*)&n16, 2);
					}
					tgiFile.read((char*)&n16, 2);
					tgiFile.read((char*)&n16, 2);
					tgiFile.read((char*)&n16, 2);

					tgiFile.read((char*)&n8, 1);
					if (n8 > 0)
					{
						for (TGIint nn=n8;nn>0;nn--)
						{
							tgiFile.read((char*)&n16, 2);
							tgiFile.read((char*)&n16, 2);
							tgiFile.read((char*)&n16, 2);
							tgiFile.read((char*)&n16, 2);
							tgiFile.read((char*)&n16, 2);
							tgiFile.read((char*)&n8, 1);
							tgiFile.read((char*)&n8, 1);
							if (version >= 4)
							{
								tgiFile.read((char*)&n8, 1);
								tgiFile.read((char*)&n8, 1);
								tgiFile.read((char*)&n8, 1);
							}
						}
					}

					tgiFile.read((char*)&n8, 1);
				}

			}
		}

		//map data
		for (i=0;i<nWidth*nHeight;i++)
		{
			tgiFile.read((char*)&n8, 1);
			TGIGlobals::endianConvert(order, &n8, 1);
			pMap[i].classId = n8;
			tgiFile.read((char*)&n8, 1);
			TGIGlobals::endianConvert(order, &n8, 1);
			pMap[i].nSprite = n8;
			
		}
	}

	tgiFile.close();



	//end copy

	/*nProbaBloc = 0;
	nIA1 = 0;
	nIA2 = 0;
	nIA3 = 1;*/

	this->nWidth = nWidth;
	this->nHeight = nHeight;

	//bonus type
	DstroyGame::params.initBonuses();

	TGIlong lId, lIndex;

	std::vector<DstroyItem*> vecObject;
	std::list<DstroyItem*> listObject;
	std::vector<DstroyItem*> vecToMakeMap;

	register std::list<DstroyItem*>::iterator itList;

	TGIGlobals::playMusic(DstroyGlobals::addResText(strMusic), -1, nMusicRepeat);
	loadB(DstroyGlobals::addResText(strB));
	loadE(DstroyGlobals::addResText(strE));
	loadM(DstroyGlobals::addResText(strM));
	loadG(DstroyGlobals::addResText(strG), nWallNo, vecToMakeMap);

	for (i=0;i<4;i++)
	{
		pdsPlayer[i]->setPosGrid(nxPlayer[i], nyPlayer[i]);
		pdsPlayer[i]->setStartPos(nxPlayer[i], nyPlayer[i]);
		addObject(pdsPlayer[i], 10);
	}

	

	if (matrixGame)
	{
		delete [] matrixGame;
		matrixGame = NULL;
	}
	matrixGame = new std::list<DstroyItem*>[nWidth * nHeight];

	ia.init(nWidth, nHeight);

	//TGIint nTotalWalls = 0;
	//TGIint nSize = nWidth*nHeight;
	DstroyItem* pObject;

	TGIint nRand;

	for (i=0;i<nHeight;i++)
	for (k=0;k<nWidth;k++)
	{
		lId = pMap[i*nWidth + k].classId;
		lIndex = pMap[i*nWidth + k].nSprite;

		for (j=0;j<vecToMakeMap.size();j++)
		{
			if (vecToMakeMap[j]->classId == lId)
			{
				pObject = new DstroyItem(*vecToMakeMap[j]);
				pObject->bVisible = true;
				pObject->setPosGrid(k, i);
				pObject->setCurrentSprite(lIndex);
				
				if (pObject->classId == CLASSID_FLOOR)
					addObject(pObject, 0);
				else
					addObject(pObject, 1);

				break;
			}
		}
	}

	//placons les nids a monstres
	DstroyNest* pNestOut, *pNestCreator;
	for (i=0;i<nNest;i++)
	{
		pNestOut = new DstroyNest(dsNestOutStandard);
		pNestCreator = new DstroyNest(dsNestCreatorStandard);
		if (DstroyGame::params.nDifficulty == 3)
		{
			pNestOut->initOut(nNestMonsterType[i], 4, nNestMonsterLife[i]);
		}
		else
		{
			pNestOut->initOut(nNestMonsterType[i], nNestMonsterIA[i], nNestMonsterLife[i]);
		}
		pNestCreator->initCreator(nNestLife[i], nNestPeriodicity[i], nNestMaxMonster[i], pNestOut);
		pNestOut->setPosGrid(nxNestOut[i], nyNestOut[i]);
		pNestCreator->setPosGrid(nxNestCreator[i], nyNestCreator[i]);
		//on supprime les objets au meme endroit et on met un NO(0) à la place
		getObjectsOnPos(NULL, nxNestCreator[i], nyNestCreator[i], listObject);
		/*for (j=0;j<vecObject.size();j++)
		{
			deleteObject(vecObject[j]);
		}*/
		for (itList=listObject.begin();itList!=listObject.end();itList++)
		{
			deleteObject(*itList);
		}
		for (j=0;j<vecToMakeMap.size();j++)
		{
			if (vecToMakeMap[j]->classId == CLASSID_NO)
			{
				pObject = new DstroyItem(*vecToMakeMap[j]);
				pObject->bVisible = true;
				pObject->setPosGrid(nxNestCreator[i], nyNestCreator[i]);
				pObject->setCurrentSprite(0);
				addObject(pObject, 1);
				break;
			}
		}
		getObjectsOnPos(NULL, nxNestOut[i], nyNestOut[i], listObject);
		for (itList=listObject.begin();itList!=listObject.end();itList++)
		{
			deleteObject(*itList);
		}
		for (j=0;j<vecToMakeMap.size();j++)
		{
			if (vecToMakeMap[j]->classId == CLASSID_NO)
			{
				pObject = new DstroyItem(*vecToMakeMap[j]);
				pObject->bVisible = true;
				pObject->setPosGrid(nxNestOut[i], nyNestOut[i]);
				pObject->setCurrentSprite(0);
				addObject(pObject, 1);
				break;
			}
		}
		addObject(pNestCreator, 3);
		addObject(pNestOut, 3);
	}


	//placons les monstres sur le terrain
	//cas spéciaux des boss
	if (/*strcmp(strMusic, "boss.mod")==0*/DstroyGame::params.nLevel == 48)
	{
		dsMonsterStandard1.lSpeed = 2;
		dsMonsterStandard2.lSpeed = 2;
	}

	DstroyMonster* pMonster;
	TGIuint8 nIA = 0;
	for (i=0;i<nIA1+nIA2+nIA3;i++)
	{
		if (i==nIA1)
			nIA = 1;
		if (i==nIA1+nIA2)
			nIA = 2;

		if (i%2)
		{
			pMonster = new DstroyMonster(dsMonsterStandard1);
		}
		else
		{
			pMonster = new DstroyMonster(dsMonsterStandard2);
		}
		j = k = 0;
		while (!canPlaceItem(j,k, 5))
		{
			j = rand() % nWidth;
			k = rand() % nHeight;
		}
		pMonster->bVisible = true;
		pMonster->setPosGrid(j, k);
		if (DstroyGame::params.nDifficulty == 3)
		{
			if (nIA <= 1)
				pMonster->nIA = 3;
			else
				pMonster->nIA = 4;
		}
		else
		{
			pMonster->nIA = nIA;
		}
		addObject(pMonster, 8);
	}

	//placons les softs walls
	for (i=1;i<nHeight-1;i++)
	for (k=1;k<nWidth-1;k++)
	{
		nRand = rand()%256;
		if (nRand < nProbaBloc && /*pMap[i*nWidth + k].classId == CLASSID_FLOOR*/canPlaceItem(k, i, 2))
		{
			pObject = new DstroySoftWall(dsSoftWallStandard);
			pObject->setPosGrid(k, i);
			pObject->setCurrentSprite(pMap[i*nWidth + k].nSprite);
			pObject->bVisible = true;
			((DstroySoftWall*)pObject)->setBonus(&(DstroyGame::params));							

			addObject(pObject, 3);
		}
	}

	delete [] pMap;

	for (i=0;i<vecToMakeMap.size();i++)
	{
		delete vecToMakeMap[i];
	}
	vecToMakeMap.clear();

	return true;
}

bool DstroyGame::getObjectsOnPos(DstroyItem* pObjectSource, TGIint x, TGIint y, std::list<DstroyItem*>& listObject)
{

	listObject.clear();

	if (x < 0 || x >= nWidth)
		return false;
	if (y < 0 || y >= nHeight)
		return false;

	TGIint nIndex = y*nWidth+x;
	register std::list<DstroyItem*>::iterator it;

	for (it=matrixGame[nIndex].begin();it!=matrixGame[nIndex].end();it++)
	{
		if ((*it) != pObjectSource)
			listObject.push_back((*it));
	}
	
	for (it=vecObjectMoving.begin();it!=vecObjectMoving.end();it++)
	{
		if ((*it) != pObjectSource && (*it)->gridX() == x && (*it)->gridY() == y)
			listObject.push_back((*it));
	}

	//vecObject.remove(pObjectSource);

	

	/*for (i=0;i<matrixGame[nIndex].size();i++)
	{
		if ((matrixGame[nIndex])[i] != pObjectSource)
		{
			vecObject.push_back(matrixGame[nIndex][i]);
		}
	}
	for (i=0;i<vecObjectMoving.size();i++)
	{
		if (vecObjectMoving[i] != pObjectSource && vecObjectMoving[i]->gridX() == x && vecObjectMoving[i]->gridY() == y)
			vecObject.push_back(vecObjectMoving[i]);
	}*/

	return true;
}

bool DstroyGame::canPlaceItem(TGIint x, TGIint y, TGIint nRange)
{
	TGIint xs, ys;
	std::list<DstroyItem*> listObject;
	register std::list<DstroyItem*>::iterator itList;

	getObjectsOnPos(NULL, x, y, listObject);
	//for (i=0;i<vecObject.size();i++)
	for (itList=listObject.begin();itList!=listObject.end();itList++)
	{
		if ((*itList)->isPlain() || (*itList)->classId == CLASSID_MONSTER || (*itList)->classId == CLASSID_PLAYER)
			return false;
	}

	ys=0;
	for (xs=-nRange;xs<=nRange;xs++)
	{
		getObjectsOnPos(NULL, x+xs, y+ys, listObject);
		for (itList=listObject.begin();itList!=listObject.end();itList++)
		{
			if ((*itList)->classId == CLASSID_PLAYER)
				return false;
		}
	}
	xs=0;
	for (ys=-nRange;ys<=nRange;ys++)
	{
		getObjectsOnPos(NULL, x+xs, y+ys, listObject);
		for (itList=listObject.begin();itList!=listObject.end();itList++)
		{
			if ((*itList)->classId == CLASSID_PLAYER)
				return false;
		}
	}

	return true;
}

bool DstroyGame::addObject(TGIObject* pObject, TGIint nDepth)
{
	DstroyItem* pItem = (DstroyItem*)pObject;
	if (pItem->classId == CLASSID_NO || pItem->classId == CLASSID_FLOOR || pItem->classId == CLASSID_WALL || pItem->classId == CLASSID_SOFTWALL || pItem->classId == CLASSID_EXPLOSION)
	{
		if (pItem->gridY() >= 0 && pItem->gridY() < nHeight && pItem->gridX() >=0 && pItem->gridX() < nWidth)
			matrixGame[pItem->gridY()*nWidth + pItem->gridX()].push_back(pItem);
	}
	else
	{
		vecObjectMoving.push_back(pItem);
	}
	if (pItem->classId == CLASSID_MONSTER)
	{
		vecMonster.push_back((DstroyMonster*)pObject);
	}
	if (pItem->classId == CLASSID_NEST && ((DstroyNest*)pItem)->nType == NESTTYPE_CREATOR)
	{
		vecNest.push_back((DstroyNest*)pObject);
	}
	if (pItem->classId == CLASSID_BOMB)
	{
		vecBomb.push_back((DstroyBomb*)pObject);
	}

	return TGIMain::addObject(pObject, nDepth);
}

bool DstroyGame::deleteObject(TGIObject* pObject, bool bDelete)
{
	DstroyItem* pItem = (DstroyItem*)pObject;
	TGIuint16 index;
	
	if (pItem->classId == CLASSID_NO || pItem->classId == CLASSID_FLOOR || pItem->classId == CLASSID_WALL || pItem->classId == CLASSID_SOFTWALL || pItem->classId == CLASSID_EXPLOSION)
	{
		if (pItem->gridY() >= 0 && pItem->gridY() < nHeight && pItem->gridX() >=0 && pItem->gridX() < nWidth)
		{
			index = pItem->gridY()*nWidth + pItem->gridX();

			register std::list<DstroyItem*>::iterator it;
			for (it=matrixGame[index].begin();it!=matrixGame[index].end();it++)
			{
				if ((*it) == pItem)
				{
					matrixGame[index].erase(it);
					break;
				}
			}
		}
		//si c'est une explosion on la stocke plutot que de la supprimer
		if (pItem->classId == CLASSID_EXPLOSION)
		{
			reserveExplosion.add(pItem);
			return TGIMain::deleteObject(pObject, false);
		}
		else
		{
			//reserveTrash.add(pItem);
			return TGIMain::deleteObject(pObject, true);
		}
	}
	else
	{
		register std::list<DstroyItem*>::iterator it;
		for (it=vecObjectMoving.begin();it!=vecObjectMoving.end();it++)
		{
			if ((*it) == pItem)
			{
				vecObjectMoving.erase(it);
				break;
			}
		}
	}

	if (pItem->classId == CLASSID_MONSTER)
	{
		register std::list<DstroyMonster*>::iterator it;
		for (it=vecMonster.begin();it!=vecMonster.end();it++)
		{
			if ((*it) == pItem)
			{
				vecMonster.erase(it);
				//reserveTrash.add(pItem);
				return TGIMain::deleteObject(pObject, true);
			}
		}
	}
	if (pItem->classId == CLASSID_NEST)
	{
		register std::list<DstroyNest*>::iterator it;
		for (it=vecNest.begin();it!=vecNest.end();it++)
		{
			if ((*it) == pItem)
			{
				vecNest.erase(it);
				//reserveTrash.add(pItem);
				return TGIMain::deleteObject(pObject, true);
			}
		}
	}
	if (pItem->classId == CLASSID_BOMB)
	{
		register std::list<DstroyBomb*>::iterator it;
		for (it=vecBomb.begin();it!=vecBomb.end();it++)
		{
			if ((*it) == pItem)
			{
				vecBomb.erase(it);
				reserveBomb.add(pItem);
				return TGIMain::deleteObject(pObject, false);
			}
		}
	}

	//reserveTrash.add(pItem);
	return TGIMain::deleteObject(pObject, true);
}

bool DstroyGame::exit(void)
{
	reserveBomb.clear();
	reserveExplosion.clear();
	reserveTrash.clear();

	TGIMain::exit();
	if (TGIGlobals::theMain == NULL)
	{
		DstroyMenuMain* pMenu;
		pMenu = new DstroyMenuMain;
	}

	return true;
}


void DstroyGame::createPlayers(void)
{
	TGIint i;
	for (i=0;i<DstroyGame::params.nPlayers;i++)
	{
		pdsPlayer[i]->bVisible = true;
		pdsPlayer[i]->bAlive = true;
		pdsPlayer[i]->nBombsLeft = pdsPlayer[i]->nBombs = DstroyGame::params.pnBombs[i];
		pdsPlayer[i]->nBombDurationLeft = DstroyGame::params.pnBombDuration[i];
		pdsPlayer[i]->nFlames = DstroyGame::params.pnFlame[i];
		/*pdsPlayer[i]->bShield = true;
		pdsPlayer[i]->tgEndShield = TGITime::getCurrentTime();
		pdsPlayer[i]->tgEndShield += 3000;*/
		pdsPlayer[i]->setShield(3000);

		pTextLives[i] = NULL;

		if (DstroyGame::params.pnLives[i] == 0)
		{
			//on ressuc(e?)ite a chaque début de nouveau niveau
			DstroyGame::params.pnLives[i] = 1;
			pdsPlayer[i]->nBombsLeft = pdsPlayer[i]->nBombs = 1;
			pdsPlayer[i]->nBombDurationLeft = 4;
			pdsPlayer[i]->nFlames = 1;
			//mais qui est "ite"?
		}
		
		//swap (pr n'échanger qu'une fois, on échange que le plus petit avec le plus grand)
		if (i<DstroyGame::params.pnSwap[i])
			swapPlayers(i, DstroyGame::params.pnSwap[i]);

	}

	TGIint width = TGIGlobals::screenWidth;
	TGIint height = TGIGlobals::screenHeight;

	TGISurface* pBg = NULL;
	pBg = new TGISurface;

	switch (DstroyGame::params.nPlayers)
	{
	case 1:
		delete pBg;
		pBg = NULL;
		addScreen(0, 0, width, height, 0, 0, nWidth*nSpriteSize, nHeight*nSpriteSize, pdsPlayer[0]);
		break;
	case 2:
		pBg->loadImage(DstroyGlobals::addResText("pf2.pcx"));
		addScreen(0, 0, 156, 154, 0, 0, nWidth*nSpriteSize, nHeight*nSpriteSize, pdsPlayer[0]);
		addScreen(164, 86, 156, 154, 0, 0, nWidth*nSpriteSize, nHeight*nSpriteSize, pdsPlayer[1]);
		break;
	case 3:
		pBg->loadImage(DstroyGlobals::addResText("pf3.pcx"));
		addScreen(0, 0, 156, 116, 0, 0, nWidth*nSpriteSize, nHeight*nSpriteSize, pdsPlayer[0]);
		addScreen(164, 124, 156, 116, 0, 0, nWidth*nSpriteSize, nHeight*nSpriteSize, pdsPlayer[1]);
		addScreen(164, 0, 156, 116, 0, 0, nWidth*nSpriteSize, nHeight*nSpriteSize, pdsPlayer[2]);
		break;
	case 4:
		pBg->loadImage(DstroyGlobals::addResText("pf4.pcx"));
		addScreen(0, 0, 156, 116, 0, 0, nWidth*nSpriteSize, nHeight*nSpriteSize, pdsPlayer[0]);
		addScreen(164, 124, 156, 116, 0, 0, nWidth*nSpriteSize, nHeight*nSpriteSize, pdsPlayer[1]);
		addScreen(164, 0, 156, 116, 0, 0, nWidth*nSpriteSize, nHeight*nSpriteSize, pdsPlayer[2]);
		addScreen(0, 124, 156, 116, 0, 0, nWidth*nSpriteSize, nHeight*nSpriteSize, pdsPlayer[3]);
				
		break;
	default:
		break;
	}

	setBackground(pBg);
	pBg = NULL;

	drawLives();
}

bool DstroyGame::events(void)
{
	TGIuint16 i;
	TGIint nAlive;
	TGIint nOneAlive = -1;
	std::list<DstroyMonster*>::iterator itMonster;

	nAlive = 0;

	if (bFinishedGame)
	{
		if (TGITime::getCurrentTime() > ttEnd)
		{
			bRunning = false;
			DstroyPressFire* pMenu;
			pMenu = new DstroyPressFire;
		}
		return TGIMain::events();
	}

	ia.calculateRisk();
	for (itMonster=vecMonster.begin();itMonster!=vecMonster.end();itMonster++)
	{
		ia.think(*itMonster);
	}

	if (DstroyGame::params.nMode == GAMEMODE_FIGHT || DstroyGame::params.nMode == GAMEMODE_KILLER)
	{
		for (i=0;i<4;i++)
		{
			if (pdsPlayer[i]->bAlive || pdsPlayer[i]->bVisible)
			{
				nOneAlive = i;
				nAlive++;
			}
		}
		if (nAlive <= 1 && this->vecBomb.empty())
		{
			//gagné!
			if (nOneAlive != -1)
				DstroyGame::params.pnWins[nOneAlive]++;
			finishGame();
		}
	}
	if (DstroyGame::params.nMode == GAMEMODE_ADVENTURE)
	{
		for (i=0;i<4;i++)
		{
			if (!pdsPlayer[i]->bAlive && !pdsPlayer[i]->bVisible && DstroyGame::params.pnLives[i] > 0)
			{
				DstroyGame::params.pnLives[i]--;
				if (DstroyGame::params.pnLives[i] > 0)
				{
					pdsPlayer[i]->setPosGrid(pdsPlayer[i]->startX, pdsPlayer[i]->startY);
					pdsPlayer[i]->bAlive = true;
					pdsPlayer[i]->bVisible = true;
					pdsPlayer[i]->setCurrentSprite(0);
					/*pdsPlayer[i]->bShield = true;
					pdsPlayer[i]->tgEndShield = TGITime::getCurrentTime();
					pdsPlayer[i]->tgEndShield += 3000;*/
					pdsPlayer[i]->setShield(3000);
				}
				drawLives();
			}

			if (DstroyGame::params.pnLives[i] > 0)
			{
				nAlive++;
			}
		}
		if (nAlive == 0)
		{
			//perdu
			DstroyGame::params.setLevel(0);
			finishGame();
		}
		if (this->vecMonster.empty() && this->vecNest.empty() && this->vecBomb.empty())
		{
			//gagné!
			DstroyGame::params.setLevel(DstroyGame::params.nLevel+1);
			for(i=0;i<4;i++)
			{
				DstroyGame::params.pnBombs[i] = pdsPlayer[i]->nBombs;
				DstroyGame::params.pnBombDuration[i] = pdsPlayer[i]->nBombDurationLeft;
				DstroyGame::params.pnFlame[i] = pdsPlayer[i]->nFlames;
			}
			DstroyGame::params.save(7);
			finishGame();
		}

	}

	return TGIMain::events();
}

bool DstroyGame::loadCommandsFromPlainText(std::string strFile)
{


	//get the number of keys whitch can be pressed
	/*int nNumKeys=0;
	SDL_GetKeyState(&nNumKeys);

	//blah blah
	//normalement on devrait lire dans le fichier sdlKey=lIdRecipient,lId

	TGIInputMessage message;


	ifs.close();*/

	return true;
}

void DstroyGame::bonusExplosion(void)
{
	//TGIuint16 i;
	register std::list<std::pair<TGIObject*, TGIint> >::iterator itObject; 

	for (itObject=getFirstObjectToQuePasa();itObject!=getEndObject();itObject++)
	{
		if (((DstroyItem*)itObject->first)->classId == CLASSID_BOMB)
		{
			((DstroyBomb*)itObject->first)->makeExplode();
		}
	}
}

void DstroyGame::bonusChange(DstroyPlayer* pSrc)
{
	TGIint nSwap = rand()%DstroyGame::params.nPlayers;
	while (pdsPlayer[nSwap] == pSrc || !(pdsPlayer[nSwap]->bAlive))
	{
		nSwap++;
	}
	DstroyPlayer* pDest = pdsPlayer[nSwap];

	TGIint x,y;
	x = pSrc->gridX();
	y = pSrc->gridY();

	pSrc->teleport(pDest->gridX(), pDest->gridY());
	pDest->teleport(x, y);
}

void DstroyGame::bonusCrossFire(void)
{
	TGIuint8 j = 10;

	DstroyBomb* pBomb;
	std::list<DstroyItem*> listObject;
	register std::list<DstroyItem*>::iterator itObject;

	TGIint newX, newY;
	bool bOK;

	for (;j>0;j--)
	{
		bOK = false;
		newX = rand()%nWidth;
		newY = rand()%nHeight;
		while (!bOK)
		{
			newX++;
			if (newX >= nWidth)
			{
				newX = 1;
				newY = (newY+1)%nHeight;
			}
			bOK = true;

			getObjectsOnPos(NULL, newX, newY, listObject);
			//for (i=0;i<vecObject.size();i++)
			for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
			{
				if ((*itObject)->isPlain())
				{
					bOK = false;
					break;
				}
			}
		}
		pBomb = createBomb();
		pBomb->bVisible = true;
		pBomb->initBomb(NULL, newX, newY, 2, 4);

		addObject(pBomb, 7);
	}
}

void DstroyGame::bonusMonsterFreeze(void)
{
	//TGIuint16 i;
	register std::list<DstroyMonster*>::iterator it;
	//for (i=0;i<vecMonster.size();i++)
	for (it=vecMonster.begin();it!=vecMonster.end();it++)
	{
		(*it)->bFreeze = true;
		(*it)->tgEndBonus = TGITime::getCurrentTime();
		(*it)->tgEndBonus += 10000;
	}
}

void DstroyGame::bonusMonsterSpeed(void)
{
	//TGIuint16 i;
	register std::list<DstroyMonster*>::iterator it;
	//for (i=0;i<vecMonster.size();i++)
	for (it=vecMonster.begin();it!=vecMonster.end();it++)
	{
		(*it)->bSpeed = true;
		(*it)->tgEndBonus = TGITime::getCurrentTime();
		(*it)->tgEndBonus += 10000;
	}
}

void DstroyGame::bonusNextLevel(void)
{
	DstroyGame::params.setLevel(DstroyGame::params.nLevel+1);
	for(TGIuint8 i=0;i<4;i++)
	{
		DstroyGame::params.pnBombs[i] = pdsPlayer[i]->nBombs;
		DstroyGame::params.pnBombDuration[i] = pdsPlayer[i]->nBombDurationLeft;
		DstroyGame::params.pnFlame[i] = pdsPlayer[i]->nFlames;
	}
	finishGame();
}

void DstroyGame::bonusSwap(DstroyPlayer* pSrc)
{
	TGIint nSwap = rand()%DstroyGame::params.nPlayers;
	while (pdsPlayer[nSwap] == pSrc || !(pdsPlayer[nSwap]->bAlive))
	{
		nSwap++;
	}

	TGIint i;
	for (i=0;i<DstroyGame::params.nPlayers;i++)
	{
		if (pdsPlayer[i] == pSrc)
		{
			swapPlayers(i, nSwap);
			break;
		}
	}

	//DstroyPlayer* pDest = pdsPlayer[nSwap];

	//points
	TGIint nTemp=0, nTemp2=0;
	for (i=0;i<DstroyGame::params.nPlayers;i++)
	{
		if (pdsPlayer[i] == pSrc)
		{
			nTemp = DstroyGame::params.pnWins[i];
			nTemp2 = DstroyGame::params.pnSwap[i];
			break;
		}
	}
	DstroyGame::params.pnWins[i] = DstroyGame::params.pnWins[nSwap];
	DstroyGame::params.pnWins[nSwap] = nTemp;
	DstroyGame::params.pnSwap[i] = DstroyGame::params.pnSwap[nSwap];
	DstroyGame::params.pnSwap[nSwap] = nTemp2;
}

void DstroyGame::swapPlayers(TGIint p1, TGIint p2)
{
	if (p1 == p2)
		return;

	DstroyPlayer* pSrc = pdsPlayer[p1];
	DstroyPlayer* pDest = pdsPlayer[p2];

	//commandes
	TGIuint16 i;
	for (i=0;i<vecInputMessage.size();i++)
	{
		if (vecInputMessage[i].lIdRecipient == pSrc->lId)
		{
			vecInputMessage[i].lIdRecipient = pDest->lId;
		}
		else if (vecInputMessage[i].lIdRecipient == pDest->lId)
		{
			vecInputMessage[i].lIdRecipient = pSrc->lId;
		}
	}
}


void DstroyGame::bonusReversePlayer(DstroyPlayer* pSrc)
{
	for (TGIuint16 i=0;i<DstroyGame::params.nPlayers;i++)
	{
		if (pdsPlayer[i] != pSrc)
		{
			pdsPlayer[i]->bReverse = true;
			pdsPlayer[i]->tgEndReverse = TGITime::getCurrentTime();
			pdsPlayer[i]->tgEndReverse += 6000;
		}	
	}
}


void DstroyGame::drawLives(void)
{
	if (DstroyGame::params.nMode != GAMEMODE_ADVENTURE)
		return;

	TGIint i;
	for (i=0;i<4;i++)
	{
		if (pTextLives[i])
		{
			TGIMain::deleteObject(pTextLives[i]);
			pTextLives[i] = NULL;
		}
	}

	char strLives[8];

	TGIint width = TGIGlobals::screenWidth;
	TGIint height = TGIGlobals::screenHeight;

	std::vector<TGIObject*> vecObjectText;

	switch (DstroyGame::params.nPlayers)
	{
	case 1:
		sprintf(strLives, "%d", DstroyGame::params.pnLives[0]);
		font.writeText(strLives, 5, height - 5 - 8, TAcenter, 0, &vecObjectText);
		pTextLives[0] = vecObjectText[0];
		break;
	case 2:
		sprintf(strLives, "%d", DstroyGame::params.pnLives[0]);
		font.writeText(strLives, 5, height*2/3 - 8, TAcenter, 0, &vecObjectText);
		pTextLives[0] = vecObjectText[0];

		sprintf(strLives, "%d", DstroyGame::params.pnLives[1]);
		font.writeText(strLives, width/2+2+5, height - 5 - 8, TAcenter, 0, &vecObjectText);
		pTextLives[1] = vecObjectText[0];
		break;
	case 4:
		sprintf(strLives, "%d", DstroyGame::params.pnLives[3]);
		font.writeText(strLives, 5, height - 5 - 8, TAcenter, 0, &vecObjectText);
		pTextLives[3] = vecObjectText[0];
	case 3:
		sprintf(strLives, "%d", DstroyGame::params.pnLives[0]);
		font.writeText(strLives, 5, height/2 - 8, TAcenter, 0, &vecObjectText);
		pTextLives[0] = vecObjectText[0];

		sprintf(strLives, "%d", DstroyGame::params.pnLives[1]);
		font.writeText(strLives, width/2+2+5, height - 5 - 8, TAcenter, 0, &vecObjectText);
		pTextLives[1] = vecObjectText[0];

		sprintf(strLives, "%d", DstroyGame::params.pnLives[2]);
		font.writeText(strLives, width/2+2+5, height/2 - 8, TAcenter, 0, &vecObjectText);
		pTextLives[2] = vecObjectText[0];
		break;
	default:
		break;
	}
}

void DstroyGame::stop(void)
{
	bPause = true;
	bool bSkipLevel = false;

	for(TGIint i=0;i<4;i++)
	{
		DstroyGame::params.pnBombs[i] = pdsPlayer[i]->nBombs;
		DstroyGame::params.pnBombDuration[i] = pdsPlayer[i]->nBombDurationLeft;
		DstroyGame::params.pnFlame[i] = pdsPlayer[i]->nFlames;
	}
	vecCurrentMessage.clear();

	DstroyMenuPause* pMenu;
	pMenu = new DstroyMenuPause(&bRunning, &bSkipLevel);
	while (TGIGlobals::theMain)
	{
		TGIGlobals::theMain->init();
		TGIGlobals::theMain->run();
		//pMenu->exit();
	}

	TGIGlobals::theMain = this;
	bPause = false;

	if (bSkipLevel)
	{
		bonusNextLevel();
	}

}

void DstroyGame::finishGame(void)
{
	bFinishedGame = true;

	register TGIuint16 i;
	register std::list<DstroyMonster*>::iterator it;

	//for (i=0;i<vecMonster.size();i++)
	for (it=vecMonster.begin();it!=vecMonster.end();it++)
	{
		(*it)->win();
	}
	for (i=0;i<4;i++)
	{
		pdsPlayer[i]->win();
	}

	ttEnd = TGITime::getCurrentTime();
	ttEnd += 3000;
}

void DstroyGame::addLifeToPlayer(DstroyPlayer* pPlayer)
{
	TGIuint16 i;
	for (i=0;i<4;i++)
	{
		if (pdsPlayer[i] == pPlayer)
		{
			if (DstroyGame::params.pnLives[i] < 10) // 9 max
			{
				DstroyGame::params.pnLives[i]++;
				drawLives();
			}
		}
	}
}


void DstroyGame::makeLower(char* pTexte)
{
	int i=0;
	while ((pTexte)[i] != 0)
	{
		if ((pTexte)[i] >= 65 && (pTexte)[i] <= 90)
		{
			(pTexte)[i] += 32;
		}
		i++;
	}
}

DstroyBomb* DstroyGame::createBomb()
{
	DstroyBomb* pNewBomb = NULL;
	
	if (reserveBomb.get((void**)&pNewBomb))
		return pNewBomb;
	
	pNewBomb = new DstroyBomb(dsBombStandard);
	

	return pNewBomb;
}

DstroyExplosion* DstroyGame::createExplosion()
{
	DstroyExplosion* pNewExplosion = NULL;
	
	if (reserveExplosion.get((void**)&pNewExplosion))
		return pNewExplosion;
	
	pNewExplosion = new DstroyExplosion(dsExplosionStandard);

	return pNewExplosion;
}
