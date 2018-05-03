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
#include "DstroyPlayer.h"

#include "DstroyGame.h"


//private data for the player
#define ANIM_SIZE 9
#define ANIM_LEFT 18
#define ANIM_RIGHT 27
#define ANIM_UP 9
#define ANIM_DOWN 0
#define ANIM_DIE 36
#define ANIM_WIN 45
 
#define ANIM_SPEED 50

#define MOVING_MARGIN 4


DstroyPlayer::DstroyPlayer(void)
{
	classId = CLASSID_PLAYER;

	bAlive = false;
	bWinner = false;


	bCross = false;
	bRemote = false;
	pRemoteBomb = NULL;
	bMonster = false;
	reinitBonus();

	bDropBomb = false;

	lSpeed = 2;
	nBombs = 1;
	nBombsLeft = 1;
	nFlames = 1;
	nBombDurationLeft = 4;

	startX = startY = 0;

	nAnimSpeed = 15;
}

DstroyPlayer::~DstroyPlayer(void)
{
}

bool DstroyPlayer::changeSprite()
{
	//quePasa();
	

	if (!bAlive && bVisible)
	{
		//dying
		setCurrentSprite(getCurrentSprite()+1);

		if (getCurrentSprite() >= 43)
		{
			nAnimSpeed = 500;
		}
		if (getCurrentSprite() >= 44)
		{
			bVisible = false;
			nAnimSpeed = 50;
		}

		return true;
	}

	/*if (bShadow)
		bVisible = false;
	else if (bShield)
		bVisible = !bVisible;
	else
		bVisible = bAlive;*/
	
	

	/*if (dirMoving == stand)
		return;*/

	int nStart, nNew;

	switch (dirMoving)
	{
	case left:
		nStart = ANIM_LEFT;
		break;
	case right:
		nStart = ANIM_RIGHT;
		break;
	case up:
		nStart = ANIM_UP;
		break;
	case down:
		nStart = ANIM_DOWN;
		break;
	default:
		if (bWinner)
		{
			nStart = ANIM_WIN;
		}
		else
		{
			setCurrentSprite(getCurrentSprite() - getCurrentSprite()%ANIM_SIZE);
			return true;
		}
	}	
	nNew = (getCurrentSprite() + 1)%ANIM_SIZE + nStart;

	setCurrentSprite(nNew);

	dirMoving = stand;

	return true;
}


void DstroyPlayer::move(Direction dir)
{
	if (bReverse)
	{
		switch (dir)
		{
		case up:
			dirMoving = down;
			break;
		case down:
			dirMoving = up;
			break;
		case left:
			dirMoving = right;
			break;
		case right:
			dirMoving = left;
			break;
		default:
			break;
		}
	}
	else
	{
		dirMoving = dir;
	}
	bMoving = true;
}

void DstroyPlayer::treatMessage(TGIInputMessage* pMessage)
{
	if (bFreeze || bWinner || !bAlive)
		return;

	switch(pMessage->lId)
	{
	case left:
	case right:
	case up:
	case down:
		move((Direction)pMessage->lId);
		break;
	case 10:
		bDropBomb = true;
		break;
	case 20:
		((DstroyGame*)TGIGlobals::theMain)->bonusNextLevel();
		break;
	default:
		return;
	}
}

