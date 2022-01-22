/****************************************************************************
	Description:	Implements the Poses used for autonomous.
	Classes:		CTrajectoryConstants
	Project:		2022 Rapid React Robot Code
****************************************************************************/

#include "TrajectoryConstants.h"

///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
    Description:	Set selected trajectory based on enumerator
	Arguments:		int nSelection
	Derived from:	Nothing
******************************************************************************/
void CTrajectoryConstants::SelectTrajectory(int nSelection)
{
	switch(nSelection)
	{
		case eTestPath:
			// Read and store the trajectory from a pre-generated JSON file
			m_SelectedPath = TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/paths/output/TestPath.wpilib.json");
			break;

		case eAdvancement:
			// Read and store the trajectory from a pre-generated JSON file
			m_SelectedPath = TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/paths/output/Advancement.wpilib.json");
			break;
			
		default:
			// Read and store the trajectory from a pre-generated JSON file
			m_SelectedPath = TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/paths/output/TestPath.wpilib.json");
			break;
	}
}

/******************************************************************************
    Description:	Set selected trajectory based on new trajectory
	Arguments:		Trajectory Path
	Derived from:	Nothing
******************************************************************************/
void CTrajectoryConstants::SelectTrajectory(Trajectory Path)
{
	m_SelectedPath = Path;
}