#include <iostream>
#include <QApplication>
#include <QTextEdit>
#include "qt_net_application.hpp"
#include "qt_execution_context.hpp"
#include "main_window.hpp"

int
main(int argc, char** argv)
{
    qt_net_application app(argc, argv);
    qt_execution_context exec_context;

    main_window w;
    w.show();

    app.exec();
    return 0;
}
