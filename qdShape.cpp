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
  bool case1 =
      isCollinear(coordinates[0], coordinates[1], coordinates[2]); // ABC
  bool case2 =
      isCollinear(coordinates[0], coordinates[1], coordinates[3]); // ABD
  bool case3 =
      isCollinear(coordinates[0], coordinates[2], coordinates[3]); // ACD
  bool case4 =
      isCollinear(coordinates[1], coordinates[2], coordinates[3]); // BCD

  if (case1 || case2 || case3 || case4) {
    std::cout << "error 4" << std::endl;
    exit(4);
  }
}

// Determines if point 'x' is on the line a-b
bool onSegment(std::pair<int, int> a, std::pair<int, int> x,
               std::pair<int, int> b) {

  bool xSegCheck = x.first <= std::max(a.first, b.first) &&
                   x.first >= std::min(a.first, b.first);
  bool ySegCheck = x.second <= std::max(a.second, b.second) &&
                   x.second >= std::min(a.second, b.second);

  if (xSegCheck && ySegCheck) {
    return true;
  }
  return false;
}

// Determine the orientation of three given points
int setOrientation(std::pair<int, int> a, std::pair<int, int> b,
                std::pair<int, int> c) {

  int val = (b.second - a.second) * (c.first - b.first) -
            (b.first - a.first) * (c.second - b.second);

  if (val == 0)
    return 0; // points are colinear

  return (val > 0) ? 1 : 2; // 1 = clockwise | 2 = counter-clockwise
}

// Determines based on orientation if lines intersect
// This algo was adapted from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool QuadShape::doIntersect(std::pair<int, int> a, std::pair<int, int> b,
                            std::pair<int, int> c, std::pair<int, int> d) {

  int o1 = setOrientation(a, b, c);
  int o2 = setOrientation(a, b, d);
  int o3 = setOrientation(c, d, a);
  int o4 = setOrientation(c, d, b);

  if (o1 != o2 && o3 != o4)
    return true;

  // c-a-d are collinear and a lies on the line c-d
  if (o3 == 0 && onSegment(c, a, d))
    return true;

  // c-b-d are collinear and b lies on the line c-d
  if (o4 == 0 && onSegment(c, b, d))
    return true;

  // a-b-c are collinear and c lies on the line a-b
  if (o1 == 0 && onSegment(a, c, b))
    return true;

  // a-d-b are collinear and d lies on the line a-b
  if (o2 == 0 && onSegment(a, d, b))
    return true;

  return false;
}

// checks for orientation of 3 points at a time and errors if lines are
// collinear or cross each other
void QuadShape::lineIntersectCheck() {
  bool case1 = doIntersect(coordinates[0], coordinates[1], coordinates[2],
                           coordinates[3]);
  bool case2 = doIntersect(coordinates[1], coordinates[2], coordinates[3],
                           coordinates[0]);

  if (case1 || case2) {
    std::cout << "error 3\n";
    exit(3);
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
