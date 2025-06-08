#include "resolveredirectioncommand.h"
#include <iredirector.h>
#include <IoC.h>
#include <iostream>

void ResolveRedirectionCommand::Execute()
{
    try
    {
        auto redirector = IoC::Resolve<IRedirectorPtr>("ProcessPacketCmd.GetRedirector", _request);
        std::string new_location = redirector->GetLocation();

        JsonPtr json = _response->getJson();
        json->as_object().emplace("location", new_location);
    } catch ( IException *e )
    {
        delete e;
    }
}
