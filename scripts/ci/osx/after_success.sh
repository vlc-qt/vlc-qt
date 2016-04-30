#!/bin/bash
set -ev

# Report code coverage
bash <(curl -s https://codecov.io/bash) -f build/coverage.info
