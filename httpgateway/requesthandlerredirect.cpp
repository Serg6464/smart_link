#include "requesthandlerredirect.h"
#include "iredirector.h"
#include <IoC.h>

RequestHandlerRedirect::RequestHandlerRedirect()
{

}


bool RequestHandlerRedirect::handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response)
{
    try
    {
        if (request->getRequest()->method() == http::verb::get) {
            auto redirector = IoC::Resolve<IRedirectorPtr>("ProcessPacketCmd.GetRedirector", request);
            auto& res = response->getResponse();
            res.result(http::status::temporary_redirect);
            res.set(http::field::location, redirector->GetLocation());
            res.set(http::field::content_type, "text/plain");
            res.body() = "Redirect";
            res.prepare_payload();
            return true;
        }
    } catch ( IException *e )
    {
        delete e;
    }
    return ChainRequestHandler::handle(request, response);
}
