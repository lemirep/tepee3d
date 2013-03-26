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

Qt.include("twitter.js")
Qt.include("storage.js")

var tweets;
var tweetsHome;
var tweetsMentions;

var selectedTweet;
var selectedTweetID;
var myUsername = "brillanceau";
var currentScreenName = "brillanceau";
var currentUserID = "";
var currentTweetText = "";
var isLandscape = true;
var width;

//var widgetTweetIndex = -1;
//var widgetRefreshCount = 0;
var twitter = null;
//var geolocation;
var append = false;
var listsModel;
var searchesModel;

// UI components
var waiting;
var doneIndicator;
var errorIndicator;
var profile;
var tweetListContainer;
var trends;
var loginPage;
var newHomeTweetsIndicator;
var newMentionsIndicator;
var mainMenu;

var page = 1;
var autoRefresh = false;
var autoRefreshURL = "";
var autoRefreshIndex = 0;
var lastTweetID = "";
var lastHomeTweetID = "";
var lastMentionsTweetID = "";
var searchLat = "";
var searchLon = "";
var searchQuery = "";

// Timelines
var HOME_TIMELINE_URL = "https://api.twitter.com/1/statuses/home_timeline.json";	
var PUBLIC_TIMELINE_URL = "https://api.twitter.com/1/statuses/public_timeline.json";
var MENTIONS_TIMELINE_URL = "https://api.twitter.com/1/statuses/mentions.json";
var DIRECT_TIMELINE_URL = "https://api.twitter.com/1/direct_messages.json";
var FAVOURITES_TIMELINE_URL = "https://api.twitter.com/1/favorites.json";
var RETWEETSME_TIMELINE_URL = "https://api.twitter.com/1/statuses/retweets_of_me.json";
var PUBLIC_TIMELINE = "https://api.twitter.com/1/statuses/public_timeline.json";
var RETWEETSTOME_TIMELINE_URL = "https://api.twitter.com/1/statuses/retweeted_to_me.json";
var FRIENDS_TIMELINE_URL = "https://api.twitter.com/1/statuses/friends_timeline.json";
var FRIENDS_URL = "http://api.twitter.com/1/statuses/friends.json";
var FOLLOWERS_TIMELINE_URL = "https://api.twitter.com/1/statuses/followers.json";
var USER_TIMELINE_URL = "https://api.twitter.com/1/statuses/user_timeline.json";
var SEARCH_URL = "http://search.twitter.com/search.json";
var LIST_STATUSES_URL = "https://api.twitter.com/1/:user/lists/:id/statuses.json";

function setComponents(waitingItem,
                       doneIndicatorItem,
                       profileItem,
                       tweetListContainerItem,
                       errorIndicatorItem,
                       welcomePage,
                       newHomeTweets,
                       newMentions,
                       menu) {
    waiting = waitingItem;
    doneIndicator = doneIndicatorItem;
    profile = profileItem;
    tweetListContainer = tweetListContainerItem;
    errorIndicator = errorIndicatorItem;
    loginPage = welcomePage;
    homeIcon = newHomeTweets;
    mentionsIcon = newMentions;
    mainMenu = menu;
}


function getTwitterTimeAndLogin() {
    initializeTwitterObject();
    showWaiting(qsTr("Please wait..."));
    twitter.requestTime( login );
}

function getTwitterTimeAndToken() {
    initializeTwitterObject();
    showWaiting(qsTr("Please wait..."));
    twitter.requestTime( requestToken );
}


function requestToken() {
    initializeTwitterObject();
    twitter.requestToken();
}

function setLastHomeID(lastHomeID) {
    lastHomeTweetID = lastHomeID;
}

function setLastMentionID(lastMentionID) {
    lastMentionsTweetID = lastMentionID;
}

function checkNewHomeTweets() {
    twitter.checkNewHomeTweets( lastHomeTweetID, parseNewHomeTweetsResult );
}

