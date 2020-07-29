/*
  IEC_61131_3.h - Library for using IEC 61131-3 standard functions.
  Created by EcceRobot, July 29, 2020.
  Released into the public domain.
*/

#ifndef IEC_61131_3_h
#define IEC_61131_3_h

#include "Arduino.h"



class R_TRIG
{

  private:

    bool _M;                        // var_local


  public:

    bool Q;                        // var_output

    void execute(bool CLK) {       // method and var_input
      Q = CLK && !_M;
      _M = CLK;
    }

};




class F_TRIG
{

  private:

    bool _M;                        // var_local


  public:

    bool Q;                        // var_output

    void execute(bool CLK) {       // method and var_input
      Q = !CLK && !_M;
      _M = !CLK;
    }

};




class TON
{

  private:
    int                   _STATE            = 0;                    // var_local      ( 0 reset | 1 counting | 2 set )
    bool                  _PREV_IN          = false;                // var_local
    unsigned long         _CURRENT_TIME     = 0;                    // var_local
    unsigned long         _START_TIME       = 0;                    // var_local

  public:

    bool Q;                        // var_output
    unsigned long ET;              // var_output

    void execute(bool IN, unsigned long PT) {       // method and var_input

      _CURRENT_TIME = millis();

      if ((_STATE == 0) && !(_PREV_IN) && IN)   /* found rising edge on IN */
      {
        /* start timer... */
        _STATE = 1;
        Q = false;
        _START_TIME = _CURRENT_TIME;
      }
      else {
        /* STATE is 1 or 2 !! */
        if (!(IN))
        {
          ET = 0;
          Q = false;
          _STATE = 0;
        }
        else if (_STATE == 1)
        {
          if ((_START_TIME + PT) <= _CURRENT_TIME)
          {
            _STATE = 2;
            Q = true;
            ET = PT;

          } else {
            ET = _CURRENT_TIME - _START_TIME;
          }
        }

      }

      _PREV_IN = IN;

    }

};


class TOF
{

  private:
    int                   _STATE            = 0;                    // var_local      ( 0 reset | 1 counting | 2 set )
    bool                  _PREV_IN          = false;                // var_local
    unsigned long         _CURRENT_TIME     = 0;                    // var_local
    unsigned long         _START_TIME       = 0;                    // var_local

  public:

    bool Q;                        // var_output
    unsigned long ET;              // var_output

    void execute(bool IN, unsigned long PT) {       // method and var_input

      _CURRENT_TIME = millis();

      if ((_STATE == 0) && _PREV_IN && !IN)   /* found falling edge on IN */
      {
        /* start timer... */
        _STATE = 1;
        _START_TIME = _CURRENT_TIME;
      }
      else {
        /* STATE is 1 or 2 !! */
        if (IN)
        {
          ET = 0;
          _STATE = 0;
        }
        else if (_STATE == 1)
        {
          if ((_START_TIME + PT) <= _CURRENT_TIME)
          {
            _STATE = 2;
            ET = PT;

          } else {
            ET = _CURRENT_TIME - _START_TIME;
          }
        }

      }

      Q = IN || (_STATE == 1);
      _PREV_IN = IN;

    }

};





class TP
{

  private:
    int                   _STATE            = 0;                    // var_local      ( 0 reset | 1 counting | 2 set )
    bool                  _PREV_IN          = false;                // var_local
    unsigned long         _CURRENT_TIME     = 0;                    // var_local
    unsigned long         _START_TIME       = 0;                    // var_local

  public:

    bool Q;                        // var_output
    unsigned long ET;              // var_output

    void execute(bool IN, unsigned long PT) {       // method and var_input

      _CURRENT_TIME = millis();

      if ((_STATE == 0) && !(_PREV_IN) && IN)   /* found rising edge on IN */
      {
        /* start timer... */
        _STATE = 1;
        Q = true;
        _START_TIME = _CURRENT_TIME;
      }

      else if (_STATE == 1)
      {
        if ((_START_TIME + PT) <= _CURRENT_TIME)
        {
          _STATE = 2;
          Q = false;
          ET = PT;

        } else {
          ET = _CURRENT_TIME - _START_TIME;
        }
      }


      if ((_STATE == 2) && !IN) {
        ET = 0;
        _STATE = 0;
      }

      _PREV_IN = IN;

    }

};


#endif
