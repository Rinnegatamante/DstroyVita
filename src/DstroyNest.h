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

#define NESTTYPE_CREATOR 1
#define NESTTYPE_OUT 2

class DstroyNest : public DstroyItem
{
	TGIuint16 nPeriode; //periode entre chaque monstre
	DstroyNest* pNestOut;
	
	TGIuint8 nLives;
	TGIuint8 nMonsterType;
	TGIuint8 nIA;
	TGIuint8 nMonsterLife;
	TGIuint16 nMonsterMax;

	TGITime tgWhenToCreateMonster;

	bool bShield;
	TGITime tgWhenToEndShield;

public:
	TGIuint8 nType;
	DstroyNest(void);
public:
	~DstroyNest(void);
public:
	bool changeSprite(void);
public:
	void quePasa(void);
public:
	void createMonster(void);
	void prepareCreateMonster(void);
public:
	void destroy(void);
public:
	bool initOut(TGIuint8 nMonsterType, TGIuint8 nIA, TGIuint8 nMonsterLife);
	bool initCreator(TGIuint8 nLives, TGIuint16 nPeriode, TGIuint16 nMonsterMax, DstroyNest* pNestOut);
public:
	void copy(const DstroyNest& from);
};
