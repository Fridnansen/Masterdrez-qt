#ifndef LCDNUMBER
#define LCDNUMBER

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

class LCDNumber : public QLCDNumber {
  Q_OBJECT

public:
  QTimer *timer;
  QTime *timeValue;

public:
  LCDNumber(QWidget *parentWidget) { setParent(parentWidget); }
  ~LCDNumber() {}

  void Init(int minutes, int seconds) {
    timer = new QTimer();
    timeValue = new QTime(0, minutes, seconds);
    display(timeValue->toString());
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(setDisplay()));
  }

public slots:
  void setDisplay() {
    timeValue->setHMS(0, timeValue->addSecs(-1).minute(),
                      timeValue->addSecs(-1).second());
    display(timeValue->toString());
  }
};

#endif // LCDNUMBER
