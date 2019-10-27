using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using Newtonsoft.Json.Linq;
using UnityEngine;
using UnityEngine.Networking;

public class JsonDataManager : MonoBehaviour
{
    // 一日ごとのデータを格納。
    Dictionary<DateTime, List<TimeAndType>> countPerDayDict;

    void Start ()
    {
        // テストデータ
        TextAsset textasset = new TextAsset ();
        textasset = Resources.Load ("jsondata", typeof (TextAsset)) as TextAsset;
        string jsonText = textasset.text;

        StartCoroutine (ConnectToHttpCoroutine ());

        // はじめにAPIにアクセスしてJSONデータをとってくる。

        var jo = JObject.Parse (jsonText);
        var bigTimes = CreateTimes (jo, "big");
        var smallTimes = CreateTimes (jo, "small");
        CreateDictPerDay (bigTimes, smallTimes);
    }

    //コルーチン
    IEnumerator ConnectToHttpCoroutine ()
    {
        // URLをGETで用意
        UnityWebRequest webRequest = UnityWebRequest.Get ("http://127.0.0.1:5000/jp_api/0");
        //URLに接続して結果が戻ってくるまで待機
        yield return webRequest.SendWebRequest ();

        //エラーが出ていないかチェック
        if (webRequest.isNetworkError)
        {
            //通信失敗
            Debug.Log (webRequest.error);
        }
        else
        {
            //通信成功
            Debug.Log (webRequest.downloadHandler.text);
        }
    }

    void CreateDictPerDay (IList<string> bigTimes, IList<string> smallTimes)
    {
        countPerDayDict = new Dictionary<DateTime, List<TimeAndType>> ();
        RoopPerType (bigTimes, "big");
        RoopPerType (smallTimes, "small");

        foreach (var dic in countPerDayDict)
        {
            //Debug.Log ("key: " + dic.Key);
            foreach (var v in dic.Value)
            {
                //Debug.Log ($"{v.time} | {v.type}");
            }
        }
    }

    void RoopPerType (IList<string> times, string type)
    {
        var pattern = "yyyy-M-d";
        DateTime parsedDate;
        TimeSpan parsedTimeSpan;

        foreach (var str in times)
        {
            var pair = str.Split (' ');

            // 日付のパース
            if (DateTime.TryParseExact (pair[0], pattern, null,
                    DateTimeStyles.None, out parsedDate))
            {
                //Debug.Log ($"Converted '{pair[0]}' to {parsedDate:d}.");
            }
            else
            {
                Debug.LogError ($"Unable to convert '{pair[0]}' to a date and time.");
            }

            // 時刻のパース
            try
            {
                parsedTimeSpan = TimeSpan.Parse (pair[1]);
            }
            catch (FormatException)
            {
                Debug.LogError ($"{pair[1]}: Bad Format");
            }

            // すでにその日付のキーが存在
            if (countPerDayDict.ContainsKey (parsedDate))
            {
                countPerDayDict[parsedDate].Add (new TimeAndType (parsedTimeSpan, type));
            }
            // まだない
            else
            {
                countPerDayDict.Add (parsedDate, new List<TimeAndType> ());
                countPerDayDict[parsedDate].Add (new TimeAndType (parsedTimeSpan, type));
            }
        }
    }

    IList<string> CreateTimes (JObject jo, string size)
    {
        IList<JToken> jTokens = jo[size]["time"].Children ().ToList ();
        IList<string> times = new List<string> ();

        foreach (var jToken in jTokens)
        {
            times.Add (jToken.ToString ());
        }
        return times;
    }
}

/// <summary>
/// 時刻と種類の型
/// </summary>
public class TimeAndType
{
    public readonly TimeSpan time;
    public readonly string type;

    public TimeAndType (TimeSpan time, string type)
    {
        this.time = time;
        this.type = type;
    }
}