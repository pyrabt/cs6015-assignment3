./classifier < testInput.txt > testOutput.txt
diff -a testOutput.txt answers.txt
error=$?
if [ $error -eq 0 ]
then
echo "test passed"
elif [ $error -eq 1 ]
then
echo "test failed"
exit 1
else
echo "test didn't run properly"
exit 1
fi

# ERROR 1 TEST CASES
./classifier < testCaseFiles/error1_1.txt
error=$?
if [ $error == 0 ]
then
echo "too many points error test failed"
elif [ $error == 1 ]
then
echo "too many points error test passed"
fi

./classifier < testCaseFiles/error1_2.txt
error=$?
if [ $error == 0 ]
then
echo "invalid character error test failed"
elif [ $error == 1 ]
then
echo "invalid character error test passed"
fi

./classifier < testCaseFiles/error1_3.txt
error=$?
if [ $error == 0 ]
then
echo "point out of range (HIGH) error test failed"
elif [ $error == 1 ]
then
echo "point out of range (HIGH) error test passed"
fi

./classifier < testCaseFiles/error1_4.txt
error=$?
if [ $error == 0 ]
then
echo "point out of range (LOW) error test failed"
elif [ $error == 1 ]
then
echo "point out of range (LOW) error test passed"
fi

./classifier < testCaseFiles/error1_5.txt
error=$?
if [ $error == 0 ]
then
echo "too few points error test failed"
elif [ $error == 1 ]
then
echo "too few points error test passed"
fi

# ERROR 2 TEST CASES
./classifier < testCaseFiles/error2_1.txt
error=$?
if [ $error == 0 ]
then
echo "coinciding points error test failed"
elif [ $error == 1 ]
then
echo "coinciding points error test passed"
fi

# ERROR 3 TEST CASES
./classifier < testCaseFiles/error3_1.txt
error=$?
if [ $error == 0 ]
then
echo "intersecting lines error test failed"
elif [ $error == 3 ]
then
echo "intersecting lines error test passed"
fi

./classifier < testCaseFiles/error3_2.txt
error=$?
if [ $error == 0 ]
then
echo "intersecting lines error test failed"
elif [ $error == 3 ]
then
echo "intersecting lines error test passed"
fi

# ERROR 4 TEST CASES
./classifier < testCaseFiles/error4_1.txt
error=$?
if [ $error == 0 ]
then
echo "collinear points error test failed"
elif [ $error == 4 ]
then
echo "collinear points error test passed"
fi
