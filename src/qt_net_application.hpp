#pragma once
#include "qt_work_event.hpp"
#include <QApplication>

class qt_net_application : public QApplication
{
    using QApplication::QApplication;

protected:
    bool
    event(QEvent *event) override;
};