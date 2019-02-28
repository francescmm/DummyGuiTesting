QTDIR="/opt/qt59"
PATH="$QTDIR/bin:$PATH"
qt57-env.sh

cd DummyGui
qmake DummyGui.pro
make -j 2
cd ..
cd DummyTesting
qmake DummyTesting.pro
make -j 2
./DummyTesting
