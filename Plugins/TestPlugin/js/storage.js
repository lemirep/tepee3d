var map = new Object();
/** Set value to storage */
function setKeyValue(key, value) {
    console.log("In  setKeyValue - set value <" + value + "> for key <" + key + ">");
    map[key] = value;
}

/** Get value from storage */
function getKeyValue(key, callback) {

    map["oauthToken"] = "317385464-FcPKqOIc0zZm7b8tHeDOVlX0m0WU9ru7K6yKBQPV";
    map["oauthTokenSecret"] = "ewCRwatHBEdBLIhZnth3IWoxddADI6R3c6sr3mUZag";
     console.log("In  getKeyValue - get value <" + map[key] + "> for key <" + key + ">");
    if (map[key] == "")
        callback(key,"");
    else
        callback(key, map[key])
}
