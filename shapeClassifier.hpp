//
//  shapeClassifer.hpp
//
//  Created by William Marringa on 1/20/19.

#ifndef shapeClassifer_hpp
#define shapeClassifer_hpp

#include "qdShape.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

class qShapeClasser {
private:
  bool isSquare(const QuadShape shapeToClass);
  bool isParallelogram(const QuadShape shapeToClass);
  bool isRectangle(const QuadShape shapeToClass);
  bool isRhombus(const QuadShape shapeToClass);
  bool isTrapezoid(const QuadShape shapeToClass);
  bool isKite(const QuadShape shapeToClass);

public:
  std::string classifyShape(const QuadShape shapeToClass);
};

#endif /* shapeClassifer.hpp */
