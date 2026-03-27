#!/bin/bash -eu
# Copyright 2022 Google LLC
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
pushd $SRC
if [ ! -d openssl-3.0.19 ]; then
    tar -xf openssl-3.0.19.tar.gz
    cd openssl-3.0.19
    ./Configure linux-x86_64 no-tests
    make -j"$(nproc)"
    make install_sw
fi
popd

mkdir my_build

pushd my_build/
# cmake -DFUZZER=ON -DLIB_FUZZING_ENGINE="$LIB_FUZZING_ENGINE" \
cmake -DFUZZER=ON -DLIB_FUZZING_ENGINE="$LIB_FUZZING_ENGINE" \
    -DCMAKE_EXE_LINKER_FLAGS="-lm -Wl,-rpath,'\$ORIGIN/lib'" -DWITH_MYSQL=OFF -Wno-dev ../. -DBUILD_SHARED_LIBS=OFF
make -j$(nproc)
popd

$CC $CFLAGS -I$SRC/coturn/src/apps/common -I$SRC/coturn/src/client \
    -I$SRC/coturn/src/server -I$SRC/coturn/src \
    $SRC/coturn/fuzzing/FuzzStun.c -o $OUT/FuzzStun $LIB_FUZZING_ENGINE \
    $SRC/coturn/my_build/lib/libturn_server.a \
    $SRC/coturn/my_build/lib/libturncommon.a \
    $SRC/coturn/my_build/lib/libturnclient.a \
    $SRC/openssl-3.0.19/libssl.a \
    $SRC/openssl-3.0.19/libcrypto.a \
    -ldl -pthread -lm

pushd fuzzing/input/
# cp FuzzStun_seed_corpus.zip $OUT/FuzzStun_seed_corpus.zip
cp FuzzStunClient_seed_corpus.zip $OUT/FuzzStunClient_seed_corpus.zip

unzip -n FuzzStun_seed_corpus.zip -d combined
unzip -n FuzzStunClient_seed_corpus.zip -d combined
zip -r $OUT/FuzzStun_seed_corpus.zip combined/
popd

pushd /lib/x86_64-linux-gnu/
mkdir $OUT/lib/
cp libevent* $OUT/lib/.
popd
