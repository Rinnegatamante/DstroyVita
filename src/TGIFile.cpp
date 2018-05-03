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
#include "TGIFile.h"



TGIFile::TGIFile(void)
{
	pFile = NULL;
}

TGIFile::~TGIFile(void)
{
	close();
}

bool TGIFile::openRead(const char* strFile, bool bBinary)
{
	close();
	char* strMode;
	
	if (bBinary)
		strMode = "rb";
	else
		strMode = "r";
		

	pFile = fopen(strFile, strMode);
	if (!pFile)
	{
		return false;
	}

	return true;
}

bool TGIFile::open(const char* strFile, bool bBinary)
{
	close();
	char* strMode;
	
	if (bBinary)
		strMode = "r+b";
	else
		strMode = "r+";
		

	pFile = fopen(strFile, strMode);
	if (!pFile)
		return create(strFile, bBinary);

	return true;
}

bool TGIFile::create(const char* strFile, bool bBinary)
{
	close();
	char* strMode;
	
	if (bBinary)
		strMode = "wb";
	else
		strMode = "w";
		

	pFile = fopen(strFile, strMode);
	if (!pFile)
		return false;

	return true;
}

bool TGIFile::isOpen()
{
	return pFile != NULL;
}

bool TGIFile::eof()
{
	if (!isOpen())
		return true;
	if (feof(pFile))
		return true;

	return false;
}


bool TGIFile::close()
{
	if (!isOpen())
		return true;

	fclose(pFile);
	pFile = NULL;

	return true;
}

bool TGIFile::seekFromBegin(TGIuint16 nSeek)
{
	if (!isOpen())
		return false;

	fseek(pFile, nSeek, SEEK_SET);

	return true;
}

bool TGIFile::seekFromHere(TGIuint16 nSeek)
{
	if (!isOpen())
		return false;

	fseek(pFile, nSeek, SEEK_CUR);

	return true;
}

bool TGIFile::seekFromEnd(TGIuint16 nSeek)
{
	if (!isOpen())
		return false;

	fseek(pFile, nSeek, SEEK_END);

	return true;
}

bool TGIFile::read(char* pValue, TGIuint16 nSize)
{
	if (!isOpen())
		return false;

	fread(pValue, 1, nSize, pFile);

	return true;
}

bool TGIFile::write(char* pValue, TGIuint16 nSize)
{
	if (!isOpen())
		return false;

	fwrite(pValue, 1, nSize, pFile);

	return true;
}


TGIuint16 TGIFile::getPos()
{
	if (!isOpen())
		return false;

	return (TGIuint16)ftell(pFile);
}