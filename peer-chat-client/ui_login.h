/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLineEdit *lineUser;
    QLineEdit *linePass;
    QPushButton *btnLogin;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(237, 149);
        lineUser = new QLineEdit(login);
        lineUser->setObjectName(QStringLiteral("lineUser"));
        lineUser->setGeometry(QRect(60, 30, 113, 22));
        linePass = new QLineEdit(login);
        linePass->setObjectName(QStringLiteral("linePass"));
        linePass->setGeometry(QRect(60, 80, 113, 22));
        btnLogin = new QPushButton(login);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        btnLogin->setGeometry(QRect(80, 115, 80, 21));
        label = new QLabel(login);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 10, 61, 16));
        label_2 = new QLabel(login);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 60, 58, 14));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Peer-Chat Login", Q_NULLPTR));
        btnLogin->setText(QApplication::translate("login", "Login", Q_NULLPTR));
        label->setText(QApplication::translate("login", "Username", Q_NULLPTR));
        label_2->setText(QApplication::translate("login", "Password", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
