#pragma once
#include "actions.h"
#include <string>

using namespace std;

class Lockable
{
    public:
        Lockable(bool canClose = false, bool closed = false, bool locked = false);

        virtual ~Lockable();

        bool getCanClose();
        bool isClosed();
        bool isLocked();

        void Open(const string& name);
        void Close(const string& name);
        void Lock(const string& name);
        void Unlock(const string& name);

    protected:
        const bool canClose;
        bool closed;
        bool locked;
};

