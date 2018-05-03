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
#include "DstroyGameParams.h"

#include "TGIGlobals.h"
#include "TGIFile.h"

#include "DstroyGlobals.h"

#define CURRENT_VERSION 1

DstroyGameParams::DstroyGameParams(void)
{
	TGIuint8 i;

	probaHasBonus = 90;

/*	probaLife = 1;
	probaBomb = 80;
	probaFlame = 80;
	probaBonus = 95;*/

	


	setMode(GAMEMODE_FIGHT);
	nPlayers = 4;
	for (i=0;i<4;i++)
	{
		pnWins[i] = 0;
		pnBombs[i] = 1;
		pnFlame[i] = 1;
		pnBombDuration[i] = 4;
		pnSwap[i] = i;
	}
	nWins = 3;

	nDifficulty = 0;
	nLevel = 0;

	







	/*probaChange = 0; //?
	probaControl = 0; //?
	probaCross = 0; //?
	probaCrossFire = 15; //des bombes sont placées aléatoirement sur le terrain
	probaDropBomb = 15; //chiasse
	probaFastBomb = 15; //les bombes posées petent plus vite
	probaFreeze = 15; //freezé
	probaMonsterFreeze = 15; //montres freezés
	probaMonsterSpeed = 15; //monstres accélérés
	probaRemote = 5; //bombe jaune
	probaReverse = 15; //commandes inversées
	probaShadow = 15; //invisible
	probaShield = 15; //invulnérable
	probaSlow = 15; //lent
	probaSlowBomb = 15; //les bombes posées petent moins vite
	probaExplosion = 15; //toutes les bombes sur le terrain explosent
	probaLooser = 15;
		
	//mode aventure
	probaNextLevel = 0; //Passe au niveau suivant

	//mode fight
	probaMonster = 5; //tranforme en monstre
	probaSwap = 10; //les joueurs échangent leur bonhomme
	probaTransfert = 15; //les joueurs échangent leur position
	probaReversePlayer = 15; //commandes inversées pr les autres*/


}

DstroyGameParams::~DstroyGameParams(void)
{
}

void DstroyGameParams::initBonuses(void)
{
	TGIint j=0,i;
	double lim;

	double maxProba;
	maxProba = probaTransfert + probaControl + probaCross + probaCrossFire + probaDropBomb + probaFastBomb + 
		probaFreeze + probaMonsterFreeze + probaMonsterSpeed + probaRemote + probaReverse + probaShadow + 
		probaShield + probaSlow + probaSlowBomb + probaExplosion + probaLooser + probaNextLevel + 
		probaMonster + probaSwap + probaChange + probaReversePlayer;
	maxProba = 256.0 / maxProba;

	for (i=0;i<256;i++)
	{
		type[i]= -1;
		subType[i]= -1;
	}

	
	for (i=0;i<probaLife;i++)
		type[j++] = BONUS_LIFE;
	for (i=0;i<probaBomb;i++)
		type[j++] = BONUS_BOMB;
	for (i=0;i<probaFlame;i++)
		type[j++] = BONUS_FLAME;
	for (;j<256;j++)
		type[j] = BONUS_SPECIAL;

	j=0;
	lim = (double)probaChange*maxProba;
	while (j<lim)
		subType[j++] = BONUSS_CHANGE;
	lim += (double)probaControl*maxProba;
	while (j<lim)
		subType[j++] = BONUSS_CONTROL;
	lim += (double)probaCross*maxProba;while(j<lim)
		subType[j++] = BONUSS_CROSS;
	lim += (double)probaCrossFire*maxProba;while(j<lim)
		subType[j++] = BONUSS_CROSSFIRE;
	lim += (double)probaDropBomb*maxProba;while(j<lim)
		subType[j++] = BONUSS_DROPBOMB;
	lim += (double)probaFastBomb*maxProba;while(j<lim)
		subType[j++] = BONUSS_FASTBOMB;
	lim += (double)probaFreeze*maxProba;while(j<lim)
		subType[j++] = BONUSS_FREEZE;
	lim += (double)probaMonsterFreeze*maxProba;while(j<lim)
		subType[j++] = BONUSS_MONSTERFREEZE;
	lim += (double)probaMonsterSpeed*maxProba;while(j<lim)
		subType[j++] = BONUSS_MONSTERSPEED;
	lim += (double)probaRemote*maxProba;while(j<lim)
		subType[j++] = BONUSS_REMOTE;
	lim += (double)(probaReverse)*maxProba;while(j<lim)
		subType[j++] = BONUSS_REVERSE;
	lim += (double)(probaShadow)*maxProba;while(j<lim)
		subType[j++] = BONUSS_SHADOW;
	lim += (double)(probaShield)*maxProba;while(j<lim)
		subType[j++] = BONUSS_SHIELD;
	lim += (double)(probaSlow)*maxProba;while(j<lim)
		subType[j++] = BONUSS_SLOW;
	lim += (double)(probaSlowBomb)*maxProba;while(j<lim)
		subType[j++] = BONUSS_SLOWBOMB;
	lim += (double)(probaExplosion)*maxProba;while(j<lim)
		subType[j++] = BONUSS_EXPLOSION;
	lim += (double)(probaNextLevel)*maxProba;while(j<lim)
		subType[j++] = BONUSS_NEXTLEVEL;
	lim += (double)(probaMonster)*maxProba;while(j<lim)
		subType[j++] = BONUSS_MONSTER;
	lim += (double)(probaSwap)*maxProba;while(j<lim)
		subType[j++] = BONUSS_SWAP;
	lim += (double)(probaTransfert)*maxProba;while(j<lim)
		subType[j++] = BONUSS_TRANSFERT;
	lim += (double)(probaReversePlayer)*maxProba;while(j<lim)
		subType[j++] = BONUSS_REVERSEPLAYER;

	nSubTypeSize = j;

	char strText[256];
	sprintf(strText, "\nBonus alloues : %d\n", nSubTypeSize);
	TGIGlobals::Trace(strText);

}

