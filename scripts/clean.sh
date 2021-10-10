#!/bin/bash

set -e

# loop in future if too many

(cd local_packages/libnotify && npm run clean)
(cd local_packages/ibus && npm run clean)
