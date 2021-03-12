sudo ssh-keygen -A &&
sudo update-rc.d ssh enable &&
sudo invoke-rc.d ssh start &&
echo "SSH enabled"

