#ifndef IMAGE_ASSETS_H
#define IMAGE_ASSETS_H

// each image asset is represented by three arrays:
// - an array of colors (CLR)
// - an array of indices (IDX)
// - an array of counts (CNT)
// plus a size constant for the indices array (ISZ)

// endfield_logo.png
extern const char* endfieldLogoCLR[];
extern const int endfieldLogoIDX[];
extern const int endfieldLogoISZ;
extern const int endfieldLogoCNT[];

// boot base
extern const char* bootBaseCLR[];
extern const int bootBaseIDX[];
extern const int bootBaseISZ;
extern const int bootBaseCNT[];

// auton base
extern const char* autonBaseCLR[];
extern const int autonBaseIDX[];
extern const int autonBaseISZ;
extern const int autonBaseCNT[];

// auton base
extern const char* userctlBaseCLR[];
extern const int userctlBaseIDX[];
extern const int userctlBaseISZ;
extern const int userctlBaseCNT[];

#endif // IMAGE_ASSETS_H