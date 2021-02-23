
sudo rm /etc/localtime
echo "Europe/Helsinki" | sudo tee /etc/timezone
dpkg-reconfigure -f noninteractive tzdata

