wget -O qt5.zip https://github.com/francescmm/ci-utils/releases/download/qt_5.13/qt5.zip;
unzip -qq qt5.zip -d qt5;
export PATH=`pwd`/qt5/bin:$PATH;
export QT_PLUGIN_PATH=`pwd`/qt5/plugins;
cd DummyGui
`pwd`/qt5/bin/qmake DummyGui.pro
make -j 2
cd ..
cd DummyTesting
`pwd`/qt5/bin/qmake DummyTesting.pro
make -j 2
./DummyTesting --platform offscreen
