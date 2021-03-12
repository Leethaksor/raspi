curl https://www.linux-projects.org/listing/uv4l_repo/lpkey.asc | sudo apt-key add -
echo "deb http://www.linux-projects.org/listing/uv4l_repo/raspbian/stretch stretch main" | sudo tee -a /etc/apt/sources.list

sudo apt update
sudo apt install cmake liblog4cpp5-dev libv4l-dev git vim uv4l uv4l-server uv4l-raspicam uv4l-raspicam-extras -y
sudo cp -f ./uv4l-raspicam.conf /etc/uv4l/uv4l-raspicam.conf

sudo cp -f ./uv4l_raspicam.service /etc/systemd/system/uv4l_raspicam.service/uv4l_raspicam.service

sudo cp -f ./uv4l-time-overlay.cpp /usr/share/uv4l/raspicam/uv4l-time-overlay.cpp
cd /usr/share/uv4l/raspicam/
sudo g++ -o uv4l-time-overlay uv4l-time-overlay.cpp -std=c++11
sudo cp -f ./uv4l_raspicam_text.service /etc/systemd/system/uv4l_raspicam_text.service

cd
git clone https://github.com/mpromonet/v4l2rtspserver.git

cd v4l2rtspserver/
cmake .
make
sudo make install

echo "please reboot"


