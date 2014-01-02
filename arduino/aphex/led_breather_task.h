#pragma once

class LedBreatherTask {
  public:
    LedBreatherTask( const int pin, const float period );

    void slice() const;

  private:
    const int _pin;
    const float _period;
};
