#!/bin/bash -eu
# Copyright 2019 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
################################################################################

# Run the OSS-Fuzz script in the project.
apt-get update

export BUILD_ROOT=$PWD

echo "CC: ${CC:-}"
echo "CXX: ${CXX:-}"
echo "LIB_FUZZING_ENGINE: ${LIB_FUZZING_ENGINE:-}"
echo "CFLAGS: ${CFLAGS:-}"
echo "CXXFLAGS: ${CXXFLAGS:-}"
echo "OUT: ${OUT:-}"

export MAKEFLAGS+="-j$(nproc)"

# Install dependencies
# apt-get -y install autoconf autogen automake libtool pkg-config python

# For now, do not install the following libraries (as they won't be in the
# final image):
# libasound2-dev libflac-dev libogg-dev libopus-dev libvorbis-dev

# Compile the fuzzer.
autoreconf -vif
./configure --disable-shared --enable-ossfuzzers
make V=1

# Copy the fuzzer to the output directory.
cp -v ossfuzz/sndfile_fuzzer $OUT/
cp -v ossfuzz/sndfile_alt_fuzzer $OUT/

# To make CIFuzz fast, see here for details: https://github.com/libsndfile/libsndfile/pull/796
for fuzzer in sndfile_alt_fuzzer sndfile_fuzzer; do
  echo "[libfuzzer]" > ${OUT}/${fuzzer}.options
  echo "close_fd_mask = 3" >> ${OUT}/${fuzzer}.options
done

if [ -d $SRC/seeds ]; then 
  zip -r $OUT/sndfile_alt_fuzzer_seed_corpus.zip $SRC/seeds/*
fi
