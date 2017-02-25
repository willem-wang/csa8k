

#include "qttelnet.h"
#include <QtGui>

#include <QtGui/QFont>
#include <QtCore/QEvent>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QMainWindow>
#include <QShortcut>
#include <QInputDialog>
#include <QApplication>

class LoginDialog : public QDialog
{
public:
    LoginDialog(QWidget *parent = 0)
        : QDialog(parent)
    {
        QGridLayout *gl = new QGridLayout;
        setLayout(gl);

        QLabel *l;

        l = new QLabel("&Login:", this);
        gl->addWidget(l, 0, 0);
        lle = new QLineEdit(this);
        gl->addWidget(lle, 0, 1);
        l->setBuddy(lle);

        l = new QLabel("&Password:", this);
        gl->addWidget(l, 1, 0);
        ple = new QLineEdit(this);
        ple->setEchoMode(QLineEdit::Password);
        gl->addWidget(ple, 1, 1);
        l->setBuddy(ple);

        QWidget *hbox = new QWidget(this);
        QHBoxLayout *hboxlayout = new QHBoxLayout;

        gl->addWidget(hbox, 2, 0, 1, 2);

        QPushButton *pb;
        pb = new QPushButton("&Ok");
        connect(pb, SIGNAL(clicked()), this, SLOT(accept()));
        hboxlayout->addWidget(pb);

        pb = new QPushButton("&Cancel");
        connect(pb, SIGNAL(clicked()), this, SLOT(reject()));
        hboxlayout->addWidget(pb);

        hbox->setLayout(hboxlayout);
    }

    QString login() const { return lle->text(); }
    QString password() const { return ple->text(); }

    QLineEdit *lle, *ple;
private:
//    QLineEdit *lle, *ple;
};

class TelnetClient : public QMainWindow
{
    Q_OBJECT
public:
    TelnetClient(QWidget *par = 0)
        : QMainWindow(par), t(new QtTelnet)
    {
        //t->setPromptString("Welcome");

        QWidget *vbox = new QWidget(this);
        QVBoxLayout *vboxlayout = new QVBoxLayout();

        textEdit = new QTextEdit();
        lineEdit = new QLineEdit();
        status = new QLabel();
        quit = new QPushButton("Quit");
        connect(quit, SIGNAL(clicked()), this, SLOT(close()));

        vboxlayout->addWidget(textEdit);
        vboxlayout->addWidget(lineEdit);
        vboxlayout->addWidget(status);
        vboxlayout->addWidget(quit);
        vbox->setLayout(vboxlayout);
        setCentralWidget(vbox);

        QFont fnt = textEdit->font();
        fnt.setFamily("Fixed");
        textEdit->setFont(fnt);

        lineEdit->installEventFilter(this);
        installEventFilter(this);

        QShortcut *shortcut;

        shortcut = new QShortcut(this);
        shortcut->setKey(Qt::CTRL + Qt::Key_D);
        connect(shortcut, SIGNAL(activated()),
                this, SLOT(deleteCharOrLogout()));

        shortcut = new QShortcut(this);
        shortcut->setKey(Qt::CTRL + Qt::Key_Z);
        connect(shortcut, SIGNAL(activated()), this, SLOT(suspend()));

        shortcut = new QShortcut(this);
        shortcut->setKey(Qt::CTRL + Qt::Key_C);
        connect(shortcut, SIGNAL(activated()), this, SLOT(kill()));

        textEdit->setReadOnly(false);

        connect(lineEdit, SIGNAL(returnPressed()),
                this, SLOT(lineReturnPressed()));
        //connect(text)
        // connect(textEdit,SIGNAL(returnPressed()),
        //this,SLOT(textReturnPressed()) );

        connect(t, SIGNAL(message(const QString &)),
                this, SLOT(telnetMessage(const QString &)));
        connect(t, SIGNAL(loginRequired()),
                this, SLOT(telnetLoginRequired()));
        connect(t, SIGNAL(loginFailed()),
                this, SLOT(telnetLoginFailed()));
        connect(t, SIGNAL(loggedOut()),
                this, SLOT(telnetLoggedOut()));
        connect(t, SIGNAL(loggedIn()),
                this, SLOT(telnetLoggedIn()));
        connect(t, SIGNAL(connectionError(QAbstractSocket::SocketError)),
                this, SLOT(telnetConnectionError(QAbstractSocket::SocketError)));

        connect(t,SIGNAL(telnetLoginRequiredok()),this,SLOT(telnetLoginRequiredokdeal()));

#if 0
        QString host = QInputDialog::getText(this,
                                             "Host name",
                                             "Host name of Telnet server",
                                             QLineEdit::Normal,
                                             "localhost");
        host = host.trimmed();
        if (!host.isEmpty())
            t->connectToHost(host);
        else
            textEdit->setPlainText("Not connected");
#endif
    }

