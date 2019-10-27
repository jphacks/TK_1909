import pandas as pd
import random
import time

def strTimeProp(start, end, format, prop):

    stime = time.mktime(time.strptime(start, format))
    etime = time.mktime(time.strptime(end, format))

    ptime = stime + prop * (etime - stime)

    return time.strftime(format, time.localtime(ptime))


def randomDate(start, end, prop):
    return strTimeProp(start, end, '%Y-%m-%d %H:%M', prop)


kind = ['big', 'small']
df = pd.DataFrame({
    'kind':[],
    'date':[]})

for i in range(300):
    s_kind = random.choice(kind)
    s_time = randomDate("2019-09-30 00:00", "2019-10-30 23:59", random.random())
    i_date = pd.Series([s_time,s_kind],index=df.columns)
    df = df.append(i_date,ignore_index=True)
df.to_csv('test.csv')