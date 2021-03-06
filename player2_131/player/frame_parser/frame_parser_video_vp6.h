/************************************************************************
COPYRIGHT (C) STMicroelectronics R&D Ltd 2007

Source file name : frame_parser_video_vp6.h
Author :           Julian

Definition of the frame parser video vp6 class implementation for player 2.


Date        Modification                                    Name
----        ------------                                    --------
19-May_08   Created                                         Julian

************************************************************************/

#ifndef H_FRAME_PARSER_VIDEO_VP6
#define H_FRAME_PARSER_VIDEO_VP6

// /////////////////////////////////////////////////////////////////////
//
//      Include any component headers

#include "vp6.h"
#include "frame_parser_video.h"

// /////////////////////////////////////////////////////////////////////////
//
// Locally defined structures
//

#define VP6_REFERENCE_FRAMES_FOR_FORWARD_DECODE                 1

/* Range code class for accessing arithmetically coded parts of the bitstream */
class RangeCoder_c
{
protected:
    unsigned int                Data;
    int                         High;
    int                         Bits;
    unsigned char*              Buffer;

public:

    /* Initialise the pointer */
    void Init (unsigned char* Pointer)
    {
        High            = 0xff;
        Bits            = 8;
        Buffer          = Pointer;
        Data            = *Buffer++ << 8;
        Data           |= *Buffer++;
    }

    /* Retrive a single bit */
    int GetBit (void)
    {
        int                 Low             = (High + 1) >> 1;
        unsigned int        LowShift        = Low << 8;
        int                 Bit             = Data >= LowShift;

        if (Bit)
        {
            High            = (High - Low) << 1;
            Data           -= LowShift;
        }
        else
            High            = Low << 1;

        /* normalize */
        Data              <<= 1;
        if (--Bits == 0)
        {
            Bits            = 8;
            Data           |= *Buffer++;
        }
        return Bit;
    }

    int GetBits (int Bits)
    {
        int Value   = 0;

        while (Bits--)
            Value   = (Value << 1) | GetBit();

        return Value;
    }

    int HighVal (void)
    {
        return High;
    }

    int BitsVal (void)
    {
        return Bits;
    }

    unsigned int DataVal (void)
    {
        return Data;
    }

    unsigned char* BufferVal (void)
    {
        return Buffer;
    }
};


// /////////////////////////////////////////////////////////////////////////
//
// The class definition
//

/// Frame parser for Vp6
class FrameParser_VideoVp6_c : public FrameParser_Video_c
{
private:
    class RangeCoder_c          RangeDecoder;

    Vp6StreamParameters_t*      StreamParameters;
    Vp6FrameParameters_t*       FrameParameters;
    Vp6StreamParameters_t       CopyOfStreamParameters;

    struct Vp6MetaData_s        MetaData;
    bool                        StreamMetadataValid;
    Rational_t                  FrameRate;

    FrameParserStatus_t         ReadStreamMetadata(                             void );
    FrameParserStatus_t         ReadPictureHeader(                              void );

    FrameParserStatus_t         CommitFrameForDecode(                           void );
    bool                        NewStreamParametersCheck(                       void );

public:

    FrameParser_VideoVp6_c(                                                     void );
    ~FrameParser_VideoVp6_c(                                                    void );

    //
    // Overrides for component base class functions
    //

    FrameParserStatus_t         Reset(                                          void );

    //
    // FrameParser class functions
    //

    FrameParserStatus_t         RegisterOutputBufferRing(                       Ring_t          Ring );

    //
    // Stream specific functions
    //

    FrameParserStatus_t         ReadHeaders(                                    void );

    FrameParserStatus_t         PrepareReferenceFrameList(                      void );

    FrameParserStatus_t         ForPlayUpdateReferenceFrameList(                void );

    FrameParserStatus_t         RevPlayProcessDecodeStacks(                     void );
    FrameParserStatus_t         RevPlayGeneratePostDecodeParameterSettings(     void );
    FrameParserStatus_t         RevPlayRemoveReferenceFrameFromList(            void );
};

#endif

