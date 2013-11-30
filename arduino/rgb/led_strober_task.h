#pragma once

class LedStroberTask {
  public:
    LedStroberTask( const int pin, const int period );

    void slice() const;

  private:
    const int _pin;
    const int _period;
};
