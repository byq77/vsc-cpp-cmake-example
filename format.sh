#!/bin/bash

# Format all C++ files in the project
# Excludes build, install, .git, and other common directories

find . -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \) \
    -not -path '*/build/*' \
    -not -path '*/install/*' \
    -not -path '*/.git/*' \
    -not -path '*/CMakeFiles/*' \
    -not -path '*/cmake-build-*/*' \
    -not -path '*/node_modules/*' \
    -not -path '*/.vscode/*' \
    -not -path '*/.github/*' \
    -exec clang-format -i {} \;

echo "C++ formatting complete!"
