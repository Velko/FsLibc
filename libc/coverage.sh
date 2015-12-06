#!/bin/sh
lcov -c --rc lcov_branch_coverage=1 -d Debug -o Debug/coverage.info
genhtml Debug/coverage.info --branch-coverage -o cov_report
