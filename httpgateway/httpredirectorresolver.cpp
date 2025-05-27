#include "httpredirectorresolver.h"
#include <IoC.h>
#include "irules.h"
#include <RuntimeError.h>


HttpRedirectorResolver::HttpRedirectorResolver(IJsonObjectPtr jsonobject)
    :_jsonobject(jsonobject)
{

}

std::string HttpRedirectorResolver::GetLocation()
{
    IRulesPtr rule = IoC::Resolve<IRulesPtr>("Redirector.GetLocationRule", _jsonobject);
    if( rule != nullptr ){
        return rule->get_location();
    } else {
        throw new RuntimeError("Redirection rules not configure\n");
    }
}
