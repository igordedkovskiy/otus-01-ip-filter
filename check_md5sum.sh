#!/bin/bash
#!/bin/sh

answer=$(cat ./ip_filter.tsv | ./Release/ip_filter | md5sum)
answer=${answer:0:32}
md5="24e7a7b2270daee89c64d3ca5fb3da1a"

echo $answer
echo $md5

#if [ "$answer" -ne "$md5" ] # for integers
if [ "$answer" != "$md5" ]; then # for strings
    exit 0
fi

exit 1