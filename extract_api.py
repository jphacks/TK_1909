import pandas as pd
from flask import Flask, jsonify, render_template, redirect, request, url_for,current_app
import datetime
import requests
import matplotlib.pyplot as plt


app = Flask(__name__)

#if __name__ in "__main__":
 #   app.run(debug=True, threaded=True, port=3000)
@app.route("/jp_api/<manth_flg>", methods=["GET"])
def schedule_index(manth_flg):
    r_day = 7
    r_end = datetime.datetime.today()
    if manth_flg == 1:
        r_day = 30
    r_start = r_end - datetime.timedelta(days=r_day)
    r_start = r_start.strftime("%Y-%m-%d %H:%M")
    r_end = r_end.strftime("%Y-%m-%d %H:%M")
    df = pd.read_csv("test.csv")
    df = df[(df['date'] >= r_start) & (df['date'] <= r_end)]
    big_time = df.date[df['kind'] == "big"]
    small_time = df.date[df['kind'] == "small"]
    df['date'] = pd.to_datetime(df['date'])
    df['date'] = df['date'].dt.strftime('%Y-%m-%d')
    df = df.sort_values('date')
    date_df = pd.DataFrame(pd.date_range(df['date'].iloc[0],df['date'].iloc[-1] , freq='D').date, columns=['date'])
    kind_df = pd.DataFrame(df['kind'].unique(), columns=['kind'])
    date_df['key'] = 0
    kind_df['key'] = 0
    tmp_df = date_df.merge(kind_df, on='key').drop('key', axis=1)
    cnt_df = pd.DataFrame(df.groupby(['date','kind']).count()).reset_index()
    cnt_df.rename( columns={'Unnamed: 0':'cnt'}, inplace=True )
    cnt_df['date'] = cnt_df['date'].astype(str)
    tmp_df['date'] = tmp_df['date'].astype(str)

    cnt_df = pd.merge(tmp_df,cnt_df, on=['kind', 'date'], how="left")
    cnt_df = cnt_df.fillna(0)
    l_cnt =cnt_df[cnt_df['kind'] == "big"].reset_index()
    t_cnt =cnt_df[cnt_df['kind'] == "small"].reset_index()
    l_cnt['small'] = t_cnt['cnt']
    l_cnt.rename( columns={'cnt':'big'}, inplace=True )
    l_cnt = l_cnt.set_index('date')
    l_cnt = l_cnt[['small','big']]

    
    if(manth_flg==1):
        l_cnt.plot()
        plt.savefig('term_graph.png')
    
    else:
        l_cnt.plot.bar()
        plt.savefig('term_graph.png')
    
    big_time2 = pd.to_datetime(big_time)
    big_time2 = big_time2.dt.strftime('%H')
    small_time2 = pd.to_datetime(small_time)
    small_time2 = small_time2.dt.strftime('%H')
    big_time = list(big_time)
    small_time = list(small_time)
    plt.figure()
    plt.hist(big_time2,bins=24)
    plt.savefig('big_hist.png')
    plt.figure()
    plt.hist(small_time2,bins=24)
    plt.savefig('small_hist.png')

    data = {
        'graph': 'term_graph.png',
        'big':{
            'graph': 'big_hist.png',
            'time' : big_time

        },
        'small':{
            'graph': 'small_hist.png',
            'time' : small_time

        }
    }

    return jsonify(data)


if __name__ == "__main__":
   app.run(host='0.0.0.0',port=3000,threaded=True)
