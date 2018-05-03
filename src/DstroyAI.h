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

#include "DstroyMonster.h"

class DstroyAI
{
	TGIuint8* matrixRisk;
	TGIuint8* matrixRiskAdvanced;
	TGIuint16 nWidth, nHeight;

	void calculateRisk(TGIuint16 x, TGIuint16 y, TGIuint8 nDuration, TGIuint16 lim, bool bAdvanced);

public:
	DstroyAI(void);
	~DstroyAI(void);
public:
	void init(TGIuint16 nWidth, TGIuint16 nHeight);
public:
	void setRisk(TGIuint16 x, TGIuint16 y, TGIuint8 nRisk, bool bAdvanced);
public:
	TGIuint8 getRisk(TGIuint16 x, TGIuint16 y, bool bAdvanced);
public:
	void calculateRisk(void);
public:
	void think(DstroyMonster* pMonster);
public:
	double distance(TGIuint16 x, TGIuint16 y, DstroyItem* pItem2);
	
};
