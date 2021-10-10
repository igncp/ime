#!/bin/bash

set -e

npm run clean

npm run build

npm run lint

npm run check:ts
