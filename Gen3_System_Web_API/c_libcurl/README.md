Gen 3 System Web API with C and libcurl
=

This was tested on Ubuntu Linux 18.04 with build-essential and libcurl4-openssl-dev packages installed

Installed curl devel package:
-
sudo apt install build-essential libcurl4-openssl-dev

```
cd .../examples/Gen3_System_Web_API/c_libcurl/
make

make run ARGS='<IP ADDRESS> <STATUS KEY> [<STATUS KEY> [...]]'
    -- OR --
./build/webApi <IP ADDRESS> <STATUS KEY> [<STATUS KEY> [...]]
```

This utility will change the internal command between "getStatusItem" and "getStatusItemBatch" depending on how many STATUS KEY's are provided

Examples:
-

Get Input Peak Power Reading
-
```
webApi <IP Address>[:PORT] RF_POWER_LEVEL_INPUT_PEAK
```
Response:
-
```
JSON Request: {"messageType":"getStatusItem","key":"RF_POWER_LEVEL_INPUT_PEAK"}
Resp: {"meta":{"apiVersion":1,"processingStartTime":1653097823.063624,"socketName":"ipc:\/\/\/tmp\/root-statusProcessorAPI","jsonContent":{"messageType":"getStatusItem","key":"RF_POWER_LEVEL_INPUT_PEAK"},"processingEndTime":1653097823.066405,"processingTimeMilliseconds":2.781},"messageType":"commandComplete","result":"success","resultPayload":{"key":"RF_POWER_LEVEL_INPUT_PEAK","rackId":0,"slotId":0,"fullKey":"RF_POWER_LEVEL_INPUT_PEAK|RACK:0|SLOT:0","value":-0.01,"units":"dBm","timeoutMs":5000,"label":"Input Peak Hold","user":"ROOT","internalCacheExpiryTime":1653097828.003153},"request":{"messageType":"getStatusItem","key":"RF_POWER_LEVEL_INPUT_PEAK"}}
```

Get Input RMS Power Reading
-
```
webApi <IP Address>[:PORT] RF_POWER_LEVEL_INPUT_RMS
```
Response:
-
```
JSON Request: {"messageType":"getStatusItem","key":"RF_POWER_LEVEL_INPUT_RMS"}
Resp: {"meta":{"apiVersion":1,"processingStartTime":1653098016.074261,"socketName":"ipc:\/\/\/tmp\/root-statusProcessorAPI","jsonContent":{"messageType":"getStatusItem","key":"RF_POWER_LEVEL_INPUT_RMS"},"processingEndTime":1653098016.078321,"processingTimeMilliseconds":4.06},"messageType":"commandComplete","result":"success","resultPayload":{"key":"RF_POWER_LEVEL_INPUT_RMS","rackId":0,"slotId":0,"fullKey":"RF_POWER_LEVEL_INPUT_RMS|RACK:0|SLOT:0","value":-70,"units":"dBm","timeoutMs":5000,"label":"Input RMS","user":"ROOT","internalCacheExpiryTime":1653098021.075683},"request":{"messageType":"getStatusItem","key":"RF_POWER_LEVEL_INPUT_RMS"}}
```

Get Input Peak & RMS Power Readings Together
-
```
webApi <IP Address>[:PORT] RF_POWER_LEVEL_INPUT_PEAK RF_POWER_LEVEL_INPUT_RMS
```
Response:
-
```
JSON Request: {"messageType":"getStatusItemBatch","keys":["RF_POWER_LEVEL_INPUT_PEAK","RF_POWER_LEVEL_INPUT_RMS"]}
Resp: {"meta":{"apiVersion":1,"processingStartTime":1653098072.05375,"socketName":"ipc:\/\/\/tmp\/root-statusProcessorAPI","jsonContent":{"messageType":"getStatusItemBatch","keys":["RF_POWER_LEVEL_INPUT_PEAK","RF_POWER_LEVEL_INPUT_RMS"]},"processingEndTime":1653098072.056452,"processingTimeMilliseconds":2.702},"messageType":"commandComplete","result":"success","resultPayload":[{"key":"RF_POWER_LEVEL_INPUT_PEAK","rackId":0,"slotId":0,"fullKey":"RF_POWER_LEVEL_INPUT_PEAK|RACK:0|SLOT:0","value":-0.03,"units":"dBm","timeoutMs":5000,"label":"Input Peak Hold","user":"ROOT","internalCacheExpiryTime":1653098076.773807},{"key":"RF_POWER_LEVEL_INPUT_RMS","rackId":0,"slotId":0,"fullKey":"RF_POWER_LEVEL_INPUT_RMS|RACK:0|SLOT:0","value":-15.64,"units":"dBm","timeoutMs":5000,"label":"Input RMS","user":"ROOT","internalCacheExpiryTime":1653098076.769954}],"request":{"messageType":"getStatusItemBatch","keys":["RF_POWER_LEVEL_INPUT_PEAK","RF_POWER_LEVEL_INPUT_RMS"]}}
```
