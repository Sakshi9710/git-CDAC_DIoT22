const coap = require('coap')
const server = coap.createServer()

server.on('request', (req, res) => {
    //print req res
    //console.log(req);
    console.log(req.url);
  res.end('Hello ' + req.url.split('/')[1] + '\n')
})

server.listen(() => {
    console.log("CoAP is Running........")
})