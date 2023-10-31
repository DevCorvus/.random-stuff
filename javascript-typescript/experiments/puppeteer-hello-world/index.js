import puppeteer from "puppeteer";

async function openPage() {
  const browser = await puppeteer.launch({
    headless: false,
    slowMo: 500,
  });

  const page = await browser.newPage();
  await page.goto("https://www.example.com");
  await page.close();
}

// openPage();

async function takeScreenshot() {
  const browser = await puppeteer.launch({
    headless: "new",
  });

  const page = await browser.newPage();
  await page.goto("https://www.example.com");
  await page.screenshot({ path: "example.png" });

  await browser.close();
}

// takeScreenshot();

async function navigateWebPage() {
  const browser = await puppeteer.launch({
    slowMo: 200,
    headless: false,
  });
  const page = await browser.newPage();
  await page.goto("https://quotes.toscrape.com");
  await page.click('a[href="/login"]');
  await new Promise((resolve) => setTimeout(resolve, 3000));
  await browser.close();
}

// navigateWebPage();

async function getDataFromWebPage() {
  const browser = await puppeteer.launch({
    slowMo: 200,
    headless: false,
  });
  const page = await browser.newPage();
  await page.goto("https://www.example.com");
  const data = await page.evaluate(() => {
    let title = document.querySelector("h1").innerText;
    let description = document.querySelector("p").innerText;
    return {
      title,
      description,
    };
  });
  console.log(data);
  await browser.close();
}

// getDataFromWebPage();

async function handleDynamicWebPage() {
  const browser = await puppeteer.launch({
    headless: false,
    slowMo: 200,
  });
  const page = await browser.newPage();
  await page.goto("https://quotes.toscrape.com");
  //   await page.waitForSelector('div[data-loaded="true"]');
  const data = await page.evaluate(() => {
    const quotes = document.querySelectorAll(".quote");
    const data = [...quotes].map((quote) => {
      const quoteText = quote.querySelector(".text").innerText;
      const author = quote.querySelector(".author").innerText;
      const tags = [...quote.querySelectorAll(".tag")].map(
        (tag) => tag.innerText,
      );
      return {
        quoteText,
        author,
        tags,
      };
    });
    return data;
  });
  console.log(data);
  await browser.close();
}

// handleDynamicWebPage();
