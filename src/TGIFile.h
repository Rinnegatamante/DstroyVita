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

#include <stdio.h>
#include "TGIGlobals.h"

class TGIFile
{
	FILE* pFile;
public:
	TGIFile(void);
	virtual ~TGIFile(void);

	bool create(const char* strFile, bool bBinary);
	bool openRead(const char* strFile, bool bBinary);
	bool open(const char* strFile, bool bBinary);
	bool close();

	bool read(char* pValue, TGIuint16 nSize);
	bool write(char* pValue, TGIuint16 nSize);

	bool seekFromBegin(TGIuint16 nSeek);
	bool seekFromHere(TGIuint16 nSeek);
	bool seekFromEnd(TGIuint16 nSeek);
	TGIuint16 getPos();


	bool isOpen();
	bool eof();
};
