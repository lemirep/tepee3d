.import QtQuick.LocalStorage 2.0 as Sql

/** Set value to storage */
function setKeyValue(key, value) {
    var db = Sql.openDatabase("TestPlugin", "1.0", "KeyValueStorage", 10);
    db.transaction(function(tx) {
       tx.executeSql('CREATE TABLE IF NOT EXISTS ' +
                     'KeyValueStorage(keyName TEXT, textValue TEXT)');
       var rs = tx.executeSql('SELECT keyName FROM KeyValueStorage WHERE keyName = "' + key + '"');
       var sql = "";
       var data = [ value, key ];
       if(rs.rows.length>0) {
           sql = "UPDATE KeyValueStorage SET textValue = '" + value + "' WHERE keyName = '" + key + "'";
       } else {
           sql = "INSERT INTO KeyValueStorage(textValue, keyName) VALUES ('" + value + "','" + key + "')";
       }
       tx.executeSql(sql);
    });
}

/** Get value from storage */
function getKeyValue(key, callback) {
    var db = Sql.openDatabaseSync("TestPlugin", "1.0", "KeyValueStorage", 10);
    db.transaction(function(tx) {
       tx.executeSql('CREATE TABLE IF NOT EXISTS KeyValueStorage(keyName TEXT, textValue TEXT)');
       var result = "";
       var rs = tx.executeSql('SELECT textValue FROM KeyValueStorage WHERE keyName = "' + key + '"');
       for (var i = 0; i < rs.rows.length; i++) {
           result = rs.rows.item(i).textValue;
           callback(key,result);
           return;
       }
       if(rs.rows.length==0) {
           callback(key,"");
       }
    });
}
