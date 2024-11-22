#pragma once


//*** Acquisition Warnings ***
#define AWRN_OK               0		//Image Quality is Ok
	//Quality warnings for 1 fingerprint acquisition
#define AWRN_NOTFOUND         1		//fingerprint not found
#define AWRN_MANYFINGERPRINTS 2		//too many fingerprints than expected
#define AWRN_LOWCONTRAST      3		//the fingerprint is not enough dark: apply more pressure or use a moisturizer
#define AWRN_DARKFINGERPRINT  4		//the fingerprint is not enough dark: apply less pressure or dry up fingerprints
#define AWRN_LOWQUALITY       5		//Low quality fingerprints: try using a moisturizer
#define AWRN_DIRTYPRISM       6		//Please clean the platen surface
#define AWRN_TOO_LEFT         7		//Fingerprint is too much close to left margin
#define AWRN_TOO_RIGHT        8		//Fingerprint is too much close to right margin
#define AWRN_TOO_TOP          9		//Fingerprint is too much close to top margin
#define AWRN_TOO_BOTTOM      10		//Fingerprint is too much close to bottom margin
#define AWRN_ROTATION        11		//Excessive rotation
#define AWRN_NOTSTILL        12		//Motion detected
