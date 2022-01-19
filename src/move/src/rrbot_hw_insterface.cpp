/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, University of Colorado, Boulder
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Univ of CO, Boulder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Dave Coleman
   Desc:   Example ros_control hardware interface blank template for the RRBot
           For a more detailed simulation example, see sim_hw_interface.cpp
*/

#include "rrbot_hw_interface.h"


namespace rrbot_control
{
RRBotHWInterface::RRBotHWInterface(ros::NodeHandle& nh, urdf::Model* urdf_model)
  : ros_control_boilerplate::GenericHWInterface(nh, urdf_model)
{
  ROS_INFO_NAMED("rrbot_hw_interface", "RRBotHWInterface Ready.");
}

void RRBotHWInterface::read(ros::Duration& elapsed_time)
{
  // ----------------------------------------------------
  // ----------------------------------------------------
  // ----------------------------------------------------
  //
  // FILL IN YOUR READ COMMAND FROM USB/ETHERNET/ETHERCAT/SERIAL ETC HERE
  //
  // ----------------------------------------------------
  // ----------------------------------------------------
  // ----------------------------------------------------
        try {
            if (mpSerial->available()) {
                // clean cache
                // mpSerial->flushInput();
                std::string data;
                size_t res = mpSerial->readline(data, 100);
                // std::cout << "Read from serial. data: " << data;
                // check data
                if (data.size()>20) {
                    char notUsed[100];
                    int hours, minutes;
                    float seconds, robot, head, vLeft, vRight;
                    int n = sscanf(data.c_str(), "%[^S]S:%d:%d:%f:Robot%f,Head%f,Left%f,Right%f\r",
                                                notUsed, &hours, &minutes, &seconds, &robot, &head, &vLeft, &vRight);
                    if (n == 8) {
                        //printf("--TS:%d:%d:%f:Robot%f,Head%f,Left%f,Right%f\n", hours, minutes, seconds, robot, head, vLeft, vRight);
                        sensor_msgs::JointState state;
                        state.header.stamp = ros::Time::now();
                        state.effort = {hours*60*60+minutes*60+seconds, robot, head};
                        state.velocity = {vLeft, vRight};
                        mStatePub.publish(state);
                        //ros::spinOnce();
                    }
                }
            }
        } catch (...) {
        } 
    // if serial port error, return -1
  
}

void RRBotHWInterface::write(ros::Duration& elapsed_time)
{
  // Safety
  enforceLimits(elapsed_time);

  // ----------------------------------------------------
  // ----------------------------------------------------
  // ----------------------------------------------------
  //
  // FILL IN YOUR WRITE COMMAND TO USB/ETHERNET/ETHERCAT/SERIAL ETC HERE
  //
  // FOR A EASY SIMULATION EXAMPLE, OR FOR CODE TO CALCULATE
  // VELOCITY FROM POSITION WITH SMOOTHING, SEE
  // sim_hw_interface.cpp IN THIS PACKAGE
  //
  // DUMMY PASS-THROUGH CODE
  for (std::size_t joint_id = 0; joint_id < num_joints_; ++joint_id)
    joint_position_[joint_id] += joint_position_command_[joint_id];
  // END DUMMY CODE
  //
  // ----------------------------------------------------
  // ----------------------------------------------------
  // ----------------------------------------------------
   // todo: remove those limits
    if (velocity > 20) velocity = 20;
    if (velocity < -20) velocity = -20;
    if (rotate > 20) rotate = 20;
    if (rotate < -20) rotate = -20;

    uint8_t *v = (uint8_t *)&velocity;
    uint8_t *r = (uint8_t *)&rotate;
    uint8_t *h = (uint8_t *)&head;
    std::vector<uint8_t> buffer{0x55, 0xaa, 0x0e, 0x03, v[0], v[1], v[2], v[3], r[0], r[1], r[2], r[3], h[0], h[1], h[2], h[3]};
    
    uint8_t crc;
    for (unsigned int i = 2; i < buffer.size(); ++i) {
        crc += buffer[i];
    }
    crc = (0xff)&(~crc);
    buffer.push_back(crc);

    std::cout << "Motor::move called! data:";
    for (unsigned int i = 0; i < buffer.size(); ++i) {
        std::cout << std::hex << int(buffer[i]) << "-";
    }
    std::cout << std::endl;
    mpSerial->write(buffer.data(), buffer.size());
}

void RRBotHWInterface::enforceLimits(ros::Duration& period)
{
  // ----------------------------------------------------
  // ----------------------------------------------------
  // ----------------------------------------------------
  //
  // CHOOSE THE TYPE OF JOINT LIMITS INTERFACE YOU WANT TO USE
  // YOU SHOULD ONLY NEED TO USE ONE SATURATION INTERFACE,
  // DEPENDING ON YOUR CONTROL METHOD
  //
  // EXAMPLES:
  //
  // Saturation Limits ---------------------------
  //
  // Enforces position and velocity
  pos_jnt_sat_interface_.enforceLimits(period);
  //
  // Enforces velocity and acceleration limits
  // vel_jnt_sat_interface_.enforceLimits(period);
  //
  // Enforces position, velocity, and effort
  // eff_jnt_sat_interface_.enforceLimits(period);

  // Soft limits ---------------------------------
  //
  // pos_jnt_soft_limits_.enforceLimits(period);
  // vel_jnt_soft_limits_.enforceLimits(period);
  // eff_jnt_soft_limits_.enforceLimits(period);
  //
  // ----------------------------------------------------
  // ----------------------------------------------------
  // ----------------------------------------------------
}

}  // namespace rrbot_control