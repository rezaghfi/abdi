
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"

namespace ns3 {

  int main(int argc, char* argv[])
  {
    CommandLine cmd;
    cmd.Parse(argc, argv);

    AnnotatedTopologyReader topologyReader("", 25);
    //topologyReader.SetFileName("src/ndnSIM/examples/topologies/sprintHighConTopo.txt");
    //topologyReader.SetFileName("src/ndnSIM/examples/topologies/sprintMediumConTopo.txt");
    topologyReader.SetFileName("src/ndnSIM/examples/topologies/sprintLowConTopo.txt");
    topologyReader.Read();

    // Install NDN stack on all nodes
    ndn::StackHelper ndnHelper;
    //set lru for replacement
    ndnHelper.setPolicy("nfd::cs::lru");
 
    ndnHelper.InstallAll();

    // Set strategy
    ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/best-route");
    //ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/rfa");
    //ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/saf");
    //ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/smdp");
    //ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/lamdp");
    //ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/amif");

    // Installing global routing interface on all nodes
    ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
    ndnGlobalRoutingHelper.InstallAll();

    // Getting containers for the consumer/producer
    Ptr<Node> producer = Names::Find<Node>("Node42");
    Ptr<Node> consumer = Names::Find<Node>("Node12");
    // IF ERROR
    // NodeContainer consumerNodes;
    // consumerNodes.Add(Names::Find<Node>("Node12"));

    // Install NDN applications
    std::string prefix = "/prefix";

    // send interest in constant rate
    ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
    //ndn::AppHelper consumerHelper("ns3::ndn::ConsumerZipfMandelbrot");
    consumerHelper.SetPrefix(prefix);
    consumerHelper.SetAttribute("Frequency", StringValue("4000")); // interests per second

    consumerHelper.Install(consumer);

    ndn::AppHelper producerHelper("ns3::ndn::Producer");
    producerHelper.SetPrefix(prefix);
    producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
    producerHelper.Install(producer);


    // Add /prefix origins to ndn::GlobalRouter
    ndnGlobalRoutingHelper.AddOrigins(prefix, producer);

    // Calculate and install FIBs
    ndn::GlobalRoutingHelper::CalculateRoutes();

    Simulator::Stop(Seconds(50.0));

    // tracer --------- it for rate trace and drop trace
    ndn::L3RateTracer::InstallAll("output/rate-trace.txt", Seconds(0.5));
    L2RateTracer::InstallAll("output/drop-trace.txt", Seconds(0.5));
    //ndn::AppDelayTracer::InstallAll("output/app-delays-trace.txt");

    Simulator::Run();
    Simulator::Destroy();

    return 0;
  }

} // namespace ns3

int main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
