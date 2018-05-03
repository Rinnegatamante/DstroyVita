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
#include "DstroyIntro.h"

#include "DstroyGlobals.h"

#include "DstroyIntro2.h"



DstroyIntro::DstroyIntro(void)
{
}

DstroyIntro::~DstroyIntro(void)
{
}

bool DstroyIntro::init(void)
{
	if (!TGIMain::init())
		return false;

	TGIGlobals::playMusic(DstroyGlobals::addResText("story.mod"));

	TGISurface* pSurface;
	pSurface = new TGISurface;
	pSurface->setInvisibleColor(0, 0, 0);
	pSurface->loadImage(DstroyGlobals::addResText("ld.pcx"));
	
	font.setSurface(pSurface);
	pSurface = NULL;

	TGIuint16 x = 0, y = 0;
	font.importLetter('A', false, x, y, 32, 32); x = 32;
	font.importLetter('B', false, x, y, 60-x, 32); x = 60;
	font.importLetter('C', false, x, y, 83-x, 32); x = 83;
	font.importLetter('D', false, x, y, 113-x, 32); x = 113;
	font.importLetter('E', false, x, y, 139-x, 32); x = 139;
	font.importLetter('F', false, x, y, 170-x, 32); x = 170;
	font.importLetter('G', false, x, y, 196-x, 32); x = 196;
	font.importLetter('H', false, x, y, 224-x, 32); x = 224;
	font.importLetter('I', false, x, y, 245-x, 32); x = 245;
	font.importLetter('J', false, x, y, 268-x, 32); x = 0;
	y += 33;
	font.importLetter('K', false, x, y, 46-x, 32); x = 46;
	font.importLetter('L', false, x, y, 81-x, 32); x = 81;
	font.importLetter('M', false, x, y, 119-x, 32); x = 119;
	font.importLetter('N', false, x, y, 154-x, 32); x = 154;
	font.importLetter('O', false, x, y, 179-x, 32); x = 179;
	font.importLetter('P', false, x, y, 205-x, 32); x = 205;
	font.importLetter('Q', false, x, y, 238-x, 32); x = 238;
	font.importLetter('R', false, x, y, 279-x, 32); x = 0;
	y += 33;
	font.importLetter('S', false, x, y, 26-x, 32); x = 26;
	font.importLetter('T', false, x, y, 57-x, 32); x = 57;
	font.importLetter('U', false, x, y, 88-x, 32); x = 88;
	font.importLetter('V', false, x, y, 116-x, 32); x = 116;
	font.importLetter('W', false, x, y, 157-x, 32); x = 157;
	font.importLetter('X', false, x, y, 195-x, 32); x = 195;
	font.importLetter('Y', false, x, y, 225-x, 32); x = 225;
	font.importLetter('Z', false, x, y, 249-x, 32); x = 249;

	x = 0;
	y = 104;
	font.importLetter('a', false, x, y, 7, 10); x = 7;
	font.importLetter('b', false, x, y, 15-x, 10); x = 15;
	font.importLetter('c', false, x, y, 23-x, 10); x = 23;
	font.importLetter('d', false, x, y, 31-x, 10); x = 31;
	font.importLetter('e', false, x, y, 38-x, 10); x = 38;
	font.importLetter('f', false, x, y, 43-x, 10); x = 43;
	font.importLetter('g', false, x, y, 51-x, 10); x = 51;
	font.importLetter('h', false, x, y, 59-x, 10); x = 59;
	font.importLetter('i', false, x, y, 62-x, 10); x = 62;
	font.importLetter('j', false, x, y, 69-x, 10); x = 69;
	font.importLetter('k', false, x, y, 77-x, 10); x = 77;
	font.importLetter('l', false, x, y, 84-x, 10); x = 84;
	font.importLetter('m', false, x, y, 92-x, 10); x = 92;
	font.importLetter('n', false, x, y, 100-x, 10); x = 100;
	font.importLetter('o', false, x, y, 108-x, 10); x = 108;
	font.importLetter('p', false, x, y, 115-x, 10); x = 115;
	font.importLetter('q', false, x, y, 123-x, 10); x = 123;
	font.importLetter('r', false, x, y, 130-x, 10); x = 130;
	font.importLetter('s', false, x, y, 138-x, 10); x = 138;
	font.importLetter('t', false, x, y, 146-x, 10); x = 146;
	font.importLetter('u', false, x, y, 152-x, 10); x = 152;
	font.importLetter('v', false, x, y, 160-x, 10); x = 160;
	font.importLetter('w', false, x, y, 171-x, 10); x = 171;
	font.importLetter('x', false, x, y, 179-x, 10); x = 179;
	font.importLetter('y', false, x, y, 186-x, 10); x = 186;
	font.importLetter('z', false, x, y, 195-x, 10); x = 195;

	x = 1;
	y = 121;
	font.importLetter('1', false, x, y, 8, 10); x = 9;
	font.importLetter('2', false, x, y, 15-x, 10); x = 16;
	font.importLetter('4', false, x, y, 22-x, 10); x = 22;
	font.importLetter('5', false, x, y, 30-x, 10); x = 30;
	font.importLetter('6', false, x, y, 36-x, 10); x = 36;
	font.importLetter('7', false, x, y, 43-x, 10); x = 43;
	font.importLetter('8', false, x, y, 51-x, 10); x = 51;
	font.importLetter('9', false, x, y, 57-x, 10); x = 57;
	font.importLetter('0', false, x, y, 65-x, 10); x = 65;
	font.importLetter(',', false, x, y, 68-x, 10); x = 68;
	font.importLetter('.', false, x, y, 71-x, 10); x = 71;
	font.importLetter('\'', false, x, y, 75-x, 10); x = 75;
	font.importLetter('"', false, x, y, 83-x, 10); x = 83;
	font.importLetter(':', false, x, y, 87-x, 10); x = 87;
	font.importLetter(';', false, x, y, 92-x, 10); x = 92;
	font.importLetter('?', false, x, y-1, 101-x, 10); x = 101;
	font.importLetter('!', false, x, y, 105-x, 10); x = 105;
	font.importLetter('(', false, x, y, 109-x, 10); x = 109;
	font.importLetter(')', false, x, y, 115-x, 10); x = 115;
	font.importLetter('3', false, x, y, 124-x, 10); x = 124;
	font.importLetter(' ', false, x, y, 132-x, 10); x = 132;

	addScreen(0, 0, 320, 200, 0, 0, 320, 200, NULL, 0, 0);
	addScreen(0, 200, 320, 40, 640, 0, 960, 40, NULL, 640, 0);

	nCurrentPage = 0;
	nextPage();

	return true;
}

