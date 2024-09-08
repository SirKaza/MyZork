#include "lockable.h"
#include <iostream>
#include <string>

using namespace std;

Lockable::Lockable(bool canClose, bool closed, bool locked) 
	: canClose(canClose), closed(closed), locked(locked) {

}

Lockable::~Lockable() {

}

bool Lockable::getCanClose() {
	return canClose;
}

bool Lockable::isClosed() {
	return closed;
}

bool Lockable::isLocked() {
	return locked;
}

void Lockable::Open(const string& name) {
    if (canClose && !locked && closed) {
        closed = false;
        cout << name << " is now opened.\n";
    }
    else if (locked) {
        cout << name << " is locked and cannot be opened.\n";
    }
    else if (!closed) {
        cout << name << " is already opened.\n";
    }
    else {
        cout << name << " isn't something you can open.\n";
    }
}

void Lockable::Close(const string& name) {
    if (canClose && !closed) {
        closed = true;
        cout << name << " is now closed.\n";
    }
    else if (closed) {
        cout << name << " is already closed.\n";
    }
    else {
        cout << name << " isn't something you can close.\n";
    }
}

void Lockable::Lock(const string& name) {
    if (!closed) {
        cout << "You need to close " << name << " first before locking.\n";
    }
    else {
        locked = true;
        cout << name << " is now locked.\n";
    }
}

void Lockable::Unlock(const string& name) {
    if (locked) {
        locked = false;
        cout << name << " is now unlocked.\n";
    }
    else {
        cout << name << " is already unlocked.\n";
    }
}
