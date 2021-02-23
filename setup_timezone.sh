
rm /etc/localtime
echo "Europe/Helsinki" > /etc/timezone
dpkg-reconfigure -f noninteractive tzdata

