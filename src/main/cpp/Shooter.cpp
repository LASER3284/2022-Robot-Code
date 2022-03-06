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
CShooter::CShooter() {
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
	m_bShooterOn = false;
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
	m_pFlywheelMotor1->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor);
	m_pFlywheelMotor1->Config_kP(0, m_dPropotional);
	m_pFlywheelMotor1->Config_kI(0, m_dIntegral);
	m_pFlywheelMotor1->Config_kD(0, m_dDerivative);
	m_pFlywheelMotor1->Config_kF(0, m_dFeedForward);
	m_pFlywheelMotor1->ConfigClosedloopRamp(5.500);

	m_pFlywheelMotor2->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor);
	m_pFlywheelMotor2->ConfigClosedloopRamp(5.500);
	m_pFlywheelMotor2->Config_kP(0, m_dPropotional);
	m_pFlywheelMotor2->Config_kI(0, m_dIntegral);
	m_pFlywheelMotor2->Config_kD(0, m_dDerivative);
	m_pFlywheelMotor2->Config_kF(0, m_dFeedForward);

	m_pFlywheelMotor2->Follow(*m_pFlywheelMotor1);
	m_pFlywheelMotor2->SetInverted(true);
	m_bShooterOn = false;
	m_bShooterFullSpeed = false;

	SmartDashboard::PutNumber("dExpectedShotVelocity", dExpectedShotVelocity);
	SmartDashboard::PutNumber("dExpectedIdleVelocity", dExpectedIdleVelocity);
}

/******************************************************************************
	Description:	Start the flywheel at one hundred percent
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CShooter::StartFlywheelShot()
{
	if (!m_bSafety) 
	{
		m_pFlywheelMotor1->Set(ControlMode::Velocity, dExpectedShotVelocity);
		m_bShooterOn = true;
	}
	else Stop();
}

void CShooter::IdleStop() {
	if(!m_bSafety) {
		m_pFlywheelMotor1->Set(ControlMode::Velocity, dExpectedIdleVelocity);
		m_bShooterOn = true;
	}
	else Stop();
}

/******************************************************************************
	Description:	A tick function that checks the speed of the flywheel to see if it is at full speed.
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CShooter::Tick() {
	double dMotor1Velocity = m_pFlywheelMotor1->GetSelectedSensorVelocity();
	SmartDashboard::PutNumber("dMotor1Velocity", dMotor1Velocity);
	double dVelocityDiff = abs(dMotor1Velocity - dExpectedShotVelocity);
	m_bShooterFullSpeed = (dVelocityDiff < 100);
}