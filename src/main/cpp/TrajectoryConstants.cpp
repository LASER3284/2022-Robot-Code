/****************************************************************************
	Description:	Implements the Poses used for autonomous.
	Classes:		CTrajectoryConstants
	Project:		2022 Rapid React Robot Code
****************************************************************************/

#include "TrajectoryConstants.h"

#include <pathplanner/lib/PathPlanner.h>
using namespace pathplanner;

///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
    Description:	Set selected trajectory based on enumerator
	Arguments:		int nSelection
	Derived from:	Nothing
******************************************************************************/
void CTrajectoryConstants::SelectTrajectory(int nSelection)
{
	Trajectory path;
	string pathPath = m_mpPathFileName.at((Paths)nSelection);
	path = TrajectoryUtil::FromPathweaverJson(pathPath);

	m_pSelectedPath = new Trajectory(path);
}

/******************************************************************************
    Description:	Set selected trajectory based on new trajectory
	Arguments:		Trajectory Path
	Derived from:	Nothing
******************************************************************************/
void CTrajectoryConstants::SelectTrajectory(Trajectory Path)
{
	free(m_pSelectedPath);
	m_pSelectedPath = new Trajectory(Path);
}