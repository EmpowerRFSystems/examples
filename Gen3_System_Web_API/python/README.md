Gen 3 System Web API with Python
=

This was tested on Windows 10 with Python 3.10


```
cd .../examples/Gen3_System_Web_API/python
```

This utility will change the internal command between "getStatusItem" and "getStatusItemBatch" depending on how many STATUS KEY's are provided

Examples:
-

Get Input Peak Power Reading
-
```
py ./webApi.py <IP Address>[:PORT] RF_POWER_LEVEL_INPUT_PEAK
```
Response:
-
```
JSON Request: {'messageType': 'getStatusItem', 'key': 'RF_POWER_LEVEL_INPUT_PEAK'}
Resp: {
  "messageType": "commandComplete",
  "meta": {
    "apiVersion": 1,
    "jsonContent": {
      "key": "RF_POWER_LEVEL_INPUT_PEAK",
      "messageType": "getStatusItem"
    },
    "processingEndTime": 1653416268.263941,
    "processingStartTime": 1653416268.261529,
    "processingTimeMilliseconds": 2.412,
    "socketName": "ipc:///tmp/root-statusProcessorAPI"
  },
  "request": {
    "key": "RF_POWER_LEVEL_INPUT_PEAK",
    "messageType": "getStatusItem"
  },
  "result": "success",
  "resultPayload": {
    "fullKey": "RF_POWER_LEVEL_INPUT_PEAK|RACK:0|SLOT:0",
    "internalCacheExpiryTime": 1653416273.206862,
    "key": "RF_POWER_LEVEL_INPUT_PEAK",
    "label": "Input Peak Hold",
    "rackId": 0,
    "slotId": 0,
    "timeoutMs": 5000,
    "units": "dBm",
    "user": "ROOT",
    "value": -0.03
  }
}
```

Get Input RMS Power Reading
-
```
webApi <IP Address>[:PORT] RF_POWER_LEVEL_INPUT_RMS
```
Response:
-
```
JSON Request: {'messageType': 'getStatusItem', 'key': 'RF_POWER_LEVEL_INPUT_RMS'}
Resp: {
  "messageType": "commandComplete",
  "meta": {
    "apiVersion": 1,
    "jsonContent": {
      "key": "RF_POWER_LEVEL_INPUT_RMS",
      "messageType": "getStatusItem"
    },
    "processingEndTime": 1653416357.668051,
    "processingStartTime": 1653416357.665528,
    "processingTimeMilliseconds": 2.523,
    "socketName": "ipc:///tmp/root-statusProcessorAPI"
  },
  "request": {
    "key": "RF_POWER_LEVEL_INPUT_RMS",
    "messageType": "getStatusItem"
  },
  "result": "success",
  "resultPayload": {
    "fullKey": "RF_POWER_LEVEL_INPUT_RMS|RACK:0|SLOT:0",
    "internalCacheExpiryTime": 1653416362.47211,
    "key": "RF_POWER_LEVEL_INPUT_RMS",
    "label": "Input RMS",
    "rackId": 0,
    "slotId": 0,
    "timeoutMs": 5000,
    "units": "dBm",
    "user": "ROOT",
    "value": -70
  }
}
```

Get Input Peak & RMS Power Readings Together
-
```
webApi <IP Address>[:PORT] RF_POWER_LEVEL_INPUT_PEAK RF_POWER_LEVEL_INPUT_RMS
```
Response:
-
```
JSON Request: {'messageType': 'getStatusItemBatch', 'keys': ['RF_POWER_LEVEL_INPUT_PEAK', 'RF_POWER_LEVEL_INPUT_RMS']}
Resp: {
  "messageType": "commandComplete",
  "meta": {
    "apiVersion": 1,
    "jsonContent": {
      "keys": [
        "RF_POWER_LEVEL_INPUT_PEAK",
        "RF_POWER_LEVEL_INPUT_RMS"
      ],
      "messageType": "getStatusItemBatch"
    },
    "processingEndTime": 1653416115.795078,
    "processingStartTime": 1653416115.792199,
    "processingTimeMilliseconds": 2.879,
    "socketName": "ipc:///tmp/root-statusProcessorAPI"
  },
  "request": {
    "keys": [
      "RF_POWER_LEVEL_INPUT_PEAK",
      "RF_POWER_LEVEL_INPUT_RMS"
    ],
    "messageType": "getStatusItemBatch"
  },
  "result": "success",
  "resultPayload": [
    {
      "fullKey": "RF_POWER_LEVEL_INPUT_PEAK|RACK:0|SLOT:0",
      "internalCacheExpiryTime": 1653416120.748042,
      "key": "RF_POWER_LEVEL_INPUT_PEAK",
      "label": "Input Peak Hold",
      "rackId": 0,
      "slotId": 0,
      "timeoutMs": 5000,
      "units": "dBm",
      "user": "ROOT",
      "value": -0.05
    },
    {
      "fullKey": "RF_POWER_LEVEL_INPUT_RMS|RACK:0|SLOT:0",
      "internalCacheExpiryTime": 1653416120.747195,
      "key": "RF_POWER_LEVEL_INPUT_RMS",
      "label": "Input RMS",
      "rackId": 0,
      "slotId": 0,
      "timeoutMs": 5000,
      "units": "dBm",
      "user": "ROOT",
      "value": -70
    }
  ]
}
```
