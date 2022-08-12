const coap = require('coap')
const server = coap.createServer()
const randomNumber = Math.random()
const Temp = Math.random()*(10 - 60)

server.on('request', (req, res) => {
    //print req res
    
    if(req.url == '/temp')
    {
      res.end('Hello ' + Temp + '\n')
    }
    else {
      res.end("Invalid URL")
    }
  //res.end('Hello ' + console.log(randomNumber) )
})

server.listen(() => {
    console.log("CoAP is Running........")
})