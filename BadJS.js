
function foo(x) {
    switch(x) {
        case (() => { return 'abc'}):
            console.log('Made it')
            break
        case zip(x): 
            console.log('zip worked')
            break
        deault: 
            console.log('Default case')
            break
    }
}

function zip(x) {
    return 'abc'
}

foo('abc')
foo('def')
