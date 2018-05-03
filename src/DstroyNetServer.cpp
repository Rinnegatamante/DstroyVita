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
#include "DstroyNetServer.h"

DstroyNetServer::DstroyNetServer(void)
{
}

DstroyNetServer::~DstroyNetServer(void)
{
}


bool DstroyNetServer::receivePacketWaitingConnect()
{
	if (!receivePacket())
	{
		return false;
	}
	/*if (len < 10)
		return false;*/
	//on parse le message et on regarde de quoi il s'agit
	if (pBuffer[0] == NETMSG_CONNECT)
	{
		//connection d'un client
		if (!addClientFromLastPacketReceived())
		{
			return false;
		}
		vecClientName.push_back(pBuffer+1);

		return true;
	}
	if (pBuffer[0] == NETMSG_DISCONNECT)
	{
		TGIuint8 nClient;
		if (!getClientFromLastPacketReceived(nClient))
			return false;
		deleteClient(nClient);
		vecClientName.erase(vecClientName.begin() + nClient);

		return true;
	}

	return false;
	
}

bool DstroyNetServer::receivePacketGame()
{
	if (!receivePacket())
	{
		return false;
	}

	return true;
}