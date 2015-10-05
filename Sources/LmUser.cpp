/*
 * LmUser.cpp
 *
 *  Created on: 9 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmUser.h"

LmUser::LmUser()
{

	//primitive type
	m_iScore = 0;
	m_bMale = true;

	//pointer
	m_pUserName = nullptr;
	m_pUserTabletName = nullptr;
	m_bParent=nullptr;


}

LmUser::~LmUser()
{

}

void LmUser::addToScore(int points)
{
	m_iScore += points;
}
