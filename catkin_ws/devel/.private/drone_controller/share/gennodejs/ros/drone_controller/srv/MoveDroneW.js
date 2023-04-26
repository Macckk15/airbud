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

class MoveDroneWRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.dx = null;
      this.dy = null;
      this.dalt = null;
      this.dyaw = null;
    }
    else {
      if (initObj.hasOwnProperty('dx')) {
        this.dx = initObj.dx
      }
      else {
        this.dx = 0.0;
      }
      if (initObj.hasOwnProperty('dy')) {
        this.dy = initObj.dy
      }
      else {
        this.dy = 0.0;
      }
      if (initObj.hasOwnProperty('dalt')) {
        this.dalt = initObj.dalt
      }
      else {
        this.dalt = 0.0;
      }
      if (initObj.hasOwnProperty('dyaw')) {
        this.dyaw = initObj.dyaw
      }
      else {
        this.dyaw = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MoveDroneWRequest
    // Serialize message field [dx]
    bufferOffset = _serializer.float64(obj.dx, buffer, bufferOffset);
    // Serialize message field [dy]
    bufferOffset = _serializer.float64(obj.dy, buffer, bufferOffset);
    // Serialize message field [dalt]
    bufferOffset = _serializer.float64(obj.dalt, buffer, bufferOffset);
    // Serialize message field [dyaw]
    bufferOffset = _serializer.float64(obj.dyaw, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MoveDroneWRequest
    let len;
    let data = new MoveDroneWRequest(null);
    // Deserialize message field [dx]
    data.dx = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dy]
    data.dy = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dalt]
    data.dalt = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dyaw]
    data.dyaw = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 32;
  }

  static datatype() {
    // Returns string type for a service object
    return 'drone_controller/MoveDroneWRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '07412add1f140833b90a1495d256d55d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 dx
    float64 dy
    float64 dalt
    float64 dyaw
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MoveDroneWRequest(null);
    if (msg.dx !== undefined) {
      resolved.dx = msg.dx;
    }
    else {
      resolved.dx = 0.0
    }

    if (msg.dy !== undefined) {
      resolved.dy = msg.dy;
    }
    else {
      resolved.dy = 0.0
    }

    if (msg.dalt !== undefined) {
      resolved.dalt = msg.dalt;
    }
    else {
      resolved.dalt = 0.0
    }

    if (msg.dyaw !== undefined) {
      resolved.dyaw = msg.dyaw;
    }
    else {
      resolved.dyaw = 0.0
    }

    return resolved;
    }
};

class MoveDroneWResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.command_status = null;
    }
    else {
      if (initObj.hasOwnProperty('command_status')) {
        this.command_status = initObj.command_status
      }
      else {
        this.command_status = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MoveDroneWResponse
    // Serialize message field [command_status]
    bufferOffset = _serializer.bool(obj.command_status, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MoveDroneWResponse
    let len;
    let data = new MoveDroneWResponse(null);
    // Deserialize message field [command_status]
    data.command_status = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'drone_controller/MoveDroneWResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '943f51d9faa4a44a232934ed3bd1b114';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool    command_status
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MoveDroneWResponse(null);
    if (msg.command_status !== undefined) {
      resolved.command_status = msg.command_status;
    }
    else {
      resolved.command_status = false
    }

    return resolved;
    }
};

module.exports = {
  Request: MoveDroneWRequest,
  Response: MoveDroneWResponse,
  md5sum() { return '07cc5e7856beb68b29432db43546cf40'; },
  datatype() { return 'drone_controller/MoveDroneW'; }
};
