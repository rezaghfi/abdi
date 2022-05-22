sudo apt install build-essential libsqlite3-dev libboost-all-dev libssl-dev git python3-setuptools castxml
sudo apt install gir1.2-goocanvas-2.0 gir1.2-gtk-3.0 libgirepository1.0-dev python3-dev python3-gi python3-gi-cairo python3-pip python3-pygraphviz python3-pygccxml
sudo pip3 install kiwi
cd NFD
git checkout master1
cd ../../../
./waf configure --enable-examples
./waf
cd src/ndnSIM/NFD
git checkout master
cd ..