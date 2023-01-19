from oneM2M_functions  import *
import time
import random
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
ae = "Project_DHT6"
cnt = "Temperature"
cnt2 = "Humidity"
create_ae(uri_cse,ae)

uri_ae=uri_cse+"/"+ae
create_cnt(uri_ae,cnt)
create_cnt(uri_ae,cnt2)

uri_cnt = uri_ae + "/" + cnt
uri_cnt1 = uri_ae + "/" + cnt2

ae2 = "Project_Ultra6"
cnt3 = "Delta"
create_ae(uri_cse,ae2)

uri_ae2 = uri_cse+"/"+ae2
create_cnt(uri_ae2,cnt3)

uri_cnt3 = uri_cse+'/'+ae2 + "/" + cnt3

# for i in range(10):
#     create_data_cin(uri_cnt, str(random.random()*5+25))

#     create_data_cin(uri_cnt1, str(random.random()*10+45))
#     create_data_cin(uri_cnt3, str(int(random.random()*10+20)))
#     time.sleep(0.5)

# for i in range(20):
#     create_data_cin(uri_cnt, str(random.random()*5+25+i*0.5))

#     create_data_cin(uri_cnt1, str(random.random()*10+45+i*1.1))
#     create_data_cin(uri_cnt3, str(int(random.random()*10+42 + i*2.5)))
#     time.sleep(0.5)

# for i in range(10):
#     create_data_cin(uri_cnt, str(random.random()*5+25-i*0.1))

#     create_data_cin(uri_cnt1, str(random.random()*10+45-i*0.5))
#     create_data_cin(uri_cnt3, str(int(random.random()*20+64  - i*4.5)))
#     time.sleep(0.5)


create_ae(uri_cse,ae2)
create_cnt(uri_cse+"/"+ae2,cnt3)

# for i in range(15,60,5):
#     create_data_cin(uri_cnt3, str(i))
#     time.sleep(1)
# for i in range(47,13,-3):
#     create_data_cin(uri_cnt3, str(i))
#     time.sleep(2)
