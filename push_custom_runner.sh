#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

GHCR_USER="gabe-sherman"
IMAGE_NAME="oss-fuzz-base-runner"
TAG="latest"
FULL_IMAGE="ghcr.io/${GHCR_USER}/${IMAGE_NAME}:${TAG}"
LOCAL_DEV_IMAGE="gcr.io/oss-fuzz-base/base-runner:custom"

pushd $SCRIPT_DIR/infra/base-images/base-runner
echo "Building ${FULL_IMAGE}"
docker build -t "$FULL_IMAGE" .
docker build -t "$LOCAL_DEV_IMAGE" .
popd
docker push "${FULL_IMAGE}"