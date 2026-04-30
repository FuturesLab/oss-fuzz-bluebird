mkdir -p seeds && \
    wget -qO- https://samples.ffmpeg.org/MPEG-4/ \
    | grep -oP '(?<=href=")[^"]+\.mp4' \
    | xargs -I{} wget -P seeds https://samples.ffmpeg.org/MPEG-4/{}