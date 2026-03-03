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

# Redundant 'find' commands for every build are costly, patch this out
python3 - <<'PY'
from pathlib import Path
p = Path("contrib/oss-fuzz/build.sh")
s = p.read_text()
old = """mkdir afl_testcases
(cd afl_testcases; tar xf "$SRC/afl_testcases.tgz")
mkdir tif
find afl_testcases -type f -name '*.tif' -exec mv -n {} tif/ \;
zip -rj tif.zip tif/
cp tif.zip "$OUT/tiff_read_rgba_fuzzer_seed_corpus.zip"
cp "$SRC/tiff.dict" "$OUT/tiff_read_rgba_fuzzer.dict"
"""
new = """if [ ! -d "afl_testcases" ]; then
    mkdir afl_testcases
    (cd afl_testcases; tar xf "$SRC/afl_testcases.tgz")
    mkdir tif
    find afl_testcases -type f -name '*.tif' -exec mv -n {} tif/ \;
    zip -rj tif.zip tif/
    cp tif.zip "$OUT/tiff_read_rgba_fuzzer_seed_corpus.zip"
    cp "$SRC/tiff.dict" "$OUT/tiff_read_rgba_fuzzer.dict"
fi
"""
if old in s:
    s = s.replace(old, new, 1)
    p.write_text(s)
PY


. contrib/oss-fuzz/build.sh
