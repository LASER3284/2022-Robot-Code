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
	Trajectory path;
	switch(nSelection)
	{
		case eTestPath:
			// Read and store the trajectory from a pre-generated JSON file
			path = TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/paths/output/TestPath.wpilib.json");
			break;

		case eAdvancement1:
			// Read and store the trajectory from a pre-generated JSON file
			path = TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/paths/output/Advancement1.wpilib.json");
			break;
			
		case eAdvancement2:
			// Read and store the trajectory from a pre-generated JSON file
			path = TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/paths/output/Advancement2.wpilib.json");
			break;
		
		default:
			// Read and store the trajectory from a pre-generated JSON file
			path = TrajectoryUtil::FromPathweaverJson("/home/lvuser/deploy/paths/output/TestPath.wpilib.json");
			break;
	}

	m_pSelectedPath = (Trajectory*)malloc(sizeof(path) + 1);
	memcpy(m_pSelectedPath, &path, sizeof(path) + 1);
}

/******************************************************************************
    Description:	Set selected trajectory based on new trajectory
	Arguments:		Trajectory Path
	Derived from:	Nothing
******************************************************************************/
void CTrajectoryConstants::SelectTrajectory(Trajectory Path)
{
	free(m_pSelectedPath);
	
	m_pSelectedPath = (Trajectory*)malloc(sizeof(Path));
	memcpy(m_pSelectedPath, &Path, sizeof(Path));
}