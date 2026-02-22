#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

pushd $SCRIPT_DIR/infra/base-images/base-runner
docker build -t gcr.io/oss-fuzz-base/base-runner:custom .
popd