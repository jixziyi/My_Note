# Json

## JObject / JArray
可以使用JObject和JArray来操作数据，过程中无需了解数据细节
需要引用 Newtonsoft.Json.Linq 命名空间
``` CSharp
using Newtonsoft.Json.Linq;

public void BeltPlace<T>(string name, List<T> slots)
{
    string data = JsonConvert.SerializeObject(new { Name = name, Slots = slots });
    string send = "BTC" + data;
    client.Send(send);
}

JObject jObj = (JObject)JsonConvert.DeserializeObject(msg);
string name = jObj["Name"].ToString();
JArray slots = (JArray) jObj["Slots"];
```

