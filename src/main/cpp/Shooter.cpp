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
	m_pFlywheelMotor1		= new WPI_TalonFX(nFlywheelMotor1);
	m_pFlywheelMotor2		= new WPI_TalonFX(nFlywheelMotor2);

	m_bSafety				= true;
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

/******************************************************************************
	Description:	CTransfer destructor, delete variables
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
void CShooter::Stop()
{
	m_pFlywheelMotor1->Set(0.000);
}

/******************************************************************************
	Description:	CTransfer destructor, delete variables
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
void CShooter::SetSafety(bool bSafety)
{
	m_bSafety = bSafety;
}

/******************************************************************************
	Description:	CShooter Init function, initialize motors
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
void CShooter::Init()
{
	m_pFlywheelMotor2->Follow(*m_pFlywheelMotor1);
}

/******************************************************************************
	Description:	Start the flywheel at one hundred percent
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CShooter::StartFlywheel()
{
	if (!m_bSafety) m_pFlywheelMotor1->Set(dFlywheelMotorSpeed);
	else Stop();
}