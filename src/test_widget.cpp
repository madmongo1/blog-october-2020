//
// Created by rhodges on 09/11/2020.
//

#include "test_widget.hpp"
#include "qt_executor.hpp"
#include <QString>
#include <string>

void
test_widget::showEvent(QShowEvent *event)
{
    net::co_spawn(
    qt_executor(), [this] {
        return run_demo();
    },
    net::detached);

    QTextEdit::showEvent(event);
}

void
test_widget::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);
}

net::awaitable<void>
test_widget::run_demo()
{
    using namespace std::literals;

    auto timer = net::high_resolution_timer(co_await net::this_coro::executor);

    for (int i = 0; i < 10; ++i)
    {
        timer.expires_after(1s);
        co_await timer.async_wait(net::use_awaitable);
        this->setText(QString::fromStdString(std::to_string(i + 1) + " seconds"));
    }
    co_return;
}
