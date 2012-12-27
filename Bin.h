#ifndef BIN_H_INC
#define BIN_H_INC

#include "util.h"
#include "element.h"
#include <memory>

struct Bin;

Bin * BinCreate(unsigned);
Bin * BinCreate(Pointer<Bin>);
void BinDestroy(Bin*);

typedef util::deleter<Bin>::bind<BinDestroy> BinDeleter;
typedef std::unique_ptr<Bin, BinDeleter> UniqueBin;

UniqueBin BinInstance(unsigned);
UniqueBin BinInstance(Pointer<Bin>);

//these functions will accept either a Bin* or a UniqueBin
void BinCollapse(Pointer<Bin>);
unsigned BinHeight(Pointer<Bin>);
element& BinAt(Pointer<Bin>, unsigned);
bool BinEmpty(Pointer<Bin>);
void BinFill(Pointer<Bin>, unsigned);

#endif
