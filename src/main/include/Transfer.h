
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
	CANSparkMax*          m_pTopBeltMotor;
	CANSparkMax*          m_pFrontBeltMotor;
	CANSparkMax*          m_pBackBeltMotor;
};

//////////////////////////////////////////////////////////////////////////////
#endif
