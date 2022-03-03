
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
#include <frc/filter/Debouncer.h>

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
	void StartVerticalShot();
	void StartFront();
	void StartBack();
	void StopVertical();
	void StopFront();
	void StopBack();
	void UpdateLocations();

	// Arranged Vertical, Front, Back
	bool m_aBallLocations[3] = {false, false, false};
	bool m_bBallLocked = false;
private:
	// Declare class objects and variables.

	DigitalInput*		m_pTopInfrared;
	Debouncer*			m_pTopInfraredDebouncer;

	DigitalInput*		m_pFrontInfrared;
	DigitalInput*		m_pBackInfrared;

	CANSparkMax*		m_pTopMotor;
	CANSparkMax*		m_pFrontMotor;
	CANSparkMax*		m_pBackMotor;
	int 				m_nBallCount = 0;
};

//////////////////////////////////////////////////////////////////////////////
#endif
