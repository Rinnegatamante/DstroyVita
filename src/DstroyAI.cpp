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
#include "DstroyAI.h"

#include "DstroyGame.h"
#include <math.h>
#include <string.h>

DstroyAI::DstroyAI(void)
{
	matrixRisk = NULL;
	matrixRiskAdvanced = NULL;
}

DstroyAI::~DstroyAI(void)
{
	if (matrixRisk)
	{
		delete [] matrixRisk;
		matrixRisk = NULL;

		delete [] matrixRiskAdvanced;
		matrixRiskAdvanced = NULL;
	}
}

void DstroyAI::init(TGIuint16 nWidth, TGIuint16 nHeight)
{
	if (matrixRisk)
	{
		delete [] matrixRisk;
		matrixRisk = NULL;

		delete [] matrixRiskAdvanced;
		matrixRiskAdvanced = NULL;
	}

	this->nWidth = nWidth;
	this->nHeight = nHeight;

	matrixRisk = new TGIuint8[nWidth*nHeight];
	matrixRiskAdvanced = new TGIuint8[nWidth*nHeight];
}

void DstroyAI::setRisk(TGIuint16 x, TGIuint16 y, TGIuint8 nRisk, bool bAdvanced)
{
	if (x<0 || x>=nWidth || y<0 || y>=nHeight)
		return;

	if (!bAdvanced)
	{
		if (nRisk > matrixRisk[y*nWidth + x])
			matrixRisk[y*nWidth + x] = nRisk;
	}
	else
	{
		if (nRisk > matrixRiskAdvanced[y*nWidth + x])
			matrixRiskAdvanced[y*nWidth + x] = nRisk;
	}
}

TGIuint8 DstroyAI::getRisk(TGIuint16 x, TGIuint16 y, bool bAdvanced)
{
	if (x<0 || x>=nWidth || y<0 || y>=nHeight)
		return 255;

	if (!bAdvanced)
		return matrixRisk[y*nWidth + x];
	else
		return matrixRiskAdvanced[y*nWidth + x];
}

void DstroyAI::calculateRisk()
{
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;
	//TGIuint16 i;
	register std::list<DstroyBomb*>::iterator itBomb;

	memset(matrixRisk, 0, nWidth*nHeight*sizeof(TGIuint8));
	memset(matrixRiskAdvanced, 0, nWidth*nHeight*sizeof(TGIuint8));

	//for (i=0;i<pGame->vecBomb.size();i++)
	for (itBomb=pGame->vecBomb.begin();itBomb!=pGame->vecBomb.end();itBomb++)
	{
		//si la bombe ne pete pas tout de suite, on la regarde pas
		if ((*itBomb)->nDurationLeft > 2)
			continue;

		calculateRisk((*itBomb)->gridX(), (*itBomb)->gridY(), (*itBomb)->nDurationLeft, (*itBomb)->nFlames, false);
		//calculateRisk((*itBomb)->gridX(), (*itBomb)->gridY(), (*itBomb)->nDurationLeft, (*itBomb)->nFlames, true);
		
	}
}

void DstroyAI::calculateRisk(TGIuint16 x, TGIuint16 y, TGIuint8 nDuration, TGIuint16 lim, bool bAdvanced)
{
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;
	register TGIuint16 j;
	bool bContinue;
	std::list<DstroyItem*> listObject;
	register std::list<DstroyItem*>::iterator itObject;
	TGIuint8 nRiskMax;

	nRiskMax = 255 - (nDuration*64);

	//centre
	setRisk(x, y, nRiskMax, bAdvanced);

	//gauche		
	bContinue = true;
	for (j=1;j<=lim && bContinue;j++)
	{
		pGame->getObjectsOnPos(NULL, x - j, y, listObject);
		//for (k=0;k<vecObject.size();k++)
		for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
		{
			if (bAdvanced && (*itObject)->classId == CLASSID_BOMB && getRisk((*itObject)->gridX(), (*itObject)->gridY(), bAdvanced) < nRiskMax)
			{
				calculateRisk((*itObject)->gridX(), (*itObject)->gridY(), nDuration, ((DstroyBomb*)(*itObject))->nFlames, bAdvanced);
			}
			if ((*itObject)->isPlain())
			{
				bContinue = false;
				break;
			}			
		}
		if (bContinue)
		{
			setRisk(x - j, y, nRiskMax - j, bAdvanced);
		}
	}
	//droite
	bContinue = true;
	for (j=1;j<=lim && bContinue;j++)
	{
		pGame->getObjectsOnPos(NULL, x + j, y, listObject);
		for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
		{
			if (bAdvanced && (*itObject)->classId == CLASSID_BOMB && getRisk((*itObject)->gridX(), (*itObject)->gridY(), bAdvanced) < nRiskMax)
			{
				calculateRisk((*itObject)->gridX(), (*itObject)->gridY(), nDuration, ((DstroyBomb*)(*itObject))->nFlames, bAdvanced);
			}
			if ((*itObject)->isPlain())
			{
				bContinue = false;
				break;
			}			
		}
		if (bContinue)
		{
			setRisk(x + j, y, nRiskMax - j, bAdvanced);
		}
	}
	//haut
	bContinue = true;
	for (j=1;j<=lim && bContinue;j++)
	{
		pGame->getObjectsOnPos(NULL, x, y - j, listObject);
		for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
		{
			if (bAdvanced && (*itObject)->classId == CLASSID_BOMB && getRisk((*itObject)->gridX(), (*itObject)->gridY(), bAdvanced) < nRiskMax)
			{
				calculateRisk((*itObject)->gridX(), (*itObject)->gridY(), nDuration, ((DstroyBomb*)(*itObject))->nFlames, bAdvanced);
			}
			if ((*itObject)->isPlain())
			{
				bContinue = false;
				break;
			}			
		}
		if (bContinue)
		{
			setRisk(x, y - j, nRiskMax - j, bAdvanced);
		}
	}
	//bas
	bContinue = true;
	for (j=1;j<=lim && bContinue;j++)
	{
		pGame->getObjectsOnPos(NULL, x, y + j, listObject);
		for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
		{
			if (bAdvanced && (*itObject)->classId == CLASSID_BOMB && getRisk((*itObject)->gridX(), (*itObject)->gridY(), bAdvanced) < nRiskMax)
			{
				calculateRisk((*itObject)->gridX(), (*itObject)->gridY(), nDuration, ((DstroyBomb*)(*itObject))->nFlames, bAdvanced);
			}
			if ((*itObject)->isPlain())
			{
				bContinue = false;
				break;
			}
		}
		if (bContinue)
		{
			setRisk(x, y + j, nRiskMax - j, bAdvanced);
		}
	}
}


