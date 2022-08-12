                                                                                                 
const axios = require('axios').default

axios({
        method:"delete",    
        url:'https://sleepy-island-07017.herokuapp.com/users/me', 
        data : 
        {
          "API_KEY" : "T4fB44P4V3fGG44",
           "type" : "Kitchen",
            "tag" : "Aurdino",
            "value" : 100.2,
            "unit" : "C"  
        },
          headers: {Authorization: "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2Mjk2MzRhY2E4ODYwYjAwMTczMDcwZTkiLCJpYXQiOjE2NTQwOTAyMTJ9.dxz5i6XVXjaMqQMx0AMnii7cBUG-y9M0uZIxLYnYFhw" }
      })
      .then(function (response) {
        console.log(response);
      })
      .catch(function (error) {
        console.log(error);
      });