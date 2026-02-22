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


. contrib/oss-fuzz/build.sh
