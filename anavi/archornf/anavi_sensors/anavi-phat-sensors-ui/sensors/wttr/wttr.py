import requests
import json

city = "Uppsala"
url = "https://wttr.in/" + city + "?format=j1"

res = requests.get(url)
#print(res.text)
#print(json.loads(res.text))

data = json.loads(res.text)
#print(data)
temp = data["current_condition"][0]["temp_C"]
time = data["current_condition"][0]["observation_time"]
print_text = '{ "temp_C": "' + temp + '", "observation_time": "' + time + '" }'
#print(print_text)

if len(time) > 2:
    with open('/home/pi/Code/anavi-phat-sensors-ui/data/wttr.json', 'w') as f:
        print(print_text, file=f)
