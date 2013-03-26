/*
    Copyright 2011 - Tommi Laukkanen (www.substanceofcode.com)

    This file is part of TwimGo.

    NewsFlow is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with NewsFlow. If not, see <http://www.gnu.org/licenses/>.
*/

Qt.include("sha1.js")

String.prototype.startsWith = function(str) {return (this.match("^"+str)==str)}

function XAuth() {

    var OAUTH_CONSUMER_TOKEN = "XCL6luL7vjkEQ2s4bjRiFg";
    var OAUTH_CONSUMER_SECRET = "wpIYreMj0GM3Uo6GZGcHCbPlObFN3nevdURE2LZalM";
    var HMACSHA1SignatureType = "HMAC-SHA1";

    var OAuthVersion = "1.0";
    var OAuthParameterPrefix = "oauth_";

    var OAuthConsumerKeyKey = "oauth_consumer_key";
    var OAuthCallbackKey = "oauth_callback";
    var OAuthVersionKey = "oauth_version";
    var OAuthSignatureMethodKey = "oauth_signature_method";
    var OAuthSignatureKey = "oauth_signature";
    var OAuthTimestampKey = "oauth_timestamp";
    var OAuthNonceKey = "oauth_nonce";
    var OAuthTokenKey = "oauth_token";
    var OAuthTokenSecretKey = "oauth_token_secret";
    var OAuthVerifier = "oauth_verifier";

    var token = "";
    var tokenSecret = "";
    var timeCorrection = 0;

    var showError;

    var OAUTH_ACCESS_TOKEN_URL = "https://api.twitter.com/oauth/access_token";

    this.setErrorCallback = function(callback) {
        showError = callback;
    }

    this.setTokenAndSecret = function(newToken, newTokenSecret) {
        token = newToken;
        tokenSecret = newTokenSecret;
    }

    function doWebRequest(method, url, callback, errorCallback) {
        var doc = new XMLHttpRequest();
        console.log("HTTPRequest to " + url);
        doc.onreadystatechange = function() {
            var shortURL = url;
            if (doc.readyState == XMLHttpRequest.HEADERS_RECEIVED) {
                var status = doc.status;
                console.log("HTTP status on headers " + status);
                if(timeCorrection==0) {
                    var twitterDateString = doc.getResponseHeader("Date");
                    console.log("Twitter date: " + twitterDateString);
                    if(twitterDateString.length>0) {
                        var twitterDate = parseDate(twitterDateString);
                        timeCorrection = twitterDate.getTime() - (new Date()).getTime();
                        console.log("Twitter time offset: " + timeCorrection);
                    } else {
                        console.log("Couldn't parse Twitter time offset");
                    }
                }
                if(status!=200) {
                    if(shortURL.length>32) {
                        shortURL = shortURL.substring(0,40) + "..";
                    }
                    showError("Twitter API returned " + status + " " + doc.statusText + " on URL " + shortURL);
                    return;
                }
            } else if (doc.readyState == XMLHttpRequest.DONE) {
                var status = doc.status;
                if(timeCorrection==0) {
                    var twitterDateString = doc.getResponseHeader("Date");
                    console.log("Twitter date: " + twitterDateString);
                    if(twitterDateString.length>0) {
                        var twitterDate = parseDate(twitterDateString);
                        timeCorrection = twitterDate.getTime() - (new Date()).getTime();
                        console.log("Twitter time offset: " + timeCorrection);
                    } else {
                        console.log("Couldn't parse Twitter time offset");
                    }
                }
                if(status!=200) {
                    console.log("HTTP status " + status);
                    if(shortURL.length>40) {
                        shortURL = shortURL.substring(0,40) + "..";
                    }
                    showError("Twitter API returned " + status + " " + doc.statusText + " on URL " + shortURL);
                    return;
                }
                var data = doc.responseText;
                if(typeof(data)=="undefined") {
                    data = "";
                }
                console.log("data=" + data);
                console.log("Callback=" + callback);
                callback(data);
            }
        }
        doc.open(method, url);
        doc.send();
    }

    this.getQueryParameters = function(url) {
        var questionMarkIndex = url.indexOf("?");
        if(questionMarkIndex<0) {
            return new Array();
        }
        var parameters = url.substring(questionMarkIndex+1);
        var params = new Array();
        var para = parameters.split("&");
        for(var i=0; i<para.length; i++) {
            if(para[i].startsWith("oauth")==false) {
                var nameValue = para[i].split("=");
                var q = [nameValue[0], nameValue[1]];
                params.push(q);
            }
        }
        return params;
    }

    this.generateSignatureBase = function(url,consumerKey,token,tokenSecret,httpMethod,timeStamp,nonce,signatureType) {
        if (typeof(token)=="undefined")
        {
            token = "";
        }
        if (typeof(tokenSecret)=="undefined")
        {
            tokenSecret = "";
        }

        var parameters = this.getQueryParameters(url);
        parameters.push( [OAuthVersionKey, OAuthVersion] );
        parameters.push( [OAuthNonceKey, nonce] );
        parameters.push( [OAuthTimestampKey, timeStamp] );
        parameters.push( [OAuthSignatureMethodKey, signatureType] );
        parameters.push( [OAuthConsumerKeyKey, consumerKey] );
        if (typeof(token)!="undefined" && token!="")
        {
            parameters.push( [OAuthTokenKey, token] );
        }

        this.sortParameters( parameters );

        var normalizedUrl = this.getSchemeAndHost(url);
        normalizedUrl += this.getAbsolutePath(url);
        var normalizedRequestParameters = this.normalizeRequestParameters(parameters);

        var signatureBase = "";
        signatureBase += httpMethod + "&";
        signatureBase += this.encode(normalizedUrl) + "&";
        signatureBase += this.encode(normalizedRequestParameters);

        var returnObject = new Object();
        returnObject.normalizedUrl = normalizedUrl;
        returnObject.normalizedRequestParameters = normalizedRequestParameters;
        returnObject.signatureBase = signatureBase;

        return returnObject;
    }

    this.getSchemeAndHost = function(url) {
        var startIndex = url.indexOf("//")+2;
        var endIndex = url.indexOf("/", startIndex);
        return url.substring(0,endIndex);
    }

    this.getAbsolutePath = function(url) {
        var startIndex = url.indexOf("//")+2;
        var endIndex = url.indexOf("/", startIndex);
        var questionMark = url.indexOf("?");
        if(questionMark>0) {
            return url.substring(endIndex, questionMark);
        } else {
            return url.substring(endIndex);
        }
    }

    this.sortParameters = function(items) {
        items.sort();
    }

    this.generateSignature = function(url, consumerKey, consumerSecret,token,tokenSecret,httpMethod,timeStamp,nonce) {
        var obj = this.generateSignatureBase(
                url,
                consumerKey,
                token,
                tokenSecret,
                httpMethod,
                timeStamp,
                nonce,
                HMACSHA1SignatureType);
        var signatureBase = obj.signatureBase;
        var tokenSec = "";
        if(typeof(tokenSecret)!="undefined") {
            tokenSec = tokenSecret;
        }
        var key = this.encode(consumerSecret) + "&" + this.encode(tokenSec);
        var signature = this.getSignature(signatureBase, key);
        obj.signature = signature;
        return obj;
    }

    this.getSignature = function(message, key)  {
        var b64pad = '=';
        var signature = b64_hmac_sha1(key, message);
        return signature;
    }

    this.normalizeRequestParameters = function( parameters ) {
        var sb = "";
        for(var i in parameters) {
            var par = parameters[i];
            sb += par[0] + "=" + par[1] + "&";
        }
        return sb.substring(0, sb.length-1);
    }

    this.generateTimeStamp = function() {
        var d = new Date();
        var utc = Date.UTC(d.getFullYear(), d.getMonth(), d.getDate(), d.getHours(), d.getMinutes(), d.getSeconds());
        var t = utc + 0;
        var p = (new Date()).getTime() + timeCorrection;
        console.log("t: " + t);
        console.log("p: " + p);
        return Math.floor(p / 1000);
    }

    // pass in the 'created_at' string returned from twitter //
    // stamp arrives formatted as Tue Apr 07 22:52:51 +0000 2009 //
    // Wed, 10 Aug 2011 19:30:24 GMT
    function parseDate(stamp)
    {
        try {
            var parts = stamp.split(" ");
            var dayName;
            var monthName;
            var day;
            var time;
            var hours;
            var minutes;
            var seconds;
            var offset;
            var year;

            // Wed, 10 Aug 2011 19:30:24 GMT
            dayName = parts[0];
            day = parseInt(parts[1], 10);
            monthName = parts[2];
            year = parseInt(parts[3], 10);
            time = parts[4].split(":");
            hours = parseInt(time[0], 10);
            minutes = parseInt(time[1], 10);
            seconds = parseInt(time[2], 10);

            var month = 0;
            if(monthName=="Jan") {
                month = 0;
            } else if(monthName=="Feb") {
                month = 1;
            } else if(monthName=="Mar") {
                month = 2;
            } else if(monthName=="Apr") {
                month = 3;
            } else if(monthName=="May") {
                month = 4;
            } else if(monthName=="Jun") {
                month = 5;
            } else if(monthName=="Jul") {
                month = 6;
            } else if(monthName=="Aug") {
                month = 7;
            } else if(monthName=="Sep") {
                month = 8;
            } else if(monthName=="Oct") {
                month = 9;
            } else if(monthName=="Nov") {
                month = 10;
            } else if(monthName=="Dec") {
                month = 11;
            }

            var dt = new Date();
//            dt.setDate(day);
//            dt.setYear(year);
//            dt.setMonth(month);
//            dt.setHours(hours);
//            dt.setMinutes(minutes);
//            dt.setSeconds(seconds);
            dt.setUTCDate(day);
            dt.setYear(year);
            dt.setUTCMonth(month);
            dt.setUTCHours(hours);
            dt.setUTCMinutes(minutes);
            dt.setUTCSeconds(seconds);

            return dt;
        } catch(err) {
            console.log("Error while parsing date: " + err);
            return new Date();
        }
    }

    var nonceChars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXTZabcdefghiklmnopqrstuvwxyz";

    this.generateNonce = function(length) {
        var chars = nonceChars;
        var result = "";
        for (var i = 0; i < length; ++i) {
            var rnum = Math.floor(Math.random() * chars.length);
            result += chars.substring(rnum, rnum+1);
        }
        return result;
    }

    // private String unreservedCharactersPattern = "[a-zA-Z0-9\\-\\._~]";
    // private String unreservedCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-._~";

    this.encode = function(s) {
        if (typeof(s)=="undefined" || s=="") {
            return "";
        }
        s = encodeURIComponent(s);
        // Now replace the values which encodeURIComponent doesn't do
        // encodeURIComponent ignores: - _ . ! ~ * ' ( )
        // OAuth dictates the only ones you can ignore are: - _ . ~
        // Source: http://developer.mozilla.org/en/docs/Core_JavaScript_1.5_Reference:Global_Functions:encodeURIComponent
        s = s.replace(/\!/g, "%21");
        s = s.replace(/\*/g, "%2A");
        s = s.replace(/\'/g, "%27");
        s = s.replace(/\(/g, "%28");
        s = s.replace(/\)/g, "%29");
        return s;
    }

    this.webRequest = function(isPost, url, parameters, callback) {
      var method = "GET"
      //Setup postData for signing.
      //Add the postData to the querystring.
      var postData = "";
      if (isPost)
      {
          method = "POST";
      }
      if (typeof(parameters)!=undefined && parameters!=null && parameters.length>0)
      {
          //Decode the parameters and re-encode using the oAuth UrlEncode method.
          for(var i in parameters) {
              var q = parameters[i];
              if(typeof(q[0]!="undefined" && q[0]!="" && typeof(q[1])!="undefined" && q[1]!="")) {
                  if(postData.length>0) {
                      postData += "&";
                  }
                  postData += q[0] + "=" + this.encode(q[1]);
              }
          }
          if (url.indexOf("?") > 0)
          {
              url += "&";
          }
          else
          {
              url += "?";
          }
          url += postData;
      }
      console.log("URL before: " + url);
      while(url.indexOf("?&")>0) {
        url = url.replace("?&", "?");
      }
      console.log("URL after: " + url);
      var nonce = this.generateNonce(16);
      var timeStamp = this.generateTimeStamp();


      //Generate Signature
      var obj = this.generateSignature(
              url,
              OAUTH_CONSUMER_TOKEN,
              OAUTH_CONSUMER_SECRET,
              token,
              tokenSecret,
              method,
              timeStamp,
              nonce);
      var sig = obj.signature;

      var outUrl = obj.normalizedUrl;
      var querystring = obj.normalizedRequestParameters;
      //if(token.length>0) {
         if(querystring.length>0) {
              querystring += "&";
          }
          querystring += "oauth_signature=" + this.encode(sig);
      //}
      if (querystring.length > 0)
      {
          outUrl += "?";
      }
      console.log("method < " + method + "> ---" +outUrl + querystring);
      doWebRequest(method, outUrl + querystring, callback);
  }

}
