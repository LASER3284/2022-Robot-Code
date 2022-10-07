
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
	void ReverseVertical();
	void StopVertical();

	void StartBack();
	void ReverseBack();

	void StopBack();
	void UpdateLocations();

	// Arranged Vertical, Back
	bool m_aBallLocations[2] = {false, false};
private:
	// Declare class objects and variables.
	DigitalInput*		m_pTopInfrared;
	DigitalInput*		m_pBackInfrared;

	CANSparkMax*		m_pTopMotor;
	CANSparkMax*		m_pBackMotor;
	int 				m_nBallCount = 0;

	Debouncer*			m_pTopDebouncer;
	Debouncer*			m_pBackDebouncer;
};

//////////////////////////////////////////////////////////////////////////////
#endif
