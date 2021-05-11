#!/bin/bash

set -e

make

export REPO_ROOT=$PWD

bash ./tests/unit-test/test-unit.sh
bash ./tests/issue/test-issue.sh
