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
	int m_iScore;
	bool m_bParent;

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
		return m_iScore;
	}

	void setPScore(int pScore) {
		m_iScore = pScore;
	}

	bool isBParent() const {
		return m_bParent;
	}

	void setBParent(bool bParent) {
		m_bParent = bParent;
	}
};



#endif /* CLASSES_SOURCES_LMUSER_H_ */
