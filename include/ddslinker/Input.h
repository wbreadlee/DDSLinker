#pragma once

#include <string>
#include <functional>
#include <yarp/os/PortReader.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/ConnectionReader.h>

#include "../../src/Base.h"

using yarp::os::Bottle;
using yarp::os::ConnectionReader;
using yarp::os::PortReader;
using namespace std;

namespace Friend {
namespace DDS {

class YarpReaderDataProcessor : public PortReader {
public:
    typedef std::function<void(ConnectionReader&)> readCallback;
    virtual void setCallback(const readCallback& callback) { _callback = callback; }
    bool read(ConnectionReader& data) override {
        _callback(data);
        return true;
    }
private:
    readCallback _callback;
};

template <typename T>
class Input : public Friend::DDS::Base<T> {
public:
    typedef function<void(T&)> readCallback;
    Input();
    explicit Input(const string& name);
    Input(const string& name, const readCallback& callback);
    virtual void create(const string& name);
    virtual void create(const string& name, const readCallback& callback);
    bool isConnected() override { return false; };
private:
    YarpReaderDataProcessor _dataProcessor;
    T _lastState;
    readCallback _callback;

};
} // namespace DDSLinker
} // namespace Friend

