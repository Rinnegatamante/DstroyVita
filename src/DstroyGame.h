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

#include <vector>
#include <list>
#include "TGIMain.h"

#include "DstroyGlobals.h"

#include "DstroyBomb.h"
#include "DstroyExplosion.h"
#include "DstroySoftWall.h"
#include "DstroyBonus.h"
#include "DstroyMonster.h"
#include "DstroyPlayer.h"
#include "DstroyNest.h"
#include "DstroyTeleporting.h"
#include "DstroyGameParams.h"

#include "DstroyAI.h"
#include "DstroyOptions.h"

#include "TGISound.h"
#include "TGIFont2.h"
#include "TGIReserve.h"

class DstroyGame : public TGIMain
{
	DstroyAI ia;
	TGIuint16 nMusicRepeat;

	TGITime ttEnd;

	TGIuint8 nSpriteSize;
	bool bOptionsText;

	//lors de la creation du terrain, si on peut placer quelque chose aléatoirement ici
	bool canPlaceItem(TGIint x, TGIint y, TGIint nRange);
	
	//stockage des pointeurs des objets, pr améliorer les perf
	//dans une matrice fixe pr les objects fixes
	std::list<DstroyItem*>* matrixGame;
	//dans un vecteur pr les objects mobiles
	std::list<DstroyItem*> vecObjectMoving;

	//prout
	bool loadCommandsFromPlainText(std::string strFile);

	//chargement des images de sprite
	bool loadB(std::string cstrFile);
	bool loadM(std::string cstrFile);
	bool loadE(std::string cstrFile);
	bool loadG(std::string cstrFile, TGIuint8 nWallNo, std::vector<DstroyItem*>& vecToMakeMap);

	
	//texte des vies
	TGIObject* pTextLives[4];

	
public:
	//reserves de bombes, explosions et trash
	TGIReserve reserveBomb;
	TGIReserve reserveExplosion;
	TGIReserve reserveTrash;

	DstroyOptions options;
	//text
	TGIFont2 font;
	bool bFinishedGame;
	//taille du terrain
	TGIint nWidth, nHeight;

	DstroyGame(void);
	~DstroyGame(void);
	//paramètres du jeu, en static car créé par un autre TGIMain (oui c'est nul)
	static DstroyGameParams params;

	//objets qui peuvent etre ajoutés en cours de jeu
	DstroyBomb dsBombStandard;
	DstroyExplosion dsExplosionStandard;
	DstroySoftWall dsSoftWallStandard;
	DstroyBonus dsBonusStandard;
	DstroyMonster dsMonsterStandard1, dsMonsterStandard2;
	DstroyNest dsNestCreatorStandard, dsNestOutStandard;
	DstroyPlayer* pdsPlayer[4];
	DstroyTeleporting dsTeleportingStandard;

	//pour l'IA, a faire
	std::list<DstroyMonster*> vecMonster;
	TGIuint16 nCurrentMonsterToThink;
	std::list<DstroyBomb*> vecBomb;

	std::list<DstroyNest*> vecNest;

	//sons
	TGISound soundBomb, soundFlame, soundXtraLife;
	TGISound soundBoom;

	TGISound soundChange, soundControl, soundCross, soundCrossFire, soundDropBomb, soundFastBomb;
	TGISound soundFreeze, soundMonsterFreeze, soundMonsterSpeed, soundRemote, soundReverse, soundShadow;
	TGISound soundShield, soundSlow, soundSlowBomb, soundExplosion;
	TGISound soundNextLevel;
	TGISound soundMonster, soundSwap, soundTransfert, soundReversePlayer;

	TGISound* typeSound[3];
	TGISound* subTypeSound[21];

	//init: remplit les objets, et le terrain etc...
	bool init();
	//exit: crée un menu
	bool exit(void);
	//charge une carte
	bool loadMap(std::string strMap);
	//crée les joueurs et les screen en fonction
	void createPlayers(void);
	//event surchargé pr stopper si un joueur a gagné
	bool events(void);

	//récupere la liste des objects a une position donnée
	bool getObjectsOnPos(DstroyItem* pObjectSource, TGIint x, TGIint y, std::list<DstroyItem*>& vecObject);
	
	bool addObject(TGIObject* pObject, TGIint nDepth);
	bool deleteObject(TGIObject* pObject, bool bDelete=false);
	
	
	//bonus
	void bonusExplosion(void);
	void bonusChange(DstroyPlayer* pSrc);
	void bonusCrossFire(void);
	void bonusMonsterFreeze(void);
	void bonusMonsterSpeed(void);
	void bonusNextLevel(void);
	void bonusSwap(DstroyPlayer* pSrc);
	void bonusReversePlayer(DstroyPlayer* pSrc);
public:
	
	void drawLives(void);
public:
	void stop(void);
public:
	void finishGame(void);
public:
	void addLifeToPlayer(DstroyPlayer* pPlayer);
	void swapPlayers(TGIint p1, TGIint p2);
public:
	void makeLower(char* pTexte);

	DstroyBomb* createBomb();
	DstroyExplosion* createExplosion();
};
