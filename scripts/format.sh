#!/bin/bash
set -e

if ! command -v clang-format &> /dev/null; then
    echo "Error: clang-format not found. Install it with: brew install clang-format"
    exit 1
fi

find src -name "*.cpp" -o -name "*.h" | xargs clang-format -i
