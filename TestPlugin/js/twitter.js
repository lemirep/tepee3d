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

Qt.include("xauth.js")
Qt.include("storage.js")

var Twitter = function() {

    // XAuth specific parameters
    var OAUTH_REQUEST_TOKEN_URL = "https://api.twitter.com/oauth/request_token";
    var OAUTH_ACCESS_TOKEN_URL = "https://api.twitter.com/oauth/access_token";
    var OAUTH_AUTHORIZE_URL = "https://api.twitter.com/oauth/authorize";

    // Timelines
    var HOME_TIMELINE_URL = "https://api.twitter.com/1/statuses/home_timeline.json";
    var PUBLIC_TIMELINE_URL = "https://api.twitter.com/1/statuses/public_timeline.json";
    var MENTIONS_TIMELINE_URL = "https://api.twitter.com/1/statuses/mentions.json";
    var DIRECT_TIMELINE_URL = "https://api.twitter.com/1/direct_messages.json";
    var FAVOURITES_TIMELINE_URL = "https://api.twitter.com/1/favorites.json";
    var RETWEETSME_TIMELINE_URL = "https://api.twitter.com/1/statuses/retweets_of_me.json";
    var TWEET_TIMELINE_URL = "https://api.twitter.com/1/statuses/show/@id.json";

    // Lists
    var LISTS_URL = "https://api.twitter.com/1/@user/lists.json";

    // Trends
    var TRENDS_URL = "https://api.twitter.com/1/trends/1.json";

    // Users
    var USER_URL = "https://api.twitter.com/1/users/show.json";

    // Actions
    var STATUS_UPDATE_URL = "https://api.twitter.com/1/statuses/update.json";
    var RETWEET_URL = "https://api.twitter.com/1/statuses/retweet/";
    var FAVOURITE_URL = "https://api.twitter.com/1/favorites/create/";
    var UNFAVOURITE_URL = "https://api.twitter.com/1/favorites/destroy/";
    var FOLLOW_URL = "https://api.twitter.com/1/friendships/create.json";
    var UNFOLLOW_URL = "https://api.twitter.com/1/friendships/destroy.json";
    var DIRECT_URL = "https://api.twitter.com/1/direct_messages/new.json";
    var SEARCH_URL = "https://search.twitter.com/search.json";
    var DESTROY_URL = "https://api.twitter.com/1/statuses/destroy/@id.json";

    // Searches
    var SEARCHES_URL = "https://api.twitter.com/1/saved_searches.json";
    var SAVE_SEARCH_URL = "https://api.twitter.com/1/saved_searches/create.json";
    var REMOVE_SEARCH_URL = "https://api.twitter.com/1/saved_searches/destroy/@id.json";

    // API
    var RATE_LIMIT_STATUS_URL = "https://api.twitter.com/1/account/rate_limit_status.json";

    // Time
    var TIME_TEST_URL = "https://api.twitter.com/1/help/test.json";

    // Sorry... These aren't public
    var CONSUMER_KEY = "XCL6luL7vjkEQ2s4bjRiFg";
    var CONSUMER_SECRET = "wpIYreMj0GM3Uo6GZGcHCbPlObFN3nevdURE2LZalM";

    var sig = "hmac-sha1";
    var xauth = new XAuth();
    var hasToken = false;

    var tokenDBCounter = 0;
    var token = "";
    var tokenSecret = "";


    var errorCallback;

    this.setErrorCallback = function(error) {
        errorCallback = error;
        xauth.setErrorCallback(error);
    }

    this.requestTime = function(subMethod) {
        xauth.webRequest(false, TIME_TEST_URL, "", subMethod);
    }

    this.requestToken = function() {
        xauth.setTokenAndSecret("", "");
        xauth.webRequest(true, OAUTH_REQUEST_TOKEN_URL, "", this.parseRequestToken);
    }

    this.parseRequestToken = function(response) {
        console.log("Response: " + response);
        // Sample response:
        // oauth_token=334ymkflgbVAdYqmeaFhz3uLsQDIRJF8rxjRJjQY&
        // oauth_token_secret=wjff75gyM1m6eSCmHoFfTdVIGHKebZH9zLwjyXWeR6I&
        // oauth_callback_confirmed=true
        var oauth_token = parseParameter(response, "oauth_token");
        var oauth_token_secret = parseParameter(response, "oauth_token_secret");
        setKeyValue("oauthToken", oauth_token);
        setKeyValue("oauthTokenSecret", oauth_token_secret);
        xauth.setTokenAndSecret(oauth_token, oauth_token_secret);
        hasToken = false;
        authorizeWindow.visible = true;
        authorizeWindow.load(oauth_token);
    }

    /** Login to Twitter */
    this.login = function() {
        if(hasToken) {
            console.log("login - loading home");
            loadTimeline(HOME_TIMELINE_URL, false);
            return;
        }
        console.log( "Loading tokens from DB" );
        this.resetTokenAndSecretFromDB();
    }

    this.resetToken = function() {
        hasToken = false;
        setKeyValue("oauthToken", "");
        setKeyValue("oauthTokenSecret", "");
        xauth.setTokenAndSecret("", "");
    }

    this.handleTweets = function(data) {
        doTweets(data);
    }

    this.resetTokenAndSecretFromDB = function() {
        tokenDBCounter = 0;
        getKeyValue("oauthToken", this.parseTokensFromDB);
        getKeyValue("oauthTokenSecret", this.parseTokensFromDB);
    }

    this.parseTokensFromDB = function(key, value) {
         if(key=="oauthToken") {
            token = value;
         } else {
            tokenSecret = value;
         }
         tokenDBCounter++;
         if(tokenDBCounter==2) {
             if(token.indexOf("-")>0) {
                console.log("use existing tokens");
                hasToken = true;
                xauth.setTokenAndSecret(token, tokenSecret);
                loadTimeline(HOME_TIMELINE_URL, false);
            } else {
                console.log("Getting access token");
                xauth.webRequest(false, OAUTH_ACCESS_TOKEN_URL, "", function(token) { //  this.parseTokenSync);
                     console.log("Access token data: " + token);
                     var oauthToken = parseParameter(token, "oauth_token");
                     var oauthTokenSecret = parseParameter(token, "oauth_token_secret");
                     var user_id = parseParameter(token, "user_id");
                     var screen_name = parseParameter(token, "screen_name");
                     if(typeof(oauthToken)=="undefined" || oauthToken.length==0) {
                         showLogin();
                         errorCallback("Couldn't authenticate with given username and password");
                         return;
                     }
                     hasToken = true;
                     setKeyValue("oauthToken", oauthToken);
                     setKeyValue("oauthTokenSecret", oauthTokenSecret);
                     setKeyValue("screenName", screen_name);
                     setKeyValue("userId", user_id)

                     myUsername = screen_name;
                     currentScreenName = screen_name;
                     currentUserID = user_id;

                     xauth.setTokenAndSecret(oauthToken, oauthTokenSecret);
                     loadTimeline(HOME_TIMELINE_URL, false);
                 });


            }
         }
    }

    /** Get tweets */
    this.getTweets = function(url, callback) {
        if(hasToken==true) {
            if(url.indexOf("?")>0) {
                url = url + "&include_entities=true";
            } else {
                url = url + "?include_entities=true";
            }
            console.log("Callback=" + callback);
            xauth.webRequest(false, url, "", callback);
        }
    }

    /** Get rate limit */
    this.loadRateLimit = function(callback) {
        var url = RATE_LIMIT_STATUS_URL;
        xauth.webRequest(false, url, "", callback);
    }

    /** Get lists */
    this.getLists = function(user, callback) {
        var url = LISTS_URL.replace("@user", user);
        xauth.webRequest(false, url, "", callback);
    }

    /** Get trends */
    this.loadTrends = function(callback) {
        var url = TRENDS_URL;
        xauth.webRequest(false, url, "", callback);
    }

    /** Get single tweet */
    this.getTweet = function(id, callback) {
        if(hasToken==true) {
            var url = TWEET_TIMELINE_URL.replace("@id", id);
            xauth.webRequest(false, url, "", callback);
        }
    }

    /** Get saved searches */
    this.getSavedSearches = function(callback) {
        if(hasToken==true) {
            xauth.webRequest(false, SEARCHES_URL, "", callback);
        }
    }

    /** Follow */
    this.follow = function(userid, callback) {
        var params = new Array();
        params.push(["user_id", userid]);
        xauth.webRequest(true, FOLLOW_URL, params, callback);
    }

    /** Unfollow */
    this.unfollow = function(userid, callback) {
        var params = new Array();
        params.push(["user_id", userid]);
        xauth.webRequest(true, UNFOLLOW_URL, params, callback);
    }

    /** Destroy tweet */
    this.destroy = function(tweetid, callback) {
        var url = DESTROY_URL.replace("@id", tweetid);
        xauth.webRequest(true, url, "", callback);
    }

    /** Save search */
    this.saveSearch = function(query, callback) {
        var params = new Array();
        params.push(["query", query]);
        xauth.webRequest(true, SAVE_SEARCH_URL, params, callback);
    }

    /** Remove search */
    this.removeSearch = function(searchid, callback) {
        var url =REMOVE_SEARCH_URL.replace("@id", searchid);
        xauth.webRequest(true, url, "", callback);
    }

    /** Check for new home tweets */
    this.checkNewHomeTweets = function(tweetID, callback) {
        var params = new Array();
        if(tweetID.length>0) {
            params.push(["since_id", String(tweetID)]);
        }
        params.push(["count", "1"]);
        params.push(["trim_user", "true"]);
        xauth.webRequest(false, HOME_TIMELINE_URL, params, callback);
    }

    /** Check for new mentions */
    this.checkNewMentions = function(tweetID, callback) {
        var params = new Array();
        if(tweetID.length>0) {
            params.push(["since_id", String(tweetID)]);
        }
        params.push(["count", "1"]);
        params.push(["trim_user", "true"]);
        xauth.webRequest(false, MENTIONS_TIMELINE_URL, params, callback);
    }

    /** Update status */
    this.updateStatus = function(status, replyid, lat, lon, callback) {
        var url = STATUS_UPDATE_URL + "?status=" + status;
        var params = new Array();
        params.push(["status", status]);
        if(typeof(replyid)!=undefined && replyid.length>0) {
            params.push(["in_reply_to_status_id", replyid]);
        }
        if(typeof(lat)!=undefined && lat!=null && lat.length>0) {
            params.push(["lat", lat.replace(",", ".")]);
            params.push(["long", lon.replace(",", ".")]);
            params.push(["display_coordinates", "true"]);
        }
        xauth.webRequest(true, STATUS_UPDATE_URL, params, callback);
    }

    this.searchTweets = function(url, callback) {
        var doc = new XMLHttpRequest();
        console.log("HttpRequest to " + url);
        doc.onreadystatechange = function() {
            if (doc.readyState == XMLHttpRequest.HEADERS_RECEIVED) {
            } else if (doc.readyState == XMLHttpRequest.DONE) {
                console.log("HttpRequest DONE");
                var data = doc.responseText;
                callback(data);
            }
        }
        doc.open("GET", url);
        doc.send();
    }

    /** Update status */
    this.directTweet = function(status, userid, callback) {
        var params = new Array();
        params.push(["text", status]);
        if(isNumber(userid)) {
            params.push(["user_id", userid]);
        } else {
            params.push(["screen_name", userid]);
        }
        xauth.webRequest(true, DIRECT_URL, params, callback);
    }

    /** Get user */
    this.getUser = function(userid, callback) {
        var params = new Array();
        params.push(["id", userid]);
        xauth.webRequest(false, USER_URL, params, callback);
    }

    /** Retweet */
    this.retweet = function(tweetid, callback) {
        xauth.webRequest(true, RETWEET_URL + tweetid + ".json", "", callback);
    }

    /** Mark as favourite */
    this.favourite = function(tweetid, callback) {
        xauth.webRequest(true, FAVOURITE_URL + tweetid + ".json", "", callback);
    }

    /** Mark as unfavourite */
    this.unfavourite = function(tweetid, callback) {
        xauth.webRequest(true, UNFAVOURITE_URL + tweetid + ".json", "", callback);
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

    function isNumber(n) {
      return !isNaN(parseFloat(n)) && isFinite(n);
    }


}