void DstroyPlayer::quePasa()
{
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;
	std::list<DstroyItem*> listObject;
	register std::list<DstroyItem*>::iterator itObject;
	//DstroyItem* pObject = NULL;

	if (!bAlive || bWinner)
		return;

	if (bShield)
	{
		if (tgEndShield < TGITime::getCurrentTime())
		{
			bShield = false;
			bVisible = true;
		}	
		else if (tgAlmostEndShield < TGITime::getCurrentTime())
		{
			//double clignotement
			nShieldEtat = (nShieldEtat + 1) % 12;
			bVisible = (nShieldEtat/6 == 0);
		}
		else
		{
			//simple clignotement
			bVisible = !bVisible;
		}
		
	}
	if (bShadow)
	{
		if (tgEndShadow < TGITime::getCurrentTime())
		{
			bShadow = false;
			bVisible = true;
		}
		else
		{
			bVisible = false;	
		}
	}
	bReverse = bReverse && tgEndReverse > TGITime::getCurrentTime();
	if (bSlow && tgEndSlow < TGITime::getCurrentTime())
	{
		setX(X()-(X()&1));
		setY(Y()-(Y()&1));
		bSlow = false;
	}
	bSpeed = bSpeed && tgEndSpeed > TGITime::getCurrentTime();
	bFreeze = bFreeze && tgEndFreeze > TGITime::getCurrentTime();
	bDropBombs = bDropBombs && tgEndDropBombs > TGITime::getCurrentTime();
	bCannotDropBomb = bCannotDropBomb && tgEndCannotDropBomb > TGITime::getCurrentTime();

	//the "bomb" has been pressed
	if ((bDropBomb && !pRemoteBomb && !bCannotDropBomb) || bDropBombs)
	{
		bDropBomb = false;
		if (nBombsLeft != 0)
		{
			dropBomb();
		}
	}
	if (bDropBomb && pRemoteBomb && !bDropBombs)
	{
		bDropBomb = false;
		pRemoteBomb->makeExplode();
		pRemoteBomb = NULL;
	}

	//tests
	pGame->getObjectsOnPos(this, gridX(), gridY(), listObject);
	for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
	{
		//bonus
		if ((*itObject)->classId == CLASSID_BONUS && !bMonster)
		{
			getBonus((*itObject));
		}

		//test de mort
		if (!bShield && ((*itObject)->classId == CLASSID_EXPLOSION || ((*itObject)->classId == CLASSID_MONSTER && !bMonster)))
		{
			dirMoving = stand;
			bAlive = false;
			bVisible = true;
			setCurrentSprite(ANIM_DIE);
			reinitBonus();

			//looser
			TGIint nBombsDiff = nBombs - nBombsLeft;
			nBombs /= 2;
			if (nBombs == 0) nBombs = 1;
			nBombsLeft = nBombs - nBombsDiff;
			if (nBombsLeft < 0)
				nBombsLeft = 0;
			
			nFlames /= 2;
			if (nFlames == 0) nFlames = 1;

			bRemote = false;


			return;
		}
	}

	//moving
	if (bMoving)
	{
		bMoving = false;

		TGIint offsetX=0, offsetY=0;
		bool bCanMove = false;

		switch (dirMoving)
		{
		case left:
			offsetX = -1;
			if (X() > gridX()*width) bCanMove = true; //test if he's not completely on the case
			break;
		case right:
			offsetX = 1;
			if (X() < gridX()*width) bCanMove = true;
			break;
		case up:
			offsetY = -1;
			if (Y() > gridY()*height) bCanMove = true;
			break;
		case down:
			offsetY = 1;
			if (Y() < gridY()*height) bCanMove = true;
			break;
		default:
			//bouh!
			break;
		}	

		//if he's really moving
		if (offsetX != 0 || offsetY != 0)
		{

			if (!bCanMove)
			{
				//on regarde si on peut aller dans cette direction
				bCanMove = canMove(gridX()+offsetX, gridY()+offsetY);

				//si on peut on se cale pr rentrer comme il faut dans la case
				if (bCanMove)
				{
					if (offsetX != 0)
					{
						if (Y() < gridY()*height)
						{
							offsetX = 0;				
							offsetY = 1;
						}
						if (Y() > gridY()*height)
						{
							offsetX = 0;				
							offsetY = -1;
						}
					}
					else //offsetY != 0 (was)
					{
						if (X() < gridX()*width)
						{
							offsetY = 0;
							offsetX = 1;
						}
						if (X() > gridX()*width)
						{
							offsetY = 0;
							offsetX = -1;
						}
					}
				}
				//si on peut pas, on essaie de contourner
				if (!bCanMove)
				{
					if (offsetX != 0)
					{
						if (Y() < gridY()*height)
						{
							//on regarde si la case ou on veut aller est possible
							bCanMove = canMove(gridX()+offsetX, gridY()-1);
							if (bCanMove)
								offsetY = -1;
							else
								offsetY = 0;
							offsetX = 0;	
						}
						if (Y() > gridY()*height)
						{		
							//on regarde si la case ou on veut aller est possible
							bCanMove = canMove(gridX()+offsetX, gridY()+1);
							if (bCanMove)
								offsetY = 1;
							else
								offsetY = 0;
							offsetX = 0;
						}
					}
					else //offsetY != 0 (was)
					{
						if (X() < gridX()*width)
						{			
							//on regarde si la case ou on veut aller est possible
							bCanMove = canMove(gridX()-1, gridY()+offsetY);
							if (bCanMove)
								offsetX = -1;
							else
								offsetX = 0;
							offsetY = 0;
						}
						if (X() > gridX()*width)
						{		
							//on regarde si la case ou on veut aller est possible
							bCanMove = canMove(gridX()+1, gridY()+offsetY);
							if (bCanMove)
								offsetX = +1;
							else
								offsetX = 0;
							offsetY = 0;	
						}
					}
				}
			}
			

			if (bCanMove)
			{
				if (bSlow)
				{
					setX(X() + lSpeed*offsetX/2);
					setY(Y() + lSpeed*offsetY/2);
				}
				else
				{
					setX(X() + lSpeed*offsetX);
					setY(Y() + lSpeed*offsetY);
				}

				//on refait le test de mort car on a bougé
				pGame->getObjectsOnPos(this, gridX(), gridY(), listObject);
				for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
				{
					//test de mort
					if (!bShield && ((*itObject)->classId == CLASSID_EXPLOSION || ((*itObject)->classId == CLASSID_MONSTER && !bMonster)))
					{
						dirMoving = stand;
						bAlive = false;
						bVisible = true;
						setCurrentSprite(ANIM_DIE);
						reinitBonus();

						//looser
						TGIint nBombsDiff = nBombs - nBombsLeft;
						nBombs /= 2;
						if (nBombs == 0) nBombs = 1;
						nBombsLeft = nBombs - nBombsDiff;
						if (nBombsLeft < 0)
							nBombsLeft = 0;
						
						nFlames /= 2;
						if (nFlames == 0) nFlames = 1;

						bRemote = false;


						return;
					}
				}
			}		
			else
			{
				dirMoving = stand;
			}
		}
		
	}

	
	

	//dirMoving = stand;
}
void DstroyPlayer::dropBomb(void)
{
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;
	std::list<DstroyItem*> listObject;
	register std::list<DstroyItem*>::iterator itObject;

	pGame->getObjectsOnPos(this, gridX(), gridY(), listObject);
	for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
	{
		//you cant drop a bomb if there's already one here
		if ((*itObject)->classId == CLASSID_BOMB)
			return;
	}

	DstroyBomb* pNewBomb;
	pNewBomb = pGame->createBomb();//= new DstroyBomb(pGame->dsBombStandard);
	pNewBomb->bVisible = true;
	if (bDropBombs || !bRemote)
		pNewBomb->initBomb(this, gridX(), gridY(), nFlames, nBombDurationLeft);
	else
	{
		pNewBomb->initBomb(this, gridX(), gridY(), nFlames, 0);
		pRemoteBomb = pNewBomb;
	}

	//pGame->vecObject.push_back(pNewBomb);
	pGame->addObject(pNewBomb, 7);
	pNewBomb = NULL;

	nBombsLeft--;
}

