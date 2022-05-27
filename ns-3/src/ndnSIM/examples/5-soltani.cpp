
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"

namespace ns3 {

  int main(int argc, char* argv[])
  {
    CommandLine cmd;
    cmd.Parse(argc, argv);

    AnnotatedTopologyReader topologyReader("", 25);
    topologyReader.SetFileName("src/ndnSIM/examples/topologies/n50.txt");
    topologyReader.Read();

    // Install NDN stack on all nodes
    ndn::StackHelper ndnHelper;
    //set soltani for replacement
    ndnHelper.setPolicy("nfd::cs::soltani");
    ndnHelper.setCsSize(1000);
    ndnHelper.InstallAll();

    // Set strategy
    ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/soltani");

    // Installing global routing interface on all nodes
    ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
    ndnGlobalRoutingHelper.InstallAll();

    // Getting containers for the consumer/producer
    Ptr<Node> producer = Names::Find<Node>("s1");
    Ptr<Node> consumer = Names::Find<Node>("c1");
    // IF ERROR
    // NodeContainer consumerNodes;
    // consumerNodes.Add(Names::Find<Node>("Node12"));

    // Install NDN applications
    std::string prefix = "/prefix";

    // send interest in constant rate
    ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
    consumerHelper.SetPrefix(prefix);
    consumerHelper.SetAttribute("Frequency", StringValue("200")); // interests per second
    //consumerHelper.SetAttribute("Frequency", StringValue("250")); // interests per second
    //consumerHelper.SetAttribute("Frequency", StringValue("300")); // interests per second
    //consumerHelper.SetAttribute("Frequency", StringValue("350")); // interests per second
    //consumerHelper.SetAttribute("Frequency", StringValue("400")); // interests per second
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
    ndn::AppDelayTracer::InstallAll("output/app-delays-trace.txt");
    ndn::CsTracer::InstallAll("output/cs-trace.txt", Seconds(0.5));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
  }

} // namespace ns3

int main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
