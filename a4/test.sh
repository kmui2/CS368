#!/bin/bash

# Global constants
readonly DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
readonly LIB_DIR="/p/course/cs368-isung/public/libraries"
readonly ALL_FILES=( \
    "GradStudent.cpp" \
    "GradStudent.hpp" \
    "main.cpp" \
    "processStudent.cpp" \
    "processStudent.hpp" \
    "Student.cpp" \
    "Student.hpp" \
    "students.txt" \
    "test.c" \
    "test.sh" \
    "UndergradStudent.cpp" \
    "UndergradStudent.hpp" \
)
readonly INPUT_DIR="/u/i/s/isung/public/html/cs368/a4"
readonly INPUT_FILES=( \
    "GradStudent.hpp" \
    "main.cpp" \
    "processStudent.hpp" \
    "students.txt" \
    "test.c" \
    "test.sh" \
    "UndergradStudent.hpp" \
)
readonly CPP_FILES=("GradStudent.cpp" "processStudent.cpp" "Student.cpp" "UndergradStudent.cpp")
readonly GTEST_INCLUDE="$LIB_DIR/googletest/googletest/include/"
readonly VALID_ARGS=( \
    "BasicStudentTest" \
    "BasicUndergradStudentTest" \
    "BasicGradStudentTest" \
    "BasicProcessStudentTest" \
    "AdvancedStudentTest" \
    "AdvancedUndergradStudentTest" \
    "AdvancedGradStudentTest" \
    "AdvancedProcessStudentTest" \
)

trap "cleanup; exit 1" SIGINT

# Cleans up intermediate files
cleanup() {
    rm -rf ./a4test ./testStudents.txt
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
    local mutable_count=$(grep -ow "mutable" ./GradStudent.cpp ./processStudent.cpp ./Student.cpp ./Student.hpp ./UndergradStudent.cpp | wc -l)
    local volatile_count=$(grep -ow "volatile" ./GradStudent.cpp ./processStudent.cpp ./Student.cpp ./Student.hpp ./UndergradStudent.cpp | wc -l)
    local flag=0
    if ((mutable_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"mutable\" in code files")
        flag=1
    fi
    if ((volatile_count > 0)); then
        (>&2 echo "Error; there are more than 0 occurrences of the word \"volatile\" in code files")
        flag=1
    fi
    if ((flag == 1)); then
        (>&2 echo "Please fix the above errors, exiting")
        exit 1
    fi

    # Basic checks for Student.hpp
    local public_count=$(grep -ow "public" ./Student.hpp | wc -l)
    local protected_count=$(grep -ow "protected" ./Student.hpp | wc -l)
    local private_count=$(grep -ow "private" ./Student.hpp | wc -l)
    local friend_count=$(grep -ow "friend" ./Student.hpp | wc -l)
    local num_students_count=$(grep -ow "static int numStudents" ./Student.hpp | wc -l)
    local brace_count=$(grep -o "}" ./Student.hpp | wc -l)
    if ((public_count == 0)); then
        (>&2 echo "Error: could not find public section of Student class")
        flag=1
    fi
    if ((public_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of the word \"public\" in Student.hpp")
        flag=1
    fi
    if ((protected_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"protected\" in Student.hpp")
        flag=1
    fi
    if ((private_count == 0)); then
        (>&2 echo "Error: could not find private section of Student class")
        flag=1
    fi
    if ((private_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of the word \"private\" in Student.hpp")
        flag=1
    fi
    if ((friend_count > 0)); then
        (>&2 echo "Error: there are more than 0 occurrences of the word \"friend\" in Student.hpp")
        flag=1
    fi
    if ((num_students_count == 0)); then
        (>&2 echo "Error: could not find line \"static int numStudents\" in Student.hpp")
        flag=1
    fi
    if ((num_students_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of the line \"static int numStudents\" in Student.hpp")
        flag=1
    fi
    if ((brace_count == 0)); then
        (>&2 echo "Error: could not find \"}\" in Student.hpp")
        flag=1
    fi
    if ((brace_count > 1)); then
        (>&2 echo "Error: there is more than 1 occurrence of \"}\" in Student.hpp. Make sure the implementations of all methods are in Student.cpp.")
        flag=1
    fi
    if ((flag == 1)); then
        (>&2 echo "Please fix the above errors in Student.hpp, exiting")
        exit 1
    fi

    # More advanced checks for Student.hpp
    cmp <(grep -v "^//" "$INPUT_DIR/Student.hpp" | head -n20) <(grep -v "^//" ./Student.hpp | head -n20 | tr -d "\r") > /dev/null 2>&1
    if (($? != 0)); then
        (>&2 echo "Warning: changes to first 20 lines of code (ignoring the file comment) in Student.hpp")
    fi
    cmp <(tail -n78 "$INPUT_DIR/Student.hpp") <(tail -n78 ./Student.hpp | tr -d "\r") > /dev/null 2>&1
    if (($? != 0)); then
        (>&2 echo "Warning: changes to last 78 lines of Student.hpp")
    fi
    local modified=$(head -n-78 ./Student.hpp | grep -v "^//" | tail -n+21)
    local semicolon_count=$(echo "$modified" | grep -o ";" | wc -l)
    local function_count=$(echo "$modified" | grep -o ") *;" | wc -l)
    if ((function_count < semicolon_count)); then
        (>&2 echo "Warning: found $semicolon_count occurrences of \";\" and $function_count occurrences of \")\" followed by \";\" in modified section of Student.hpp. You may only define new methods, not new instance variables, in Student.hpp.")
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

# Runs the test case specified by the argument.
# @param $1: the name of the test case
# @return 0 if the test passes, or non-zero if it fails
run_test() {
    local test_status
    ./a4test --gtest_filter="A4Test.$1"
    test_status=$?
    rm -rf ./testCleanReviewRatings.txt ./testCleanReviews.txt ./testRatings.txt
    return $test_status
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

    # Compile code into ./a4test
    g++ -std=c++11 "${CPP_FILES[@]/#/.\/}" ./main.cpp -o ./a4test
    if (($? != 0)); then
        (>&2 echo "Could not compile code, exiting")
        exit 1
    fi
    rm -rf ./a4test

    # Compile unit tests into ./a4test
    g++ -std=c++11 -isystem "$GTEST_INCLUDE" -pthread "${CPP_FILES[@]/#/.\/}" ./test.c "$LIB_DIR/libgtest.a" -o ./a4test
    if (($? != 0)); then
        (>&2 echo "Could not compile unit tests, exiting")
        exit 1
    fi

    # Run unit tests
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
