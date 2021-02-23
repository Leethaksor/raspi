ssh-keygen -A &&
update-rc.d ssh enable &&
invoke-rc.d ssh start &&
echo "SSH enabled"