bool DstroyIntro::events(void)
{
	//TGIuint16 i;
	register std::list<std::pair<TGIObject*, TGIint> >::iterator itObject; 

	if (bMoveImage)
	{
		//on bouge l'image
		for (itObject=getFirstObject();itObject!=getEndObject();itObject++)
		{
			if (itObject->first->lId == 1)
			{
				itObject->first->setX(itObject->first->X() - 2);
				if (itObject->first->X() == 0)
				{
					bMoveImage = false;
					nStep = 0;
				}
				if (itObject->first->X() == -320)
				{
					bMoveImage = false;
					nextPage();
					break;
				}
			}
		}
	}
	else
	{
		//on bouge le texte
		nStep++;
		if (nStep > 7)
		{
			itObject = getFirstObject();
			itObject++;
			TGIint maxPos = itObject->first->Y();
			for (itObject=getFirstObject();itObject!=getEndObject();itObject++)
			{
				if (itObject->first->lId != 1)
				{
					itObject->first->setY(itObject->first->Y() - 1);
					if (itObject->first->Y() > maxPos)
					{
						maxPos = itObject->first->Y();
					}
				}
			}
			if (maxPos < -12)
			{
				bMoveImage = true;
			}
			nStep = 0;
		}
	}

	return TGIMain::events();
}

void DstroyIntro::nextPage(void)
{
	nCurrentPage++;
	switch (nCurrentPage)
	{
	case 1:
		setPage1();
		break;
	case 2:
		setPage2();
		break;
	case 3:
		setPage3();
		break;
	case 4:
		setPage4();
		break;
	case 5:
		setPage5();
		break;
	case 6:
		setPage6();
		break;
	case 7:
		setPage7();
		break;
	case 8:
		setPage8();
		break;
	default:
		{
			TGIGlobals::stopMusic();
			stop();
			break;
		}
	}
}

