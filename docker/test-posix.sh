#!/bin/bash 
cd test/
source  ~/zephyrproject/zephyr/zephyr-env.sh
source ~/zephyrproject/.venv/bin/activate
find / -name west 
echo $PATH
west build -b=native_posix
west build -t run
