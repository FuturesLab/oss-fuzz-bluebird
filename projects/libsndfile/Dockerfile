# Copyright 2020 Google Inc.
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

FROM gcr.io/oss-fuzz-base/base-builder

RUN apt-get -y install autoconf autogen automake libtool pkg-config python
RUN git clone --depth 1 https://github.com/libsndfile/libsndfile.git /src/libsndfile
RUN mkdir -p seeds && \
    for dir in A-codecs A-codecs/MP3 AIFF au; do \
        BASE_URL="https://samples.ffmpeg.org/$dir/"; \
        echo "Fetching samples from $BASE_URL..."; \
        wget -qO- "$BASE_URL" \
        | grep -oP '(?<=href=")[^"]+\.(wav|mp3|aif|aiff|au)' \
        | xargs -I{} wget -q -P seeds "$BASE_URL/{}"; \
    done


WORKDIR $SRC/libsndfile
COPY build.sh $SRC/
