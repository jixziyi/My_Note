
Mongoose是基于node-mongodb-native开发的MongoDB nodejs驱动，可以在异步的环境下执行。
<!--more-->

**Connect**
``` javascript
//方式1
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/test');

//方式二
var db = mongoose.connection;
db.on('error', console.error.bind(console, 'conection err:'));
db.once('open', function(){
	// do something...
});
```

**Schema**
With Mongoose, everything is derived from a Schema.
Schema包含数据类型：String、Number、Date、Buffer、Boolean、Mixed`任意类型`、ObjectId、Array
``` javascript
var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var blogSchema = new Schema({
	title:	String,
	author:	String,
	body:	String,
	comments:	[{body:String, date: Date}],
	date:	{type:Date, default: Date.now},
	hidden:	Boolean
})
```

**Model**
Compiling schema into a Model.
``` javascript
var Kitten = mongoose.model('Kitten', kittySchema)；
var kit = new Kitten({
  title:'AAA',
  author:'XXX',
  body:'afdsas'
});
kit.save(function(err){
  if(err){
    return handleError(err);
  }
})

Kitten.create({
  title:'AAA',
  author:'XXX',
  body:'afdsas'
}, function(err, small){
  if(err){
    return handleError(err);
  }
})
```
