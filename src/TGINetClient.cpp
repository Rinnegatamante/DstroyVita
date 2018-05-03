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
#include "TGINetClient.h"

TGINetClient::TGINetClient(void)
{
#ifndef TGI_NONET
	nChannel = -1;
	socket = NULL;
#endif
	pBuffer = NULL;
}

TGINetClient::~TGINetClient(void)
{
	disconnect();
}


bool TGINetClient::operator ==(const TGINetClient& a)
{
#ifndef TGI_NONET
	return (ip.host == a.ip.host && ip.port == a.ip.port && nChannel == a.nChannel);
#else
	return false;
#endif
}

bool TGINetClient::connectToServer(char* strHost, TGIuint16 nPort, TGIuint16 nPacketSize)
{
#ifndef TGI_NONET
	disconnect();

	socket = SDLNet_UDP_Open(0);
	if (socket == NULL)
		return false;

	if (SDLNet_ResolveHost(&ipServer,strHost,nPort)==-1)
		return false;

	nChannel = SDLNet_UDP_Bind(socket, 0, &ipServer);

	return nChannel != -1;
#else
	return false;
#endif
}

bool TGINetClient::connectToServer(TGIuint32 host, TGIuint16 nPort, TGIuint16 nPacketSize)
{
#ifndef TGI_NONET
	
	pBuffer = new char[nPacketSize];
	this->nPacketSize = nPacketSize;

	
	ipServer.host = host;
	ipServer.port = nPort;

	

	nChannel = SDLNet_UDP_Bind(socket, 0, &ipServer);

	return nChannel != -1;
#else
	return false;
#endif
}

bool TGINetClient::disconnect()
{
#ifndef TGI_NONET
	if (nChannel != -1)
	{
		SDLNet_UDP_Unbind(socket, nChannel);
	}
	if (socket)
	{
		SDLNet_UDP_Close(socket);
		socket=NULL;
	}
	if (pBuffer)
	{
		delete [] pBuffer;
		pBuffer = NULL;
		nPacketSize = 0;
	}

	return true;
#else
	return false;
#endif
	
}

bool TGINetClient::sendPacket(char* pBuffer, TGIuint16 len)
{
#ifndef TGI_NONET
	UDPpacket *pPacket;
	Uint8* pOldData;

	pPacket = SDLNet_AllocPacket(256);

	//pPacket->address = ipServer;
	//pPacket->channel = nChannel;
	pOldData = pPacket->data;
	pPacket->data = (Uint8*)pBuffer;
	pPacket->len = len;

	int nRes = SDLNet_UDP_Send(socket, 0, pPacket);

	pPacket->data = pOldData;

	return nRes > 0;
#else
	return false;
#endif
}

bool TGINetClient::receivePacket()
{
#ifndef TGI_NONET
	UDPpacket packet;
	packet.data = (Uint8*)pBuffer;
	packet.maxlen = nPacketSize;

	int nRes = SDLNet_UDP_Recv(socket, &packet);
	if (nRes <= 0)
		return false;
#else
	return false;
#endif

}

