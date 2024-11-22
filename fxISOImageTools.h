//----------------------------------------------------------------------------------------------------
//
// Company:	BiometriKa s.r.l. - www.biometrika.it
// E-mail:	info@biometrika.it
//
// Copyright(C) 2014, Biometrika s.r.l.
// All rights reserved.
//
// History
// 
//----------------------------------------------------------------------------------------------------
#ifndef FXISOIMAGETOOLS_H
#define FXISOIMAGETOOLS_H


#ifndef BYTE
typedef unsigned char BYTE;
#endif

#include "AcquisitionWarnings.h"


#ifdef WIN32
	// win32
#define _fxexport __declspec(dllexport)
#define _fxcall __stdcall
#else
	// linux
#define _fxexport 
#define _fxcall 
#endif // LINUX


#ifdef __cplusplus
extern "C" {
#endif

 
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_EvaluateWarning(int quality100, BYTE *image, int width, int height, int resolution, int *qualityWarning);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_EvaluateWarning
//
//	Description:
//		Evaluates a fingerprint image and returns a "qualityEvaluation"  
//		warning as defined in "AcquisitionWarnings.h".
//
//	Parameters:
//		quality100        Input - the quality score given by the SDK, <0 if not evaluated
//		image             Input - the image buffer
//		width             Input - the image width
//		height            Input - the image height
//		resolution        Input - the resolution of the image in Dot Per Inch
//		qualityWarning    Output - if a warning on this image is found, this parameter is not zero
//	Returns:
//		returns 0 if the image has been checked
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_EvaluateNISTQuality(BYTE *image, int width, int height, int resolution, int *quality5);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_EvaluateNISTQuality
//
//	Description:
//		Evaluates a fingerprint image and returns the NIST quality score
//		between [1..5] (excellent to poor)
//
//	Parameters:
//		image             Input - the image buffer
//		width             Input - the image width
//		height            Input - the image height
//		resolution        Input - the resolution of the image in Dot Per Inch
//		quality5          Output - the NIST quality score: 1(excellent), 2(very good), 3(good), 4(fair), 5(poor)
//	Returns:
//		returns 0 if the image has been checked
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_NFIQ_Evaluate(BYTE* image, int width, int height, int* quality100);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_NFIQ_Evaluate
//
//	Description:
//		Evaluates a 500 DPI fingerprint image quality and returns the NIST 
//		NFIQ-2 score between [0..100] (poor to excellent)
//      If NFIQ-2 dll are not found, FxISOImageTools reverts to NFIQ version 1 
//      and 5 discrete levels are returned: {0,10,20,30,50}
//
//	Parameters:
//		image             Input - the image buffer
//		width             Input - the image width
//		height            Input - the image height
//		quality100       Output - the NIST NFIQ-2 quality score
//	Returns:
//		returns 0 if the image has been checked
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_NFIQ_GetVersion(int* major, int* minor);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_NFIQ_GetVersion
//
//	Description:
//      Retrieves the version of NFIQ algorithm used.      
//      NFIQ version 2 if UMPI_NFIQ2.dll and associated files are present in the path
//      If NFIQ-2 dll are not found, FxISOImageTools reverts to NFIQ version 1 
// 
// Parameters:
//      major: Output - the major version 
//	    minor: Output - the major version
// 
// Returns:
//      returns 0 if the function succeeded

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_NFIQ_SetFolder(const char *relativePath);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_NFIQ_SetFolder
//
//	Description:
//		Set the sub-folder where NFIQ-2 dll are stored
//      In that folder there should be the following files:
//       + UMPI_NFIQ2.dll
//       + nist_plain_tir-ink.txt
//       + nist_plain_tir-ink.yaml
//       + Nfiq2Api.dll
//       + opencv_worldNNN.dll, where "NNN" is the version
//
//	Parameters:
//		relativePath      Input - the path relative to current application folder
//                                (the default folder is the current one, i.e.: ".\\")
//	Returns:
//		returns 0 if dll loaded and the function succeeded
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_Clean(BYTE *image, int width, int height);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_Clean
//
//	Description:
//		Performs a clean of the image background surrounding the fingerprint, 
//		to remove latency fingerprints and other dirt.
//		The new image is stored on the same buffer passed with the image.
//
//	Parameters:
//		image       Input/Output - the image buffer
//		width       Input - the image width
//		height      Input - the image height
//	Returns:
//		returns 0 if the image has been cleaned
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_EnhanceContrast(BYTE *image, int width, int height);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_EnhanceContrast
//
//	Description:
//		Enhance the contrast of the fingerprint image.
//		This function is used on low contrst fingerprint (usually dry fingerprints)
//		and after the FxISO_ImageTool_Clean() has been called on this image.
//		The new image is stored on the same buffer passed with the image.
//
//	Parameters:
//		image       Input/Output - the image buffer
//		width       Input - the image width
//		height      Input - the image height
//	Returns:
//		returns 0 if the image has been enhanced
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_Segmentation(BYTE * image, int width, int height, int *newWidth, int *newHeight);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_Segmentation
//
//	Description:
//		Performa a segmentation of the fingerprint from the background.
//		This function is used to reduce the image size to contain only valuable fingerprint information.
//		Can be called after the FxISO_ImageTool_Clean() has been called on this image.
//		The new image is stored on the same buffer passed with the image.
//
//	Parameters:
//		image       Input/Output - the image buffer
//		width       Input - the image width
//		height      Input - the image height
//		newWidht    Output - new image width
//		newHeight   Output - new image height
//	Returns:
//		returns 0 if the fingerprint has been found
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_CompressJPEG2000(BYTE *pImage, int width, int height, float compressionRatio,
                                                                             BYTE *pJpg2k, int bufferSize, int *compressedSize);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_CompressJPEG2000
//
//	Description:
//		Compress the grey image in a JPEG 2000 format. 
//
//	Parameters:
//		pImage            Input - the image buffer
//		width             Input - the image width
//		height            Input - the image height
//		compressionRatio  Input - the required compression ratio. for lossless compression use '1'.
//		pJpg2k            Output - the compressed stream. The buffer should be already allocated
//		bufferSize        Input - the size of 'pJpg2k' buffer
//		compressedSize    Output - the size of the compressed stream stored in 'pJpg2k'
//	Returns:
//		returns 0 if the image has been compressed
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_CompressWSQ(BYTE *pImage, int width, int height, float compressionRatio,
                                                  BYTE *pWsqk, int bufferSize, int *compressedSize);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_CompressWSQ
//
//	Description:
//		Compress the 8bit gray image in a WSQ format. 
//      The algorithm respects the given compressionRatio with a +/1% tollerance
//
//	Parameters:
//		pImage            Input - the image buffer
//		width             Input - the image width
//		height            Input - the image height
//		compressionRatio  Input - the required compression ratio. For 10:1 compression use 10, for 15:1 compression use 15
//		pWsq              Output - the compressed stream. The buffer should be already allocated
//		bufferSize        Input - the size of 'pWsq' buffer
//		compressedSize    Output - the size of the compressed stream stored in 'pWsq'
//	Returns:
//		returns 0 if the image has been compressed
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ImageTool_CompressWSQ_maxSize(BYTE* pImage, int width, int height, char *comment,
                                                          BYTE* pWsqk, int maxCompressedSize, int* compressedSize);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_CompressWSQ_maxSize
//
//	Description:
//		Compress the 8bit gray image in a WSQ format. 
//      A final compression size is specified. The algorithm selects the 
//      compression ratio based on imput parameters: (width*height)/maxCompressedSize.
//      The compressed result could be 1% smaller, but not greater.
//
//	Parameters:
//		pImage            Input - the image buffer
//		width             Input - the image width
//		height            Input - the image height
//      comment           Input - text string to be stored inside wsq. Can be NULL for "no comment"
//		pWsq              Output - the compressed stream. The buffer should be already allocated
//		maxCompressedSize Input - the expected compressed size, should be less than 'pWsq' buffer length
//		compressedSize    Output - the size of the compressed stream stored in 'pWsq'
//	Returns:
//		returns 0 if the image has been compressed
//------------------------------------------------------------------------------

_fxexport int _fxcall FxISO_ImageTool_CompressWSQ_bitPerPixel(BYTE* pImage, int width, int height, char* comment, float bitAllocationTarget,
                                                              BYTE* pWsqk, int bufferSize, int* compressedSize);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ImageTool_CompressWSQ_bitPerPixel
//
//	Description:
//		Compress the 8bit gray image in a WSQ format. 
//      The bitAllocationTarget parameter is usefull to perform NIST compliancy tests 
//      at 0.75 and 2.25 bits per pixel compression
//
//	Parameters:
//		pImage               Input - the image buffer
//		width                Input - the image width
//		height               Input - the image height
//      comment              Input - text string to be stored inside wsq. Can be NULL for "no comment"
//		bitAllocationTarget  Input - the bit allocation target, from 0.75 to 2.25
//		pWsq                 Output - the compressed stream. The buffer should be already allocated
//		bufferSize           Input - the size of 'pWsq' buffer
//		compressedSize       Output - the size of the compressed stream stored in 'pWsq'
//	Returns:
//		returns 0 if the image has been compressed
//------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
//     ANSI/NIST-ITL 1-2011 output format (updated to 2015 version)
//----------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ANSIRecord1_Reset(char *destAgencyId, char *origAgencyId,
                                                                    char *transactionNumber, char *typeOfTransaction,
                                                                    int year, int month, int day);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ANSIRecord1_Reset
