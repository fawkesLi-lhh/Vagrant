#include"HttpResponse.h"

HttpResponse::HttpResponse()
:header(LONG),value(LONG),has_gen(false),respLen(-1){ 
   header.append("HTTP/1.1 200 OK\n");
}

void HttpResponse::addValue(const char* str){
   value.append(str);
}

void HttpResponse::addHeader(const char* str){
   header.append(str);
}
void HttpResponse::addCookie(const char* str){
   String buffer(MIDDLE);
   sprintf(buffer.c_str(),"Cookie: %s\n",str);
   header.append(buffer);
}

String HttpResponse::getHeader(){
   return header;
}
String HttpResponse::getValue(){
   return value;
}

void HttpResponse::generateResponse(){
   has_gen = true;
   String buffer(MIDDLE);
   if(respLen == -1)respLen = strlen(value.c_str());
   sprintf(buffer.c_str(),"Content-Length: %d\n",respLen);
   header.append(buffer.c_str());
   header.append("Connection: keep-alive\n");
   header.append("\n");
   header.append(value.c_str());
}

String& HttpResponse::getResponse(){
   if(!has_gen)generateResponse();
   return header;
}

void HttpResponse::setResponseLength(int len){
   respLen = len;
}


// GET /index.html HTTP/1.1
// Host: localhost:5656
// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:84.0) Gecko/20100101 Firefox/84.0
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive
// Cookie: _ga=GA1.1.303439046.1606725789
// Upgrade-Insecure-Requests: 1


// end
// var/www/html/index.html
// ok
// HTTP/1.1 200 OK
// Content-Length: 2161
// Connection: keep-alive


// <!DOCTYPE html>
// <html lang="en">
// <head>
//     <meta charset="UTF-8">
//     <title>Title</title>
//     <style>
//         * {
//             margin: 0;
//             padding: 0;
//         }
//         html {
//             height: 100%;
//         }
//         body {
//             height: 100%;
//             display: flex;
//             justify-content: center;
//             align-items: center;
//             overflow: hidden;
//         }
//         .login {
//             width: 350px;
//             height: 230px;
//             background-color: rgba(0,0,0,.3);
//             display: flex;
//             flex-direction: column;
//             align-content: center;
//             justify-content: center;
//             border-radius: 5px;
//         }
//         p {
//             text-align: center;
//             margin: 12px auto;
//             color: #fff;
//         }
//         button {
//             width: 220px;
//             height: 30px;
//             background-color: skyblue;
//             font-size: 18px;
//             font-weight: bold;
//             line-height: 30px;
//             border: 0;
//         }
//         input {
//             height: 23px;
//         }
//     </style>
// </head>
// <body style="background-color: #1c77ac;">
// <div class="login">
//     <h3 style="text-align: center; color: #fff;">登录测试</h3>
//     <p>
//         账号：<input type="text" name="user" id="user">
//     </p>
//     <p>
//         密码：<input type="password" name="pwd" id="pwd">
//     </p>
//     <p>
//         <button type="button" id="btn">提交</button>
//     </p>
// </div>
// </body>
// <script type="text/javascript" src="https://cdn.jsdelivr.net/npm/jquery/dist/jquery.min.js"></script>
// <script>
//     var btn = document.getElementById("btn");
//     var user = document.getElementById("user");
//     var pwd = document.getElementById("pwd");
//     btn.onclick = function() {
//         $.ajax({
//             url: "http://localhost:6546/xinguan/ProvinceTotal",
//             type: "POST",
//             data: {"name":user.value,"passward":pwd.value},
//             dataType: "json",
//             success: function(res) {
//                 console.log(res);
//             }
//         });
//     }
// </script>
// </html>

// GET /favicon.ico HTTP/1.1
// Host: localhost:5656
// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:84.0) Gecko/20100101 Firefox/84.0
// Accept: image/webp,*/*
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive
// Referer: http://localhost:5656/index.html
// Cookie: _ga=GA1.1.303439046.1606725789


// end
// var/www/html/favicon.ico
// ok
// HTTP/1.1 404 Not Found
// Content-Length: 49
// Connection: keep-alive

// The requested file was not found on this server.


