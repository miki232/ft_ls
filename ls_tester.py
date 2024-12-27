import subprocess
import os
import difflib
import argparse

def run_command(cmd):
    try:
        # Add -C flag to ls but not ft_ls
        if cmd.startswith('ls '):
            cmd = cmd.replace('ls ', 'ls -C ')
        result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        return result.stdout, result.stderr
    except Exception as e:
        return "", str(e)

def compare_outputs(test_name, ft_ls_out, ls_out):
    diff = list(difflib.unified_diff(
        ft_ls_out.splitlines(),
        ls_out.splitlines(),
        fromfile='ft_ls',
        tofile='ls',
        lineterm=''
    ))

    if diff:
        print(f"\n❌ {test_name} - FAILED")
        print('\n'.join(diff[:20]))  # Show first 20 lines of diff
        return False
    print(f"✅ {test_name} - PASSED")
    return True

def run_tests():
    test_cases = [
        ("Basic ls", ""),
        ("List all", "-a"),
        ("Long format", "-l"),
        ("Recursive", "-R"),
        ("Sort by time", "-t"),
        ("Reverse sort", "-r"),
        ("Combined flags", "-la"),
        ("Complex combination", "-laRt"),
    ]

    passed = 0
    total = len(test_cases)

    for name, flags in test_cases:
        print(f"\nRunning test: {name}")
        ft_ls_out, ft_ls_err = run_command(f"./ft_ls {flags}")
        ls_out, ls_err = run_command(f"ls {flags}")

        if compare_outputs(name, ft_ls_out, ls_out):
            passed += 1

        # Check error handling
        if ft_ls_err != ls_err:
            print(f"❌ Error handling differs:")
            print(f"ft_ls error: {ft_ls_err}")
            print(f"ls error: {ls_err}")

    print(f"\nTest Summary: {passed}/{total} tests passed")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Test ft_ls against system ls')
    args = parser.parse_args()
    run_tests()