bool DstroyPlayer::canMove(TGIint x, TGIint y)
{
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;
	std::list<DstroyItem*> listObject;
	register std::list<DstroyItem*>::iterator itObject;

	pGame->getObjectsOnPos(this, x, y, listObject);
	if (bCross)
	{
		for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
		{
			if ((*itObject)->isPlain() && (*itObject)->classId != CLASSID_BOMB)
			{
				return false;
			}
		}
	}
	else
	{
		for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
		{
			if ((*itObject)->isPlain())
			{
				return false;
			}
		}
	}

	//nothing stops him
	return true;
}

void DstroyPlayer::getBonus(DstroyItem* pBonus)
{
	DstroyBonus* pB = (DstroyBonus*)pBonus;
	if (pB->bDestroyed)
		return;
	pB->take();

	if (pB->nType == BONUS_LIFE)
	{
		DstroyGame* pGame = ((DstroyGame*)TGIGlobals::theMain);
		pGame->addLifeToPlayer(this);
	}

	if (pB->nType == BONUS_FLAME)
	{
		if (nFlames < 8)
			nFlames++;
		return;
	}
	if (pB->nType == BONUS_BOMB)
	{
		if (nBombs < 15)
		{
			nBombs++;
			nBombsLeft++;
		}
		return;
	}
	if (pB->nType == BONUS_SPECIAL)
	{
		DstroyGame* pGame = ((DstroyGame*)TGIGlobals::theMain);

		switch (pB->nSubType)
		{
		case BONUSS_CHANGE:
			pGame->bonusChange(this);
			break;
		case BONUSS_CONTROL:
			break;
		case BONUSS_CROSS:
			bCross = true;
			break;
		case BONUSS_CROSSFIRE:
			pGame->bonusCrossFire();
			break;
		case BONUSS_DROPBOMB:
			tgEndDropBombs = TGITime::getCurrentTime();
			tgEndDropBombs += 10000;
			bDropBombs = true;
			break;
		case BONUSS_FASTBOMB:
			if (nBombDurationLeft != 2)
				nBombDurationLeft--;
			break;
		case BONUSS_FREEZE:
			tgEndFreeze = TGITime::getCurrentTime();
			tgEndFreeze += 6000;
			bFreeze = true;
			break;
		case BONUSS_MONSTERFREEZE:
			pGame->bonusMonsterFreeze();
			break;
		case BONUSS_MONSTERSPEED:
			pGame->bonusMonsterSpeed();
			break;
		case BONUSS_REMOTE:
			bRemote = true;
			break;
		case BONUSS_REVERSE:
			tgEndReverse = TGITime::getCurrentTime();
			tgEndReverse += 6000;
			bReverse = true;
			break;
		case BONUSS_SHADOW:
			tgEndShadow = TGITime::getCurrentTime();
			tgEndShadow += 10000;
			bShadow = true;
			break;
		case BONUSS_SHIELD:
			/*tgEndShield = TGITime::getCurrentTime();
			tgEndShield += 15000;
			bShield = true;*/
			setShield(15000);
			break;
		case BONUSS_SLOW :
			tgEndSlow = TGITime::getCurrentTime();
			tgEndSlow += 10000;
			bSlow = true;
			break;
		case BONUSS_SLOWBOMB:
			if (nBombDurationLeft != 5)
				nBombDurationLeft++;
			break;
		case BONUSS_EXPLOSION:
			pGame->bonusExplosion();
			break;
		case BONUSS_LOOSER:
			{
				TGIint nBombsDiff = nBombs - nBombsLeft;
				nBombs /= 2;
				if (nBombs == 0) nBombs = 1;
				nBombsLeft = nBombs - nBombsDiff;
				if (nBombsLeft < 0)
					nBombsLeft = 0;
				
				nFlames /= 2;
				if (nFlames == 0) nFlames = 1;
			}
			break;
		case BONUSS_NEXTLEVEL:
			pGame->bonusNextLevel();
			break;
		case BONUSS_MONSTER:
			{
				classId = CLASSID_MONSTER;
				bMonster = true;
				vecSprite.clear();

				DstroyMonster* pMonster;
				if (rand()%2)
				{
					pMonster = &((DstroyGame*)TGIGlobals::theMain)->dsMonsterStandard1;
				}
				else
				{
					pMonster = &((DstroyGame*)TGIGlobals::theMain)->dsMonsterStandard2;
				}

				for (TGIuint16 i=0;i<pMonster->getSpriteCount();i++)
				{
					this->addSprite(*(pMonster->getSprite(i)));
				}
				this->lSpeed = 1;
			}
			break;
		case BONUSS_SWAP:
			pGame->bonusSwap(this);
			break;
		case BONUSS_TRANSFERT:
			{
				
				std::list<DstroyItem*> listObject;
				register std::list<DstroyItem*>::iterator itObject;

				//on cherche une nouvelle place
				TGIint newX, newY;
				bool bOK = false;
				newX = rand()%pGame->nWidth;
				newY = rand()%pGame->nHeight;
				while (!bOK)
				{
					newX++;
					if (newX >= pGame->nWidth)
					{
						newX = 1;
						newY = (newY+1)%pGame->nHeight;
					}
					bOK = true;

					pGame->getObjectsOnPos(this, newX, newY, listObject);
					for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
					{
						if ((*itObject)->isPlain())
						{
							bOK = false;
							break;
						}
					}
				}

				//on téléporte
				teleport(newX, newY);			
			}
			break;
		case BONUSS_REVERSEPLAYER:
			pGame->bonusReversePlayer(this);
			break;
		}	
	}
	
}

