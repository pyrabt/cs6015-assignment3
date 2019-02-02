//
//  qdShape.cpp
//  assignment3
//
//  Created by William Marringa on 1/16/19.
//  Copyright © 2019 William Marringa. All rights reserved.
//

#include "qdShape.hpp"
#include <algorithm>
#include <cctype>
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
  lineIntersectCheck();
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
  checkForDuplicatePoints();
  collinearPointsCheck();
}

bool isCollinear(std::pair<int, int> A, std::pair<int, int> B,
                 std::pair<int, int> C) {
  return ((C.second - B.second) * (B.first - A.first)) ==
         ((B.second - A.second) * (C.first - B.first));
}

// checking cases for collinear points
void QuadShape::collinearPointsCheck() {
  bool case1 = isCollinear(coordinates[0], coordinates[1], coordinates[2]); // ABC
  bool case2 = isCollinear(coordinates[0], coordinates[1], coordinates[3]); // ABD
  bool case3 = isCollinear(coordinates[0], coordinates[2], coordinates[3]); // ACD
  bool case4 = isCollinear(coordinates[1], coordinates[2], coordinates[3]); // BCD

  if (case1 || case2 || case3 || case4) {
    std::cout << "error 4" << std::endl;
    exit(4);
  }
}

// checks for orientation of 3 points at a time and errors if lines are
// collinear or cross each other
void QuadShape::lineIntersectCheck() {
  if (slopes[0] > 0 && slopes[2] < 0) {
    if (coordinates[1].second >= coordinates[2].second) {
      std::cout << "error 3: Intersecting Lines" << std::endl;
      exit(3);
    }
  }
}

// very poor algo complexity, but i'm really tired so this will have to do for
// now
void QuadShape::checkForDuplicatePoints() {
  for (int i = 0; i < coordinates.size(); ++i) {
    for (int j = i + 1; j < coordinates.size(); ++j) {
      if (coordinates[i] == coordinates[j]) {
        std::cout << "error 2" << std::endl;
        exit(1);
      }
    }
  }
}

// checking if point is a valid integer
bool QuadShape::isNumberString(std::string num) {
  for (char c : num) {
    if (c < 48 || c > 57) {
      return false;
    }
  }
  return true;
}

// This validates the string tokens read in from the input file
void QuadShape::inputValErrorChecking(const std::string num) {
  if (isNumberString(num) == false) {
    std::cout << "error 1" << std::endl;
    exit(1);
  }
  if (std::stoi(num) < 0 ||
      std::stoi(num) > 100) { // Checking for valid point range
    std::cout << "error 1" << std::endl;
    exit(1);
  }
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
    inputValErrorChecking(number);
    points.push_back(std::stoi(number));
  }

  if (points.size() != 6) { // Error checking for invalid # of points
    std::cout << "error 1" << std::endl;
    exit(1);
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
