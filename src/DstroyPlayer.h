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
#include "DstroyItem.h"
#include "TGITime.h"
#include "DstroyBomb.h"


class DstroyPlayer : public DstroyItem
{


	bool bDropBomb;
	bool bMoving;
	bool bWinner;
	
	TGIuint8 nShieldEtat;
	
	
protected:
	bool changeSprite();
public:
	DstroyPlayer(void);
public:
	~DstroyPlayer(void);
	
	void quePasa();
	void move(Direction dir);
	void treatMessage(TGIInputMessage* pMessage);
public:
	void dropBomb(void);

	DstroyBomb* pRemoteBomb;

	//pr les bonus
	bool bReverse;
	TGITime tgEndReverse;
	bool bShadow;
	TGITime tgEndShadow;
	bool bShield;
	TGITime tgEndShield;
	TGITime tgAlmostEndShield;
	bool bSlow;
	TGITime tgEndSlow;
	bool bSpeed;
	TGITime tgEndSpeed;
	bool bFreeze;
	TGITime tgEndFreeze;
	bool bDropBombs;
	TGITime tgEndDropBombs;
	bool bCannotDropBomb;
	TGITime tgEndCannotDropBomb;

	bool bMonster;
	bool bCross;
	bool bRemote;

	int nBombs;
	int nBombsLeft;
	int nBombDurationLeft;
	int nFlames;

	bool bAlive;
	TGIuint16 startX, startY;
public:
	bool canMove(TGIint x, TGIint y);
	void getBonus(DstroyItem* pBonus);
	void reinitBonus(void);
	void teleport(TGIint x, TGIint y);
	void setStartPos(TGIint x, TGIint y);
	void win(void);
	void setShield(TGIuint16 nDuration);
};


