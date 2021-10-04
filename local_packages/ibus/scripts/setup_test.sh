#!/bin/bash

set -e

# @TODO
sudo sed -i \
  's|<exec>.*$|<exec>/home/igncp/development/ime/local_packages/ibus/scripts/test_custom_ime</exec>|' \
  /usr/share/ibus/component/custom-ime.xml

echo "XML file updated"