function parseNewHomeTweetsResult(data) {
    var homeTweets = eval("[" + data + "]")[0];
    if(homeTweets.length>0) {
        var firstTweet = homeTweets[0];
        lastHomeTweetID = firstTweet.id_str;
        console.log("New home ID: " + lastHomeTweetID);
        saveLastTweetIDs();
        homeIcon.showNewIndicator = true;
//        if(birdSound.muted==false) {
//            birdSound.play();
//        }
    }
    checkNewMentions();
}

function checkNewMentions() {
    twitter.checkNewMentions( lastMentionsTweetID, parseNewMentions );
}

function parseNewMentions(data) {
    var mentionTweets = eval("[" + data + "]")[0];
    if(mentionTweets.length>0) {
        var firstTweet = mentionTweets[0];
        lastMentionsTweetID = firstTweet.id_str;
        saveLastTweetIDs();
        mentionsIcon.showNewIndicator = true;
//        if(birdSound.muted==false) {
//            birdSound.play();
//        }
    }
}

function saveLastTweetIDs() {
    setKeyValue("lastHomeID", lastHomeTweetID);
    setKeyValue("lastMentionID", lastMentionsTweetID);
}

function showLogin() {
    getTwitterTimeAndToken();
    welcomePage.visible = true;
    authorizeWindow.visible = true;
}

function setSelectedTweet(id) {
    selectedTweetID = id;
}

function setSelectedUser(id) {
    currentUserID = id;
}

function loadMentions() {
    loadTimeline(MENTIONS_TIMELINE_URL, false);
}

function loadRateLimit() {
    twitter.loadRateLimit(parseRateLimit);
}

function parseRateLimit(data) {
/*  {"hourly_limit":150,
    "reset_time_in_seconds":1297626293,
    "reset_time":"Sun Feb 13 19:44:53 +0000 2011",
    "remaining_hits":150}
*/
    var rate = eval("[" + data + "]")[0];
    var resetDate = new Date();
    resetDate.setTime(rate.reset_time_in_seconds*1000);
    var hours = String(resetDate.getHours());
    if(hours.length==1) {
        hours = "0" + hours;
    }
    var minutes = String(resetDate.getMinutes());
    if(minutes.length==1) {
        minutes = "0" + minutes;
    }
    mainMenu.apiStatus = "API remaining hits: " + rate.remaining_hits + " Hourly limit: " + rate.hourly_limit + " reset at " + hours + ":" + minutes;
}

function loadHome() {
    loadTimeline(HOME_TIMELINE_URL, false);
}

function loadDirectMessages() {
    loadTimeline(DIRECT_TIMELINE_URL, false);
}

function loadFollowers() {
    loadTimeline(FOLLOWERS_TIMELINE_URL, false);
}

function loadRetweets() {
    loadTimeline(RETWEETSME_TIMELINE_URL, false);
}

function loadFavourites() {
    loadTimeline(FAVOURITES_TIMELINE_URL, false);
}

function loadCurrentUserTweets() {
    var url = USER_TIMELINE_URL + "?user_id=" + currentUserID;
    loadTimeline(url, false);
}

function loadUserTweets() {
    var url = USER_TIMELINE_URL;
    loadTimeline(url, false);
}

function loadFriends() {
    loadTimeline(FRIENDS_URL, false);
}

function loadReplyText(replyID, replyText) {
    twitter.getTweet(replyID, parseSingleReply);
}

function parseSingleReply(data) {
    var tweet = eval("[" + data + "]")[0];
    replyTextContainer.replyText = tweet.user.screen_name + ": " + tweet.text;
}

function loadList(listID) {
    var url = LIST_STATUSES_URL.replace(":user", myUsername).replace(":id", listID);
    loadTimeline(url, false);
}

function follow() {
    //waiting.state = "shown";
    twitter.follow(currentUserID, okCallback);
}

function unfollow() {
    //waiting.state = "shown";
    twitter.unfollow(currentUserID, okCallback);
}

function loadTrends(trendsModel) {
    trends = trendsModel;
    //waiting.state = "shown";
    twitter.loadTrends(parseTrends);
}

