
#ifndef I_TOOL_CORE_H
#define I_TOOL_CORE_H

class IToolCore {
public:
    
    virtual ~IToolCore() = default;

    virtual bool Init() = 0;

    virtual void Run() = 0;

    virtual void Clean() = 0;
};

#endif