#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

GHCR_USER="gabe-sherman"
IMAGE_NAME="oss-fuzz-base-runner"
TAG="latest"
FULL_IMAGE="ghcr.io/${GHCR_USER}/${IMAGE_NAME}:${TAG}"

pushd $SCRIPT_DIR/infra/base-images/base-runner
echo "Building ${FULL_IMAGE}"
docker build -t "$FULL_IMAGE" .
popd
docker push "${FULL_IMAGE}"