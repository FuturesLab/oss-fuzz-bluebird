#!/bin/bash -eu
# Copyright 2018 Google Inc.
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


# build script moves header file, make sure to copy it back to source for rebuilding
export WORK=/worktmp
mkdir -p $WORK

cp $WORK/lib/* $SRC/jbigkit/libjbig/ 2>/dev/null || true
cp $WORK/include/* $SRC/jbigkit/libjbig/ 2>/dev/null || true

# mkdir commands run into issues when building normally
echo '#!/bin/bash' > /usr/local/bin/mkdir
echo '/bin/mkdir -p "$@"' >> /usr/local/bin/mkdir
chmod +x /usr/local/bin/mkdir

pushd "$SRC/zlib"
./configure --static --prefix="$WORK"
make -j$(nproc) CFLAGS="$CFLAGS -fPIC"
make install
popd

# Build libjpeg-turbo
pushd "$SRC/libjpeg-turbo"
cmake . -DCMAKE_INSTALL_PREFIX=$WORK -DENABLE_STATIC=on -DENABLE_SHARED=off
make -j$(nproc)
make install
popd

# Build libjbig
pushd "$SRC/jbigkit"
if [ "$ARCHITECTURE" = "i386" ]; then
    echo "#!/bin/bash" > gcc
    echo "clang -m32 \$*" >> gcc
    chmod +x gcc
    PATH=$PWD:$PATH make lib
else
    make lib
fi

mv "$SRC"/jbigkit/libjbig/*.a "$WORK/lib/"
mv "$SRC"/jbigkit/libjbig/*.h "$WORK/include/"
popd

cmake . -DCMAKE_INSTALL_PREFIX=$WORK -DBUILD_SHARED_LIBS=off
make -j$(nproc)
make install

if [ "$ARCHITECTURE" = "i386" ]; then
    $CXX $CXXFLAGS -std=c++11 -I$WORK/include \
        $SRC/libtiff/contrib/oss-fuzz/tiff_read_rgba_fuzzer.cc -o $OUT/tiff_read_rgba_fuzzer \
        $LIB_FUZZING_ENGINE $WORK/lib/libtiffxx.a $WORK/lib/libtiff.a $WORK/lib/libz.a $WORK/lib/libjpeg.a \
        $WORK/lib/libjbig.a $WORK/lib/libjbig85.a
else
    $CXX $CXXFLAGS -std=c++11 -I$WORK/include \
        $SRC/libtiff/contrib/oss-fuzz/tiff_read_rgba_fuzzer.cc -o $OUT/tiff_read_rgba_fuzzer \
        $LIB_FUZZING_ENGINE $WORK/lib/libtiffxx.a $WORK/lib/libtiff.a $WORK/lib/libz.a $WORK/lib/libjpeg.a \
        $WORK/lib/libjbig.a $WORK/lib/libjbig85.a -Wl,-Bstatic -llzma -Wl,-Bdynamic
fi

if [ ! -d "afl_testcases" ]; then
    mkdir afl_testcases
    (cd afl_testcases; tar xf "$SRC/afl_testcases.tgz")
    mkdir tif
    find afl_testcases -type f -name '*.tif' -exec mv -n {} tif/ \;
    zip -rj tif.zip tif/
    cp tif.zip "$OUT/tiff_read_rgba_fuzzer_seed_corpus.zip"
    cp "$SRC/tiff.dict" "$OUT/tiff_read_rgba_fuzzer.dict"
fi
