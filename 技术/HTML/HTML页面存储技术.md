
# HTML页面存储技术

## Web SQL

<!-- more -->

## IndexedDB

## Local Storage

## Session Storage

## Cookies

**设置Cookie**
语法说明：

1. Cookie默认有效时间是当前Session，指定时间方法是给定expires值
2. Cookie存储时使用`key=value`形式，不同值间使用`;`和` `/空格分隔，Cookie键值对中不能出现分号`;`、逗号`,`、等号`=`、以及空格` `。针对特殊字符处理方式是使用`escape()`函数进行编码，解码时使用`unescape()`函数。

```javascript
var MaxAge = new Date();
MaxAge.setDate(MaxAge.getDate() + 14);
document.cookie = "user=guo;expires=" + MaxAge;
```
<div>
<input type="button" onclick="setCookie()" value="SetCookie" />
Name:
<input id="Name" type="text" />
<input type="button" onclick="getCookie()" value="GetCookie" />
<script type="text/javascript">
function setCookie(){
	var MaxAge = new Date();
	MaxAge.setDate(MaxAge.getDate() + 14);
	var Name = this.document.getElementById("Name").value;
	var address = escape("Shen Zhen");
	document.cookie = "user=" + Name + "; expires=" + MaxAge;
	document.cookie = "address=" + address + "; expires=" + MaxAge;
}
function getCookie(){
	alert(document.cookie);
}
</script>
</div>

**Cookie使用**

```javascript
//设置Cookie
function setCookie(name, value, expireHours){
	var date = new Date();
	date.setTime(date.getTime + expireHours*3600*1000);
	var str = name + "=" excape(value) + "; expires=" + date.toGMTString();
	document.cookie = str;
}

//获取Cookie
function getCookie(name){
	var arr = document.cookie.match(new RegExp("(^| )user=([^;]*)(;|$)"));
	if(arr != null){return unexcape(arr[2]);}
	else{return null;}
}

//删除Cookie
function delCookie(name){
	var exp = new Date();
	exp.setTime(exp.getTime() - 1);
	var cval = getCookie(name);
	if (cval != null){
		document.cookie = name + "=" + cval + "; expires=" + exp.toGMTString();
	}
}
```

## Application Cache
