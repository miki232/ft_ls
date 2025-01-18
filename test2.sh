#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Counter for tests
TOTAL_TESTS=0
PASSED_TESTS=0

# Function to run test and check valgrind output
run_test() {
    local test_name="$1"
    local command="$2"
    ((TOTAL_TESTS++))

    echo -n "Testing $test_name... "

    # Run valgrind
    valgrind --leak-check=full --error-exitcode=1 --quiet $command > /dev/null 2>&1

    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${NC}"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}ERROR${NC}"
        echo "Command that failed: $command"
        # Run valgrind again with detailed output
        valgrind --leak-check=full $command
    fi
}

# Make sure the program exists and is executable
if [ ! -x "./ft_ls" ]; then
    echo -e "${RED}Error: ft_ls not found or not executable${NC}"
    exit 1
fi

# Create test directory structure
echo "Setting up test environment..."
mkdir -p test_dir/empty_dir
mkdir -p test_dir/subdir1/subdir2
touch test_dir/file1.txt
touch test_dir/file2.txt
touch test_dir/.hidden_file
touch test_dir/subdir1/file3.txt
ln -s test_dir/file1.txt test_dir/symlink
chmod 777 test_dir/file1.txt
chmod 444 test_dir/file2.txt

# Basic tests
run_test "Basic ls" "./ft_ls"
run_test "ls with directory" "./ft_ls test_dir"
run_test "ls with -l flag" "./ft_ls -l"
run_test "ls with -a flag" "./ft_ls -a"
run_test "ls with -R flag" "./ft_ls -R"
run_test "ls with multiple flags" "./ft_ls -la"
run_test "ls with multiple directories" "./ft_ls test_dir test_dir/subdir1"
run_test "ls with hidden files" "./ft_ls -a test_dir"
run_test "ls with symbolic link" "./ft_ls -l test_dir/symlink"
run_test "ls empty directory" "./ft_ls test_dir/empty_dir"
run_test "ls with invalid directory" "./ft_ls nonexistent_directory"
run_test "ls with mixed valid/invalid paths" "./ft_ls test_dir nonexistent_directory"
run_test "ls with all flags" "./ft_ls -laR test_dir"
run_test "ls with repeated flags" "./ft_ls -ll -aa test_dir"
run_test "ls with current and parent directory" "./ft_ls . .."

# Complex combinations
run_test "Complex test 1" "./ft_ls -la test_dir/subdir1 test_dir/empty_dir"
run_test "Complex test 2" "./ft_ls -R test_dir/subdir1 ."
run_test "Complex test 3" "./ft_ls -laR test_dir/. test_dir/.."

# Clean up test directory
echo "Cleaning up test environment..."
rm -rf test_dir

# Print summary
echo "----------------------------------------"
echo "Test Summary:"
echo "Total tests: $TOTAL_TESTS"
echo "Passed tests: $PASSED_TESTS"
echo "Failed tests: $((TOTAL_TESTS - PASSED_TESTS))"
if [ $TOTAL_TESTS -eq $PASSED_TESTS ]; then
    echo -e "${GREEN}All tests passed!${NC}"
else
    echo -e "${RED}Some tests failed.${NC}"
    exit 1
fi