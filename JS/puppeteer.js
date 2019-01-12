// To be run in lambda
// npm i puppeteer-core  chrome-aws-lambda
// package as zip and upload to lambnda function

const chromium = require("chrome-aws-lambda");
const puppeteer = require("puppeteer-core");

exports.handler = async (event, context) => {
  let result = null;
  let browser = null;

  try {
    browser = await puppeteer.launch({
      args: chromium.args,
      executablePath: await chromium.executablePath,
      headless: chromium.headless
    });

    let page = await browser.newPage();

    await page.goto(event.url || "https://example.com");

    result = await page.title();
  } catch (error) {
    return context.fail(error);
  } finally {
    if (browser !== null) {
      await browser.close();
    }
  }
  response = {
    statusCode: 200,
    body: JSON.stringify(result),
    headers: {
      "Access-Control-Allow-Origin": "*",
      "Access-Control-Allow-Methods": "GET,OPTIONS",
      "Access-Control-Allow-Headers":
        "Content-Type,X-Amz-Date,Authorization,X-Api-Key,X-Amz-Security-Token",
      "Content-Type": "application/json"
    }
  };
  console.log("Complete");
  return response;
  // return context.succeed(result);
};

