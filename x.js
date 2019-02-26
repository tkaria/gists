var q = require('q');
var input = 2;

function f1(f) {
  var deferred = q.defer();
  setTimeout((f) => {
    deferred.resolve(f + 1);
  }, 1200)
  return deferred.promise;
}

f1(input)
  .then((x) => {
    console.log('f1: ', x);
  })


function f2(f) {
  var deferred = q.defer();
  setTimeout(() => {
    deferred.resolve(f + 1);
  }, 1200)
  return deferred.promise;
}

f2(input)
  .then((x) => {
    console.log('f2: ', x)
  })

/***************************************/
var add1 = function (i) {
  return i + 1;
}
var times2 = function (i) {
  return i * 2;
}

function f3(input) {
  var deferred = q.defer();
  setTimeout(() => {
    if (input % 2 == 0) {
      // must be an odd number
      return deferred.reject('Invalid input');
    } else {
      //   return deferred.resolve(add1.bind(null, input)());
      //   return deferred.resolve(add1(input))
      //   return deferred.resolve(input + 1)
    }
  }, 1200)
  return deferred.promise;
}

f3(input)
  .then((x) => {
    console.log('f3: ', x);
  })
  .catch((err) => {
    console.log('f3: ', err);
  })


function f4(input) {
  var promise = new Promise((resolve, reject) => {
  setTimeout(() => {
    if (input % 2 == 0) {
      return resolve(input + 1);
    } else {
      return reject('Not quite ...')
    }
  }, 1200)
  })
  return promise;

}

f4(input)
  .then((x) => {
    console.log('f4: ', x);
  })
  .catch((err) => {
    console.log('f4: ', err);
  })
