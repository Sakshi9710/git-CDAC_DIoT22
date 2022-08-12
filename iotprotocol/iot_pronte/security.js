module.exports = {
    mqtt: {
        
        authenticate: function(client, username, password, callback) {
          let isAuthenticate = (username=='diot' && password =='diot');
          if(isAuthenticate) {
            //Authenticated clients are allowed
            client.user = "diot";
            callback(null , true);
          }
          else {
             //Authenticated clients are disconnected
            callback(null , false);
          }
        },

         authorizePublish: function(client, topic, payload, callback) {
              if(client.user == topic.split('/')[1]) {
                callback(null , true);
              }
              else {
                callback(null , false);
              }
         },
         authorizeSubscribe: function(client, topic, callback) {
          if(client.user == topic.split('/')[1]) {
            callback(null , true);
          }
          else {
            callback(null , false);
          }
         }
      }
}
 