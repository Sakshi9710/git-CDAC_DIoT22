                                                                                                 
const axios = require('axios').default
axios({
        method:"post",    
        url:'https://connect.cloud.kaaiot.com:443/kp1/calkt78n7nk35lghoqs0-vo3/dcx/lHHq9Zs6qu/json', 
        data:{
            "temp" : 24.5,
           
        }
        })

      .then(function (response) {
        console.log(response.status);
      })
      .catch(function (error) {
        console.log(error);
      });