//
//	Description:
//		This function reset all the information set on Record type-1. 
//      It has to be called before starting to insert information for a new transaction
//
//	Parameters:
//      destAgencyId        Input – the destination agency identification number (DAI)
//      origAgencyId        Input – the originating agency identification number(OAI)
//      transactionNumber   Input – transaction control number(TCN)
//      typeOfTransaction   Input – type of transaction(TOT)
//      year                Input – year of submission(> 2000)
//      month               Input – month of submission(in[1..12])
//      day                 Input – day of submission(in[1..31])
//	Returns:
//		returns 0 if the function succeeded
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ANSIRecord1_AddRecord(int recordType, int IDC);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ANSIRecord1_AddRecord
//
//	Description:
//      This function add in the header a reference to a record, reporting the type 
//      and its internal refecence index (IDC)
//
//	Parameters:
//      recordType   Input – 4 or 14, the only allowed record types in this SDK
//      IDC          Input – progressive index of the record, in [0..99]
//	Returns:
//		returns 0 if the function succeeded
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ANSIRecord1_Export2011(BYTE * outputBuffer, int maxBufferSize, int* outputSize);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ANSIRecord1_Export2011
//
//	Description:
//      This function exports a record type-1 in ANSI/NIST-ITL 1-2011 
//      (update 2015) format, traditional encoding
//
//	Parameters:
//      outputBuffer   Output – buffer to store the encoded record
//      maxBufferSize  Input – max output size
//      outputSize     Output – size of generated record
//
//	Returns:
//		returns 0 if the function succeeded
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ANSIRecord14_Export2011(
                                            BYTE * outputBuffer, int maxBufferSize, int* outputSize,
                                            int IDC, int fingerIndex, int NISTquality, int amputated,
                                            char* sourceAgency, char* deviceID, char* comment,
                                            int year, int month, int day,
                                            int width, int height, int compressionType,
                                            BYTE * imagedata, int dataSize);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ANSIRecord14_Export2011
