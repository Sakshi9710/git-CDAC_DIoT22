const axios = require('axios').default
//url2:"https://api.thingspeak.com/channels/1756830/fields/1.json?api_key=92TD4TQASW447Z28&results=2"                                                                                                 

axios({
        method:"get",    
        url:"https://api.thingspeak.com/channels/1756830/fields/1.json?api_key=92TD4TQASW447Z28&results=2", 
        params:{ "api_key":"92TD4TQASW447Z28",
    
        },

        })
      .then(function (response) {
        console.log(response.data);
      })
      .catch(function (error) {
        console.log(error);
      });