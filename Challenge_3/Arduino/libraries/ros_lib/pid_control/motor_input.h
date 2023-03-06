#ifndef _ROS_pid_control_motor_input_h
#define _ROS_pid_control_motor_input_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace pid_control
{

  class motor_input : public ros::Msg
  {
    public:
      typedef float _input_type;
      _input_type input;
      typedef float _time_type;
      _time_type time;

    motor_input():
      input(0),
      time(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_input;
      u_input.real = this->input;
      *(outbuffer + offset + 0) = (u_input.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_input.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_input.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_input.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->input);
      offset += serializeAvrFloat64(outbuffer + offset, this->time);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_input;
      u_input.base = 0;
      u_input.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_input.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_input.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_input.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->input = u_input.real;
      offset += sizeof(this->input);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->time));
     return offset;
    }

    const char * getType(){ return "pid_control/motor_input"; };
    const char * getMD5(){ return "68938b46224a92992b7cd8fd6233cc91"; };

  };

}
#endif
