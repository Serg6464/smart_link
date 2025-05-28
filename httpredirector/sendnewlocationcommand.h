#ifndef SENDNEWLOCATIONCOMMAND_H
#define SENDNEWLOCATIONCOMMAND_H

#include <ICommand.h>
#include <isendableconnection.h>

class SendNewLocationCommand;
using SendNewLocationCommandPtr = std::shared_ptr<SendNewLocationCommand>;

class SendNewLocationCommand : public ICommand
{
    std::shared_ptr<ISendableConnection> _sendprocessor;
public:
    SendNewLocationCommand( std::shared_ptr<ISendableConnection> sendprocessor )
        :_sendprocessor(sendprocessor)
    {};
    static inline SendNewLocationCommandPtr Create(std::shared_ptr<ISendableConnection> sendprocessor)
    {
        return std::make_shared<SendNewLocationCommand>( sendprocessor );
    };

    // ICommand interface
public:
    void Execute()
    {
        _sendprocessor->send();
    }
};

#endif // SENDNEWLOCATIONCOMMAND_H
