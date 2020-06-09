/********************************************************************************
** Form generated from reading UI file 'ParallelControlUI.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARALLELCONTROLUI_H
#define UI_PARALLELCONTROLUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ParallelControlUIClass
{
public:
    QPushButton *btn_calc;
    QDoubleSpinBox *spin_x;
    QDoubleSpinBox *spin_y;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QDoubleSpinBox *spin_y_2;
    QDoubleSpinBox *spin_x_2;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_sum_5;
    QLabel *label_sum_6;
    QLabel *label_sum_7;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_sum_8;
    QLabel *label_3;
    QLabel *label_sum_2;
    QLabel *label_6;
    QLabel *label_sum;
    QLabel *label_sum_3;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_sum_4;

    void setupUi(QDialog *ParallelControlUIClass)
    {
        if (ParallelControlUIClass->objectName().isEmpty())
            ParallelControlUIClass->setObjectName(QString::fromUtf8("ParallelControlUIClass"));
        ParallelControlUIClass->resize(686, 324);
        btn_calc = new QPushButton(ParallelControlUIClass);
        btn_calc->setObjectName(QString::fromUtf8("btn_calc"));
        btn_calc->setGeometry(QRect(70, 240, 161, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        btn_calc->setFont(font);
        spin_x = new QDoubleSpinBox(ParallelControlUIClass);
        spin_x->setObjectName(QString::fromUtf8("spin_x"));
        spin_x->setGeometry(QRect(150, 30, 81, 31));
        spin_x->setMinimum(-999999.000000000000000);
        spin_x->setMaximum(999999.000000000000000);
        spin_y = new QDoubleSpinBox(ParallelControlUIClass);
        spin_y->setObjectName(QString::fromUtf8("spin_y"));
        spin_y->setGeometry(QRect(150, 70, 81, 31));
        spin_y->setMinimum(-999999.000000000000000);
        label = new QLabel(ParallelControlUIClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 40, 54, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(14);
        label->setFont(font1);
        label_2 = new QLabel(ParallelControlUIClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 80, 54, 21));
        label_2->setFont(font1);
        label_4 = new QLabel(ParallelControlUIClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 120, 54, 21));
        label_4->setFont(font1);
        spin_y_2 = new QDoubleSpinBox(ParallelControlUIClass);
        spin_y_2->setObjectName(QString::fromUtf8("spin_y_2"));
        spin_y_2->setGeometry(QRect(150, 150, 81, 31));
        spin_y_2->setMinimum(-999999.000000000000000);
        spin_x_2 = new QDoubleSpinBox(ParallelControlUIClass);
        spin_x_2->setObjectName(QString::fromUtf8("spin_x_2"));
        spin_x_2->setGeometry(QRect(150, 110, 81, 31));
        spin_x_2->setMinimum(-999999.000000000000000);
        spin_x_2->setMaximum(999999.000000000000000);
        label_5 = new QLabel(ParallelControlUIClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(70, 160, 54, 21));
        label_5->setFont(font1);
        label_10 = new QLabel(ParallelControlUIClass);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(381, 96, 88, 26));
        label_10->setFont(font1);
        label_9 = new QLabel(ParallelControlUIClass);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(381, 31, 88, 26));
        label_9->setFont(font1);
        label_sum_5 = new QLabel(ParallelControlUIClass);
        label_sum_5->setObjectName(QString::fromUtf8("label_sum_5"));
        label_sum_5->setGeometry(QRect(381, 63, 91, 27));
        label_sum_5->setFont(font1);
        label_sum_6 = new QLabel(ParallelControlUIClass);
        label_sum_6->setObjectName(QString::fromUtf8("label_sum_6"));
        label_sum_6->setGeometry(QRect(381, 128, 91, 27));
        label_sum_6->setFont(font1);
        label_sum_7 = new QLabel(ParallelControlUIClass);
        label_sum_7->setObjectName(QString::fromUtf8("label_sum_7"));
        label_sum_7->setGeometry(QRect(381, 193, 91, 27));
        label_sum_7->setFont(font1);
        label_11 = new QLabel(ParallelControlUIClass);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(381, 161, 88, 26));
        label_11->setFont(font1);
        label_12 = new QLabel(ParallelControlUIClass);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(381, 226, 88, 26));
        label_12->setFont(font1);
        label_sum_8 = new QLabel(ParallelControlUIClass);
        label_sum_8->setObjectName(QString::fromUtf8("label_sum_8"));
        label_sum_8->setGeometry(QRect(381, 258, 91, 27));
        label_sum_8->setFont(font1);
        label_3 = new QLabel(ParallelControlUIClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(271, 31, 88, 26));
        label_3->setFont(font1);
        label_sum_2 = new QLabel(ParallelControlUIClass);
        label_sum_2->setObjectName(QString::fromUtf8("label_sum_2"));
        label_sum_2->setGeometry(QRect(271, 128, 81, 27));
        label_sum_2->setFont(font1);
        label_6 = new QLabel(ParallelControlUIClass);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(271, 96, 88, 26));
        label_6->setFont(font1);
        label_sum = new QLabel(ParallelControlUIClass);
        label_sum->setObjectName(QString::fromUtf8("label_sum"));
        label_sum->setGeometry(QRect(271, 63, 81, 27));
        label_sum->setFont(font1);
        label_sum_3 = new QLabel(ParallelControlUIClass);
        label_sum_3->setObjectName(QString::fromUtf8("label_sum_3"));
        label_sum_3->setGeometry(QRect(271, 193, 81, 27));
        label_sum_3->setFont(font1);
        label_7 = new QLabel(ParallelControlUIClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(271, 161, 88, 26));
        label_7->setFont(font1);
        label_8 = new QLabel(ParallelControlUIClass);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(271, 226, 88, 26));
        label_8->setFont(font1);
        label_sum_4 = new QLabel(ParallelControlUIClass);
        label_sum_4->setObjectName(QString::fromUtf8("label_sum_4"));
        label_sum_4->setGeometry(QRect(271, 258, 91, 27));
        label_sum_4->setFont(font1);

        retranslateUi(ParallelControlUIClass);

        QMetaObject::connectSlotsByName(ParallelControlUIClass);
    } // setupUi

    void retranslateUi(QDialog *ParallelControlUIClass)
    {
        ParallelControlUIClass->setWindowTitle(QCoreApplication::translate("ParallelControlUIClass", "ParallelControlUI", nullptr));
        btn_calc->setText(QCoreApplication::translate("ParallelControlUIClass", "\350\257\267\346\261\202Move", nullptr));
        label->setText(QCoreApplication::translate("ParallelControlUIClass", "M1:", nullptr));
        label_2->setText(QCoreApplication::translate("ParallelControlUIClass", "M2:", nullptr));
        label_4->setText(QCoreApplication::translate("ParallelControlUIClass", "M3:", nullptr));
        label_5->setText(QCoreApplication::translate("ParallelControlUIClass", "M4:", nullptr));
        label_10->setText(QCoreApplication::translate("ParallelControlUIClass", "V2_Real", nullptr));
        label_9->setText(QCoreApplication::translate("ParallelControlUIClass", "V1_Real", nullptr));
        label_sum_5->setText(QString());
        label_sum_6->setText(QString());
        label_sum_7->setText(QString());
        label_11->setText(QCoreApplication::translate("ParallelControlUIClass", "V3_Real", nullptr));
        label_12->setText(QCoreApplication::translate("ParallelControlUIClass", "V4_Real", nullptr));
        label_sum_8->setText(QString());
        label_3->setText(QCoreApplication::translate("ParallelControlUIClass", "P1_Real", nullptr));
        label_sum_2->setText(QString());
        label_6->setText(QCoreApplication::translate("ParallelControlUIClass", "P2_Real", nullptr));
        label_sum->setText(QString());
        label_sum_3->setText(QString());
        label_7->setText(QCoreApplication::translate("ParallelControlUIClass", "P3_Real", nullptr));
        label_8->setText(QCoreApplication::translate("ParallelControlUIClass", "P4_Real", nullptr));
        label_sum_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ParallelControlUIClass: public Ui_ParallelControlUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARALLELCONTROLUI_H
