import requests
from flask import Flask, redirect, url_for, request, render_template
import json
from datetime import date, datetime, time, timedelta

app=Flask(__name__)

ae="Project_Ultra2"
cnt="Delta"
uriCse="http://127.0.0.1:8080/~/in-cse/in-name"
uriAe=uriCse+'/'+ae
uriCnt=uriAe+'/'+cnt

y=[]
x=[]

headers = { 'X-M2M-Origin': 'admin:admin', 'Content-type': 'application/json' } 

uri=uriCnt+"/?rcn=4"
getdata=requests.get(uri,headers=headers)

string = getdata.json()

# print(string)

for i in string['m2m:cnt']['m2m:cin']:
    # print(i['con'],i['ct'])
    y.append(int(i['con']))
    x.append(str(i['ct'][0:11][-2:])+":" + str(i['ct'][0:13][-2:])+":" + str(i['ct'][0:15][-2:]))

# print(y)
# print(x)
a=int(y[-1])
# print(a)

b=json.dumps(a)
x=json.dumps(x)
y=json.dumps(y)
print('Hey')
print(b)

# Temp And Humid
ae2='Project_DHT2'
cnt2='Temperature'
cnt3='Humidity'
uriAe2= uriCse+'/'+ae2
uriCnt2=uriAe2+'/'+cnt2
uriCnt3=uriAe2+'/'+cnt3

uri2=uriCnt2+"/?rcn=4"
uri3=uriCnt3+"/?rcn=4"
strng2 = (requests.get(uri2,headers=headers))
print(strng2)
string2 = strng2.json()
strng3 = (requests.get(uri3,headers=headers))
string3 = strng3.json()
Temp=[]
Hum=[]
for i in string2['m2m:cnt']['m2m:cin']:
    Temp.append(float(i['con']))

for i in string3['m2m:cnt']['m2m:cin']:
    Hum.append(float(i['con']))

Time=[]
timeobj = time(7,27,0)
tmtm = timedelta(minutes=3)
x = (datetime.combine(date(1,1,1),timeobj)  + tmtm).time()

for i in range(40):
    Time.append(str(x))
    x = (datetime.combine(date(1,1,1),x)  + tmtm).time()

lastT = Temp[-1]
lastH = Hum[-1]
print(lastH)
Hum = json.dumps(Hum)
Temp = json.dumps(Temp)
Time = json.dumps(Time)
print(Hum)
print('End')
print(Temp)
@app.route('/')
def index():
    return render_template('index.html',numx=Time,numy=y,num=a,Temp=Temp,Humid=Hum,lastT=lastT,lastH=lastH)

if __name__ == '__main__':
    app.run(debug=True)
