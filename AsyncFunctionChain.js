const Q = require('q')

async function foo (a, cb) {
  for (let i of a) {
    console.log('foo: ', i)
    await cb(i)
  }
}

async function bar (b) {
  console.log('bar: ', b)
  return Promise.then(() => {
    return setTimeout((b) => {
      return b + 1
    }, 1000)
  })
}

// async function main () {
//   console.log(z)
//   await foo(z, bar).then(() => { console.log('end main') })
// }

function chainPromise (array, callback) {
  let cb = current => {
    return prev => callback(current, prev)
  }
  return array.reduce((chain, obj) => chain.then(cb(obj)), Q.when(1))
}

async function processArray (array, fn) {
  let results = []
  for (let i = 0; i < array.length; i++) {
    let r = await fn(array[i])
    results.push(r)
  }
  return results // will be resolved value of promise
}

let z = []
for (let k = 0; k < 10; k++) {
  z.push(k)
}

// processArray(z, bar)
// foo(z, bar)
chainPromise(z, bar)
