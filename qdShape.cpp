//
//  qdShape.cpp
//  assignment3
//
//  Created by William Marringa on 1/16/19.
//  Copyright © 2019 William Marringa. All rights reserved.
//

#include "qdShape.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

QuadShape::QuadShape(const std::string vertices) {
  getCoordPairs(inputLnToIntVec(vertices));
  setSides();
  setSlopes();
}

/*
 * Assuming same number integers on each line of the input txt file.
 * Am I technically using *MAGIC* numbers? feels h4cky
 */
void QuadShape::getCoordPairs(const std::vector<int> vertices) {
  coordinates.push_back(std::make_pair(0, 0));
  coordinates.push_back(std::make_pair(vertices[0], vertices[1]));
  coordinates.push_back(std::make_pair(vertices[2], vertices[3]));
  coordinates.push_back(std::make_pair(vertices[4], vertices[5]));
}

/*
 * This takes the line which contains the formatted numbers for the 3 vertices
 * and splits by the whitespace using tokens.
 */
std::vector<int> QuadShape::inputLnToIntVec(std::string line) {
  std::vector<int> points;
  std::istringstream parser(line);
  std::string number;
  while (parser >> number) {
    points.push_back(std::stoi(number));
  }
  return points;
}

/*
 * repetitive need to come up with better solution
 * THIS ASSUMES THE POINTS FALL ON THE GRAPH IN A CERTAIN ORDER
 */
void QuadShape::setSides() {

  for (int p = 0; p < coordinates.size() - 1; ++p) {
    double xVals = pow(abs(coordinates[p + 1].first - coordinates[p].first), 2);
    double yVals =
        pow(abs(coordinates[p + 1].second - coordinates[p].second), 2);
    sideLengths.push_back(sqrt(xVals + yVals));
  }
  // loop gets first 3 sides, get last side for start/end edge
  double xVals = pow(coordinates[3].first - coordinates[0].first, 2);
  double yVals = pow(coordinates[3].second - coordinates[0].second, 2);
  sideLengths.push_back(sqrt(xVals + yVals));
}

/*
 * Calculating the slopes for each side
 */
void QuadShape::setSlopes() {
  for (int p = 0; p < coordinates.size() - 1; ++p) {
    double xVals = coordinates[p + 1].first - coordinates[p].first;
    double yVals = coordinates[p + 1].second - coordinates[p].second;
    if (xVals == 0) { // accounting for right angles
      slopes.push_back(xVals);
      continue;
    }
    slopes.push_back(yVals / xVals);
  }
  // for loop gets first 3 sides, get last side for start/end edge
  double xVals = coordinates[3].first - coordinates[0].first;
  double yVals = coordinates[3].second - coordinates[0].second;
  if (xVals == 0) {
    slopes.push_back(xVals);
  } else {
    slopes.push_back(yVals / xVals);
  }
}
