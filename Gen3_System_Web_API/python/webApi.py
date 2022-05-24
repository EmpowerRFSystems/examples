#!/usr/bin/env python3

import requests, sys, ipaddress, json

USAGE_MSG = 'Usage: webApi HOST[:PORT] KEY [KEY ...]'
STATUS_URL_FMT = 'http://{ip}/api/v1/status'

if __name__ == '__main__':
    cmdArgLen = len(sys.argv)

    if cmdArgLen < 3:
        print(USAGE_MSG)
        sys.exit(1)

    ipArg = sys.argv[1]

    try:
        ip = ipaddress.ip_address(ipArg.split(':')[0])
    except Exception as e:
        print(e)
        sys.exit(1)

    url = STATUS_URL_FMT.format(ip=ipArg)

    jsonMsg = {}

    if cmdArgLen == 3:
        jsonMsg['messageType'] = 'getStatusItem'
        jsonMsg['key'] = sys.argv[2]
    else:
        jsonMsg['messageType'] = 'getStatusItemBatch'
        jsonMsg['keys'] = sys.argv[2:]

    r = requests.post(url, json=jsonMsg)

    print('JSON Request: ' + str(jsonMsg))
    print('Resp: ' + json.dumps(r.json(), indent=2, sort_keys=True))
