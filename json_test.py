import json
import pandas as pd

a = open("test")
b = json.load(a)
print(b["message"])
df = pd.DataFrame(columns = ['A','B'])
print(df)

data = pd.Series(['hoge', 'fuga'], index=df.columns)

df = df.append(data, ignore_index = True)

print(df)