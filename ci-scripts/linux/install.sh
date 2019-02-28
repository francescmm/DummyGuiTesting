sudo add-apt-repository --yes ppa:beineri/opt-qt597-trusty
sudo add-apt-repository --yes ppa:achadwick/mypaint-testing
sudo apt-add-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install -y liblzo2-dev liblz4-dev libfreetype6-dev libpng-dev libegl1-mesa-dev libgles2-mesa-dev libsdl2-dev libglew-dev freeglut3-dev qt59script libsuperlu3-dev qt59svg qt59tools qt59multimedia wget libusb-1.0-0-dev libboost-all-dev liblzma-dev libjson-c-dev libmypaint-dev
sudo apt-get -qq install g++-4.9 libc6-i386 qt59tools qt59charts-no-lgpl
export CXX="g++-4.9 -std=c++14"
export CC="gcc-4.9"
export DISPLAY=:0.0
export XAUTHORITY=~/.Xauthority
sh -e /etc/init.d/xvfb start
