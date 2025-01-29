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

// endfield_indus_logo.png
extern const char* endfieldIndusLogoCLR[];
extern const int endfieldIndusLogoIDX[];
extern const int endfieldIndusLogoISZ;
extern const int endfieldIndusLogoCNT[];

#endif // IMAGE_ASSETS_H