//
//	Description: 
//      This function exports a record type-14 in ANSI/NIST-ITL 1-2011 
//      (update 2015) format, traditional encoding.
//      Fingerprint image is passed compressed or uncompressed grayscale as 
//      received from the scanner. Al required data to form the record are 
//      passed in this function.
//
//	Parameters:
//      outputBuffer    Output – buffer to store the encoded record
//      maxBufferSize   Input – max output size
//      outputSize      Output – size of generated record
//      IDC             Input – internal reference index
//      fingerIndex     Input – finger index, -1 if unknown(ref.table in 9.3.1)
//      NISTquality     Input – from 1 to 5, or 0 for not computed
//      amputated       Input – optional for missing(partial or total) finger
//                              0 = fingerprint ok
//                              1 = Scar(SR)
//                              2 = partially amputated(XX)
//                              3 = amputated(UP)
//      sourceAgency    Input – source agency name
//      deviceID        Input – device ID or MAC Address
//      comment         Input – optional comment
//      year            Input – acquisition year(> 2000)
//      month           Input – acquisition month(in[1..12])
//      day             Input – acquisition day(in[1..31])
//      width           Input – image width
//      height          Input – image height
//      compressionType Input – allowed compression type :
//                              0 = NONE
//                              1 = WSQ
//                              4 = JPEG2000
//                              5 = JPEG2000 lossles
//      imagedata       Input – buffer with fingerprint image data
//      datasize        Input – size of fingerprint image data
//
//	Returns:
//		returns 0 if the function succeeded
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_ANSIRecord4_Export2011(
                                            BYTE *outputBuffer, int maxBufferSize, int *outputSize,
                                            int IDC, int fingerIndex, int compressionType,
                                            BYTE *imagedata, int dataSize);
//------------------------------------------------------------------------------
//	Functions name: FxISO_ANSIRecord4_Export2011
//
//	Description: 
//      This function exports a record type-4 in ANSI/NIST-ITL 1-2011 
//      (update 2015) format, traditional encoding. 
//      Fingerprint image is passed compressed as WSQ or uncompressed 
//      grayscale as received from the scanner. Al required data to 
//      form the record are passed in this function
//
//	Parameters:
//      outputBuffer    Output – buffer to store the encoded record
//      maxBufferSize   Input – max output size
//      outputSize      Output – size of generated record
//      IDC             Input – internal reference index
//      fingerIndex     Input – finger index, -1 if unknown(ref.table in 9.3.1)
//      compressionType Input – allowed compression type:
//                              0 = NONE
//                              1 = WSQ
//      imagedata       Input – buffer with fingerprint image data
//      datasize        Input – size of fingerprint image data
//
//	Returns:
//		returns 0 if the function succeeded
//
//  NOTE:
//      This format is not recommended and can be used only to transmit 
//      a standard HiScan/HiScan PRO image, 1”x1” at 500DPI.
//------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

//------------------------------------------------------------------------------
#endif
