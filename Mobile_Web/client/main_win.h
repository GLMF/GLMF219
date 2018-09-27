
#pragma once
#include "ui_main_win.h"
class Main_Win: public QWidget, private Ui::Main_Win
{
      Q_OBJECT
   public:
      explicit Main_Win(QWidget* parent = nullptr);
   public slots:
      void appendString(QString const&);
   signals:
      void stringGiven(QString const&);
}; // class Main_Win
