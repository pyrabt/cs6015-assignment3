classifier:
	clang++ main.cpp qdShape.cpp shapeClassifier.cpp -o classifier
test:
	./classifier < testInput.txt > output.txt
