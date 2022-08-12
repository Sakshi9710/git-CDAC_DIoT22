const coap = require('coap')
const server = coap.createServer()

// the default CoAP port is 5683
server.listen(() => {
  const req = coap.request('coap://localhost/Matteo') //client

  req.on('response', (res) => {
    res.pipe(process.stdout)
    res.on('end', () => {
      process.exit(0)
    })
  })

  req.end()
})