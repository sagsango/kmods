#!/bin/bash
set -x
lsmod
sudo dmesg clear
sudo insmod hw4.ko int_str="1,2,3,4,5"
cat /proc/hw4
sudo rmmod hw4.ko
sudo dmesg | tail -n 5
