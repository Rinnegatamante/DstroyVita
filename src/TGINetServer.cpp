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
#include "TGINetServer.h"

TGINetServer::TGINetServer(void)
{
#ifndef TGI_NONET
	socket=NULL;
	pPacket = NULL;
#endif
}

TGINetServer::~TGINetServer(void)
{
	close();
}


bool TGINetServer::open(TGIuint16 nPort, TGIuint16 nPacketSize)
{
#ifndef TGI_NONET
	close();

	//on ouvre le serveur avec le bon port
	socket = SDLNet_UDP_Open(nPort);
	pPacket = SDLNet_AllocPacket(nPacketSize);

	pBuffer = (char*)(pPacket->data);
	len = nPacketSize;
	
	return socket != NULL;
#else
	return false;
#endif
}

bool TGINetServer::close()
{
#ifndef TGI_NONET
	if (socket)
	{
		SDLNet_UDP_Close(socket);
		socket=NULL;
	}
	if (pPacket)
	{
		SDLNet_FreePacket(pPacket);
		pPacket = NULL;
		pBuffer = NULL;
		len = 0;
	}

	return true;
#else
	return false;
#endif
}


bool TGINetServer::receivePacket()
{
#ifndef TGI_NONET
	int nRes = SDLNet_UDP_Recv(socket, pPacket);
	if (nRes < 1)
		return false;

	len = pPacket->len;

	//do things with pBuffer and len

	return true;
#else
	return false;
#endif
}

bool TGINetServer::addClientFromLastPacketReceived()
{
#ifndef TGI_NONET
	TGINetClient newClient;
	TGIuint8 i;

	newClient.ip = pPacket->address;
	newClient.nChannel = pPacket->channel;

	for (i=0;i<vecClient.size();i++)
	{
		if (vecClient[i] == newClient)
			return false;
	}

	vecClient.push_back(newClient);

	return true;
#else
	return false;
#endif
}

bool TGINetServer::getClientFromLastPacketReceived(TGIuint8& i)
{
#ifndef TGI_NONET
	TGINetClient newClient;

	newClient.ip = pPacket->address;
	newClient.nChannel = pPacket->channel;

	for (i=0;i<vecClient.size();i++)
	{
		if (vecClient[i] == newClient)
			return true;
	}

	return false;
#else
	return false;
#endif
}

bool TGINetServer::deleteClient(TGIuint8 nClient)
{
#ifndef TGI_NONET
	if (nClient < 0 || nClient >= vecClient.size())
		return false;

	vecClient.erase(vecClient.begin() + nClient);

	return true;
#else
	return false;
#endif
}

bool TGINetServer::sendPacket(TGIuint8 nClient, char* pBuffer, TGIuint16 len)
{
#ifndef TGI_NONET
	UDPpacket packet;
	packet.address = vecClient[nClient].ip;
	packet.channel = vecClient[nClient].nChannel;
	packet.data = (Uint8*)pBuffer;
	packet.len = len;
		
	int nRes = SDLNet_UDP_Send(socket, packet.channel, &packet);
	return (nRes > 0);
#else
	return false;
#endif

}
