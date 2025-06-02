#ifndef RESOLVEREDIRECTIONCOMMAND_H
#define RESOLVEREDIRECTIONCOMMAND_H

#include <ICommand.h>
#include <ijsonobject.h>

class ResolveRedirectionCommand;
using ResolveRedirectionCommandPtr = std::shared_ptr<ResolveRedirectionCommand>;

class ResolveRedirectionCommand : public ICommand
{
    IJsonObjectPtr _request;
    IJsonObjectPtr _response;

public:
    ResolveRedirectionCommand(IJsonObjectPtr request, IJsonObjectPtr response)
        :_request(request), _response(response)
    {
    };
    static inline ResolveRedirectionCommandPtr Create(IJsonObjectPtr request, IJsonObjectPtr response)
    {
        return std::make_shared<ResolveRedirectionCommand>(request, response);
    };

    // ICommand interface
public:
    void Execute();
};

#endif // RESOLVEREDIRECTIONCOMMAND_H
