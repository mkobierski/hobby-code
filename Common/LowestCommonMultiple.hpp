#pragma once

#include <vector>
namespace LCM {

typedef std::vector<int> VectT;
typedef VectT::iterator VIter;
typedef VectT::size_type VSizeT;

int compute(VectT const & factors);
int incrementMethod(VectT const & factors);
int tableMethod(VectT factors);
bool evenlyDivideEach(int divisor, VectT * nums);

}