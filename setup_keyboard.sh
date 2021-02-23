#https://raspberrypi.stackexchange.com/questions/5333/how-to-map-caps-lock-key-to-something-useful/45075

#/etc/default/keyboard

#sudo dpkg-reconfigure keyboard-configuration

sudo cp -f ./etc_default_keyboard /etc/default/keyboard

sudo dpkg-reconfigure -f noninteractive keyboard-configuration

sudo invoke-rc.d keyboard-setup start
sudo setsid sh -c 'exec setupcon -k --force <> /dev/tty1 >&0 2>&1'
sudo udevadm trigger --subsystem-match=input --action=change

