#pragma once

#include "config.hpp"
#include <QApplication>
#include <boost/noncopyable.hpp>
#include <cassert>
#include "qt_work_event.hpp"

struct qt_execution_context : net::execution_context
    , boost::noncopyable
{
    qt_execution_context(QApplication *app = qApp)
        : app_(app)
    {
        instance_ = this;
    }

    template<class F>
    void
    post(F f)
    {
        // c++20 auto template deduction
        auto event = new basic_qt_work_event(std::move(f));
        QApplication::postEvent(app_, event);
    }

    static qt_execution_context &
    singleton()
    {
        assert(instance_);
        return *instance_;
    }

private:
    static qt_execution_context *instance_;
    QApplication *app_;
};
