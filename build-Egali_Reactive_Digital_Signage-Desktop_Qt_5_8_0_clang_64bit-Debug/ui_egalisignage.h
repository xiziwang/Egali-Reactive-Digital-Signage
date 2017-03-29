/********************************************************************************
** Form generated from reading UI file 'egalisignage.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EGALISIGNAGE_H
#define UI_EGALISIGNAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EgaliSignage
{
public:
    QWidget *centralWidget;
    QLabel *image_main;
    QLabel *image_guidance;
    QLabel *image_secondary;

    void setupUi(QMainWindow *EgaliSignage)
    {
        if (EgaliSignage->objectName().isEmpty())
            EgaliSignage->setObjectName(QStringLiteral("EgaliSignage"));
        EgaliSignage->resize(1024, 768);
        centralWidget = new QWidget(EgaliSignage);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        image_main = new QLabel(centralWidget);
        image_main->setObjectName(QStringLiteral("image_main"));
        image_main->setGeometry(QRect(0, 0, 700, 650));
        image_guidance = new QLabel(centralWidget);
        image_guidance->setObjectName(QStringLiteral("image_guidance"));
        image_guidance->setGeometry(QRect(0, 650, 700, 118));
        image_secondary = new QLabel(centralWidget);
        image_secondary->setObjectName(QStringLiteral("image_secondary"));
        image_secondary->setGeometry(QRect(700, 0, 324, 768));
        EgaliSignage->setCentralWidget(centralWidget);

        retranslateUi(EgaliSignage);

        QMetaObject::connectSlotsByName(EgaliSignage);
    } // setupUi

    void retranslateUi(QMainWindow *EgaliSignage)
    {
        EgaliSignage->setWindowTitle(QApplication::translate("EgaliSignage", "EgaliSignage", Q_NULLPTR));
        image_main->setText(QString());
        image_guidance->setText(QString());
        image_secondary->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EgaliSignage: public Ui_EgaliSignage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EGALISIGNAGE_H
