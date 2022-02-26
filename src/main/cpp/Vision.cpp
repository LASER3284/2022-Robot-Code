/******************************************************************************
    Description:	CVisionPacket implementation
	Class:			CVisionPacket
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#include "Vision.h"
#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>

using namespace frc;
///////////////////////////////////////////////////////////////////////////////

CVisionPacket::CVisionPacket(const char* pPacketArr, unsigned int length)
{
	// Allocate the packet data
	m_pRawPacket = (char*)malloc(length);
	// Copy the packet (allocated on the stack) to a new array.
	memcpy((void*)m_pRawPacket, (void*)pPacketArr, length);
	
	// Read in the actual data from the packet.
	m_nRandVal = m_pRawPacket[0];
	m_nDetectionCount = m_pRawPacket[1];
}

CVisionPacket::CVisionPacket()
{
	m_nRandVal = 0xFF;
	m_nDetectionCount = 0xFF;
	m_kDetectionLocation = DetectionLocation::eNONE;
	m_pDetections = nullptr;
	m_pRawPacket = nullptr;
 }

CVisionPacket::~CVisionPacket()
{
	free(m_pRawPacket);
}

void CVisionPacket::ParseDetections()
{
	m_kDetectionLocation = (DetectionLocation)m_pRawPacket[0];
	// Preallocate the array
	m_pDetections = (sObjectDetection**)malloc(m_nDetectionCount * sizeof(sObjectDetection));
	for(int i = 0; i < m_nDetectionCount; i++) {
		// Get the offset that we are into the packet.
		int packetOffset = 3 + (i * sizeof(sObjectDetection));
		m_pDetections[i] = new sObjectDetection(m_pRawPacket, packetOffset);
	}
}