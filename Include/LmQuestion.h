/*
 * LmQuestion.h
 *
 *  Created on: 29 sept. 2015
 *      Author: IHMTEKDev4
 */

#ifndef CLASSES_INCLUDE_LMQUESTION_H_
#define CLASSES_INCLUDE_LMQUESTION_H_

#include <string>


class LmQuestion
{
public:

	LmQuestion();
	~LmQuestion();

	int getINumberGoodAnswer() const
	{
		return m_iNumberGoodAnswer;
	}

	const std::string& getSAnswer1() const
	{
		return m_sAnswer1;
	}

	const std::string& getSAnswer2() const
	{
		return m_sAnswer2;
	}

	const std::string& getSAnswer3() const
	{
		return m_sAnswer3;
	}

	const std::string& getSAnswer4() const
	{
		return m_sAnswer4;
	}

	const std::string& getSQuestion() const
	{
		return m_sQuestion;
	}

private:

	std::string m_sQuestion;
	std::string m_sAnswer1;
	std::string m_sAnswer2;
	std::string m_sAnswer3;
	std::string m_sAnswer4;

	int m_iNumberGoodAnswer;
};

#endif /* CLASSES_INCLUDE_LMQUESTION_H_ */
