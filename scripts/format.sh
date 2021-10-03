#!/usr/bin/env bash

set -e

find \
  . \
  -type f \
  ! -path "*node_modules*" \
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
