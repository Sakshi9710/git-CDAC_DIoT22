const coap = require('coap')
const req = coap.request({
    observe: true
})

req.on('response', (res) => {
    res.pipe(process.stdout)
})

req.end()