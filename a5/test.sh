#!/bin/bash

# Global constants
readonly DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
readonly LIB_DIR="/p/course/cs368-isung/public/libraries"
readonly ALL_FILES=( \
    "SmartInteger.cpp" \
    "SmartInteger.hpp" \
    "test.c" \
    "test.sh" \
)
readonly INPUT_DIR="/u/i/s/isung/public/html/cs368/a5"
readonly INPUT_FILES=( \
    "test.c" \
    "test.sh" \
)
readonly CPP_FILES=("SmartInteger.cpp")
readonly GTEST_INCLUDE="$LIB_DIR/googletest/googletest/include/"
readonly VALID_ARGS=( \
    "ConstructorBasicTest" \
    "ConstructorPrototypeTest" \
    "PrintBasicTest" \
    "PrintPrototypeTest" \
    "ComparisonBasicTest" \
    "ComparisonPrototypeTest" \
    "AdditionBasicTest" \
    "AdditionPrototypeTest" \
    "SubtractionBasicTest" \
    "MultiplicationBasicTest" \
    "NegationBasicTest" \
    "PreIncrementBasicTest" \
    "PreIncrementPrototypeTest" \
)

trap "cleanup; exit 1" SIGINT

# Cleans up intermediate files
cleanup() {
    rm -rf ./a5test
}

# Exits if the necessary files do not exist, or if unnecessary files exist.
check_files_exist() {
    local flag=0
    local f
    for f in "${ALL_FILES[@]}"; do
        if [ ! -f "./$f" ]; then
            (>&2 echo "Error: could not find $f")
            flag=1
        fi
    done

    if ((flag == 1)); then
        (>&2 echo "Please fix the above errors, exiting")
        exit 1
    fi
}

# Prints warnings if test files have been changed.
check_files_unchanged() {
    local cmp_msg
    local f
    for f in "${INPUT_FILES[@]}"; do
        cmp_msg=$(cmp "./$f" "$INPUT_DIR/$f" 2>&1)
        if (($? != 0)); then
            (>&2 echo "Warning: $cmp_msg")
        fi
    done
}

# Greps through the code files, and exits or warns if anything is wrong.
check_code_text() {
    # Basic checks for all files
    local extern_count=$(grep -ow "extern" ./SmartInteger.cpp ./SmartInteger.hpp | wc -l)
    local mutable_count=$(grep -ow "mutable" ./SmartInteger.cpp ./SmartInteger.hpp | wc -l)
    local volatile_count=$(grep -ow "volatile" ./SmartInteger.cpp ./SmartInteger.hpp | wc -l)
    local flag=0
    if ((extern_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"extern\" in code files")
        flag=1
    fi
    if ((mutable_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"mutable\" in code files")
        flag=1
    fi
    if ((volatile_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"volatile\" in code files")
        flag=1
    fi
    if ((flag == 1)); then
        (>&2 echo "Please fix the above errors, exiting")
        exit 1
    fi
}

# Returns whether the name of the argument is a test case or not.
# @param $1: the name of a possible test case
# @return 0 if $1 is a test case, or 1 otherwise
is_valid_arg() {
    local arg
    for arg in "${VALID_ARGS[@]}"; do
        if [ "$1" == "$arg" ]; then
            return 0
        fi
    done
    return 1
}

# Compiles and runs the test case specified by the argument.
# @param $1: the name of the test case
# @return 0 if the test passes, or non-zero if it fails
run_test() {
    g++ -std=c++11 -D "Run$arg" -isystem "$GTEST_INCLUDE" -pthread "${CPP_FILES[@]/#/.\/}" ./test.c "$LIB_DIR/libgtest.a" -o ./a5test
    if (($? != 0)); then
        (>&2 echo "Could not compile $arg, ignoring")
        rm -rf ./a5test
        return 1
    fi

    local exit_code
    ./a5test --gtest_filter="A5Test.$1"
    exit_code=$?
    rm -rf ./a5test
    return $exit_code
}

main() {
    cd "$DIR"

    if (($# == 0)); then
        (>&2 echo "Warning: no arguments specified.")
        (>&2 echo "USAGE: ./test.sh <TEST1> <TEST2> ...")
        (>&2 echo "Only performing preliminary checks.")
    fi

    check_files_exist

    check_files_unchanged

    check_code_text

    # Compile code into ./a5test
    g++ -std=c++11 -isystem "$GTEST_INCLUDE" -pthread "${CPP_FILES[@]/#/.\/}" ./test.c "$LIB_DIR/libgtest.a" -o ./a5test
    if (($? != 0)); then
        (>&2 echo "Could not compile code, exiting")
        exit 1
    fi
    rm -rf ./a5test

    # Compile and run unit tests
    local passed_test_count=0
    local test_count=0
    local arg
    for arg in "$@"; do
        is_valid_arg "$arg"
        if (($? != 0)); then
            echo "$arg is not a valid test, ignoring"
            continue
        fi
        run_test "$arg"
        if (($? == 0)); then
            ((passed_test_count += 1))
        fi
        ((test_count += 1))
        echo
    done
    cleanup

    # Success (possibly)
    echo "$passed_test_count/$test_count tests passed"
    if ((passed_test_count < test_count)); then
        exit 1
    else
        return 0
    fi
}

main "$@"