void DstroyIntro::setPage1(void)
{
	this->deleteAllObjects();

	TGIuint16 i;
	for (i=0;i<vecSurface.size();i++)
	{
		delete vecSurface[i];
	}
	vecSurface.clear();

	

	TGISurface* pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("int1.pcx"));
	vecSurface.push_back(pSurface);

	TGIObject* pObject;
	pObject = new TGIObject;
	
	TGISprite sprite;
	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	sprite.setPlacement(0, 0, 320, 200);
	pObject->addSprite(sprite);
	pObject->bVisible = true;
	pObject->setPos(320, 0);
	pObject->lId = 1;
	addObject(pObject, 10);

	TGIuint16 y = 41;
	font.writeText("D", 640, y, TAleft, 0, NULL, false); y += 5;
	font.writeText("ans le pays boodies, tout le monde", 670, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("vivait heureux! tout le monde?", 670, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("...helas non, un pauvre boodies", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("lunetteux etait trop timide pour", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("aller s'amuser avec les autres!", 650, y, TAleft, 0, NULL, false); y += 12;

	bMoveImage = true;
}

void DstroyIntro::setPage2(void)
{
	this->deleteAllObjects();

	TGIuint16 i;
	for (i=0;i<vecSurface.size();i++)
	{
		delete vecSurface[i];
	}
	vecSurface.clear();

	

	TGISurface* pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("int2.pcx"));
	vecSurface.push_back(pSurface);

	TGIObject* pObject;
	pObject = new TGIObject;
	
	TGISprite sprite;
	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	sprite.setPlacement(0, 0, 320, 200);
	pObject->addSprite(sprite);
	pObject->bVisible = true;
	pObject->setPos(320, 0);
	pObject->lId = 1;
	addObject(pObject, 10);

	TGIuint16 y = 41;
	font.writeText("C", 640, y, TAleft, 0, NULL, false); y += 5;
	font.writeText("elui ci se sentait rejete par les", 663, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("siens et decida un jour de les quitter,", 663, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("plein de tristesse dans son coeur", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("a lui qu'il avait...", 650, y, TAleft, 0, NULL, false); y += 12;

	bMoveImage = true;
}

void DstroyIntro::setPage3(void)
{
	this->deleteAllObjects();

	TGIuint16 i;
	for (i=0;i<vecSurface.size();i++)
	{
		delete vecSurface[i];
	}
	vecSurface.clear();

	

	TGISurface* pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("int3.pcx"));
	vecSurface.push_back(pSurface);

	TGIObject* pObject;
	pObject = new TGIObject;
	
	TGISprite sprite;
	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	sprite.setPlacement(0, 0, 320, 200);
	pObject->addSprite(sprite);
	pObject->bVisible = true;
	pObject->setPos(320, 0);
	pObject->lId = 1;
	addObject(pObject, 10);

	TGIuint16 y = 41;
	font.writeText("I", 640, y, TAleft, 0, NULL, false); y += 5;
	font.writeText("l marcha, marcha, marcha... et marcha", 661, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("encore. il marcha si tant plein qu'il", 661, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("arriva au pied du mont de la tour kifepeur,", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("dans laquelle habite l'immonde dark bavor!", 650, y, TAleft, 0, NULL, false); y += 12;


	bMoveImage = true;
}

void DstroyIntro::setPage4(void)
{
	this->deleteAllObjects();

	TGIuint16 i;
	for (i=0;i<vecSurface.size();i++)
	{
		delete vecSurface[i];
	}
	vecSurface.clear();

	

	TGISurface* pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("int4.pcx"));
	vecSurface.push_back(pSurface);

	TGIObject* pObject;
	pObject = new TGIObject;
	
	TGISprite sprite;
	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	sprite.setPlacement(0, 0, 320, 200);
	pObject->addSprite(sprite);
	pObject->bVisible = true;
	pObject->setPos(320, 0);
	pObject->lId = 1;
	addObject(pObject, 10);

	TGIuint16 y = 41;
	font.writeText("N", 640, y, TAleft, 0, NULL, false); y += 5;
	font.writeText("otre boodies decida malgre sa grande", 675, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("peur qu'il avait dans son ventre de", 675, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("monter pour le voir, parce que,", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("\"sait on jamais, se dit il, peut etre", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("qu'il pourra t'il m'aider... hein...", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("peut etre... quelque part... non?", 650, y, TAleft, 0, NULL, false); y += 12;


	bMoveImage = true;
}

void DstroyIntro::setPage5(void)
{
	this->deleteAllObjects();

	TGIuint16 i;
	for (i=0;i<vecSurface.size();i++)
	{
		delete vecSurface[i];
	}
	vecSurface.clear();

	

	TGISurface* pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("int5.pcx"));
	vecSurface.push_back(pSurface);

	TGIObject* pObject;
	pObject = new TGIObject;
	
	TGISprite sprite;
	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	sprite.setPlacement(0, 0, 320, 200);
	pObject->addSprite(sprite);
	pObject->bVisible = true;
	pObject->setPos(320, 0);
	pObject->lId = 1;
	addObject(pObject, 10);

	TGIuint16 y = 41;
	font.writeText("E", 640, y, TAleft, 0, NULL, false); y += 5;
	font.writeText("n effet, le grand et baveux dark bavor,", 666, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("roi des meuries, proposa de l'aider!", 666, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("il expliqua a notre boodies qu'il", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("pouvait faire disparaitre sa timidite", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("grace a la \"bassijissui\",une machine", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("diabolique qui fait peur mais qu'en", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("fait, elle fait du bien, en fait!", 650, y, TAleft, 0, NULL, false); y += 12;
	

	bMoveImage = true;
}

void DstroyIntro::setPage6(void)
{
	this->deleteAllObjects();

	TGIuint16 i;
	for (i=0;i<vecSurface.size();i++)
	{
		delete vecSurface[i];
	}
	vecSurface.clear();

	

	TGISurface* pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("int6.pcx"));
	vecSurface.push_back(pSurface);

	TGIObject* pObject;
	pObject = new TGIObject;
	
	TGISprite sprite;
	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	sprite.setPlacement(0, 0, 320, 200);
	pObject->addSprite(sprite);
	pObject->bVisible = true;
	pObject->setPos(320, 0);
	pObject->lId = 1;
	addObject(pObject, 10);

	TGIuint16 y = 41;
	font.writeText("L", 640, y, TAleft, 0, NULL, false); y += 5;
	font.writeText("e desespoir de notre boodies etait", 675, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("si grand nenorme, qu'il accepta", 675, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("d'essayer la bassijisui, sans", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("se rendre compte de l'infame piege", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("tendu par dark bavor... car cette", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("diabolique machine etait en fait", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("une machine a absorber la vitalite", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("boodies!...", 660, y, TAleft, 0, NULL, false); y += 12;

	bMoveImage = true;
}

void DstroyIntro::setPage7(void)
{
	this->deleteAllObjects();

	TGIuint16 i;
	for (i=0;i<vecSurface.size();i++)
	{
		delete vecSurface[i];
	}
	vecSurface.clear();

	

	TGISurface* pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("int7.pcx"));
	vecSurface.push_back(pSurface);

	TGIObject* pObject;
	pObject = new TGIObject;
	
	TGISprite sprite;
	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	sprite.setPlacement(0, 0, 320, 200);
	pObject->addSprite(sprite);
	pObject->bVisible = true;
	pObject->setPos(320, 0);
	pObject->lId = 1;
	addObject(pObject, 10);

	TGIuint16 y = 41;
	font.writeText("D", 640, y, TAleft, 0, NULL, false); y += 5;
	font.writeText("ark bavor devint donc un meurbood,", 670, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("melange des deux races boodies et", 670, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("meuries. de par sa double personnalite,", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("celui ci ne supporta plus de n'etre qu'un", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("demi roi, ne controlant que le territoire", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("meuries.", 660, y, TAleft, 0, NULL, false); y += 12;

	bMoveImage = true;
}

void DstroyIntro::setPage8(void)
{
	this->deleteAllObjects();

	TGIuint16 i;
	for (i=0;i<vecSurface.size();i++)
	{
		delete vecSurface[i];
	}
	vecSurface.clear();

	

	TGISurface* pSurface = new TGISurface;
	pSurface->loadImage(DstroyGlobals::addResText("int8.pcx"));
	vecSurface.push_back(pSurface);

	TGIObject* pObject;
	pObject = new TGIObject;
	
	TGISprite sprite;
	sprite.setSurface(vecSurface[vecSurface.size()-1]);
	sprite.setPlacement(0, 0, 320, 200);
	pObject->addSprite(sprite);
	pObject->bVisible = true;
	pObject->setPos(320, 0);
	pObject->lId = 1;
	addObject(pObject, 10);

	TGIuint16 y = 41;
	font.writeText("D", 640, y, TAleft, 0, NULL, false); y += 5;
	font.writeText("ark bavor decida donc d'envoyer ses", 670, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("troupes meuries envahir le joli pays", 670, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("boodies. surpris par cette attaque,", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("les boodies ne purent se defendre et", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("furent rapidement vaincus!", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("ainsi, les noirs dessins malefiques de", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("dark bavor furent realises et la terreur", 650, y, TAleft, 0, NULL, false); y += 12;
	font.writeText("se mit a regner.", 650, y, TAleft, 0, NULL, false); y += 12;

	bMoveImage = true;
}


bool DstroyIntro::exit(void)
{
	DstroyIntro2* pIntro = new DstroyIntro2;

	return TGIMain::exit();
}
