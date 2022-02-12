/******************************************************************************
	Description:	Defines the Vision control class
	Classes:		VisionPacket 
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#ifndef Vision_h
#define Vison_h

const double dAnglePerPixel     = 69.000 / 320.000;
enum DetectionClass {
    eBlueHangar = 0x01,
    eRedHangar,
    eHub,
    eRedCargo,
    eBlueCargo
};

class CVisionPacket {
public:
    CVisionPacket();
    CVisionPacket(const char* pPacketArr);
    ~CVisionPacket();

    char m_nRandVal = 0xFF;
    char m_nDetectionCount = 0xFF;

    short   m_nX;
    short   m_nY;
    short   m_nWidth;
    double  m_dHalfWidthAngle;
    short   m_nHeight;
    double  m_dHalfHeightAngle;

    char m_nConfidence;
    unsigned char m_uClass;
    int m_nDepth;
};

#endif