curl https://www.linux-projects.org/listing/uv4l_repo/lpkey.asc | sudo apt-key add -
sudo echo "\n\ndeb http://www.linux-projects.org/listing/uv4l_repo/raspbian/stretch stretch main\n" >> /etc/apt/sources.list

sudo apt update
sudo apt install cmake liblog4cpp5-dev libv4l-dev git vim uv4l uv4l-server uv4l-raspicam uv4l-raspicam-extras
sudo cp -f uv4l-raspicam.conf /etc/uv4l/

sudo cp -f uv4l_raspicam.service /etc/systemd/system/uv4l_raspicam.service/

