// using a resolved promise, the 'then' block will be triggered instantly, but its handlers will be triggered asynchronously as demonstrated by the console.logs
var resolvedProm = Promise.resolve(33);

var thenProm = resolvedProm.then(function(value){
    console.log("this gets called after the end of the main stack. the value received and returned is: " + value);
    return value;
});
// instantly logging the value of thenProm
console.log(thenProm);

// using setTimeout we can postpone the execution of a function to the moment the stack is empty
setTimeout(function(){
    console.log(thenProm);
});

