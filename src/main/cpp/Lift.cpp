/******************************************************************************
	Description:	Implements the CLift control class.
	Classes:		CLift
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "Lift.h"
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
	Description:	CLift constructor - init local variables/classes
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
CLift::CLift()
{
	m_pLiftMotor1 		= new WPI_TalonFX(nLiftMotor1);
	m_pLiftMotor2 		= new WPI_TalonFX(nLiftMotor2);
	m_pLeftSolenoid		= new Solenoid(nPCM1, PneumaticsModuleType::CTREPCM, nSolenoid1);
	m_pRightSolenoid	= new Solenoid(nPCM2, PneumaticsModuleType::CTREPCM, nSolenoid1);
}

/******************************************************************************
	Description:	CLift destructor - delete local variables/classes
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
CLift::~CLift()
{
	delete m_pLiftMotor1;
	delete m_pLiftMotor2;
	
	m_pLiftMotor1		= nullptr;
	m_pLiftMotor2		= nullptr;
}

/******************************************************************************
   	Description: 	Init - Called once when the robot is initially turned on.
	Arguments: 		None
	Returns: 		Nothing
******************************************************************************/
void CLift::Init() 
{
	m_pLeftSolenoid->Set(false);
	m_pRightSolenoid->Set(false);
}

/******************************************************************************
   	Description: 	CLift extension - extends lift arm
	Arguments: 		None
	Returns: 		Nothing
******************************************************************************/
void CLift::ExtendArms()
{
	if((m_pLiftMotor1 -> GetSelectedSensorPosition()/nCounterRev)<=dCountToMAX)
	{
    	m_pLiftMotor1 -> Set(1.0);
		m_pLiftMotor2 -> Set(1.0);
	}
	else
	{
		m_pLiftMotor1 -> Set(0.0);
		m_pLiftMotor2 -> Set(0.0);
	}
}

/******************************************************************************
   	Description: 	CLift retraction - retracts lift arm
	Arguments: 		None
	Returns: 		Nothing
******************************************************************************/
void CLift::Retract()
{
	if((m_pLiftMotor1 -> GetSelectedSensorPosition()/nCounterRev)>0)
	{
    	m_pLiftMotor1 -> Set(-1.0);
		m_pLiftMotor2 -> Set(-1.0);
	}
	else
	{
		m_pLiftMotor1 -> Set(0.0);
		m_pLiftMotor2 -> Set(0.0);
	}
}

/******************************************************************************
   	Description: 	CLift SwingArms - pneumatic hook extends
	Arguments: 		None
	Returns: 		Nothing
******************************************************************************/
void CLift::SwingArms()
{
	m_pLeftSolenoid->Set(true);
	m_pRightSolenoid->Set(true);
}

/******************************************************************************
   	Description: 	CLift Unswing - pneumatic hook retracts
	Arguments: 		None
	Returns: 		Nothing
******************************************************************************/
void CLift::Unswing()
{
	m_pLeftSolenoid->Set(false);
	m_pRightSolenoid->Set(false);
}
