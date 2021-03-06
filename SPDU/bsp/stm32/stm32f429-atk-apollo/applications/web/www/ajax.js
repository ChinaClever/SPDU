
function queryURL(url){
    var params = url.split("&");
    var obj = {};//声明对象
    for(var i=0;i<params.length;i++){
        var param = params[i].split("=");
        obj[param[0]] = param[1];//为对象赋值
    }
    
    return obj;
}

// XMLHttpRequest
function sendAjax(options) {
	
	var request;
	if (window.XMLHttpRequest) {		
		request=new XMLHttpRequest(); //  IE7+, Firefox, Chrome, Opera, Safari 浏览器执行代码
	} else {		
		request=new ActiveXObject("Microsoft.XMLHTTP"); // IE6, IE5 浏览器执行代码
	}
    request.open(options.method, options.url +'?' +options.data, true);
    request.send();
    request.onreadystatechange = function () {
        if (request.readyState === 4) {
            if (request.status >= 200 && request.status < 300) {				 
				options.success && options.success(queryURL(request.response));
            } else if (request.status >= 400) {
                options.fail && options.fail(request);
            }
        }
    };
}

/**
 * ajax请求
 * @param {Object} options
 * options: {
 *      url: 业务接口
 *      method: 请求方法
 *      data: 请求参数
 *      success: 页面渲染成功回调
 *      fail: 页面渲染失败回调
 * }
 */
function ajaxRequest(options) {
    sendAjax({
        url: '/cgi-bin/' + options.url,
        method: 'POST',
        data: options.data,
        success: function (response) {
            try {
                options.success && options.success(response);
            } catch (error) {
                options.fail && options.fail(error);
            }
        },
        fail: function (err) {
            options.fail && options.fail(err);
        }
    })
}


// var str1 = "hello {0}".format("world"); //hello world
// var str2 = "{0}总冠军, {1}总冠军".format("湖人", "骑士"); // 湖人总冠军，骑士总冠军

// var user = {name: "James",sex: "male",age: 34};
// var str3 = "史上第一个30000+8000+8000球员：{name}, 性别{sex}, 今年{age}岁".format(user); 

String.prototype.format= function() {
    if(arguments.length === 0) return this;
    var param = arguments[0], str= this;
    if(typeof(param) === 'object') {
        for(var key in param)
            str = str.replace(new RegExp("\\{" + key + "\\}", "g"), param[key]);
        return str;
    } else {
        for(var i = 0; i < arguments.length; i++)
            str = str.replace(new RegExp("\\{" + i + "\\}", "g"), arguments[i]);
        return str;
    }
}

// 对Date的扩展，将 Date 转化为指定格式的String
// 月(M)、日(d)、小时(h)、分(m)、秒(s)、季度(q) 可以用 1-2 个占位符， 
// 年(y)可以用 1-4 个占位符，毫秒(S)只能用 1 个占位符(是 1-3 位的数字) 
// 例子： 
// (new Date()).Format("yyyy-MM-dd hh:mm:ss.S") ==> 2006-07-02 08:09:04.423 
// (new Date()).Format("yyyy-M-d h:m:s.S")      ==> 2006-7-2 8:9:4.18 
Date.prototype.Format = function (fmt) {
    var o = {
        "M+": this.getMonth() + 1, //月份 
        "d+": this.getDate(), //日 
        "H+": this.getHours(), //小时 
        "m+": this.getMinutes(), //分 
        "s+": this.getSeconds(), //秒 
        "q+": Math.floor((this.getMonth() + 3) / 3), //季度 
        "S": this.getMilliseconds() //毫秒 
    };
    if (/(y+)/.test(fmt)) fmt = fmt.replace(RegExp.$1, (this.getFullYear() + "").substr(4 - RegExp.$1.length));
    for (var k in o)
    if (new RegExp("(" + k + ")").test(fmt)) fmt = fmt.replace(RegExp.$1, (RegExp.$1.length == 1) ? (o[k]) : (("00" + o[k]).substr(("" + o[k]).length)));
    return fmt;
}
