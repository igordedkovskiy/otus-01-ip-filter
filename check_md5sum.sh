#!/bin/bash
#!/bin/sh

answer=$(cat ./ip_filter.tsv | ./Release/ip_filter | md5sum)
answer=${answer:0:32}
#md5="24e7a7b2270daee89c64d3ca5fb3da1a"
md5="36b72c25de983078b68625b7610e7673"

echo $answer
echo $md5

#if [ "$answer" -ne "$md5" ] # for integers
if [ "$answer" != "$md5" ]; then # for strings
	exit 1
fi

exit 0