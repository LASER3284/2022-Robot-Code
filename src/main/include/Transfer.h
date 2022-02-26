
/******************************************************************************
	Description:            CTransfer implementation
	Classes:                CTransfer
	Project:	        	2022 Rapid React Robot Code
******************************************************************************/

#ifndef Transfer_h
#define Transfer_h

#include "IOMap.h"

#include <rev/CANSparkMax.h>
#include <frc/DigitalInput.h>

using namespace frc;
using namespace rev;
using namespace units;
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
	void StartVertical();
	void StartFront();
	void StartBack();
	void StopVertical();
	void StopFront();
	void StopBack();
	void UpdateLocations();

	// Arranged Vertical, Front, Back
	bool m_aBallLocations[3] = { false, false, false };
	time::second_t  m_nTransferStartTime = time::second_t(0);

private:
	// Declare class objects and variables.
	DigitalInput*		m_pTopInfrared;
	DigitalInput*		m_pFrontInfrared;
	DigitalInput*		m_pBackInfrared;

	CANSparkMax*		m_pTopMotor;
	CANSparkMax*		m_pFrontMotor;
	CANSparkMax*		m_pBackMotor;
};

//////////////////////////////////////////////////////////////////////////////
#endif
