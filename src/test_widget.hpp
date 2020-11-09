#pragma once
#include "config.hpp"
#include <QTextEdit>

class test_widget : public QTextEdit
{
    Q_OBJECT
public:
    using QTextEdit::QTextEdit;

private:
    void
    showEvent(QShowEvent *event) override;

    void
    hideEvent(QHideEvent *event) override;

    net::awaitable<void>
    run_demo();
};