void DstroyGameParams::setLevel(TGIuint16 nLevel)
{
	this->nLevel = nLevel;
	char strFile[256];
	sprintf(strFile, DstroyGlobals::addResText("level%03d.dstroy"), nLevel);
	cstrFile = strFile;
}

bool DstroyGameParams::save(TGIuint8 nIndex)
{
	TGIFile tgiFile;
	TGIuint16 version = CURRENT_VERSION;
	TGIuint16 order = 255;
	if (!tgiFile.open(DstroyGlobals::addConfigText("saves"), true))
		return false;

	char reserved=0;
	TGIuint16 i;

	//verifions que le fichier n'est pas vide
	tgiFile.seekFromEnd(0);
	if (tgiFile.getPos() == 0)
	{
		for (i=0;i<32*8;i++)
		{
			tgiFile.write((char*)&reserved, 1);
		}
	}
	
	tgiFile.seekFromBegin(32*nIndex);

	tgiFile.write((char*)&order, 2);
	tgiFile.write((char*)&version, 2);
	tgiFile.write((char*)&nLevel, 2);
	tgiFile.write((char*)&nDifficulty, 1);
	tgiFile.write((char*)&nPlayers, 1);
	for (i=0;i<4;i++)
	{
		tgiFile.write((char*)&pnLives[i], 1);
		tgiFile.write((char*)&pnBombs[i], 1);
		tgiFile.write((char*)&pnBombDuration[i], 1);
		tgiFile.write((char*)&pnFlame[i], 1);
	}
	for (i=0;i<8;i++)
	{
		tgiFile.write((char*)&reserved, 1);
	}

	tgiFile.close();

	return true;
}

