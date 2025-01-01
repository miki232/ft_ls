#!/bin/bash

# Tester for ft_ls - Mandatory Part
# Compare ft_ls output to the system ls command for mandatory options
# Includes memory leak checks using Valgrind

# Paths
FT_LS=./ft_ls  # Path to your ft_ls executable
SYS_LS=/bin/ls  # Path to the system ls

# Directories and files to test
TEST_DIR="test_dir"
DIFF_DIR="diff_logs"
VALGRIND_DIR="valgrind_logs"
mkdir -p $TEST_DIR
mkdir -p $DIFF_DIR
mkdir -p $VALGRIND_DIR

# Prepare test files and directories
touch $TEST_DIR/file1
mkdir -p $TEST_DIR/subdir
ln -s $TEST_DIR/file1 $TEST_DIR/symlink
touch $TEST_DIR/.hidden_file

# Helper function to run tests
run_test() {
    local description="$1"
    local options="$2"
    local log_file="$DIFF_DIR/$(echo "$description" | tr ' ' '_').log"
    local valgrind_log="$VALGRIND_DIR/$(echo "$description" | tr ' ' '_').log"

    # Run the system ls and ft_ls commands
    $SYS_LS $options $TEST_DIR > sys_ls_output.txt
    $FT_LS $options $TEST_DIR > ft_ls_output.txt

    # Sort both outputs and compare them to ignore the order
    sort sys_ls_output.txt > sys_ls_sorted.txt
    sort ft_ls_output.txt > ft_ls_sorted.txt

    # Compare sorted outputs
    if diff -u sys_ls_sorted.txt ft_ls_sorted.txt > "$log_file"; then
        echo "ok"
        rm -f "$log_file"
    else
        echo "ko"
    fi

    # Run Valgrind to check for memory leaks
    valgrind --leak-check=full --log-file="$valgrind_log" $FT_LS $options $TEST_DIR > /dev/null 2>&1
    if grep -q "All heap blocks were freed -- no leaks are possible" "$valgrind_log"; then
        echo "Valgrind: no leaks"
        rm -f "$valgrind_log"
    else
        echo "Valgrind: leaks found (see $valgrind_log)"
    fi

    # Clean up temporary files
    rm -f sys_ls_output.txt ft_ls_output.txt sys_ls_sorted.txt ft_ls_sorted.txt
}

# Basic tests
run_test "Basic listing" ""
run_test "Listing with -l" "-l"
run_test "Listing with -a" "-a"
run_test "Listing with -R" "-R"
run_test "Listing with -r" "-r"
run_test "Listing with -t" "-t"

# Combined options
run_test "Listing with -la" "-la"
run_test "Listing with -ltr" "-ltr"

# Clean up
rm -rf $TEST_DIR
