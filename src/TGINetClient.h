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

class TGINetClient;

#include "TGINetServer.h"

class TGINetClient
{
	friend class TGINetServer;
#ifndef TGI_NONET
	//used by the server
	int nChannel;
	IPaddress ip;

	UDPsocket socket;
	IPaddress ipServer;
	TGIuint16 nPacketSize;
#endif

protected:
	char* pBuffer;
	TGIuint16 len;

public:
	TGINetClient(void);
	~TGINetClient(void);

	bool operator ==(const TGINetClient& a);

	bool connectToServer(char* strHost, TGIuint16 nPort, TGIuint16 nPacketSize);
	bool connectToServer(TGIuint32 host, TGIuint16 nPort, TGIuint16 nPacketSize);
	bool disconnect();
	bool sendPacket(char* pBuffer, TGIuint16 len);
	virtual bool receivePacket();
};
