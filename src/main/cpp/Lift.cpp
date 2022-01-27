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
	m_pLiftMotor1		= new WPI_TalonFX(nLiftMotor1);
	m_pLiftMotor2		= new WPI_TalonFX(nLiftMotor2);
	m_pLiftMotor3		= new WPI_TalonFX(nLiftMotor3);
	m_pLiftMotor4		= new WPI_TalonFX(nLiftMotor4);
	m_pLeftSolenoid		= new Solenoid(PneumaticsModuleType::CTREPCM, nSolenoid1);
	m_pRightSolenoid	= new Solenoid(PneumaticsModuleType::CTREPCM, nSolenoid2);
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
	delete m_pLiftMotor3;
	delete m_pLiftMotor4;
	
	m_pLiftMotor1		= nullptr;
	m_pLiftMotor2		= nullptr;
	m_pLiftMotor3		= nullptr;
	m_pLiftMotor4		= nullptr;
}

/******************************************************************************
	Description:	CLift Init - init motors and solenoids
	Arguments:		None
	Returns:		Nothing
******************************************************************************/
void CLift::Init() 
{
	
}