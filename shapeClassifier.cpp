#include "shapeClassifier.hpp"
#include "qdShape.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

/*
 * already checking for 4 right angles with isRectangle(), so just need to
 * confirm this shape has 4 equal sides
 */
bool qShapeClasser::isSquare(const QuadShape shapeToClass) {
  std::vector<double> sides = shapeToClass.getSides();
  double side = sides[0];
  for (int s = 0; s < sides.size(); ++s) {
    if (sides[s] != side) {
      return false;
    }
  }
  return true;
}

// opposite sides must have same length and slope
bool qShapeClasser::isParallelogram(const QuadShape shapeToClass) {
  std::vector<double> sides = shapeToClass.getSides();
  std::vector<double> slopes = shapeToClass.getSlopes();

  bool oppSidesEq = (sides[0] == sides[2]) && (sides[1] == sides[3]);
  bool oppSlopesEq = (slopes[0] == slopes[2]) && (slopes[1] == slopes[3]);
  if (oppSidesEq && oppSlopesEq) {
    return true;
  }
  return false;
}

// must have 4 right angles (slopes of 0)
bool qShapeClasser::isRectangle(const QuadShape shapeToClass) {
  std::vector<double> slopes = shapeToClass.getSlopes();
  for (int s = 0; s < slopes.size(); ++s) {
    if (slopes[s] != 0) {
      return false;
    }
  }
  return true;
}

// rectangle and square checks must be false. rhombi have 4 equal length sides
bool qShapeClasser::isRhombus(const QuadShape shapeToClass) {
  std::vector<double> sides = shapeToClass.getSides();
  double side = sides[0];
  for (int s = 1; s < sides.size(); ++s) {
    if (sides[s] != side) {
      return false;
    }
  }
  return true;
}

/*
 * trapezoid has two sides with a slope of 1. The other two must be equal in
 * length and inverse slopes (.45 & -.45)
 */
bool qShapeClasser::isTrapezoid(const QuadShape shapeToClass) {
  std::vector<double> slopes = shapeToClass.getSlopes();
  bool botAndTopSlopes = slopes[0] == slopes[2];
  bool ltAndRtSlopes = slopes[1] == slopes[3];
  return (botAndTopSlopes && !ltAndRtSlopes) ||
         (!botAndTopSlopes && ltAndRtSlopes);
}

// neighboring sides must have inverse slopes and same lengths
bool qShapeClasser::isKite(const QuadShape shapeToClass) {
  std::vector<double> sides = shapeToClass.getSides();
  bool sideA = sides[0] == sides[3];
  bool sideB = sides[1] == sides[2];
  bool lenDifCheck = sides[0] != sides[2];
  return sideA && sideB && lenDifCheck;
}

// overly verbose/confusing. break out into simpler instances?
std::string qShapeClasser::classifyShape(const QuadShape shapeToClass) {
  if (isParallelogram(shapeToClass)) {
    if (isRectangle(shapeToClass)) {
      if (isSquare(shapeToClass)) {
        return "square";
      } else {
        return "rectangle";
      }
    }
    if (isRhombus(shapeToClass)) {
      return "rhombus";
    }
    return "parallelogram";
  } else if (isTrapezoid(shapeToClass)) {
    return "trapezoid";
  } else if (isKite(shapeToClass)) {
    return "kite";
  }
  return "quadrilateral";
}
