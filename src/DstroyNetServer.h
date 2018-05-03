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

#include "TGINetServer.h"

#define NETMSG_INIT 1
#define NETMSG_WALLPOS 2
#define NETMSG_INITPLAYER 3
#define NETMSG_BOMB 4
#define NETMSG_MOVE 5

#define NETMSG_CONNECT 100
#define NETMSG_DISCONNECT 101
#define NETMSG_PLAYERMOVE 102
#define NETMSG_DROPBOMB 103

class DstroyNetServer : public TGINetServer
{
	
public:
	std::vector<std::string> vecClientName;
	
	
	DstroyNetServer(void);
	~DstroyNetServer(void);

	bool receivePacketWaitingConnect();
	bool receivePacketGame();
};
