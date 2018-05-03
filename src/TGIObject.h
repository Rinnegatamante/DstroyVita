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

#include "TGIGlobals.h"
#include "TGIInputMessage.h"
#include "TGISprite.h"
#include "TGITime.h"

/* TGIObject

	graphic object
	contains TGISprite that can be changed to make animation

	can be derivated to make game objects:
		changeSprite() : modify the current sprite
		treatMessage() : treat received messages from the TGIMain

*/

class TGIObject
{
private:
	TGIint x, y; //position in the game (NOT in the screen)
	//current sprite
	TGIint nCurrentSprite;

protected:
	//TGISprites of the object
	std::vector<TGISprite> vecSprite;
	
	//time when the current sprite has to change (launch changeSprite)
	TGITime tgWhenToChangeSprite;
	//change the sprite (must be derived)
	virtual bool changeSprite();
	//treat a message received by onMessage
	virtual void treatMessage(TGIInputMessage* pMessage);

	//copy the object from another
	virtual void copy(const TGIObject& from);

	//speed of the animation (must be != 0 to launch changeSprite)
	TGIuint16 nAnimSpeed;

	
		
public:
	TGIObject(void);
	TGIObject(const TGIObject& from);
	virtual ~TGIObject(void);
	TGIObject& operator =(const TGIObject& from);

	//add a sprite
	bool addSprite(const TGISprite& sprite);

	//get a sprite from the vector
	inline TGISprite* getSprite(TGIint nIndex) { return &(vecSprite[nIndex]); };
	inline TGIuint16 getSpriteCount(void) { return (TGIuint16)vecSprite.size(); };
	//ask for changing sprite (called by TGIMain)
	inline TGISprite* doChangeSprite()
	{
		if (nAnimSpeed != 0 && tgWhenToChangeSprite <= TGITime::getCurrentTime())
		{
			if (!changeSprite())
				return NULL;
			tgWhenToChangeSprite = TGITime::getCurrentTime();
			tgWhenToChangeSprite += nAnimSpeed;
		}

		if ((int)vecSprite.size() - nCurrentSprite > 0)
			return &(vecSprite[nCurrentSprite]);

		return NULL;
	};
	//receive a message (called by TGIMain)
	inline bool onMessage(TGIInputMessage* pMessage)
	{
		if (pMessage->lIdRecipient != lId)
			return false;

		treatMessage(pMessage);

		return true;
	};
	
	//size of the object (must be fixed)
	TGIint width, height;
	//unique ID of the object (for messages: objects that dont receive message dont need a ID)
	TGIuint16 lId;

	//if the object is visible
	bool bVisible;
	//if we need to call doChangeSprite or not
	bool bDoChangeSprite;

	//action (must be derived)
	virtual void quePasa(void);

	//position fonctions		
	inline virtual void setX(TGIint x) { this->x = x; };
	inline virtual void setY(TGIint x) { this->y = x; };
	inline virtual void setPos(TGIint x, TGIint y)
	{
		this->x = x;
		this->y = y;
	};
	inline TGIint X(void) { return x; };
	inline TGIint Y(void) { return y; };

	//fixed on the screen
	bool bFixedOnScreen;

	void reset(void);
	void setCurrentSprite(TGIint nSprite);
	inline TGIint getCurrentSprite(void) { return nCurrentSprite; };

};