function parseTrends(results) {
    var lists = eval("[" + results + "]");
    lists = lists[0];
    lists = lists[0];
    lists = lists.trends;

    trends.clear();
    for(var i in lists) {
        var list = lists[i];
        trends.append({
            "name": list.name
        });
    }
    //waiting.state = "hidden";
}

/** Parse parameter from given URL */
function parseParameter(url, parameter) {
    var parameterIndex = url.indexOf(parameter);
    if(parameterIndex<0) {
        // We didn't find parameter
        return "";
    }
    var equalIndex = url.indexOf("=", parameterIndex);
    if(equalIndex<0) {
        return "";
    }
    var value = "";
    var nextIndex = url.indexOf("&", equalIndex+1);
    if(nextIndex<0) {
        value = url.substring(equalIndex+1);
    } else {
        value = url.substring(equalIndex+1, nextIndex);
    }
    return value;
}

function doSearch(search, lat, lon) {
    //waiting.state = "shown";
    var query = search;
    var url = SEARCH_URL + "?q=" + escape(query);
    if(lat!=null && lat.length>0 && lat!="NaN") {
        url += "&geocode=" + lat + "," + lon + ",20km";
    }
    autoRefreshURL = url;
    twitter.searchTweets(url, parseSearchResults);
}

function parseSearchResults(searchResults) {
    try {
        var data = eval("[" + searchResults + "]");
        append = false;
        autoRefresh = false;
        doTweets(data[0].results);
    }catch(err) {
        errorCallback("Something went wrong with your search...");
    }
}

function loadSavedSearches(searches) {
    //waiting.state = "shown";
    searchesModel = searches;
    twitter.getSavedSearches(parseSavedSearches);
}

function parseSavedSearches(results) {
    results = eval("[" + results + "]")[0];
    var searchCount = 0;
    searchesModel.clear();
    for(var i in results) {
        var saved_search = results[i];
        searchesModel.append({
            "name": saved_search.query,
            "searchid": saved_search.id
        });
    }
    //waiting.state = "hidden";
}

function saveSearch(query, lat, lon) {
    searchLat = lat;
    searchLon = lon;
    searchQuery = query;
    twitter.saveSearch(query, parseSaveSearch);
}

function parseSaveSearch(data) {
    doSearch(searchQuery, searchLat, searchLon);
}

function removeSearch(searchid) {
    showWaiting(qsTr("Removing search"));
    twitter.removeSearch(searchid, parseRemoveSearch);
}

function parseRemoveSearch(data) {
    //waiting.state = "hidden";
    doneIndicator.state = "shown";
}

function loadAndShowLists(listModel) {
    listsModel = listModel;
    //waiting.state = "shown";
    twitter.getLists(myUsername, parseLists);
}

function parseLists(results) {
    var lists = eval("[" + results + "]")[0].lists;
    listsModel.clear();
    for(var i in lists) {
        var list = lists[i];
        listsModel.append({
                          "slug": list.slug
        });
    }
    //waiting.state = "hidden";
}

function loadSingleTweet(tweetID) {
    //waiting.state = "shown";
    twitter.getTweet( tweetID, parseSingleTweet );
}

function parseSingleTweet(tweet) {
    console.log("Tweet: " + tweet);
    var tweets = eval("[" + tweet + "]");
    doTweets(tweets, false);
}

function fillProfile() {
    //waiting.state = "shown";
    twitter.getUser(currentUserID, parseProfile);
}

function parseProfile(userData) {
    var user = eval("[" + userData + "]");
    user = user[0];
    var name = "";
    var profileImage = "";
    var userLocation = "";
    var statusCount = "-";
    var followerCount = "-";
    var screenName = "";
    var userID = "";
    var url = "";
    var description = "";
    try{
        userID = String(user.id);
        profile.userID = userID;
        profile.description = user.description;
        profile.username = user.screen_name;
        profile.profileImageURL = user.profile_image_url;
        profile.userLocation = user.location;
        profile.tweetCount = user.statuses_count;
        profile.followingCount = user.friends_count;
        profile.followersCount = user.followers_count;
        if(user.following) {
            profile.isFollowing = true;
        } else {
            profile.isFollowing = false;
        }
        currentScreenName = screenName;
        currentUserID = String(userID);
    } catch(err) {
        errorCallback("Can't parse profile because " + err);
    }
    //waiting.state = "hidden";
}