bool DstroyGameParams::load(TGIuint8 nIndex, DstroyGameParams& params)
{
	TGIuint8 i;
	char reserved;
	TGIFile tgiFile;
	TGIuint16 nVersion = CURRENT_VERSION;
	
	tgiFile.openRead(DstroyGlobals::addConfigText("saves"), true);
	if (!tgiFile.isOpen())
		return false;
	
	tgiFile.seekFromBegin(32*nIndex);

	TGIuint16 order;
	TGIuint16 version;

	tgiFile.read((char*)&order, 2);
	tgiFile.read((char*)&version, 2);
	TGIGlobals::endianConvert(order, &version, 2);
	tgiFile.read((char*)&params.nLevel, 2);
	TGIGlobals::endianConvert(order, &params.nLevel, 2);
	//params.nLevel = 48;
	params.setLevel(params.nLevel);
	tgiFile.read((char*)&params.nDifficulty, 1);
	TGIGlobals::endianConvert(order, &params.nDifficulty, 1);
	tgiFile.read((char*)&params.nPlayers, 1);
	TGIGlobals::endianConvert(order, &params.nPlayers, 1);
	for (i=0;i<4;i++)
	{
		tgiFile.read((char*)&params.pnLives[i], 1);
		TGIGlobals::endianConvert(order, &params.pnLives[i], 1);
		tgiFile.read((char*)&params.pnBombs[i], 1);
		TGIGlobals::endianConvert(order, &params.pnBombs[i], 1);
		tgiFile.read((char*)&params.pnBombDuration[i], 1);
		TGIGlobals::endianConvert(order, &params.pnBombDuration[i], 1);
		tgiFile.read((char*)&params.pnFlame[i], 1);
		TGIGlobals::endianConvert(order, &params.pnFlame[i], 1);
	}
	for (i=0;i<8;i++)
	{
		tgiFile.read((char*)&reserved, 1);
	}
	tgiFile.close();

	params.setMode(GAMEMODE_ADVENTURE);

	if (params.nLevel == 0)
		return false;

	return true;
}

