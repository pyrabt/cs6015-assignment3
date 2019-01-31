classifier: main.cpp qdShape.cpp shapeClassifier.cpp
	clang++ -std=c++14 main.cpp qdShape.cpp shapeClassifier.cpp -o classifier
test:
	sh test.sh

cover:
	clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp qdShape.cpp shapeClassifier.cpp -o classifier
	LLVM_PROFILE_FILE="sInput1.profraw" ./classifier < testInput.txt
	-LLVM_PROFILE_FILE="e1_1.profraw" ./classifier < testCaseFiles/error1_1.txt
	-LLVM_PROFILE_FILE="e1_2.profraw" ./classifier < testCaseFiles/error1_2.txt
	-LLVM_PROFILE_FILE="e1_3.profraw" ./classifier < testCaseFiles/error1_3.txt
	-LLVM_PROFILE_FILE="e1_4.profraw" ./classifier < testCaseFiles/error1_4.txt
	-LLVM_PROFILE_FILE="e1_5.profraw" ./classifier < testCaseFiles/error1_5.txt
	xcrun llvm-profdata merge -sparse sInput1.profraw e1_1.profraw e1_2.profraw e1_3.profraw e1_4.profraw e1_5.profraw -o classifier.profdata
	rm -f e1_1.profraw e1_2.profraw e1_3.profraw e1_4.profraw e1_5.profraw
	xcrun llvm-cov show ./classifier -instr-profile=classifier.profdata
