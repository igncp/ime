#!/bin/bash

set -e

# loop in future if too many

(cd local_packages/libnotify && npm run build)
(cd local_packages/ibus && npm run build)