function favourite(tweetID) {
    //waiting.state = "shown";
    twitter.favourite( tweetID, okCallback);
}

function unfavourite(tweetID) {
    //waiting.state = "shown";
    twitter.unfavourite( tweetID, okCallback);
}

function destroy(tweetID) {
    //waiting.state = "shown";
    twitter.destroy( tweetID, okCallback );
    for(var i=0; i<tweetsModel.count; i++) {
        tweetsModel.remove(i);
        break;
    }
}

function instantretweet(tweetID) {
    //waiting.state = "shown";
    twitter.retweet( tweetID, okCallback );
}

function initializeTwitterObject() {
    if(typeof(twitter)=="undefined" || twitter==null) {
        twitter = new Twitter();
        twitter.setErrorCallback( errorCallback );
    }
}

function login(dummy) {
    initializeTwitterObject();
    showWaiting("Authenticating...");
    twitter.login();
}

function resetTokens() {
    if(typeof(twitter)!="undefined" && twitter!=null) {
        twitter.resetToken();
    }
}

function autoFresh() {
    autoRefresh = true;
    var url = autoRefreshURL;
    url = removeParameter(url, "since_id");
    if(typeof(lastTweetID)!="undefined") {
        if(url.indexOf("?")>0 && lastTweetID.length>0) {
            url += "&since_id=" + String(lastTweetID);
        } else {
            url += "?since_id=" + String(lastTweetID);
        }
    }
    loadTimeline(url,false);
}

function removeParameter(url, parameter) {
    var indexOfParameterStart = url.indexOf(parameter + "=");
    if(indexOfParameterStart<0) {
        return url;
    }
    var indexOfParameterEnd = url.indexOf("&", indexOfParameterStart+1);
    if(indexOfParameterEnd>0) {
        url = url.substring(0,indexOfParameterStart);
        url += url.substring(indexOfParameterEnd);
    } else {
        url = url.substring(0,indexOfParameterStart);
    }
    return url;
}

function removeHTMLTags(input) {
    return input.replace(/<\/?[^>]+(>|$)/g, "");
}

function showWaiting(reason) {

   // waitingText.text = reason;
    //waiting.state = "shown";
}

function loadTimeline(timelineUrl, appendFully) {
    console.log("My username is " + myUsername);
    showWaiting(qsTr("Loading tweets..."));
    append = appendFully;
    if(append==false) {
        autoRefreshURL = timelineUrl;
        page = 1;
        if(autoRefresh==false) {
            lastTweetID = "";
            if(timelineUrl.indexOf(HOME_TIMELINE_URL)>-1) {
                homeIcon.showNewIndicator = false;
            } else if(timelineUrl.indexOf(MENTIONS_TIMELINE_URL)>-1) {
                mentionsIcon.showNewIndicator = false;
            }
        }
    }
    twitter.getTweets(timelineUrl, parseRealTweets);
}

function parseRealTweets(tweets) {
    try {
        authorizeWindow.visible = false;
        var realTweets = tweets;
        if(typeof(realTweets)==undefined) {
            return;
        }
        if(realTweets!=null && realTweets.results!=null) {
            // Get search results
            realTweets = realTweets.results;
        }

        // Launch
        if(autoRefresh==true) {
            if(autoRefreshURL.indexOf(HOME_TIMELINE_URL)>-1) {
                checkNewMentions();
            } else {
                checkNewHomeTweets();
            }
        }
        if(realTweets.length>0 &&
                (
                    (typeof(tweets)!=undefined && tweets.length>0 && tweets[0].id!=realTweets[0].id) ||
                    (typeof(tweets)==undefined||tweets!=null||tweets.length==0)
                    )) {
            if(realTweets.indexOf("[")!=0) {
                realTweets = "[" + realTweets + "]";
                realTweets = eval(realTweets);
                realTweets = realTweets[0];
            } else {
                realTweets = eval(realTweets);
            }
            doTweets(realTweets);
        }
    }catch(exp) {
        errorCallback("Tried hard but couldn't parse Tweets because of " + exp);
    }

}

