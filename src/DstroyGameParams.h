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

#define GAMEMODE_ADVENTURE 1
#define GAMEMODE_FIGHT 2
#define GAMEMODE_KILLER 3

#define BONUS_LIFE 0
#define BONUS_BOMB 16
#define BONUS_FLAME 32
#define BONUS_SPECIAL 48

#define BONUSS_CHANGE 0
#define BONUSS_CONTROL 1
#define BONUSS_CROSS 2
#define BONUSS_CROSSFIRE 3
#define BONUSS_DROPBOMB 4
#define BONUSS_FASTBOMB 5
#define BONUSS_FREEZE 6
#define BONUSS_MONSTERFREEZE 7
#define BONUSS_MONSTERSPEED 8
#define BONUSS_REMOTE 9
#define BONUSS_REVERSE 10
#define BONUSS_SHADOW 11
#define BONUSS_SHIELD 12
#define BONUSS_SLOW 13 
#define BONUSS_SLOWBOMB 14
#define BONUSS_EXPLOSION 15
#define BONUSS_LOOSER 21

#define BONUSS_NEXTLEVEL 16

#define BONUSS_MONSTER 17
#define BONUSS_SWAP 18
#define BONUSS_TRANSFERT 19
#define BONUSS_REVERSEPLAYER 20

class DstroyGameParams
{
public:
	DstroyGameParams(void);
	~DstroyGameParams(void);

	TGIuint8 nPlayers;
	TGIuint8 nMode;
	TGIuint16 nLevel;
	TGIuint8 nDifficulty;

	TGIuint8 pnWins[4];
	TGIuint8 pnLives[4];
	TGIuint8 pnBombs[4];
	TGIuint8 pnFlame[4];
	TGIuint8 pnBombDuration[4];
	TGIuint8 pnSwap[4];

	TGIuint8 nWins;

	std::string cstrFile;

	TGIuint8 probaHasBonus;
	TGIuint8 probaLife;
	TGIuint8 probaBomb;
	TGIuint8 probaFlame;
	TGIuint8 probaBonus;

	//commun
	TGIuint8 probaTransfert; //le joueur est téléporté aléatoirement
	TGIuint8 probaControl; //?
	TGIuint8 probaCross; //traverse les bombes
	TGIuint8 probaCrossFire; //des bombes sont placées aléatoirement sur le terrain (10)
	TGIuint8 probaDropBomb; //chiasse
	TGIuint8 probaFastBomb; //les bombes posées petent plus vite
	TGIuint8 probaFreeze; //freezé
	TGIuint8 probaMonsterFreeze; //montres freezés
	TGIuint8 probaMonsterSpeed; //monstres accélérés x2
	TGIuint8 probaRemote; //bombe jaune
	TGIuint8 probaReverse; //commandes inversées
	TGIuint8 probaShadow; //invisible
	TGIuint8 probaShield; //invulnérable
	TGIuint8 probaSlow; //lent
	TGIuint8 probaSlowBomb; //les bombes posées petent moins vite
	TGIuint8 probaExplosion; //toutes les bombes sur le terrain explosent
	TGIuint8 probaLooser; //banqueroute : les options du joueur sont dimininuées de moitié

	//mode aventure
	TGIuint8 probaNextLevel; //Passe au niveau suivant

	//mode fight
	TGIuint8 probaMonster; //tranforme en monstre
	TGIuint8 probaSwap; //les joueurs échangent leur bonhomme
	TGIuint8 probaChange; //les joueurs échangent leur position
	TGIuint8 probaReversePlayer; //commandes inversées pr les autres

	TGIint type[256];
	TGIint subType[256];
	TGIuint8 nSubTypeSize;


public:
	void initBonuses(void);
public:
	void setLevel(TGIuint16 nLevel);
public:
	bool save(TGIuint8 nIndex);
public:
	static bool load(TGIuint8 nIndex, DstroyGameParams& params);
public:
	void setMode(int mode);
};
