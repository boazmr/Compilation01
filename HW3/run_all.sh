#!/bin/bash

FAILED_TESTS=()

for in_file in hw3-tests/wspTests01/tests/*.in; do
    test_name=$(basename "$in_file" .in)
    ./hw3 < "$in_file" > "hw3-tests/wspTests01/tests/$test_name.res" 2>&1
    diff -q "hw3-tests/wspTests01/tests/$test_name.res" "hw3-tests/wspTests01/tests/$test_name.out" > /dev/null
    if [ $? -ne 0 ]; then
        FAILED_TESTS+=("$test_name")
    fi
done

if [ ${#FAILED_TESTS[@]} -eq 0 ]; then
    echo "All tests passed ✅"
else
    echo "Failed tests ❌:"
    for test in "${FAILED_TESTS[@]}"; do
        echo "$test"
    done
fi