void DstroyAI::think(DstroyMonster* pMonster)
{
	DstroyGame* pGame = (DstroyGame*)TGIGlobals::theMain;
	std::list<DstroyItem*> listObject;
	register TGIuint16 i,j;
	register std::list<DstroyItem*>::iterator itObject;
	bool bInserted;
	bool bCanGo;
	bool bAdvanced = false;
	Direction bestDir;


	if (pMonster->X() != pMonster->gridX()*pMonster->width || pMonster->Y() != pMonster->gridY()*pMonster->height)
	{
		//n'est pas sur une case précise, continue dans la meme direction
		return;
	}

	//la direction qu'on préférerait ne pas prendre (revenir en arriere)
	Direction badDir=stand;
	if (pMonster->nIA != 2 && pMonster->nIA != 4)
	{
		switch (pMonster->dirMoving)
		{
		case up:
			badDir = down;
			break;
		case down:
			badDir = up;
			break;
		case left:
			badDir = right;
			break;
		case right:
			badDir = left;
			break;
		}
	}

	//ou peut-on aller
	std::vector< std::pair<Direction, TGIuint8> > vecDir;
	std::pair<Direction, TGIuint8> pairDir;

	//vecDir.reserve(4);

	if (pMonster->nIA != 0)
	{
		//on calcule le risque si on est malin
		//calculateRisk();
		if (pMonster->nIA <= 2)
		{
			bAdvanced = false;
		}
		else
		{
			bAdvanced = true;
		}

		//on peut rester en place si on est malin et si on a pas le choix
		pairDir.first = stand;
		pairDir.second = getRisk(pMonster->gridX(), pMonster->gridY(), bAdvanced);
		vecDir.push_back(pairDir);
	}
	//on regarde ou on peut aller par rapport aux murs, et on calcule le risque pr chaque direction
	//left
	{
		pGame->getObjectsOnPos(NULL, pMonster->gridX()-1, pMonster->gridY(), listObject);
		bCanGo = true;
		//for (i=0;i<vecObject.size();i++)
		for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
		{
			if ((*itObject)->isPlain() || (*itObject)->classId == CLASSID_EXPLOSION)
			{
				bCanGo = false;
				break;
			}
		}
		if (bCanGo)
		{
			pairDir.first = left;
			pairDir.second = getRisk(pMonster->gridX()-1, pMonster->gridY(), bAdvanced);
			bInserted = false;
			for (j=0;j<vecDir.size();j++)
			{
				if (vecDir[j].second > pairDir.second)
				{
					vecDir.insert(vecDir.begin()+j, pairDir);
					bInserted = true;
					break;
				}
			}
			if (!bInserted)
				vecDir.push_back(pairDir);
		}
			
	}
	//down
	{
		pGame->getObjectsOnPos(NULL, pMonster->gridX(), pMonster->gridY()+1, listObject);
		bCanGo = true;
		for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
		{
			if ((*itObject)->isPlain() || (*itObject)->classId == CLASSID_EXPLOSION)
			{
				bCanGo = false;
				break;
			}
		}
		if (bCanGo)
		{
			pairDir.first = down;
			pairDir.second = getRisk(pMonster->gridX(), pMonster->gridY()+1, bAdvanced);
			bInserted = false;
			for (j=0;j<vecDir.size();j++)
			{
				if (vecDir[j].second > pairDir.second)
				{
					vecDir.insert(vecDir.begin()+j, pairDir);
					bInserted = true;
					break;
				}
			}
			if (!bInserted)
				vecDir.push_back(pairDir);
		}
	}
	//right
	{
		pGame->getObjectsOnPos(NULL, pMonster->gridX()+1, pMonster->gridY(), listObject);
		bCanGo = true;
		for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
		{
			if ((*itObject)->isPlain() || (*itObject)->classId == CLASSID_EXPLOSION)
			{
				bCanGo = false;
				break;
			}
		}
		if (bCanGo)
		{
			pairDir.first = right;
			pairDir.second = getRisk(pMonster->gridX()+1, pMonster->gridY(), bAdvanced);
			bInserted = false;
			for (j=0;j<vecDir.size();j++)
			{
				if (vecDir[j].second > pairDir.second)
				{
					vecDir.insert(vecDir.begin()+j, pairDir);
					bInserted = true;
					break;
				}
			}
			if (!bInserted)
				vecDir.push_back(pairDir);
		}
	}
	//up
	{
		pGame->getObjectsOnPos(NULL, pMonster->gridX(), pMonster->gridY()-1, listObject);
		bCanGo = true;
		for (itObject=listObject.begin();itObject!=listObject.end();itObject++)
		{
			if ((*itObject)->isPlain() || (*itObject)->classId == CLASSID_EXPLOSION)
			{
				bCanGo = false;
				break;
			}
		}
		if (bCanGo)
		{
			pairDir.first = up;
			pairDir.second = getRisk(pMonster->gridX(), pMonster->gridY()-1, bAdvanced);
			bInserted = false;
			for (j=0;j<vecDir.size();j++)
			{
				if (vecDir[j].second > pairDir.second)
				{
					vecDir.insert(vecDir.begin()+j, pairDir);
					bInserted = true;
					break;
				}
			}
			if (!bInserted)
				vecDir.push_back(pairDir);
		}
	}


	if (pMonster->nIA == 0)
	{
		if (vecDir.empty())
		{
			pMonster->go(stand);
			return;
		}
	}	
	
	if (pMonster->nIA > 0)
	{
		//on ne va pas la ou le risque est plus grand qu'ailleurs
		for (j=(TGIuint16)vecDir.size()-1;j>0;j--)
		{
			if (vecDir[j].second > vecDir[0].second)
			{
				vecDir.pop_back();
			}
		}
	}
	
	//on supprime maintenant le stand
	if (vecDir.size() > 1)
	{
		for (j=0;j<vecDir.size();j++)
		{
			if (vecDir[j].first == stand)
			{
				vecDir.erase(vecDir.begin() + j);
			}
		}
	}
	//et le bad dir
	if (vecDir.size() > 1 && badDir != stand)
	{
		for (j=0;j<vecDir.size();j++)
		{
			if (vecDir[j].first == badDir)
			{
				vecDir.erase(vecDir.begin() + j);
			}
		}
	}
	//S'il n'y a qu'une seule solution, on y va!
	if (vecDir.size() == 1)
	{
		pMonster->go(vecDir[0].first);
		return;
	}

	//ou veut il aller
	bestDir = vecDir[rand() % (TGIuint16)vecDir.size()].first;
	double nDistance = 65000.0, d;
	if (pMonster->nIA == 2 || pMonster->nIA == 4)
	{
		//c'est un suiveur, donc il cherche a s'approcher du joueur le plus proche
		i = 0;
		for (j=0;j<DstroyGame::params.nPlayers;j++)
		{
			if (pGame->pdsPlayer[j]->bAlive)
			{
				d = distance(pMonster->gridX(), pMonster->gridY(), pGame->pdsPlayer[j]);
				if (d < nDistance)
				{
					i = j;
					nDistance = d;
				}
			}
		}

		//quel est le plus court chemin?
		nDistance = 65000.0;
		for (j=0;j<vecDir.size();j++)
		{
			if (vecDir[j].first == left)
			{
				d = distance(pMonster->gridX()-1, pMonster->gridY(), pGame->pdsPlayer[i]);
				if (d < nDistance)
				{
					bestDir = left;
					nDistance = d;
				}
			}
			if (vecDir[j].first == right)
			{
				d = distance(pMonster->gridX()+1, pMonster->gridY(), pGame->pdsPlayer[i]);
				if (d < nDistance)
				{
					bestDir = right;
					nDistance = d;
				}
			}
			if (vecDir[j].first == up)
			{
				d = distance(pMonster->gridX(), pMonster->gridY()-1, pGame->pdsPlayer[i]);
				if (d < nDistance)
				{
					bestDir = up;
					nDistance = d;
				}
			}
			if (vecDir[j].first == down)
			{
				d = distance(pMonster->gridX(), pMonster->gridY()+1, pGame->pdsPlayer[i]);
				if (d < nDistance)
				{
					bestDir = down;
					nDistance = d;
				}
			}
		}
	}

	pMonster->go(bestDir);
}

double DstroyAI::distance(TGIuint16 x, TGIuint16 y, DstroyItem* pItem2)
{
	double t1, t2;
	t1 = (x-pItem2->gridX());
	t2 = (y-pItem2->gridY());
	return sqrt(t1*t1 + t2*t2);
}

