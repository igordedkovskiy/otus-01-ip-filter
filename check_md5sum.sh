#!/bin/bash
#!/bin/sh

answer=$(cat ./ip_filter.tsv | ./ip_filter | md5sum)
answer=${answer:0:32}
md5="24e7a7b2270daee89c64d3ca5fb3da1a"

if [ "$answer" != "$md5" ]; then
    exit 1
fi

exit 0
