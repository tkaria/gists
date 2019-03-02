const mailgunAPIKey = "YOUR MAILGUN API KEY";
const mailgunPublicAPIKey = "pubkey-a8bb96c0a15d36ba27adb8bb6cef7bad";
const mailgunDomain = "sandboxe6a4853ea2494733ac84ffd27c81fc0a.mailgun.org"
let mg = require('mailgun-js')({ apiKey: mailgunAPIKey, domain: mailgunDomain })

async function sendMail() {

    let data = {
        from: "timir@ventureiq.nl",
        to: "timir@ventureiq.nl",
        subject: "Hello",
        text: "Foobar",
        html: "<h1>Foobar?</h1>"
    }
    return new Promise(function (resolve, reject) {
        mg.messages().send(data,
            function (error, body) {
                console.log("3");
                if (error) {
                    console.log("Error: ", error);
                    reject(error);
                } else {
                    console.log(body);
                    resolve(body);
                }
                console.log("4");
            })
    })
}


async function main() {
    console.log("1");
    let res = await sendMail();
    console.log(res);
    console.log("2");
}

main();