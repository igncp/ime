#!/bin/bash

set -e

./node_modules/.bin/eslint src

# loop in future if too many

(cd local_packages/libnotify && npm run lint)
(cd local_packages/ibus && npm run lint)
