//
//  main.cpp
//  assignment3
//
//  Created by William Marringa on 1/15/19.
//  Copyright © 2019 William Marringa. All rights reserved.
//

#include "qdShape.hpp"
#include "shapeClassifier.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, const char *argv[]) {
  std::string num;
  while (getline(std::cin, num)) {
    QuadShape testShape = QuadShape(num);
    qShapeClasser classifier;
    std::cout << classifier.classifyShape(testShape) << std::endl;
  }

  return 0;
}
