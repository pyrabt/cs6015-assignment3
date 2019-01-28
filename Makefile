classifier: main.cpp qdShape.cpp shapeClassifier.cpp
	clang++ main.cpp qdShape.cpp shapeClassifier.cpp -o classifier
test:
	sh test.sh
