
/******************************************************************************
	Description:            CTransfer implementation
	Classes:                CTransfer
	Project:	        	2022 Rapid React Robot Code
******************************************************************************/

#ifndef Transfer_h
#define Transfer_h

#include "IOMap.h"

#include <rev/CANSparkMax.h>

using namespace rev;
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
		Description:	        CTransfer class definition.
		Arguments:				None
		Derived From:	        Nothing
******************************************************************************/

class CTransfer 
{
public:
	// Declare class methods.
	CTransfer();
	~CTransfer();
	void Init();

private:
	// Declare class objects and variables.
	CANSparkMax*          m_pBeltMotor1;
	CANSparkMax*          m_pBeltMotor2;
	CANSparkMax*          m_pBeltMotor3;
};

//////////////////////////////////////////////////////////////////////////////
#endif