function loadNextPage() {
    //tweetsModel.remove(tweetsModel.count-1);
    autoRefreshURL = removeParameter(autoRefreshURL, "page");
    page = page+1;
    var newUrl = "";
    if(autoRefreshURL.indexOf("?")>0) {
        newUrl = autoRefreshURL + "&page=" + page;
    } else {
        newUrl = autoRefreshURL + "?page=" + page;
    }
    newUrl = removeParameter(newUrl, "since_id");
    loadTimeline(newUrl,true);
}

function updateStatus(status, replyID, isDirectTo, lat, lon) {
    //waiting.state = "shown";
    if(isDirectTo!=null && typeof(isDirectTo)!=undefined && isDirectTo.length>0) {
        twitter.directTweet(status, isDirectTo, okCallback);
    } else {
        twitter.updateStatus(status, replyID, lat, lon, okCallback);
    }
}

function convertTweetToModel(tweet) {
    try {
        var tweetDate = parseTwitterDate(tweet.created_at);
        var isoDate = tweetDate.toString("yyyy-MM-ddThh:mm:ssZ");
        var status = "";
        var inReplyTo = "";
        var inReplyToID = "";
        var retweeted = "";
        var source = tweet.source;
        var isFavourite = false;
        var tweetID = tweet.id_str;
        if(lastTweetID.length==0 && typeof(tweetID)!="undefined" && tweetID!=null) {
            lastTweetID = tweetID;
        }
        if(tweet.text!=null) {
            status = tweet.text;
            inReplyTo = tweet.in_reply_to_screen_name;
            inReplyToID = tweet.in_reply_to_status_id_str;
            isFavourite = tweet.favorited;
            if(tweet.retweeted_status!=null) {
                retweeted = " retweeted " + tweet.retweeted_status.user.screen_name;
            }
        } else {
            // Friends
            status = tweet.status.text;
            inReplyTo = tweet.status.in_reply_to_screen_name;
            inReplyToID = tweet.status.in_reply_to_status_id;
            tweetDate = parseTwitterDate(tweet.status.created_at);
        }
        var replyBlock = "";
        if(inReplyTo!=null && typeof(inReplyTo)!=undefined && inReplyTo.length>0) {
            replyBlock = " " + qsTr("in reply to") + " @" + inReplyTo;
        }
        var profileImageUrl = "";
        var userName = "";
        if(tweet.user!=null && typeof(tweet.user)!=undefined) {
            // Home, Mentions, Favourites etc.
            profileImageUrl = tweet.user.profile_image_url;
            userName = tweet.user.screen_name;
        } else if(tweet.sender!=null && typeof(tweet.sender)!=undefined) {
            // Direct Tweets
            profileImageUrl = tweet.sender.profile_image_url;
            userName = tweet.sender.screen_name;
        } else if(tweet.name!=null) {
            // Friends
            userName = tweet.screen_name;
            profileImageUrl = tweet.profile_image_url;
        } else if(tweet.from_user!=null){
            // Search
            userName = tweet.from_user;
            profileImageUrl = tweet.profile_image_url;
        }
        var twtDate = ""; // prettyDate(tweetDate);
        if(source!=null && typeof(source)!=undefined) {
            console.log("Source1: " + source);
            while(source.indexOf("&lt;")>=0 ||
                  source.indexOf("&gt;")>=0 ||
                  source.indexOf("&quot;")>=0) {
                source = source.replace("&quot;", "\"");
                source = source.replace("&lt;", "<");
                source = source.replace("&gt;", ">");
            }
            source = source.replace(/<\/?[^>]+(>|$)/g, "");
            console.log("Source2: " + source);
        } else {
            source = "";
        }
        if(inReplyToID==null) {
            inReplyToID = "";
        }

        var isMine = false;
        if(userName == myUsername) {
            isMine = true;
        }
        var isForMe = false;
        if(status.indexOf(myUsername)>=0) {
            isForMe = true;
        }

        var previewImageHTML = "";
        var displayableStatus = status;

        // Parse entities
        var urls = new Array();
        if(tweet.entities!=null && tweet.entities.urls!=null) {
            for(var i in tweet.entities.urls) {
                var urlEntity = tweet.entities.urls[i];
                var url = urlEntity.url;
                var expandedUrl = urlEntity.expanded_url;
                urls.push(expandedUrl);
                var dispUrl = urlEntity.display_url;
                /*if(dispUrl.length>32) {
                    dispUrl = dispUrl.substring(0,30) + "..";
                }
                dispUrl = dispUrl.replace("https://", "");
                dispUrl = dispUrl.replace("http://", "");
                dispUrl = dispUrl.replace("www.", "");*/
                dispUrl = "<i>" + dispUrl + "</i>";
                displayableStatus = status.replace(url,dispUrl);
                status = status.replace(url, expandedUrl);
            }
            for(var j in tweet.entities.media) {
                var mediaEntity = tweet.entities.media[j];
                console.log("Parsing media");
                if(mediaEntity.media_url!=null) {
                    previewImageHTML = mediaEntity.media_url;
                    console.log("Preview image URL: " + previewImageHTML);
                }
            }
        }
        if(previewImageHTML===null || previewImageHTML.length===0) {
            previewImageHTML = createPreviewImageHTML(status);
        }

        var tweetObject = {
            "tweetID": tweetID,
            "userName": userName,
            "status": status,
            "displayableStatus": displayableStatus,
            "profileImageURL": profileImageUrl,
            "tweetDate": twtDate,
            "tweetDateStamp": tweetDate,
            "replyBlock": replyBlock,
            "replyID": String(inReplyToID),
            "source": source,
            "imagePreviewURL": previewImageHTML,
            "isFavourite": isFavourite,
            "isMine": isMine,
            "isForMe": isForMe
        };
        if( autoRefresh==true ) {
            tweetsModel.insert(autoRefreshIndex, tweetObject);
            autoRefreshIndex++;
        } else {
            var k;
            for(k=0; k<tweetsModel.count; k++) {
                var twt = tweetsModel.get(k);
                console.log("Old tweet " + twt.tweetID + " vs. new tweet " + tweetObject.tweetID);
                if(twt.status===tweetObject.status) {
                    return;
                }
            }
            tweetsModel.append(tweetObject);
        }
    } catch(err) {
        console.log("Err: " + err);
    }
}


