#!/bin/bash

set -e

killall ibus-daemon || true

ibus-daemon -rv