void DstroyPlayer::reinitBonus(void)
{
	bShadow = false;
	bShield = false;
	
	bSpeed = false;
	bReverse = false;
	
	bFreeze = false;
	bDropBombs = false;
	bCannotDropBomb = true;
	tgEndCannotDropBomb = TGITime::getCurrentTime();
	tgEndCannotDropBomb += 1500;
	
	
	bSlow = false;
}

void DstroyPlayer::teleport(TGIint x, TGIint y)
{
	DstroyGame* pGame = ((DstroyGame*)TGIGlobals::theMain);

	bVisible = false;
				
	DstroyTeleporting* pdt = new DstroyTeleporting(pGame->dsTeleportingStandard);
	pdt->setPosGrid(gridX(), gridY());
	pdt->init();
	pGame->addObject(pdt, 10);

	pdt = new DstroyTeleporting(pGame->dsTeleportingStandard);
	pdt->setPosGrid(x, y);
	pdt->init(this);
	pGame->addObject(pdt, 10);

	this->setPosGrid(x, y);	
}

void DstroyPlayer::setStartPos(TGIint x, TGIint y)
{
	startX = x;
	startY = y;
}

void DstroyPlayer::win(void)
{
	nAnimSpeed = 100;
	bWinner = true;

	if (bShield || bShadow)
	{
		bVisible = true;
	}

	reinitBonus();
}


void DstroyPlayer::setShield(TGIuint16 nDuration)
{
	tgAlmostEndShield = TGITime::getCurrentTime();
	tgAlmostEndShield += nDuration - 3000;
	tgEndShield = tgAlmostEndShield;
	tgEndShield += 3000;

	bShield = true;
	nShieldEtat = 0;
}
