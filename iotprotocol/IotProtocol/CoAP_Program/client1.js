const coap = require('coap')
const req = coap.request('coap://localhost/iot')

  req.on('response', (res) => {
    res.pipe(process.stdout)
    res.on('end', () => {
      process.exit(0)
    })
  })

  req.end()
