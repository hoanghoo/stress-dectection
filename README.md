# Stress Predict Service
## Create Virtual Environment using (virtualenv for linux)
```
virtualenv  vend
source vend/bin/activate
```

## Install 
```
 pip3 install -r requirements.txt
 python3 run.py
```

## Usage

All responses will have the form

```json
{
    "data": "Mixed type holding the content of the response",
    "message": "Description of what happened"
}
```

Subsequent response definitions will only detail the expected value of the `data field`

### List all devices

**Definition**

`GET /hearrate`

**Response**

- `200 OK` on success
### Registering a new device

**Definition**

`POST /devices`

**Arguments**

- `"time":string (format hh:mm:ss)` time when send data
- `"date":string (format dd:mm:yyyy)` date when send data
- `"data":string(format data1,data2,...)` list data hearrate


**Response**

- `200` on success

```


