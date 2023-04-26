// Auto-generated. Do not edit!

// (in-package drone_controller.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class SetRefPoseRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.x_ref_w = null;
      this.y_ref_w = null;
      this.alt_ref_w = null;
      this.yaw_ref_w = null;
    }
    else {
      if (initObj.hasOwnProperty('x_ref_w')) {
        this.x_ref_w = initObj.x_ref_w
      }
      else {
        this.x_ref_w = 0.0;
      }
      if (initObj.hasOwnProperty('y_ref_w')) {
        this.y_ref_w = initObj.y_ref_w
      }
      else {
        this.y_ref_w = 0.0;
      }
      if (initObj.hasOwnProperty('alt_ref_w')) {
        this.alt_ref_w = initObj.alt_ref_w
      }
      else {
        this.alt_ref_w = 0.0;
      }
      if (initObj.hasOwnProperty('yaw_ref_w')) {
        this.yaw_ref_w = initObj.yaw_ref_w
      }
      else {
        this.yaw_ref_w = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetRefPoseRequest
    // Serialize message field [x_ref_w]
    bufferOffset = _serializer.float64(obj.x_ref_w, buffer, bufferOffset);
    // Serialize message field [y_ref_w]
    bufferOffset = _serializer.float64(obj.y_ref_w, buffer, bufferOffset);
    // Serialize message field [alt_ref_w]
    bufferOffset = _serializer.float64(obj.alt_ref_w, buffer, bufferOffset);
    // Serialize message field [yaw_ref_w]
    bufferOffset = _serializer.float64(obj.yaw_ref_w, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetRefPoseRequest
    let len;
    let data = new SetRefPoseRequest(null);
    // Deserialize message field [x_ref_w]
    data.x_ref_w = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [y_ref_w]
    data.y_ref_w = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [alt_ref_w]
    data.alt_ref_w = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [yaw_ref_w]
    data.yaw_ref_w = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 32;
  }

  static datatype() {
    // Returns string type for a service object
    return 'drone_controller/SetRefPoseRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fb836e8feb393aeb4dfa49d7e6234086';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 x_ref_w
    float64 y_ref_w
    float64 alt_ref_w
    float64 yaw_ref_w
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetRefPoseRequest(null);
    if (msg.x_ref_w !== undefined) {
      resolved.x_ref_w = msg.x_ref_w;
    }
    else {
      resolved.x_ref_w = 0.0
    }

    if (msg.y_ref_w !== undefined) {
      resolved.y_ref_w = msg.y_ref_w;
    }
    else {
      resolved.y_ref_w = 0.0
    }

    if (msg.alt_ref_w !== undefined) {
      resolved.alt_ref_w = msg.alt_ref_w;
    }
    else {
      resolved.alt_ref_w = 0.0
    }

    if (msg.yaw_ref_w !== undefined) {
      resolved.yaw_ref_w = msg.yaw_ref_w;
    }
    else {
      resolved.yaw_ref_w = 0.0
    }

    return resolved;
    }
};

class SetRefPoseResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.update_status = null;
    }
    else {
      if (initObj.hasOwnProperty('update_status')) {
        this.update_status = initObj.update_status
      }
      else {
        this.update_status = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetRefPoseResponse
    // Serialize message field [update_status]
    bufferOffset = _serializer.bool(obj.update_status, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetRefPoseResponse
    let len;
    let data = new SetRefPoseResponse(null);
    // Deserialize message field [update_status]
    data.update_status = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'drone_controller/SetRefPoseResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9f5872caddbe3a86c2173531b1fd3570';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool  update_status
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetRefPoseResponse(null);
    if (msg.update_status !== undefined) {
      resolved.update_status = msg.update_status;
    }
    else {
      resolved.update_status = false
    }

    return resolved;
    }
};

module.exports = {
  Request: SetRefPoseRequest,
  Response: SetRefPoseResponse,
  md5sum() { return 'a121ec35e34f22c1f30911ae51c46c9f'; },
  datatype() { return 'drone_controller/SetRefPose'; }
};
