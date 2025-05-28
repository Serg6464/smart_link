#include "resolveredirectioncommand.h"
#include <iredirector.h>
#include <IoC.h>
#include <iostream>

void ResolveRedirectionCommand::Execute()
{
    try
    {
//        auto redirector = IoC::Resolve<IRedirectorPtr>("ProcessPacketCmd.GetRedirector", _request);
        std::string new_location = "test";//redirector->GetLocation();

        //auto redirectresponse_creator(new_location);
        //_response->getJson()->reset( redirectresponse_creator.getJson() );
        JsonPtr json = _response->getJson();
        json->as_object().emplace("location", new_location);
std::cout << *json;
    } catch ( IException *e )
    {
        delete e;
    }
}
