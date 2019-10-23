QTDIR="/opt/qt513"
PATH="$QTDIR/bin:$PATH"

cd DummyGui
qmake DummyGui.pro
make -j 2
cd ..
cd DummyTesting
qmake DummyTesting.pro
make -j 2
./DummyTesting --platform offscreen
