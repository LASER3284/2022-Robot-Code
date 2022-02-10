/******************************************************************************
	Description:	Defines the Vision control class
	Classes:		VisionPacket 
	Project:		2022 Rapid React Robot Code
******************************************************************************/

#ifndef Vision_h
#define Vison_h

class VisionPacket {
public:
    VisionPacket();
    VisionPacket(const char* pPacketArr);
    ~VisionPacket();

    char m_randVal = 0xFF;
    char m_detectionCount = 0xFF;

    short m_x;
    short m_y;
    short m_width;
    short m_height;

    char m_confidence;
    unsigned char m_class;
    int m_depth;
};

#endif