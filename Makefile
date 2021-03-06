classifier: main.cpp qdShape.cpp shapeClassifier.cpp
	clang++ -std=c++14 -fsanitize=address main.cpp qdShape.cpp shapeClassifier.cpp -o classifier

test:
	sh test.sh

cover:
	clang++ -std=c++14 -fprofile-instr-generate -fcoverage-mapping main.cpp qdShape.cpp shapeClassifier.cpp -o classifier
	LLVM_PROFILE_FILE="sInput1.profraw" ./classifier < testInput.txt
	-LLVM_PROFILE_FILE="e1_1.profraw" ./classifier < testCaseFiles/error1_1.txt
	-LLVM_PROFILE_FILE="e1_2.profraw" ./classifier < testCaseFiles/error1_2.txt
	-LLVM_PROFILE_FILE="e1_3.profraw" ./classifier < testCaseFiles/error1_3.txt
	-LLVM_PROFILE_FILE="e1_4.profraw" ./classifier < testCaseFiles/error1_4.txt
	-LLVM_PROFILE_FILE="e1_5.profraw" ./classifier < testCaseFiles/error1_5.txt
	-LLVM_PROFILE_FILE="e2_1.profraw" ./classifier < testCaseFiles/error2_1.txt
	-LLVM_PROFILE_FILE="e3_1.profraw" ./classifier < testCaseFiles/error3_1.txt
	-LLVM_PROFILE_FILE="e3_2.profraw" ./classifier < testCaseFiles/error3_2.txt
	-LLVM_PROFILE_FILE="e3_3.profraw" ./classifier < testCaseFiles/error3_3.txt
	-LLVM_PROFILE_FILE="e4_1.profraw" ./classifier < testCaseFiles/error4_1.txt
	-LLVM_PROFILE_FILE="e4_2.profraw" ./classifier < testCaseFiles/error4_2.txt
	xcrun llvm-profdata merge -sparse sInput1.profraw e1_1.profraw e1_2.profraw e1_3.profraw e1_4.profraw e1_5.profraw e2_1.profraw e3_1.profraw e3_2.profraw e3_3.profraw e4_1.profraw e4_2.profraw -o classifier.profdata
	rm -f e1_1.profraw e1_2.profraw e1_3.profraw e1_4.profraw e1_5.profraw e2_1.profraw e3_1.profraw e3_2.profraw e3_3.profraw e4_1.profraw e4_2.profraw
	xcrun llvm-cov show ./classifier -instr-profile=classifier.profdata

fuzzer:
	clang++ -std=c++14 -fsanitize=address -fprofile-instr-generate -fcoverage-mapping main.cpp qdShape.cpp shapeClassifier.cpp -o classifier
	chmod +x fuzz.py
	cp fuzz.py fuzz
