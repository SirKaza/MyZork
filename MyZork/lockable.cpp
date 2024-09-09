#include "lockable.h"
#include "entity.h"
#include <iostream>
#include <string>

using namespace std;

Lockable::Lockable(bool canClose, bool closed, bool locked, const string& key)
	: canClose(canClose), closed(closed), locked(locked), key(key) {

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

void Lockable::Examine(const string& name) const {
    if (canClose) {
        string state;
        if (locked) { // if locked is closed
            state = "locked";
        }
        else if (!locked && closed) { // unlocked & closed
            state = "closed";
        }
        else { // opened
            state = "opened";
        }
        cout << "Looking closely, you notice that " << name << " is " << state << ".\n";
    }
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

void Lockable::Lock(const string& lockName, const string& keyName) {
    if (!closed) {
        cout << "You need to close " << lockName << " first before locking.\n";
        return;
    }

    // Check if the provided key is the correct key for locking
    if (key == keyName) {
        locked = true;
        cout << "You lock " << lockName << " with " << keyName << ".\n";
    }
    else {
        cout << keyName << " cannot lock " << lockName << ".\n";
    }
}

void Lockable::Unlock(const string& lockName, const string& keyName) {
    if (!locked) {
        cout << lockName << " is already unlocked.\n";
        return;
    }

    // Check if the provided key is the correct key for unlocking
    if (key == keyName) {
        locked = false;
        cout << "You unlock " << lockName << " with " << keyName << ".\n";
    }
    else {
        cout << keyName <<  " cannot unlock " << lockName << ".\n";
    }
}