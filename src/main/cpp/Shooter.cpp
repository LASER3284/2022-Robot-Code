/******************************************************************************
    Description:	CShooter implementation
	Class:			CShooter
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "Shooter.h"
#include <frc/smartdashboard/SmartDashboard.h>
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
	Description:	CShooter constructor, init variables
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
CShooter::CShooter(Joystick* pShooterJoystick)
{
	m_pFlywheelMotor1		= new CFalconMotion(nFlywheelMotor1);
	m_pFlywheelMotor2		= new CFalconMotion(nFlywheelMotor2);
}		

/******************************************************************************
	Description:	CTransfer destructor, delete variables
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
CShooter::~CShooter()
{
	delete m_pFlywheelMotor1;		
	delete m_pFlywheelMotor2;

	m_pFlywheelMotor1		= nullptr;
	m_pFlywheelMotor2		= nullptr;	
}
