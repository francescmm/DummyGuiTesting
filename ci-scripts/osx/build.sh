export PATH="/usr/local/opt/qt/bin:$PATH"
source ~/.bash_profile
export LDFLAGS="-L/usr/local/opt/qt/lib"
export CPPFLAGS="-I/usr/local/opt/qt/include"
cd DummyGui
qmake DummyGui.pro
make
cd ..
cd DummyTesting
qmake DummyTesting.pro
make
./DummyTesting.app/Contents/MacOS/DummyTesting
