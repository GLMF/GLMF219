
#include "main_win.h"

#include <QtDebug>

Main_Win::Main_Win(QWidget* parent):
   QWidget(parent)
{
   this->setupUi(this);
   QObject::connect(
            this->bt_quit, &QPushButton::clicked,
            qApp, &QApplication::quit);
   QObject::connect(
            this->le_input, &QLineEdit::returnPressed,
            [this]()
   {
      QString const input = this->le_input->text();
      this->pte_outputs->append(input);
      emit this->stringGiven(input);
      this->le_input->setText(QString());
   });
}

void Main_Win::appendString(QString const& s)
{
   this->pte_outputs->append(QStringLiteral("&mdash;<span style=\"color: darkred;\">%1</span>").arg(s));
   this->pte_outputs->append(QStringLiteral("<br/>"));
}
