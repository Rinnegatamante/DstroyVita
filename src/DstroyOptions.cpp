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
#include "DstroyOptions.h"

#include "TGIGlobals.h"
#include "DstroyGlobals.h"
#include "TGIFile.h"

#define CURRENT_VERSION 4

DstroyOptions::DstroyOptions(void)
{
	bFullScreen = false;
	bDoubleSize = false;
	bRotateScreen = false;
	bOptionsText = false;
	nGP2XmvtMode = 1;
}

DstroyOptions::~DstroyOptions(void)
{
}

void DstroyOptions::save(void)
{
	TGIFile tgiFile;
	//ofs.open(DstroyGlobals::addResText("options"), std::ofstream::trunc | std::ofstream::binary);
	if (!tgiFile.create(DstroyGlobals::addConfigText("options"), true))
		return;

	TGIuint16 order = 255;
	TGIuint16 version = CURRENT_VERSION;
	TGIuint8 n8;

	tgiFile.write((char*)&order, 2);
	tgiFile.write((char*)&version, 2);
	if (bFullScreen) n8 = 1; else n8 = 0;
	tgiFile.write((char*)&n8, 1);
	if (bDoubleSize) n8 = 1; else n8 = 0;
	tgiFile.write((char*)&n8, 1);
	if (bRotateScreen) n8 = 1; else n8 = 0;
	tgiFile.write((char*)&n8, 1);
	if (bOptionsText) n8 = 1; else n8 = 0;
	tgiFile.write((char*)&n8, 1);
	tgiFile.write((char*)&nGP2XmvtMode, 1);

	tgiFile.close();
}

void DstroyOptions::load(void)
{
	TGIFile tgiFile;
	if (!tgiFile.openRead(DstroyGlobals::addConfigText("options"), true))
		return;

	TGIuint16 order=0;
	TGIuint16 version=0;
	TGIuint8 n8=0;

	tgiFile.read((char*)&order, 2);
	tgiFile.read((char*)&version, 2);
	TGIGlobals::endianConvert(order, &version, 2);
	tgiFile.read((char*)&n8, 1);
	TGIGlobals::endianConvert(order, &n8, 1);
	bFullScreen = (n8 == 1);
	tgiFile.read((char*)&n8, 1);
	TGIGlobals::endianConvert(order, &n8, 1);
	bDoubleSize = (n8 == 1);
	if (version >= 2)
	{
		tgiFile.read((char*)&n8, 1);
		TGIGlobals::endianConvert(order, &n8, 1);
		bRotateScreen = (n8 == 1);

		if (version >=3)
		{
			tgiFile.read((char*)&n8, 1);
			TGIGlobals::endianConvert(order, &n8, 1);
			bOptionsText = (n8 == 1);
		}

		if (version >= 4)
		{
			tgiFile.read((char*)&nGP2XmvtMode, 1);
		}
	}

	tgiFile.close();
}