function okCallback(data) {
    //waiting.state = "hidden";
    doneIndicator.state = "shown";
}

function errorCallback(data) {
    //waiting.state = "hidden";
    if(typeof(data)!="undefined" && data!=null) {
        errorIndicator.reason = data;
        if(data.indexOf("Unauthorized")>0) {
            //showLogin();
            welcomePage.showButtons = true;
        }
    } else {
        errorIndicator.reason = "";
    }
    errorIndicator.state = "shown";
    console.log("ERROR: " + data);
}

function GetHashTags(text, model, tweetID) {
    console.log("Creating hashtag models. TweetID " + tweetID);
    var rePattern = new RegExp("(#(\\w+))", "gi");
    var arrMatch = null;
    var matchCount = 0;
    while(arrMatch = rePattern.exec(text)) {
        matchCount++;
        model.append({
            "actionName": arrMatch[0],
            "tweetID": tweetID
        });
    }
    rePattern = new RegExp("(@(\\w+))", "gi");
    while(arrMatch = rePattern.exec(text)) {
        matchCount++;
        model.append({
            "actionName": arrMatch[0],
            "tweetID": tweetID
        });
    }
    rePattern = new RegExp("(https?|ftp|file):\/\/[-A-Z0-9+&@#\/%?=~_|!:,.;]*[-A-Z0-9+&@#\/%=~_|]", "gi");
    while(arrMatch = rePattern.exec(text)) {
        matchCount+=2; // Link + "Read it later..." link
        model.append({
            "actionName": arrMatch[0],
            "tweetID": tweetID
        });
        // Read it later link
        var title = text.replace(arrMatch[0], "");
        model.append({
            "actionName": "https://readitlaterlist.com/" + arrMatch[0],
            "tweetID": tweetID
        });
    }
    return matchCount;
}

