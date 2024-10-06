#pragma once
#include "actions.h"
#include <string>

using namespace std;

class Lockable
{
    public:
        Lockable(bool canClose = false, bool closed = false, bool locked = false, const string& key = "");
        virtual ~Lockable();

        bool getCanClose();
        bool isClosed();
        bool isLocked();

        void Examine(const string& name) const;

        void Open(const string& name);
        void Close(const string& name);
        void Lock(const string& lockName, const string& keyName);
        void Unlock(const string& lockName, const string& keyName);

    protected:
        const bool canClose;
        bool closed;
        bool locked;
        const string& key;
};

