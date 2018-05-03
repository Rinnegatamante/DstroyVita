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
#include "TGIScreen.h"

#include "TGIGlobals.h"
#include "TGISprite.h"
#include "TGIMain.h"

TGIScreen::TGIScreen(void)
{
	pCenterObject = NULL;

	x0 = 0;
	y0 = 0;
}

TGIScreen::~TGIScreen(void)
{
}

void TGIScreen::drawScreen(void* pData)
{
	register TGISprite* pSprite;
	register TGIObject* pObject;
	register SDL_Rect rectSrc, rectDest;
	//TGIuint16 i;
	register std::list<std::pair<TGIObject*, TGIint> >::iterator itObject; 
	register int offset;

	TGIMain* pMain = (TGIMain*)pData;

	if (pCenterObject)
	{
		x0 = pCenterObject->X()*TGIGlobals::nSpriteSize - this->rectDest.w/2 + pCenterObject->width/2*TGIGlobals::nSpriteSize; 
		y0 = pCenterObject->Y()*TGIGlobals::nSpriteSize - this->rectDest.h/2 + pCenterObject->height/2*TGIGlobals::nSpriteSize; 

		if (x0 < rectLimit.x)
			x0 = rectLimit.x;
		else if (x0 > rectLimit.w)
			x0 = rectLimit.w;
		if (y0 < rectLimit.y)
			y0 = rectLimit.y;
		else if (y0 > rectLimit.h)
			y0 = rectLimit.h;

#ifdef __NDS__
		x0 -= x0%4;
#endif

	}

	

	/*char strText[256];
	sprintf(strText, "%d %d", x0, y0);
	TGIGlobals::Trace(strText);*/

	SDL_Rect rectMain;
	SDL_GetClipRect(TGIGlobals::pScreen, &rectMain);
	if (!TGIGlobals::bRotateScreen)
	{
		SDL_SetClipRect(TGIGlobals::pScreen, &this->rectDest);
	}
	else
	{
		rectDest.x = TGIGlobals::screenWidth - this->rectDest.x - this->rectDest.w;
		rectDest.y = TGIGlobals::screenHeight - this->rectDest.y - this->rectDest.h;
		rectDest.w = this->rectDest.w;
		rectDest.h = this->rectDest.h;

		SDL_SetClipRect(TGIGlobals::pScreen, &rectDest);
	}


	for (itObject=pMain->getFirstObject();itObject!=pMain->getEndObject();itObject++)
	{
		pObject = itObject->first;
		if (pObject->bVisible && !pObject->bFixedOnScreen)
		{
			rectDest.x = pObject->X()*TGIGlobals::nSpriteSize - x0;
			rectDest.y = pObject->Y()*TGIGlobals::nSpriteSize - y0;
			rectDest.w = pObject->width*TGIGlobals::nSpriteSize;
			rectDest.h = pObject->height*TGIGlobals::nSpriteSize;

			//printf("%d,%d\n", rectDest.x, rectDest.y);

			if (rectDest.x - rectDest.w < this->rectSrc.w && rectDest.y - rectDest.h < this->rectSrc.h && 
				rectDest.x + rectDest.w > 0 && rectDest.y + rectDest.h > 0)
			{
				pSprite = pObject->getSprite(pObject->getCurrentSprite());

				rectDest.x += this->rectDest.x;
				rectDest.y += this->rectDest.y;

				if (TGIGlobals::bRotateScreen)
				{
					rectDest.x = TGIGlobals::screenWidth - rectDest.x - rectDest.w - 1;
					rectDest.y = TGIGlobals::screenHeight - rectDest.y - rectDest.h - 1;
				}
				//drawing
				rectSrc.x = pSprite->x;
				rectSrc.y = pSprite->y;
				rectSrc.w = pSprite->w;
				rectSrc.h = pSprite->h;

				/*if (rectDest.x < 0)
				{
					offset = -rectDest.x;
					rectDest.x = 0;
					rectDest.w -= offset;
					rectSrc.x += offset;
					rectSrc.w -= offset;
				}
				if (rectDest.y < 0)
				{
					offset = -rectDest.y;
					rectDest.y = 0;
					rectDest.h -= offset;
					rectSrc.y += offset;
					rectSrc.h -= offset;
				}
				
				offset = rectDest.x + rectDest.w - this->rectDest.w;
				if (offset > 0)
				{
					rectDest.w -= offset;
					rectSrc.w -= offset;
				}
				offset = rectDest.y + rectDest.h - this->rectDest.h;
				if (offset > 0)
				{
					rectDest.h -= offset;
					rectSrc.h -= offset;
				}*/
				

				

				if (TGIGlobals::bRotateScreen)
				{
					

					//rectSrc.x = pSprite->getSurface()->getWidth() - rectSrc.x - rectSrc.w;
					//rectSrc.y = pSprite->getSurface()->getHeight() - rectSrc.y - rectSrc.h;
				}
				

				SDL_BlitSurface(pSprite->pTGISurface->pSurface, &rectSrc, TGIGlobals::pScreen, &rectDest);
			}
		}
	}
	SDL_SetClipRect(TGIGlobals::pScreen, &rectMain);

}
