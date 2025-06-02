#ifndef ISCOPECHANGER_H
#define ISCOPECHANGER_H

#include <IScope.h>
#include <memory>

class IScopeChanger
{
public:
    virtual ~IScopeChanger() = default;
    virtual void Change(IScopePtr scope) = 0;
};

using IScopeChangerPtr = std::shared_ptr<IScopeChanger>;

#endif
