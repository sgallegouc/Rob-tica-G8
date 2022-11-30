/********************************************************************************
** Form generated from reading UI file 'mainUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINUI_H
#define UI_MAINUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guiDlg
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QFrame *beta_frame;
    QFrame *buttons_frame;
    QFrame *signals_frame;

    void setupUi(QWidget *guiDlg)
    {
        if (guiDlg->objectName().isEmpty())
            guiDlg->setObjectName(QString::fromUtf8("guiDlg"));
        guiDlg->resize(1006, 762);
        verticalLayout = new QVBoxLayout(guiDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter_2 = new QSplitter(guiDlg);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        beta_frame = new QFrame(splitter);
        beta_frame->setObjectName(QString::fromUtf8("beta_frame"));
        beta_frame->setMinimumSize(QSize(500, 500));
        beta_frame->setFrameShape(QFrame::StyledPanel);
        beta_frame->setFrameShadow(QFrame::Raised);
        splitter->addWidget(beta_frame);
        buttons_frame = new QFrame(splitter);
        buttons_frame->setObjectName(QString::fromUtf8("buttons_frame"));
        buttons_frame->setFrameShape(QFrame::StyledPanel);
        buttons_frame->setFrameShadow(QFrame::Raised);
        splitter->addWidget(buttons_frame);
        splitter_2->addWidget(splitter);
        signals_frame = new QFrame(splitter_2);
        signals_frame->setObjectName(QString::fromUtf8("signals_frame"));
        signals_frame->setFrameShape(QFrame::StyledPanel);
        signals_frame->setFrameShadow(QFrame::Raised);
        splitter_2->addWidget(signals_frame);

        verticalLayout->addWidget(splitter_2);


        retranslateUi(guiDlg);

        QMetaObject::connectSlotsByName(guiDlg);
    } // setupUi

    void retranslateUi(QWidget *guiDlg)
    {
        guiDlg->setWindowTitle(QCoreApplication::translate("guiDlg", "forcefield", nullptr));
    } // retranslateUi

};

namespace Ui {
    class guiDlg: public Ui_guiDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINUI_H
