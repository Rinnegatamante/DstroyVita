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
#include "DstroyNetClient.h"

#include "DstroyNetServer.h"

#include <string.h>

DstroyNetClient::DstroyNetClient(void)
{
	strcpy(strName, "NoName");
}

DstroyNetClient::~DstroyNetClient(void)
{
}

bool DstroyNetClient::connect(char* strHost, TGIuint16 nPort)
{
	char buffer[256];
	
	buffer[0] = NETMSG_CONNECT;
	strcpy(buffer+1, strName);


	if (!TGINetClient::connectToServer(strHost, nPort, 256))
		return false;
	return TGINetClient::sendPacket(buffer, strlen(strName)+2);
}
bool DstroyNetClient::deconnect()
{
	char buffer[256];
	
	buffer[0] = NETMSG_DISCONNECT;
	if (!TGINetClient::sendPacket(buffer, 1))
		return false;
	return TGINetClient::disconnect();
}

bool DstroyNetClient::setName(char* str)
{
	strncpy(strName, str, 255);

	return true;
}