#include <QMainWindow>

class QMdiArea;

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    main_window(QWidget *parent = nullptr,
                Qt::WindowFlags flags = Qt::WindowFlags());

    void make_new_widget();

private:
    QMenu *widgets_menu  = nullptr;
    QMdiArea* mdi_area = nullptr;
};