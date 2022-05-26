cd NFD
git checkout master1
cd ../../../
NS_LOG=ndn-cxx.nfd.SoltaniStrategy ./waf --run=5-soltani
cd src/ndnSIM/NFD
git checkout master
cd ..