for dir in A-codecs A-codecs/MP3 AIFF au; do \
    BASE_URL="https://samples.ffmpeg.org/$dir/"; \
    echo "Fetching samples from $BASE_URL..."; \
    wget -qO- "$BASE_URL" \
    | grep -oP '(?<=href=")[^"]+\.(wav|mp3|aif|aiff|au)' \
    | xargs -I{} wget -q -P seeds "$BASE_URL/{}"; \
done