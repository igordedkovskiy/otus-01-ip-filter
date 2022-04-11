#!/bin/sh
#!/bin/bash

answer=$(cat ./ip_filter.tsv | ./ip_filter | md5sum)
answer=${answer:0:32}
#echo $answer
md5="24e7a7b2270daee89c64d3ca5fb3da1a"

#if [ "$answer" -ne "$md5" ] # for integers
if [ "$answer" != "$md5" ]; then # for strings
	exit 1
fi

exit 0
