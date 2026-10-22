mkdir -p seeds && \
    wget -qO- https://samples.ffmpeg.org/MPEG-4/ \
    | grep -oP '(?<=href=")[^"]+\.mp4' \
    | xargs -I{} wget -P seeds https://samples.ffmpeg.org/MPEG-4/{}
zip -r seeds_p1.zip seeds_p1
zip -r seeds_p2.zip seeds_p2