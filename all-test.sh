#!/bin/bash

set -e

make

export REPO_ROOT=$PWD

bash ./tests/unit-test/test-units.sh
bash ./tests/issue/test-issues.sh
