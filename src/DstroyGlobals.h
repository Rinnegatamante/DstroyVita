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
#include "DstroyNetServer.h"

#ifdef LINUX
	#include <sys/stat.h>
#endif

#ifndef DATADIR
	#ifndef __NDS__
		#define DATADIR "ux0:data/dstroydata"
	#else
		#define DATADIR "/dstroydata" //pour NDS, les ressources doivent etre dans la racine de la carte
	#endif
#endif

class DstroyGlobals
{
	static char strResText[256];

	static char strConfigText[256];
	static char strConfigDir[256];


public:
	DstroyGlobals(void);
	~DstroyGlobals(void);

	static void init()
	{
#ifdef LINUX
#ifndef CONFIG_DIR
		sprintf(strConfigDir, "%s/.dstroy", getenv("HOME"));
		// check whether config folder exists	
		const char* configFolder = addConfigText("");
		struct stat s;
		if (stat(configFolder,&s) != 0)
		{
			// if not, create it
			mkdir(configFolder,S_IRWXU);

		}
#else
		strConfigDir = CONFIG_DIR;
#endif
#endif
	}	

	static char* addResText(const char* strText)
	{
		sprintf(strResText, DATADIR "/%s", strText);
		return strResText;
	}

	static char* addConfigText(const char* strText)
	{
#ifdef LINUX
		sprintf(strConfigText, "%s/%s", strConfigDir, strText );
		return strConfigText;
#else
		return addResText(strText);
#endif
	}

	static DstroyNetServer server;
};
