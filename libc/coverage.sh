#!/bin/sh
lcov -c --rc lcov_branch_coverage=1 -d CMakeFiles/fslc.dir/src -o coverage.info
genhtml coverage.info --branch-coverage -o cov_report
