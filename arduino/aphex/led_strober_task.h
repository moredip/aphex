#pragma once

class LedStroberTask {
  public:
    LedStroberTask( const int pin, const int onPeriod, const int offPeriod );

    void slice() const;

  private:
    const int _pin;
    const int _onPeriod;
    const int _offPeriod;
};
