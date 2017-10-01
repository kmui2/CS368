#!/bin/bash

# Global constants
readonly DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
readonly CODE_DIR="/p/course/cs368-isung/public/tests/a2"
readonly INPUT_DIR="/u/i/s/isung/public/html/cs368/a2/input"
readonly NUM_TESTS=6
readonly INPUT_FILES=("asian" "gordonramsay" "ham" "marthastewart" "spam")

trap "cleanup; exit 1" SIGINT

# Cleans up intermediate files
cleanup() {
    rm -rf ./a2test ./status.txt ./intersection.txt ./union.txt
}

# Exits if the necessary files do not exist, or if unnecessary files exist.
check_files_exist() {
    if [ ! -f "./a2.cpp" ]; then
        (>&2 echo "Error: could not find a2.cpp, exiting")
        exit 1
    fi
    if [ ! -d "./testfiles" ]; then
        (>&2 echo "Error: could not find testfiles/, exiting")
        exit 1
    fi

    local flag=0
    local f
    for f in "${INPUT_FILES[@]}"; do
        if [ ! -f "./$f" ]; then
            (>&2 echo "Error: could not find $f")
            flag=1
        fi
    done

    local i
    for ((i=1; i<=NUM_TESTS; i++))
    do
        if [ ! -f "./testfiles/input$i"".txt" ]; then
            (>&2 echo "Error: could not find testfiles/input$i"".txt")
            flag=1
        fi
        if [ ! -f "./testfiles/soln$i"".txt" ]; then
            (>&2 echo "Error: could not find testfiles/soln$i"".txt")
            flag=1
        fi
    done

    if [ -e "./intersection.txt" ]; then
        (>&2 echo "Error: please remove intersection.txt before running tests")
        flag=1
    fi
    if [ -e "./union.txt" ]; then
        (>&2 echo "Error: please remove union.txt before running tests")
        flag=1
    fi

    if ((flag == 1)); then
        (>&2 echo "Please fix the above errors, exiting")
        exit 1
    fi
}

# Prints warnings if test files have been changed.
check_files_unchanged() {
    local cmp_msg
    cmp_msg=$(cmp "./test.sh" "$CODE_DIR/test.sh" 2>&1)
    if (($? != 0)); then
        (>&2 echo "Warning: $cmp_msg")
    fi

    local f
    for f in "${INPUT_FILES[@]}"; do
        cmp_msg=$(cmp "./$f" "$INPUT_DIR/$f" 2>&1)
        if (($? != 0)); then
            (>&2 echo "Warning: $cmp_msg")
        fi
    done

    local i
    for ((i=1; i<=NUM_TESTS; i++))
    do
        cmp_msg=$(cmp "./testfiles/input$i"".txt" "$CODE_DIR/testfiles/input$i"".txt" 2>&1)
        if (($? != 0)); then
            (>&2 echo "Warning: $cmp_msg")
        fi
        cmp_msg=$(cmp "./testfiles/soln$i"".txt" "$CODE_DIR/testfiles/soln$i"".txt" 2>&1)
        if (($? != 0)); then
            (>&2 echo "Warning: $cmp_msg")
        fi
    done
}

# Greps through the code files, and exits if anything is wrong.
check_code_text() {
    local mutable_count=$(grep -ow "mutable" ./a2.cpp | wc -l)
    local volatile_count=$(grep -ow "volatile" ./a2.cpp | wc -l)
    local flag=0
    if ((mutable_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"mutable\" in a2.cpp")
        flag=1
    fi
    if ((volatile_count > 0)); then
        (>&2 echo "Error; there are more than 0 occurrences of the word \"volatile\" in a2.cpp")
        flag=1
    fi
    if ((flag == 1)); then
        (>&2 echo "Please fix the above errors, exiting")
        exit 1
    fi
}

# Runs the test case specified by the argument.
# @param $1: the integer corresponding to the test case
# @return 0 if the test passes, or 1 if it fails
run_test() {
    echo "Running test case $1..."

    local soln=()
    local line
    # https://stackoverflow.com/questions/10929453/
    # read-a-file-line-by-line-assigning-the-value-to-a-variable
    while IFS="" read -r line || [[ -n "$line" ]]; do
        soln+=("$line")
    done < ./testfiles/soln"$1".txt

    local num_lines=${#soln[@]}
    local i=0
    local flag=0

    # Not checking contents of stderr - this would require another output
    # file, and if there is an infinite loop, there would be no easy way to
    # clean it up
    while IFS="" read -r line || [[ -n "$line" ]]; do
        if ((i < num_lines)); then
            if [ "$line" != "${soln[i]}" ]; then
                (>&2 echo "Error: line $(((i+1))) of printed output is incorrect")
                (>&2 echo "    Actual:   \"$line\"")
                (>&2 echo "    Expected: \"${soln[i]}\"")
                flag=1
            fi
        else
            (>&2 echo "Error: line $(((i+1))) of printed output is incorrect")
            (>&2 echo "    Actual:   \"$line\"")
            (>&2 echo "    Expected: EOF")
            flag=1
        fi
        ((i += 1))
    done < <(./a2test < ./testfiles/input"$1".txt; echo "$?" > ./status.txt)

    while ((i < num_lines)); do
        (>&2 echo "Error: line $(((i+1))) of printed output is incorrect")
        (>&2 echo "    Actual:   EOF")
        (>&2 echo "    Expected: \"${soln[i]}\"")
        flag=1
        ((i += 1))
    done

    if [ ! -f "./intersection.txt" ]; then
        (>&2 echo "Error: file intersection.txt was not created")
        flag=1
    fi
    if [ ! -f "./union.txt" ]; then
        (>&2 echo "Error: file union.txt was not created")
        flag=1
    fi

    local exit_code=$(cat ./status.txt)
    if [ "$exit_code" != "0" ]; then
        (>&2 echo "Error: your code exited with status $exit_code")
        flag=1
    fi
    rm ./status.txt
    rm -rf ./intersection.txt ./union.txt

    return $flag
}

main() {
    cd "$DIR"

    if (($# > 0)); then
        (>&2 echo "Error: expected no arguments")
        (>&2 echo "USAGE: ./test.sh")
        exit 1
    fi

    check_files_exist

    check_files_unchanged

    check_code_text

    # Compile code into ./a2test
    g++ -std=c++11 ./a2.cpp -o ./a2test
    if (($? != 0)); then
        (>&2 echo "Error: could not compile a2.cpp, exiting")
        exit 1
    fi

    # Run tests
    local passed_test_count=0
    local i
    for ((i=1; i<=NUM_TESTS; i++))
    do
        run_test "$i"
        if (($? == 0)); then
            echo "Test $i passed"
            ((passed_test_count += 1))
        else
            echo "Test $i failed"
        fi
        echo
    done
    cleanup

    # Success (possibly)
    echo "$passed_test_count/$NUM_TESTS tests passed"
    if ((passed_test_count < NUM_TESTS)); then
        exit 1
    else
        return 0
    fi
}

main "$@"
