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

bool isCornerPoint(int x, int y, std::pair<int, int> points[]) {
  for (int p = 0; p < 4; ++p) {
    if (points[p].first == x && points[p].second == y) {
      return true;
    }
  }
  return false;
}

bool QuadShape::doIntersect(std::pair<int, int> a, std::pair<int, int> b,
                            std::pair<int, int> c, std::pair<int, int> d) {
  std::pair<int, int> points[] = {a, b, c, d};
  double seg1A = b.second - a.second;
  double seg1B = a.first - b.first;
  double seg1C = (seg1A * a.first) + (seg1B * a.second);
  int seg1xmin = std::min(a.first, b.first);
  int seg1xmax = std::max(a.first, b.first);
  int seg1ymin = std::min(a.second, b.second);
  int seg1ymax = std::max(a.second, b.second);

  double seg2A = d.second - c.second;
  double seg2B = c.first - d.first;
  double seg2C = (seg2A * c.first) + (seg2B * c.second);
  int seg2xmin = std::min(c.first, d.first);
  int seg2xmax = std::max(c.first, d.first);
  int seg2ymin = std::min(c.second, d.second);
  int seg2ymax = std::max(c.second, d.second);

  double det = (seg1A * seg2B) - (seg2A * seg1B);

  if (det != 0) {
    int x = ((seg2B * seg1C) - (seg1B * seg2C)) / det;
    int y = ((seg1A * seg2C) - (seg2A * seg1C)) / det;

    bool cornerPoint = isCornerPoint(x, y, points);
    bool onLine1 = ((seg1xmin <= x) && (x <= seg1xmax)) && ((seg1ymin <= y) && (y <= seg1ymax));
    bool onLine2 = ((seg2xmin <= x) && (x <= seg2xmax)) && ((seg2ymin <= y) && (y <= seg2ymax));

    if (onLine1 && onLine2 && !cornerPoint) {
      return true;
    }
    return false;
  }
  return false;
}



// checks for orientation of 3 points at a time and errors if lines are
// collinear or cross each other
void QuadShape::lineIntersectCheck() {
  bool case1 = doIntersect(coordinates[0], coordinates[1], coordinates[1],
                           coordinates[2]); // AB v BC
  bool case2 = doIntersect(coordinates[0], coordinates[1], coordinates[2],
                           coordinates[3]); // AB v CD
  bool case3 = doIntersect(coordinates[0], coordinates[1], coordinates[3],
                           coordinates[1]); // AB v DA
  bool case4 = doIntersect(coordinates[1], coordinates[2], coordinates[2],
                           coordinates[3]); // BC v CD
  bool case5 = doIntersect(coordinates[1], coordinates[2], coordinates[3],
                           coordinates[1]); // BC v DA
  bool case6 = doIntersect(coordinates[3], coordinates[0], coordinates[2],
                           coordinates[3]); // DA v CD

  if (case1 || case2 || case3 || case4 || case5 || case6) {
    std::cout << "error 3" << std::endl;
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
