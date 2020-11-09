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
    stopped_ = false;

    // start our coroutine
    net::co_spawn(
        get_executor(), [this] { return run_demo(); }, net::detached);

    QTextEdit::showEvent(event);
}

void
test_widget::hideEvent(QHideEvent *event)
{
    // stop all coroutines
    stop_all();
    QWidget::hideEvent(event);
}

net::awaitable<void>
test_widget::run_demo()
{
    using namespace std::literals;

    auto timer = net::high_resolution_timer(co_await net::this_coro::executor);

    auto done = false;

    listen_for_stop([&] {
        done = true;
        timer.cancel();
    });

    while (!done)
    {
        for (int i = 0; i < 10; ++i)
        {
            timer.expires_after(1s);
            auto ec = boost::system::error_code();
            co_await timer.async_wait(
                net::redirect_error(net::use_awaitable, ec));
            if (ec)
            {
                done = true;
                break;
            }
            this->setText(
                QString::fromStdString(std::to_string(i + 1) + " seconds"));
        }

        for (int i = 10; i--;)
        {
            timer.expires_after(250ms);
            auto ec = boost::system::error_code();
            co_await timer.async_wait(
                net::redirect_error(net::use_awaitable, ec));
            if (ec)
            {
                done = true;
                break;
            }
            this->setText(QString::fromStdString(std::to_string(i)));
        }
    }
    co_return;
}

void
test_widget::listen_for_stop(std::function<void()> slot)
{
    if (stopped_)
        return slot();

    stop_signals_.push_back(std::move(slot));
}

void
test_widget::stop_all()
{
    stopped_ = true;
    auto copy = std::exchange(stop_signals_, {});
    for (auto &slot : copy) slot();
}

void
test_widget::closeEvent(QCloseEvent *event)
{
    stop_all();
    QWidget::closeEvent(event);
}
