#!/bin/bash

# Global constants
readonly DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
readonly LIB_DIR="/p/course/cs368-isung/public/libraries"
readonly ALL_FILES=( \
    "test.c" \
    "test.sh" \
    "Vector.hpp" \
)
readonly INPUT_DIR="/u/i/s/isung/public/html/cs368/a6"
readonly INPUT_FILES=( \
    "test.c" \
    "test.sh" \
)
readonly GTEST_INCLUDE="$LIB_DIR/googletest/googletest/include/"
readonly VALID_ARGS=( \
    "BasicTest" \
    "PushTest" \
    "PopTest" \
    "ReserveTest" \
    "ClearTest" \
    "IteratorTest" \
    "BracketAtTest" \
    "CopyConstructorTest" \
    "CopyAssignmentTest" \
    "SelfAssignmentTest" \
)

trap "cleanup; exit 1" SIGINT

# Cleans up intermediate files
cleanup() {
    rm -rf ./a6test
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
    # Basic checks for Vector.hpp
    local cstdio_count=$(grep -ow "<cstdio>" ./Vector.hpp | wc -l)
    local iostream_count=$(grep -ow "<iostream>" ./Vector.hpp | wc -l)
    local stdexcept_count=$(grep -ow "<stdexcept>" ./Vector.hpp | wc -l)
    local vector_count=$(grep -ow "<vector>" ./Vector.hpp | wc -l)
    local include_count=$(grep -ow "#include" ./Vector.hpp | wc -l)
    local begin_count=$(grep -o "/\* If you want to add methods, add them below this line \*/" ./Vector.hpp | wc -l)
    local end_count=$(grep -o "/\* If you want to add methods, add them above this line \*/" ./Vector.hpp | wc -l)
    local private_count=$(grep -ow "private" ./Vector.hpp | wc -l)
    local protected_count=$(grep -ow "protected" ./Vector.hpp | wc -l)
    local public_count=$(grep -ow "public" ./Vector.hpp | wc -l)
    local extern_count=$(grep -ow "extern" ./Vector.hpp | wc -l)
    local mutable_count=$(grep -ow "mutable" ./Vector.hpp | wc -l)
    local volatile_count=$(grep -ow "volatile" ./Vector.hpp | wc -l)
    local flag=0
    if ((cstdio_count == 0)); then
        (>&2 echo "Error: there are 0 occurrences of the word \"<cstdio>\" in Vector.hpp")
        flag=1
    fi
    if ((cstdio_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of the word \"<cstdio>\" in Vector.hpp")
        flag=1
    fi
    if ((iostream_count == 0)); then
        (>&2 echo "Error: there are 0 occurrences of the word \"<iostream>\" in Vector.hpp")
        flag=1
    fi
    if ((iostream_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of the word \"<iostream>\" in Vector.hpp")
        flag=1
    fi
    if ((stdexcept_count == 0)); then
        (>&2 echo "Error: there are 0 occurrences of the word \"<stdexcept>\" in Vector.hpp")
        flag=1
    fi
    if ((stdexcept_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of the word \"<stdexcept>\" in Vector.hpp")
        flag=1
    fi
    if ((vector_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"<vector>\" in Vector.hpp")
        flag=1
    fi
    if ((include_count < 3)); then
        (>&2 echo "Error: there are less than 3 occurrences of \"\#include\" in Vector.hpp")
        flag=1
    fi
    if ((include_count > 3)); then
        (>&2 echo "Error: there are more than 3 occurrences of \"\#include\" in Vector.hpp")
        flag=1
    fi
    if ((begin_count == 0)); then
        (>&2 echo "Error: there are 0 occurrences of the comment /* If you want to add methods, add them below this line */ in Vector.hpp")
        flag=1
    fi
    if ((begin_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of the comment /* If you want to add methods, add them below this line */ in Vector.hpp")
        flag=1
    fi
    if ((end_count == 0)); then
        (>&2 echo "Error: there are 0 occurrences of the comment /* If you want to add methods, add them above this line */ in Vector.hpp")
        flag=1
    fi
    if ((end_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of the comment /* If you want to add methods, add them above this line */ in Vector.hpp")
        flag=1
    fi
    if ((private_count == 0)); then
        (>&2 echo "Error: there are 0 occurrences of the word \"private\" in Vector.hpp")
        flag=1
    fi
    if ((private_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of the word \"private\" in Vector.hpp")
        flag=1
    fi
    if ((protected_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"protected\" in Vector.hpp")
        flag=1
    fi
    if ((public_count == 0)); then
        (>&2 echo "Error: there are 0 occurrences of the word \"public\" in Vector.hpp")
        flag=1
    fi
    if ((public_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of the word \"public\" in Vector.hpp")
        flag=1
    fi
    if ((extern_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"extern\" in Vector.hpp")
        flag=1
    fi
    if ((mutable_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"mutable\" in Vector.hpp")
        flag=1
    fi
    if ((volatile_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"volatile\" in Vector.hpp")
        flag=1
    fi
    if ((flag == 1)); then
        (>&2 echo "Please fix the above errors in Vector.hpp, exiting")
        exit 1
    fi

    # More advanced checks for Vector.hpp
    cmp <(grep -v "^//" "$INPUT_DIR/Vector.hpp" | head -n13) <(grep -v "^//" ./Vector.hpp | head -n13 | tr -d "\r") > /dev/null 2>&1
    if (($? != 0)); then
        (>&2 echo "Warning: changes to first 13 lines of code (ignoring the file comment) in Vector.hpp")
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
    g++ -std=c++11 -D "Run$arg" -isystem "$GTEST_INCLUDE" -pthread ./test.c "$LIB_DIR/libgtest.a" -o ./a6test
    if (($? != 0)); then
        (>&2 echo "Could not compile $arg, ignoring")
        rm -rf ./a6test
        return 1
    fi

    local exit_code
    ./a6test --gtest_filter="A6Test.$1"
    exit_code=$?
    rm -rf ./a6test
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

    # Compile code into ./a6test
    g++ -std=c++11 -isystem "$GTEST_INCLUDE" -pthread ./test.c "$LIB_DIR/libgtest.a" -o ./a6test
    if (($? != 0)); then
        (>&2 echo "Could not compile Vector.hpp, exiting")
        exit 1
    fi
    rm -rf ./a6test

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
    if (($passed_test_count < $test_count)); then
        exit 1
    else
        return 0
    fi
}

main "$@"
