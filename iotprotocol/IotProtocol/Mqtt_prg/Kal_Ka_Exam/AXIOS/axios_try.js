/*
1. POST the sensor data using axios
2. Fetch the sensor data (GET)
*/

const axios = require('axios').default;

// url = "https://sleepy-island-07017.herokuapp.com/sensor"

// axios.post(url, {
//     "API_KEY" : "sMvSD06MD0eSM00",
//     "type" : "Kitchen",
//     "tag" : "Arduino",
//     "value" : 999,
//     "unit": "C"
//   })
//   .then(function (response) {
//     console.log(response);
//   })
//   .catch(function (error) {
//     console.log(error);
//   });

// axios({
//     method: "post",
//     url : "https://sleepy-island-07017.herokuapp.com/sensor",
//     data : {
//         "API_KEY" : "sMvSD06MD0eSM00",
//         "type" : "Kitchen",
//         "tag" : "Arduino",
//         "value" : 999,
//         "unit": "C"
//     },
//     headers: {
//         Authorization : "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2Mjk2MzQ1YWE4ODYwYjAwMTczMDcwZDYiLCJpYXQiOjE2NTQwOTQ0NDF9.tJwtAnU3tuKz66YZ_tZLEVh9Mz3zHTtUU3ewfI1mAYw"
//       }
// })
// .then(function (response) {
//     console.log(response);
// })
// .catch(function (error) {
//     console.log(error);
// });


// axios({
//     method: "get",
//     url : "https://sleepy-island-07017.herokuapp.com/sensor",
//     headers: {
//         Authorization : "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2Mjk2MzQ1YWE4ODYwYjAwMTczMDcwZDYiLCJpYXQiOjE2NTQwOTQ0NDF9.tJwtAnU3tuKz66YZ_tZLEVh9Mz3zHTtUU3ewfI1mAYw"
//     }
// })
// .then(function (response) {
//     console.log(response.data);
// })
// .catch(function (error) {
//     console.log(error);
// });


///DELETE
// axios({
//     method : "DELETE",
//     url : "https://sleepy-island-07017.herokuapp.com/sensor",
//     headers : {
//         Authorization : "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2Mjk2MzQ1YWE4ODYwYjAwMTczMDcwZDYiLCJpYXQiOjE2NTQwOTQ0NDF9.tJwtAnU3tuKz66YZ_tZLEVh9Mz3zHTtUU3ewfI1mAYw"
//     }
// })


//GET https://api.thingspeak.com/update?api_key=RP47QNBBVW9H6NWK&field1=0


// axios({
//     method : "post",
//     url : "https://api.thingspeak.com/update?api_key=RP47QNBBVW9H6NWK&field1=0",
//     params : {
//         "api_key" : "RP47QNBBVW9H6NWK",
//         "field1" : 120
//     }
// })
// .then(function(response){
//     console.log(response.status);
// })
// .catch(function(error){
//     console.log(error.response);
// })



axios({
    method : "get",
    url : "https://api.thingspeak.com/channels/1756812/feeds.json?api_key=CFGMXY7YB74I8ALH&results=2",
    params : {
        "api_key" : "CFGMXY7YB74I8ALH"
        //"field1" : 120
    }
})
.then(function(response){
    console.log(response.data);
})
.catch(function(error){
    console.log(error.response);
})