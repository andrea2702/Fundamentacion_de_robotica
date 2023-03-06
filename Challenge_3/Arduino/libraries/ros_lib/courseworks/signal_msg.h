#ifndef _ROS_courseworks_signal_msg_h
#define _ROS_courseworks_signal_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace courseworks
{

  class signal_msg : public ros::Msg
  {
    public:
      typedef float _time_x_type;
      _time_x_type time_x;
      typedef float _signal_y_type;
      _signal_y_type signal_y;

    signal_msg():
      time_x(0),
      signal_y(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_time_x;
      u_time_x.real = this->time_x;
      *(outbuffer + offset + 0) = (u_time_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_x);
      union {
        float real;
        uint32_t base;
      } u_signal_y;
      u_signal_y.real = this->signal_y;
      *(outbuffer + offset + 0) = (u_signal_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_signal_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_signal_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_signal_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->signal_y);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_time_x;
      u_time_x.base = 0;
      u_time_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->time_x = u_time_x.real;
      offset += sizeof(this->time_x);
      union {
        float real;
        uint32_t base;
      } u_signal_y;
      u_signal_y.base = 0;
      u_signal_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_signal_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_signal_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_signal_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->signal_y = u_signal_y.real;
      offset += sizeof(this->signal_y);
     return offset;
    }

    const char * getType(){ return "courseworks/signal_msg"; };
    const char * getMD5(){ return "7a11f0834f5ad70ec78337929f76544a"; };

  };

}
#endif
