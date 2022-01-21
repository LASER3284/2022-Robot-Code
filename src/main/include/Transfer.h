
/******************************************************************************
		Description:            CTransfer implementation
	Classes:                CTransfer
	Project:	        2022 Rapid React Robot Code
******************************************************************************/

#ifndef Transfer_h
#define Transfer_h

#include "IOMap.h"
#include "SparkMotion.h"

/******************************************************************************
		Description:	        CTransfer class definition.
		Arguments:		None
		Derived From:	        Nothing
******************************************************************************/

class CTransfer {
public:
	// Declare class methods.
	CTransfer();
	~CTransfer();
	void Init();

private:
	// Declare class objects and variables.
	CSparkMotion*          m_pBeltMotor1;
	CSparkMotion*          m_pBeltMotor2;
	CSparkMotion*          m_pBeltMotor3;
};

//////////////////////////////////////////////////////////////////////////////
#endif
