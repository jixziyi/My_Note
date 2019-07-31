# JWT

## 定义
- JWT: Json Web Token，一种基于 JSON 的、用于在网络上声明某种主张的令牌 token。
- JWT 通常由三部分组成，header(头信息)、payload(消息体)、signature(签名)。它是一种用于双方之间传递安全信息的表述性声明规范
- JWT 作为一个开放的标准（RFC 7519），定义了一种简洁的、自包含的方法，从而使通信双方实现以JSON对象的形式安全的传递信息。

### header
- alg: 加密规范
- typ: JWT 字符串类型

``` json
{
  "alg": "HS256",
  "typ": "JWT"
}
```

### Payload
- iss: JWT 字符串的办法人名称
- exp: JWT 字符串过期时间
- sub: 身份
- aud: 受众
... 
- 自定义内容

``` json
{
  "iss": "PayPI",
  "sub": "Client",
  "name": "Nancy",
  "uid":  1
}
```

### Signature
- secret 密钥字符串
``` JavaScript
HMACSHA256(
  base64UrlEncode(header) + "." + 
  base64UrlEncode(payload),
  secret
)
```

### 令牌
用于 http 传输 headers 中用于验证授权的 JSON 数据，由 key 和 value 两部分组成，key 为 `Authorization`, value 为 `Bearer {JWT 字符串}`

``` json
{ "Authorization": "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiJDbGllbnQiLCJqdGkiOiIwZTRjYzVkNC0yMmIzLTQwYzUtOTBjMy0wOTk0MjFjNWRjMjkiLCJpYXQiOiIyMDE4LzcvMyAyOjE3OjQ5IiwiZXhwIjoxNTMwNjI3NDY5LCJpc3MiOiJSYXlQSSJ9.98pAaDVhNwVfiSHQVeXKhYE2ML6WK_f9rYC-iwyQEpU" }
```

