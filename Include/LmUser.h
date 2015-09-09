/*
 * LmUser.h
 *
 *  Created on: 9 sept. 2015
 *      Author: IHMTEKDev4
 *
 *      where are stocked user's data
 */

#ifndef CLASSES_SOURCES_LMUSER_H_
#define CLASSES_SOURCES_LMUSER_H_

class LmUser
{
private:

	const char* m_pUserName;
	const char* m_pUserTabletName;
	int m_pScore;

public:

	LmUser();
	~LmUser();



	const char* getPUserName() const {
		return m_pUserName;
	}

	void setPUserName(const char* pUserName) {
		m_pUserName = pUserName;
	}

	const char* getPUserTabletName() const {
		return m_pUserTabletName;
	}

	void setPUserTabletName(const char* pUserTabletName) {
		m_pUserTabletName = pUserTabletName;
	}

	int getPScore() const {
		return m_pScore;
	}

	void setPScore(int pScore) {
		m_pScore = pScore;
	}
};



#endif /* CLASSES_SOURCES_LMUSER_H_ */
