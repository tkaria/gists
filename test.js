
function a(obj) {
    obj.x = 9;
}

function b(obj) {
    a(obj);
    obj.y = 2;
}

let obj = {}
console.log(obj);
//a(obj);
b(obj);

console.log(obj);
