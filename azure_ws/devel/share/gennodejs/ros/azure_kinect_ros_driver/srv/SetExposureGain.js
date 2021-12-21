// Auto-generated. Do not edit!

// (in-package azure_kinect_ros_driver.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class SetExposureGainRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.exposure = null;
      this.gain = null;
    }
    else {
      if (initObj.hasOwnProperty('exposure')) {
        this.exposure = initObj.exposure
      }
      else {
        this.exposure = 0;
      }
      if (initObj.hasOwnProperty('gain')) {
        this.gain = initObj.gain
      }
      else {
        this.gain = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetExposureGainRequest
    // Serialize message field [exposure]
    bufferOffset = _serializer.int32(obj.exposure, buffer, bufferOffset);
    // Serialize message field [gain]
    bufferOffset = _serializer.int32(obj.gain, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetExposureGainRequest
    let len;
    let data = new SetExposureGainRequest(null);
    // Deserialize message field [exposure]
    data.exposure = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [gain]
    data.gain = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'azure_kinect_ros_driver/SetExposureGainRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '118f5ae9e1aacf44af9d676470ddbbdf';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 exposure
    int32 gain
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetExposureGainRequest(null);
    if (msg.exposure !== undefined) {
      resolved.exposure = msg.exposure;
    }
    else {
      resolved.exposure = 0
    }

    if (msg.gain !== undefined) {
      resolved.gain = msg.gain;
    }
    else {
      resolved.gain = 0
    }

    return resolved;
    }
};

class SetExposureGainResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetExposureGainResponse
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetExposureGainResponse
    let len;
    let data = new SetExposureGainResponse(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'azure_kinect_ros_driver/SetExposureGainResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetExposureGainResponse(null);
    return resolved;
    }
};

module.exports = {
  Request: SetExposureGainRequest,
  Response: SetExposureGainResponse,
  md5sum() { return '118f5ae9e1aacf44af9d676470ddbbdf'; },
  datatype() { return 'azure_kinect_ros_driver/SetExposureGain'; }
};
