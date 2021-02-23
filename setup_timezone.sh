
sudo rm /etc/localtime
echo "Europe/Helsinki" | sudo tee /etc/timezone
sudo dpkg-reconfigure -f noninteractive tzdata