function parseUsernames(text) {
    var result = "";
    var rePattern = new RegExp("(@(\\w+))", "gi");
    var arrMatch = null;
    while(arrMatch = rePattern.exec(text)) {
        if(arrMatch[0]!=("@" + myUsername)) {
            result += arrMatch[0] + " ";
        }
    }
    return result;
}

function doTweets(data) {
    if(typeof(data.results)!=undefined && data.results!=null) {
        data = data.results;
    }

    var moreIndex = -1;
    console.log("append=" + append + " autoFresh=" + autoRefresh);
    if(append==false && autoRefresh==false) {
        tweetsModel.clear();
    } else {
        moreIndex = tweetsModel.count - 1;
        if(append && moreIndex>=0) {
            tweetsModel.remove(moreIndex);
        }
    }

    if(data.length==0) {
        //waiting.state = "hidden";
        autoRefresh = false;
        return;
    }

    lastTweetID = "";
    autoRefreshIndex = 0;
    for(var x in data) {
        var tweet = data[x];
        convertTweetToModel(tweet);
    }

    // Check for indicators
    if(autoRefresh==true) {
        if(autoRefreshURL.indexOf(HOME_TIMELINE_URL)>-1) {
            homeIcon.showNewIndicator = true;
            lastHomeTweetID = lastTweetID;
        } else if(autoRefreshURL.indexOf(MENTIONS_TIMELINE_URL)>-1) {
            mentionsIcon.showNewIndicator = true;
            lastMentionsTweetID = lastTweetID;
        }
        saveLastTweetIDs();
    }

    formatTimeStamps();
    reduceModelSize();
    if( tweetsModel.count>1 &&
            tweetsModel.count<100 &&
            tweetsModel.get(tweetsModel.count-1).status.indexOf("Load more")<0) {
        tweetsModel.append({
            "tweetID": "",
            "userName": "",
            "status": "Load more...<br/><br/><br/><br/>",
            "displayableStatus": qsTr("Load more...") + "<br/><br/><br/><br/>",
            "profileImageURL": "",
            "tweetDate": "",
            "replyBlock": "",
            "replyID": "",
            "source": "",
            "imagePreviewURL": "",
            "isFavourite": false});
    }

    tweetListContainer.state = "shown";
    tweetListContainer.visible = true;
    loginPage.visible = false;
    //waiting.state = "hidden";
    autoRefresh = false;
}

function formatTimeStamps() {
    for(var i=0; i<tweetsModel.count; i++) {
        var tweet = tweetsModel.get(i);
        tweet.tweetDate = prettyDate(tweet.tweetDateStamp);
        tweetsModel.set(i, tweet);
    }
}

function reduceModelSize() {
    while(tweetsModel.count>100) {
        tweetsModel.remove( tweetsModel.count-1 );
    }
}

