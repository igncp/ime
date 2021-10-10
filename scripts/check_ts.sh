#!/bin/bash

set -e

./node_modules/.bin/tsc --project .

# loop in future if too many

(cd local_packages/libnotify && npm run check:ts)
(cd local_packages/ibus && npm run check:ts)
