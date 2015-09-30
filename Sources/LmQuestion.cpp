/*
 * LmQuestion.cpp
 *
 *  Created on: 29 sept. 2015
 *      Author: IHMTEKDev4
 */

#include "../Include/LmQuestion.h"

LmQuestion::LmQuestion(std::string l_sAnswer1, std::string l_sAnswer2,
		std::string l_sAnswer3, std::string l_sAnswer4, int l_iNumberGoodAnswer,
		std::string l_sQuestion)
{
	m_sAnswer1 = l_sAnswer1;
	m_sAnswer2 = l_sAnswer2;
	m_sAnswer3 = l_sAnswer3;
	m_sAnswer4 = l_sAnswer4;
	m_iNumberGoodAnswer = l_iNumberGoodAnswer;

	m_sQuestion = l_sQuestion;
}

LmQuestion::~LmQuestion()
{

}