function createPreviewImageHTML(text) {
    var html = "";
    var url = "";
    var imgSize = "160";
    var linkStart = 0;
    var linkEnd = 0;
    if(isLandscape==false) {
        imgSize = "240";
    }
    if(text.indexOf("http://twitpic.com/")>=0) {
        var imageID = text.substr(text.indexOf("http://twitpic.com/")+19, 6);
        url = "http://twitpic.com/show/thumb/" + imageID;
    } else if(text.indexOf("https://twitpic.com/")>=0) {
            var imageID = text.substr(text.indexOf("https://twitpic.com/")+20, 6);
            url = "https://twitpic.com/show/thumb/" + imageID;
    } else if(text.indexOf("http://yfrog.com/")>=0) {
        linkStart = text.indexOf("http://yfrog.com/");
        linkEnd = text.indexOf(" ", linkStart);
        var yfrogURL = "";
        if(linkEnd<0) {
            yfrogURL = text.substring(linkStart);
        } else {
            yfrogURL = text.substring(linkStart,linkEnd);
        }
        url = yfrogURL + ".th.jpg";
    } else if(text.indexOf("instagr.am")>=0 || text.indexOf("instagram.com")>=0) {
        linkStart = text.indexOf("http://insta");
        linkEnd = text.indexOf(" ", linkStart);
        var instagramURL = "";
        if(linkEnd<0) {
            instagramURL = text.substring(linkStart);
        } else {
            instagramURL = text.substring(linkStart,linkEnd);
        }
        url = instagramURL + "/media/?t=t";
    }
    return url;
}

function doFailure(data) {
    //waiting.state = "hidden";
    if(typeof(data)!="undefined" && data!=null) {
        errorIndicator.reason = data;
    } else {
        errorIndicator.reason = "";
    }
    errorIndicator.state = "shown";
    console.log("ERROR: " + data);
}

// Takes an ISO time and returns a string representing how
// long ago the date represents.
// 2008-01-28T20:24:17Z
function prettyDate(date){
    try {
        if(typeof(date)=="undefined") {
            return qsTr("some time ago");
        }
        var diff = (((new Date()).getTime() - date.getTime()) / 1000);
        var day_diff = Math.floor(diff / 86400);

        if ( isNaN(day_diff) || day_diff >= 31 ) {
            return qsTr("some time ago");
        } else if (day_diff < 0) {
            console.log("day_diff: " + day_diff);
            return qsTr("just now");
        }

        return day_diff == 0 && (
                    diff < 60 && qsTr("just now") ||
                    diff < 120 && qsTr("1 minute ago") ||
                    diff < 3600 && Math.floor( diff / 60 ) + " " + qsTr("min ago") ||
                    diff < 7200 && qsTr("1 hour ago") ||
                    diff < 86400 && Math.floor( diff / 3600 ) + " " + qsTr("hours ago")) ||
                day_diff == 1 && qsTr("Yesterday") ||
                day_diff < 7 && day_diff + " " + qsTr("days ago") ||
                day_diff < 31 && Math.ceil( day_diff / 7 ) + " " + qsTr("weeks ago") ||
                day_diff >= 31 && Math.ceil( day_diff / 30 ) + " " + qsTr("months ago");
    } catch(err) {
        console.log("Error: " + err);
        return qsTr("some time ago");
    }
}

// pass in the 'created_at' string returned from twitter //
// stamp arrives formatted as Tue Apr 07 22:52:51 +0000 2009 //
function parseTwitterDate(stamp)
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

        if(stamp.indexOf(",")>0) {
            // Search results
            // Date stamp in format: Sun, 09 Jan 2011 18:15:30 +0000
            // compared to           Tue Apr 07 22:52:51 +0000 2009
            dayName = parts[0];
            monthName = parts[2];
            day = parseInt(parts[1], 10);
            time = parts[4].split(":");
            hours = parseInt(time[0], 10);
            minutes = parseInt(time[1], 10);
            seconds = parseInt(time[2], 10);
            offset = parts[5];
            year = parseInt(parts[3], 10);
        } else {
            dayName = parts[0];
            monthName = parts[1];
            day = parseInt(parts[2], 10);
            time = parts[3].split(":");
            hours = parseInt(time[0], 10);
            minutes = parseInt(time[1], 10);
            seconds = parseInt(time[2], 10);
            offset = parts[4];
            year = parseInt(parts[5], 10);
        }

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
