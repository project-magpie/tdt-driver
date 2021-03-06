/************************************************************************
COPYRIGHT (C) SGS-THOMSON Microelectronics 2006

Source file name : pes.h
Author :           Nick

Definition of the constants/macros that define useful things associated with 
PES packets


Date        Modification                                    Name
----        ------------                                    --------
20-Nov-06   Created                                         Nick

************************************************************************/

#ifndef H_PES
#define H_PES

#define PES_START_CODE_MASK                     0xf0
#define PES_START_CODE_AUDIO                    0xc0
#define PES_START_CODE_VIDEO                    0xe0
#define PES_START_CODE_VIDEO_VC1                0xfd

#define IS_PES_START_CODE_VIDEO(x)              ((PES_START_CODE_VIDEO == ((x) & PES_START_CODE_MASK)) || (PES_START_CODE_VIDEO_VC1 == (x)))
#define IS_PES_START_CODE_AUDIO(x)              (PES_START_CODE_AUDIO == ((x) & PES_START_CODE_MASK))

#define PES_PADDING_START_CODE                  0xbe
#define PES_PADDING_INITIAL_HEADER_SIZE         6
#define PES_PADDING_SKIP(P)                     ((unsigned int)(((P)[4] << 8) | (P)[5]))

#define PES_START_CODE_PRIVATE_STREAM_1         0xbd
#define IS_PES_START_CODE_PRIVATE_STREAM_1(x)   (PES_START_CODE_PRIVATE_STREAM_1 == (x))

#define PES_START_CODE_EXTENDED_STREAM_ID       0xfd
#define IS_PES_START_CODE_EXTENDED_STREAM_ID(x) (PES_START_CODE_EXTENDED_STREAM_ID == (x))

#define PRIVATE_STREAM_1_SUB_PICTURE            0x20
#define PRIVATE_STREAM_1_SUB_PICTURE_MASK       (~0x1f)
#define IS_PRIVATE_STREAM_1_SUB_PICTURE(x)      (PRIVATE_STREAM_1_SUB_PICTURE == ((x) & PRIVATE_STREAM_1_SUB_PICTURE_MASK)

#define PRIVATE_STREAM_1_VBI                    0x48
#define IS_PRIVATE_STREAM_1_VBI(x)              (PRIVATE_STREAM_1_VBI == (x))

#define PRIVATE_STREAM_1_EXTENDED_SUB_PICTURE   0x60
#define PRIVATE_STREAM_1_EXTENDED_SUB_PICTURE_MASK (~0x1f)
#define IS_PRIVATE_STREAM_1_EXTENDED_SUB_PICTURE(x) (PRIVATE_STREAM_1_EXTENDED_SUB_PICTURE == \
						     ((x) & PRIVATE_STREAM_1_EXTENDED_SUB_PICTURE_MASK))
#define PRIVATE_STREAM_1_AC3                    0x80
#define PRIVATE_STREAM_1_AC3_MASK               (~0x7)
#define IS_PRIVATE_STREAM_1_AC3(x)              (PRIVATE_STREAM_1_AC3 == ((x) & PRIVATE_STREAM_1_AC3_MASK))


#define PRIVATE_STREAM_1_DTS                    0x88
#define PRIVATE_STREAM_1_DTS_MASK               (~0x7)
#define IS_PRIVATE_STREAM_1_DTS(x)              (PRIVATE_STREAM_1_DTS == ((x) & PRIVATE_STREAM_1_DTS_MASK))

#define PRIVATE_STREAM_1_SDDS                   0x90
#define PRIVATE_STREAM_1_SDDS_MASK              (~0x7)
#define IS_PRIVATE_STREAM_1_SDDS(x)             (PRIVATE_STREAM_1_SDDS == ((x) & PRIVATE_STREAM_1_SDDS_MASK))

#define PRIVATE_STREAM_1_LPCM                   0xa0
#define PRIVATE_STREAM_1_LPCM_MASK              (~0x7)
#define IS_PRIVATE_STREAM_1_LPCM(x)             (PRIVATE_STREAM_1_LPCM == ((x) & PRIVATE_STREAM_1_LPCM_MASK))

#define PES_INITIAL_HEADER_SIZE                 9
#define PES_MAX_HEADER_SIZE                     (9+256)
#define PES_HEADER_SIZE(P)                      ((unsigned int)(9+(P)[8]))
#endif
