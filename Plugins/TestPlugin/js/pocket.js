.pragma library
Qt.include("keys.js")

var waiting;
var doneIndicator;
var errorIndicator;
var waitTextLabel;

function setComponents(wait, waitText, done, error) {
    waiting = wait;
    waitTextLabel = waitText;
    doneIndicator = done;
    errorIndicator = error;
}

function addLinkToPocket(articleUrl, pocketUsername, pocketPassword, tweetID) {
    showWaiting(qsTr("Adding to your Pocket..."))
    articleUrl = articleUrl.replace("https://readitlaterlist.com/", "");
    var url = "https://readitlaterlist.com/v2/add?" +
            "apikey=" + POCKET_API_KEY +
            "&username=" + encodeURIComponent(pocketUsername) +
            "&password=" + encodeURIComponent(pocketPassword) +
            "&url=" + encodeURIComponent(articleUrl) +
            "&ref_id=" + encodeURIComponent(tweetID);
    console.log("Pocket API URL: " + url);
    var doc = new XMLHttpRequest();
    doc.onreadystatechange = function() {
        var shortURL = url;
        if (doc.readyState == XMLHttpRequest.HEADERS_RECEIVED) {
            var status = doc.status;
            if(status!=200) {
                if(shortURL.length>32) {
                    shortURL = shortURL.substring(0,40) + "..";
                }
                showError("Pocket API returned " + status + " " + doc.statusText + " on URL " + shortURL);
                return;
            }
        } else if (doc.readyState == XMLHttpRequest.DONE) {
            var status = doc.status;
            if(status!=200) {
                console.log("HTTP status " + status);
                if(shortURL.length>40) {
                    shortURL = shortURL.substring(0,40) + "..";
                }
                showError("Pocket API returned " + status + " " + doc.statusText + " on URL " + shortURL);
                return;
            }
            var data = doc.responseText;
            if(typeof(data)=="undefined") {
                data = "";
            }
            //console.log("data=" + data);
            //console.log("Callback=" + callback);
            showOk(data);
        }
    }
    doc.open("GET", url);
    doc.send();
}

function showWaiting(reason) {
    waitTextLabel.text = reason;
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
