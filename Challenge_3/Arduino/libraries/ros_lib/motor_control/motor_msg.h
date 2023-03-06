#ifndef _ROS_motor_control_motor_msg_h
#define _ROS_motor_control_motor_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace motor_control
{

  class motor_msg : public ros::Msg
  {
    public:
      typedef int32_t _pwm_type;
      _pwm_type pwm;
      typedef const char* _direction_type;
      _direction_type direction;

    motor_msg():
      pwm(0),
      direction("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_pwm;
      u_pwm.real = this->pwm;
      *(outbuffer + offset + 0) = (u_pwm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pwm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pwm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pwm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pwm);
      uint32_t length_direction = strlen(this->direction);
      varToArr(outbuffer + offset, length_direction);
      offset += 4;
      memcpy(outbuffer + offset, this->direction, length_direction);
      offset += length_direction;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_pwm;
      u_pwm.base = 0;
      u_pwm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pwm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pwm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pwm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pwm = u_pwm.real;
      offset += sizeof(this->pwm);
      uint32_t length_direction;
      arrToVar(length_direction, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_direction; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_direction-1]=0;
      this->direction = (char *)(inbuffer + offset-1);
      offset += length_direction;
     return offset;
    }

    const char * getType(){ return "motor_control/motor_msg"; };
    const char * getMD5(){ return "eafcb94fe360e4074a41b0d5e313bad6"; };

  };

}
#endif
