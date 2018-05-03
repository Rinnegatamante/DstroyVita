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

#include <vector>
#include "TGIGlobals.h"

class TGINetServer;

#include "TGINetClient.h"

class TGINetServer
{
	std::vector<TGINetClient> vecClient;
#ifndef TGI_NONET
	UDPsocket socket;
	UDPpacket *pPacket;
#endif
protected:
	char* pBuffer;
	TGIuint16 len;
public:
	TGINetServer(void);
public:
	~TGINetServer(void);

	bool open(TGIuint16 nPort, TGIuint16 nPacketSize=256);
	bool close();

	virtual bool receivePacket();
	bool addClientFromLastPacketReceived();
	bool deleteClient(TGIuint8 nClient);
	bool sendPacket(TGIuint8 nClient, char* pBuffer, TGIuint16 len);
	bool getClientFromLastPacketReceived(TGIuint8& i);
};
