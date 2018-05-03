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

#include "TGIMain.h"
#include "TGIFont2.h"

class DstroyIntro :	public TGIMain
{
	TGIFont2 font;
	bool bMoveImage;
	TGIuint8 nStep;
	TGIuint8 nCurrentPage;

public:
	DstroyIntro(void);
public:
	~DstroyIntro(void);
public:
	bool init(void);
public:
	bool events(void);
public:
	void setPage1(void);
	void setPage2(void);
	void setPage3(void);
	void setPage4(void);
	void setPage5(void);
	void setPage6(void);
	void setPage7(void);
	void setPage8(void);
public:
	void nextPage(void);
public:
	bool exit(void);
};
