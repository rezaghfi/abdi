#bash
cd NFD
git checkout master1
cd ../../../
#NS_LOG=ndn-cxx.nfd.BestRouteStrategy ./waf --run=1-variousSpeed
#NS_LOG=ndn-cxx.nfd.RFAStrategy ./waf --run=1-variousSpeed
#NS_LOG=ndn-cxx.nfd.SAFStrategy ./waf --run=1-variousSpeed
#NS_LOG=ndn-cxx.nfd.SMDPStrategy ./waf --run=1-variousSpeed
#NS_LOG=ndn-cxx.nfd.LAMDPStrategy ./waf --run=1-variousSpeed
NS_LOG=ndn-cxx.nfd.AMIFStrategy ./waf --run=1-variousSpeed

#NS_LOG=ndn-cxx.nfd.BestRouteStrategy ./waf --run=2-variousCache
#NS_LOG=ndn-cxx.nfd.RFAStrategy ./waf --run=2-variousCache
#NS_LOG=ndn-cxx.nfd.SAFStrategy ./waf --run=2-variousCache
#NS_LOG=ndn-cxx.nfd.SMDPStrategy ./waf --run=2-variousCache
#NS_LOG=ndn-cxx.nfd.LAMDPStrategy ./waf --run=2-variousCache
#NS_LOG=ndn-cxx.nfd.AMIFStrategy ./waf --run=2-variousCache

#NS_LOG=ndn-cxx.nfd.BestRouteStrategy ./waf --run=3-variousTopology
#NS_LOG=ndn-cxx.nfd.RFAStrategy ./waf --run=3-variousTopology
#NS_LOG=ndn-cxx.nfd.SAFStrategy ./waf --run=3-variousTopology
#NS_LOG=ndn-cxx.nfd.SMDPStrategy ./waf --run=3-variousTopology
#NS_LOG=ndn-cxx.nfd.LAMDPStrategy ./waf --run=3-variousTopology
#NS_LOG=ndn-cxx.nfd.AMIFStrategy ./waf --run=3-variousTopology

#NS_LOG=ndn-cxx.nfd.BestRouteStrategy ./waf --run=4-variousLinkFailure
#NS_LOG=ndn-cxx.nfd.RFAStrategy ./waf --run=4-variousLinkFailure
#NS_LOG=ndn-cxx.nfd.SAFStrategy ./waf --run=4-variousLinkFailure
#NS_LOG=ndn-cxx.nfd.SMDPStrategy ./waf --run=4-variousLinkFailure
#NS_LOG=ndn-cxx.nfd.LAMDPStrategy ./waf --run=4-variousLinkFailure
#NS_LOG=ndn-cxx.nfd.AMIFStrategy ./waf --run=4-variousLinkFailure
cd src/ndnSIM/NFD
git checkout master
cd ..