void DstroyGameParams::setMode(int mode)
{
	nMode = mode;
	if (mode == GAMEMODE_ADVENTURE)
	{
		switch(nDifficulty)
		{
		case 1:
		{
			probaLife = 10;
			probaBomb = 80;
			probaFlame = 80;
			probaBonus = 95;

			probaTransfert = 10; //téléporté n'importe ou OK
			probaControl = 0; //?
			probaCross = 10; //traverse les bombes OK
			probaCrossFire = 15; //des bombes sont placées aléatoirement sur le terrain OK
			probaDropBomb = 15; //chiasse OK
			probaFastBomb = 20; //les bombes posées petent plus vite OK
			probaFreeze = 10; //freezé OK
			probaMonsterFreeze = 25; //montres freezés OK
			probaMonsterSpeed = 15; //monstres accélérés
			probaRemote = 10; //bombe jaune OK
			probaReverse = 15; //commandes inversées OK
			probaShadow = 15; //invisible OK
			probaShield = 20; //invulnérable : la fin a faire
			probaSlow = 15; //lent OK
			probaSlowBomb = 20; //les bombes posées petent moins vite OK
			probaExplosion = 15; //toutes les bombes sur le terrain explosent OK
			probaLooser = 15; //banqueroute OK

			//mode aventure
			probaNextLevel = 3; //Passe au niveau suivant
			break;
		}
		case 2:
		{
			probaLife = 6;
			probaBomb = 80;
			probaFlame = 80;
			probaBonus = 95;

			probaTransfert = 15; //téléporté n'importe ou OK
			probaControl = 0; //?
			probaCross = 5; //traverse les bombes OK
			probaCrossFire = 10; //des bombes sont placées aléatoirement sur le terrain OK
			probaDropBomb = 20; //chiasse OK
			probaFastBomb = 20; //les bombes posées petent plus vite OK
			probaFreeze = 15; //freezé OK
			probaMonsterFreeze = 20; //montres freezés OK
			probaMonsterSpeed = 20; //monstres accélérés
			probaRemote = 5; //bombe jaune OK
			probaReverse = 20; //commandes inversées OK
			probaShadow = 15; //invisible OK
			probaShield = 15; //invulnérable : la fin a faire
			probaSlow = 20; //lent OK
			probaSlowBomb = 20; //les bombes posées petent moins vite OK
			probaExplosion = 15; //toutes les bombes sur le terrain explosent OK
			probaLooser = 20; //banqueroute OK

			//mode aventure
			probaNextLevel = 1; //Passe au niveau suivant
			break;
		}
		case 3:
		{
			probaLife = 2;
			probaBomb = 80;
			probaFlame = 80;
			probaBonus = 95;

			probaTransfert = 15; //téléporté n'importe ou OK
			probaControl = 0; //?
			probaCross = 5; //traverse les bombes OK
			probaCrossFire = 10; //des bombes sont placées aléatoirement sur le terrain OK
			probaDropBomb = 25; //chiasse OK
			probaFastBomb = 25; //les bombes posées petent plus vite OK
			probaFreeze = 20; //freezé OK
			probaMonsterFreeze = 10; //montres freezés OK
			probaMonsterSpeed = 20; //monstres accélérés
			probaRemote = 5; //bombe jaune OK
			probaReverse = 20; //commandes inversées OK
			probaShadow = 15; //invisible OK
			probaShield = 10; //invulnérable : la fin a faire
			probaSlow = 20; //lent OK
			probaSlowBomb = 20; //les bombes posées petent moins vite OK
			probaExplosion = 15; //toutes les bombes sur le terrain explosent OK
			probaLooser = 20; //banqueroute OK

			//mode aventure
			probaNextLevel = 1; //Passe au niveau suivant
			break;
		}
		case 4:
		{
			probaLife = 0;
			probaBomb = 60;
			probaFlame = 60;
			probaBonus = 136;

			probaTransfert = 15; //téléporté n'importe ou OK
			probaControl = 0; //?
			probaCross = 0; //traverse les bombes OK
			probaCrossFire = 10; //des bombes sont placées aléatoirement sur le terrain OK
			probaDropBomb = 30; //chiasse OK
			probaFastBomb = 30; //les bombes posées petent plus vite OK
			probaFreeze = 25; //freezé OK
			probaMonsterFreeze = 5; //montres freezés OK
			probaMonsterSpeed = 20; //monstres accélérés
			probaRemote = 0; //bombe jaune OK
			probaReverse = 30; //commandes inversées OK
			probaShadow = 20; //invisible OK
			probaShield = 5; //invulnérable : la fin a faire
			probaSlow = 30; //lent OK
			probaSlowBomb = 20; //les bombes posées petent moins vite OK
			probaExplosion = 15; //toutes les bombes sur le terrain explosent OK
			probaLooser = 25; //banqueroute OK

			//mode aventure
			probaNextLevel = 0; //Passe au niveau suivant
			break;
		}
		}
		
		//mode fight
		probaMonster = 0; //tranforme en monstre OK
		probaSwap = 0; //les joueurs échangent leur bonhomme OK (tester le score)
		probaChange = 0; //les joueurs échangent leur position OK
		probaReversePlayer = 0; //commandes inversées pr les autres OK
	}
	else
	{
		if (nMode == GAMEMODE_KILLER)
		{
			nDifficulty = 0;
		}

		probaLife = 0;
		probaBomb = 80;
		probaFlame = 80;
		probaBonus = 96;

		probaTransfert = 10; //téléporté n'importe ou OK
		probaControl = 0; //?
		probaCross = 4; //traverse les bombes OK
		probaCrossFire = 10; //des bombes sont placées aléatoirement sur le terrain OK
		probaDropBomb = 15; //chiasse OK
		probaFastBomb = 15; //les bombes posées petent plus vite OK
		probaFreeze = 15; //freezé OK
		probaMonsterFreeze = 15; //montres freezés OK
		probaMonsterSpeed = 15; //monstres accélérés
		probaRemote = 4; //bombe jaune OK
		probaReverse = 15; //commandes inversées OK
		probaShadow = 15; //invisible OK
		probaShield = 15; //invulnérable : la fin a faire
		probaSlow = 15; //lent OK
		probaSlowBomb = 15; //les bombes posées petent moins vite OK
		probaExplosion = 9; //toutes les bombes sur le terrain explosent OK
		probaLooser = 15; //banqueroute OK

		probaNextLevel = 0; //Passe au niveau suivant

		//mode fight
		probaMonster = 3; //tranforme en monstre OK
		probaSwap = 4; //les joueurs échangent leur bonhomme OK (tester le score)
		probaChange = 5; //les joueurs échangent leur position OK
		probaReversePlayer = 15; //commandes inversées pr les autres OK
	}

	initBonuses();
}
