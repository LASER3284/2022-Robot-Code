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
	m_bIdle					= true;
}		

/******************************************************************************
	Description:	CShooter destructor, delete variables
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
	Description:	Bring the flywheel to a stop completely
	Arguments:		None
	Derived from:	Nothing
******************************************************************************/
void CShooter::Stop()
{
	m_pFlywheelMotor1->Set(0.000);
	m_bShooterOn = false;
}

/******************************************************************************
	Description:	Set the member safety variable
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

	SmartDashboard::PutNumber("dExpectedShotVelocity", m_dExpectedShotVelocity);
	SmartDashboard::PutNumber("dExpectedIdleVelocity", m_dExpectedIdleVelocity);
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
		m_pFlywheelMotor1->Set(ControlMode::Velocity, m_dExpectedShotVelocity);
		m_bShooterOn = true;
		m_bIdle = false;
	}
	else IdleStop();
}

/******************************************************************************
	Description:	Idle the flywheel
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CShooter::IdleStop() {
	if(!m_bSafety) {
		m_pFlywheelMotor1->Set(ControlMode::Velocity, m_dExpectedIdleVelocity);
		m_bShooterOn = true;
		m_bIdle = true;
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
	double dVelocityDiff = abs(dMotor1Velocity - m_dExpectedShotVelocity);
	m_bShooterFullSpeed = (dVelocityDiff < 100);
}

/******************************************************************************
	Description:	Change the base speed of the flywheel in percentage of dVelocityPercent
	Arguments:		double dVelocityPercent - percentage to change base by
	Returns:		Nothing
******************************************************************************/
void CShooter::AdjustVelocity(double dVelocityPercent) {
	m_dFlywheelMotorSpeed += dVelocityPercent;
	m_dIdleMotorSpeed += dVelocityPercent;

    m_dExpectedShotVelocity = m_dPeakSensorVelocity * m_dFlywheelMotorSpeed;
    m_dExpectedIdleVelocity = m_dPeakSensorVelocity * m_dIdleMotorSpeed;

	SmartDashboard::PutNumber("dExpectedShotVelocity", m_dExpectedShotVelocity);
	SmartDashboard::PutNumber("dExpectedIdleVelocity", m_dExpectedIdleVelocity);

	if(m_bIdle) m_pFlywheelMotor1->Set(ControlMode::Velocity, m_dExpectedIdleVelocity);
	else m_pFlywheelMotor1->Set(ControlMode::Velocity, m_dExpectedShotVelocity);
}

/******************************************************************************
	Description:	Resets the base shoot / idle velocity
	Arguments:		Nothing
	Returns:		Nothing
******************************************************************************/
void CShooter::ResetVelocity() {
	m_dFlywheelMotorSpeed = m_dDefaultFlywheelSpeed;
	m_dIdleMotorSpeed = m_dDefaultIdleSpeed;

    m_dExpectedShotVelocity = m_dPeakSensorVelocity * m_dFlywheelMotorSpeed;
    m_dExpectedIdleVelocity = m_dPeakSensorVelocity * m_dIdleMotorSpeed;

	SmartDashboard::PutNumber("dExpectedShotVelocity", m_dExpectedShotVelocity);
	SmartDashboard::PutNumber("dExpectedIdleVelocity", m_dExpectedIdleVelocity);

	if(m_bIdle) m_pFlywheelMotor1->Set(ControlMode::Velocity, m_dExpectedIdleVelocity);
	else m_pFlywheelMotor1->Set(ControlMode::Velocity, m_dExpectedShotVelocity);
}