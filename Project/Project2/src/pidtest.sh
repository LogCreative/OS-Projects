sudo insmod pid.ko
echo "2266" > /proc/pid
cat /proc/pid
sudo rmmod pid
dmesg