//
//  qdShape.hpp
//  assignment3
//
//  Created by William Marringa on 1/16/19.
//  Copyright © 2019 William Marringa. All rights reserved.
//

#ifndef qdShape_hpp
#define qdShape_hpp

#include <stdio.h>
#include <string>
#include <utility>
#include <vector>

/*
 * Using pairs instead of a struct within another struct will reduce the
 * complexity
 */
class QuadShape {
private:
  // the coordinates of this shape
  std::vector<std::pair<int, int> > coordinates;

  // side lengths ordered bot, right, top, left
  std::vector<double> sideLengths;

  // slopes ordered bot, right, top, left
  std::vector<double> slopes;

  // parses the coordinate pairs and stores them as pairs in the shape
  void getCoordPairs(const std::vector<int> vertices);

  // reads the coordinate string and parses into vector of ints
  std::vector<int> inputLnToIntVec(std::string line);

  // calculates the 4 side lengths and pushes to this shape's list of side
  // lengths
  void setSides();

  // calculates the slopes of the 4 sides of the shape and pushes them to the
  // slope list
  void setSlopes();

  // checking if point is valid integer
  bool isNumberString(std::string num);

  // validates the string tokens read from input file
  void inputValErrorChecking(const std::string num);

public:
  // initialize shape with line containing coordinates
  QuadShape(const std::string vertices);

  // sides getter
  std::vector<double> getSides() const { return sideLengths; }

  // slopes getter
  std::vector<double> getSlopes() const { return slopes; }
};

#endif /* qdShape_hpp */
