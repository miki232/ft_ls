#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

# Test counter
TOTAL=0
PASSED=0

# Create logs directory
LOGS_DIR="valgrind_logs"
mkdir -p "$LOGS_DIR"

# Function to compare outputs
compare_outputs() {
    local test_name="$1"
    local cmd="$2"
    local log_file="$LOGS_DIR/test_${TOTAL}_${test_name// /_}.log"
    ((TOTAL++))

    echo -e "\n${BLUE}Test $TOTAL: $test_name${NC}"
    echo "Command: $cmd"

    # Set LC_ALL=C for both commands
    export LC_ALL=C

    # Run original ls and your ft_ls
    eval "$cmd" > ls_output 2>&1
    eval "./ft_ls ${cmd#ls}" > ft_ls_output 2>&1

    # Compare outputs
    if diff ls_output ft_ls_output > /dev/null; then
        echo -e "${GREEN}OK${NC}"
        ((PASSED++))
    else
        echo -e "${RED}ERROR${NC}"

        # Save detailed log
        {
            echo "Test: $test_name"
            echo "Command: $cmd"
            echo -e "\nExpected output:"
            cat ls_output
            echo -e "\nYour output:"
            cat ft_ls_output
            echo -e "\nDiff:"
            diff ls_output ft_ls_output
            echo -e "\nTimestamp: $(date)"
        } > "$log_file"

        echo "Log saved to: $log_file"
    fi
}

# Function to check memory leaks
check_memory() {
    local cmd="$1"
    local test_name="$2"
    local log_file="$LOGS_DIR/valgrind_${test_name// /_}.log"

    echo -e "\n${BLUE}Checking memory leaks for: $cmd${NC}"

    # Run Valgrind and save output to temporary file
    valgrind --leak-check=full --error-exitcode=1 --log-file="$log_file" ./ft_ls ${cmd#ls} > /dev/null 2>&1

    if [ $? -eq 0 ]; then
        echo -e "${GREEN}No memory leaks${NC}"
        rm "$log_file"  # Remove log file if no errors
    else
        echo -e "${RED}Memory leaks detected${NC}"
        echo "Valgrind log saved to: $log_file"
    fi
}

# Setup test environment
echo "Setting up test environment..."
mkdir -p test_dir/subdir1/subdir2
mkdir -p test_dir/empty_dir
touch test_dir/file1
touch test_dir/file2
touch test_dir/.hidden1
touch test_dir/.hidden2
touch test_dir/subdir1/file3
touch test_dir/subdir1/.hidden3
ln -s file1 test_dir/symlink1
chmod 644 test_dir/file1
chmod 755 test_dir/subdir1
sleep 1
touch test_dir/newer_file

# Basic tests
compare_outputs "Basic ls" "ls test_dir"
compare_outputs "Hidden files (-a)" "ls -a test_dir"
compare_outputs "Long format (-l)" "ls -l test_dir"
compare_outputs "Recursive (-R)" "ls -R test_dir"
compare_outputs "Reverse sort (-r)" "ls -r test_dir"
compare_outputs "Time sort (-t)" "ls -t test_dir"

# Combination tests
compare_outputs "Long + Hidden (-la)" "ls -la test_dir"
compare_outputs "Long + Recursive (-lR)" "ls -lR test_dir"
compare_outputs "All options (-laRrt)" "ls -laRrt test_dir"

# Edge cases
compare_outputs "Empty directory" "ls test_dir/empty_dir"
compare_outputs "Multiple directories" "ls test_dir test_dir/subdir1"
compare_outputs "Non-existent directory" "ls nonexistent"
compare_outputs "Current directory (.)" "ls ."
compare_outputs "Parent directory (..)" "ls .."
compare_outputs "Symbolic links with -l" "ls -l test_dir/symlink1"

# Additional format tests
compare_outputs "Multiple options separated (-l -a -t)" "ls -l -a -t test_dir"
compare_outputs "Combined reverse time sort (-rt)" "ls -rt test_dir"
compare_outputs "Long reverse sort (-lr)" "ls -lr test_dir"

# Check all test cases for memory leaks
for cmd in "test_dir" "-a test_dir" "-l test_dir" "-R test_dir" "-r test_dir" "-t test_dir" \
           "-la test_dir" "-lR test_dir" "-laRrt test_dir" "test_dir/empty_dir" \
           "test_dir test_dir/subdir1" "nonexistent" "." ".." "-l test_dir/symlink1"; do
    check_memory "$cmd" "${cmd// /_}"
done

# Cleanup
rm -rf test_dir ls_output ft_ls_output

# Save summary to log file
{
    echo "Test Summary"
    echo "------------"
    echo "Total tests: $TOTAL"
    echo "Passed tests: $PASSED"
    echo "Failed tests: $((TOTAL-PASSED))"
    echo "Test date: $(date)"
} > "$LOGS_DIR/summary.log"

# Print summary
echo -e "\n${BLUE}Test Summary${NC}"
echo "Total tests: $TOTAL"
echo "Passed tests: $PASSED"
echo "Failed tests: $((TOTAL-PASSED))"
echo -e "Logs directory: $LOGS_DIR"

if [ $TOTAL -eq $PASSED ]; then
    echo -e "${GREEN}All tests passed!${NC}"
else
    echo -e "${RED}Some tests failed. Check the logs in $LOGS_DIR for details.${NC}"
fi