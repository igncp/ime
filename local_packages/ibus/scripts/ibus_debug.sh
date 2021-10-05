#!/bin/bash

set -e

killall ibus-daemon || true

tmux split-window "ibus-daemon -rv"
