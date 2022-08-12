module.exports = {
  persistence: {
    // same as http://mcollina.github.io/mosca/docs/lib/persistence/redis.js.html
    type: "mongo",
    host: "mongodb://localhost:27017/ponte"
  },
  broker: {
    // same as https://github.com/mcollina/ascoltatori#redis
    type: "mongo",
    host: "mongodb://localhost:27017/ponteBroker"
  },
  logger: {
    level: 20,
    name: "MongoPonte"
  }
};