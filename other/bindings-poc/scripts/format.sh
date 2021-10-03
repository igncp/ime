#!/usr/bin/env bash

set -e

find \
  . \
  -type f \
  -name "*.[c|h]" \
  -or -name "*.cc" \
  | \
    xargs \
      -I {} \
    astyle \
      -n \
      --style=allman \
      --indent-after-parens \
      --formatted \
      {}
