#!/usr/bin/env bash

set -eo pipefail

false | true
echo "won't be printed" # この行は実行されない