    QtTelnet *t;

protected:
    void resizeEvent(QResizeEvent *ev)
    {
        QFontMetrics fm(font());
        int lh = fm.lineSpacing();
        int cw = fm.width(QChar('X'));
        QRect r = textEdit->visibleRegion().boundingRect();
        int dx = ev->oldSize().width() - r.width();
        int dy = ev->oldSize().height() - r.height();

        t->setWindowSize((ev->size().width() - dx) / cw,
                         (ev->size().height() - dy) / lh);
    }
    bool eventFilter(QObject *obj, QEvent *event)
    {
        if (event->type() == QEvent::ShortcutOverride) {
            QKeyEvent *ke = static_cast<QKeyEvent *>(event);
            if (ke->modifiers() & Qt::ControlModifier) {
                switch (ke->key()) {
                case Qt::Key_C:
                case Qt::Key_D:
                case Qt::Key_Z:
                    return true;
                default:
                    break;
                }
            }
        }
        return QObject::eventFilter(obj, event);
    }

private slots:
    void telnetLoginRequiredokdeal()
    {
        t->sendData("echo GPON_pattern > /proc/pon_phy/debug");
    }

    void telnetMessage(const QString &msg)
    {
        textEdit->append(stripCR(msg));
        QScrollBar *s = textEdit->verticalScrollBar();

        //s->setValue(s->maximum());

    }
    void telnetLoginRequired()
    {
        qDebug() << "telnetLoginRequired";
        //LoginDialog ld(this);
        LoginDialog ld;

        ld.lle->setText("admin");
        ld.ple->setText("1234");
        //accept();
        if (ld.exec() == LoginDialog::Accepted){
            t->login(ld.login(), ld.password());

            //emit t->telnetLoginRequiredok();

        }
        else
            t->logout();
    }
    void telnetLoginFailed()
    {
        qDebug() << "telnetLoginFailed";
        status->setText("Login failed");
    }
    void telnetLoggedOut()
    {
        qDebug() << "telnetLoggedOut";
        lineEdit->setEnabled(false);
        status->setText("Logged out");
    }
    void telnetLoggedIn()
    {
        qDebug() << "telnetLoggedIn";
        lineEdit->setEnabled(true);
        status->setText("Logged in");
    }
    void telnetConnectionError(QAbstractSocket::SocketError error)
    {
        qDebug() << QString("Connection error: %1").arg(error);
        status->setText(QString("Connection error: %1").arg(error));
    }
    void suspend()
    {
        t->sendControl(QtTelnet::Suspend);
    }
    void kill()
    {
        t->sendControl(QtTelnet::InterruptProcess);
    }
    void lineReturnPressed()
    {
        t->sendData(lineEdit->text());
        lineEdit->clear();
    }
    void textReturnPressed(){
        t->sendData(textEdit->toPlainText());
    }
    void deleteCharOrLogout()
    {
        if (lineEdit->text().isEmpty()) {
            t->logout();
        } else {
            int cpos = lineEdit->cursorPosition();
            QString txt = lineEdit->text();
            if (cpos < (int)txt.length()) {
                lineEdit->setText(txt.remove(cpos, 1));
                lineEdit->setCursorPosition(cpos);
            }
        }
    }


private:
    QString stripCR(const QString &msg)
    {
        QString nmsg(msg);
        nmsg.remove('\r');
        nmsg.remove(QRegExp("\033\\[[0-9;]*[A-Za-z]")); // Also remove terminal control codes
        return nmsg;
    }

private:
//    QtTelnet *t;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QLabel *status;
    QPushButton *quit;
};

#if 0
int main_login( int argc, char **argv )
{
    // QApplication a(argc, argv);
    QApplication a(argc,argv);

    TelnetClient t;
    t.show();
    return a.exec();
}
#endif

//#include "main_login.moc"

