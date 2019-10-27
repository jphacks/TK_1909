import datetime
import schedule
import time
import pandas as pd
import subprocess
import json

def job():
    df = pd.DataFrame(columns=['date','kind'])
    subprocess.call("aws s3 sync s3://dasumiru message", shell=True)
    time.sleep(10)
    tmp = open("~/message/AKIAR3QIC7VOP32KQWFI")
    j_tmp = json.load(tmp)
    while(1):
      try:
        data = pd.Series([j_tmp[i]["time"],j_tmp[i]["kind"]])
        if(df['time'] != j_tmp["time"]):
          df = df.append(data)
        i += 1
      except:
        break
    df.to_csv("~/csv/test.csv")

schedule.every().day.at("03:00").do(job)
  
while True:
  schedule.run_pending()
  time.sleep(60)