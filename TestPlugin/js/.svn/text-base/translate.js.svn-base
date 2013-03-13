Qt.include("keys.js")

var resultText;
var waiting;
var waitingLabel;
var doneIndicator;
var errorIndicator;
var token;
var translatedText;

function setComponents(wait, waitLabel, done, error) {
    waiting = wait;
    waitingLabel = waitLabel;
    doneIndicator = done;
    errorIndicator = error;
}

function getAccessToken(){
    var ajaxRequest = new XMLHttpRequest();
    ajaxRequest.onreadystatechange = function(){
        if(ajaxRequest.readyState == XMLHttpRequest.DONE){
            var status = ajaxRequest.status;
            if(status!==200) {
                //console.log("HTTP status " + status);
                showError("MS API returned " + status + " " + ajaxRequest.statusText);
                //console.log("MS result: " + ajaxRequest.responseText);
                return;
            }
            //console.log("Token result: " + ajaxRequest.responseText);
            token = eval("[" + ajaxRequest.responseText + "]")[0].access_token;
            //console.log("Access token: " + token);
            translateRequest();
        }
    }
    var grant_type = encodeURIComponent("client_credentials");
    var scope = encodeURIComponent("http://api.microsofttranslator.com");
    var params =
            "client_id=" + encodeURIComponent(AZURE_CLIENT_ID) +
            "&client_secret=" + encodeURIComponent(AZURE_CLIENT_SECRET) +
            "&grant_type=" + grant_type +
            "&scope=" + scope;
    var url="https://datamarket.accesscontrol.windows.net/v2/OAuth2-13";

    //console.log("Getting token from: " + url);

    ajaxRequest.open("POST", url, true);
    ajaxRequest.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    ajaxRequest.setRequestHeader("Content-length", params.length);
    ajaxRequest.setRequestHeader("Connection", "close");
    ajaxRequest.send(params);
}

function translate(text, resultComponent) {
    showWaiting(qsTr("Translating..."))
    resultText = resultComponent;
    translatedText = text;
    getAccessToken();
}

function translateRequest() {
    var url = "http://api.microsofttranslator.com/V2/Ajax.svc/Translate" +  //"https://api.datamarket.azure.com/Data.ashx/Bing/MicrosoftTranslator/Translate?" +
    "?Text=" + encodeURIComponent(translatedText) +
    "&To=en" +
    "&appId=" + "Bearer" + " " + encodeURIComponent(token);
    //console.log("Translate API URL: " + url);
    var doc = new XMLHttpRequest();

    doc.onreadystatechange = function() {
        var shortURL = url;
        if (doc.readyState == XMLHttpRequest.HEADERS_RECEIVED) {
            var status = doc.status;
            if(status!=200) {
                if(shortURL.length>32) {
                    shortURL = shortURL.substring(0,40) + "..";
                }
                showError("Translate API returned " + status + " " + doc.statusText + " on URL " + shortURL);
                return;
            }
        } else if (doc.readyState == XMLHttpRequest.DONE) {
            var status = doc.status;
            if(status!=200) {
                console.log("HTTP status " + status);
                if(shortURL.length>40) {
                    shortURL = shortURL.substring(0,40) + "..";
                }
                showError("Translate API returned " + status + " " + doc.statusText + " on URL " + shortURL);
                return;
            }
            var data = doc.responseText;
            if(typeof(data)=="undefined") {
                data = "";
            }
            //console.log("data=" + data);
            //console.log("Callback=" + callback);
            resultText.text = data;
            showOk(data);
        }
    }
    doc.open("GET", url);
    doc.setRequestHeader("Authorization", "Bearer" + " " + encodeURIComponent(token));
    doc.send();
}

function showWaiting(reason) {
    waitingLabel.text = reason;
    waiting.state = "shown";
}

function showOk(data) {
    waiting.state = "hidden";
    doneIndicator.state = "shown";
}

function showError(data) {
    waiting.state = "hidden";
    if(typeof(data)!="undefined" && data!=null) {
        errorIndicator.reason = data;
    } else {
        errorIndicator.reason = "";
    }
    errorIndicator.state = "shown";
    console.log("ERROR: " + data);
}

function done(result) {
    resultText.text = result;
}
