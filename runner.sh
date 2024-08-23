#!/bin/bash

make gcov_report
cp -r report/* ../var/www/html
mv ../var/www/html/index.html ../var/www/html/index.nginx-debian.html
nginx -g "daemon off;"