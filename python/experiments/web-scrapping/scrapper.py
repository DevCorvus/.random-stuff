import requests
from bs4 import BeautifulSoup, Tag

BASE_URL = "https://webscraper.io/test-sites/e-commerce/allinone"

req = requests.get(BASE_URL)
soup = BeautifulSoup(req.text, "html.parser")

product_cards = soup.find_all("div", class_="card-body")

products = []
for product_card in product_cards:
    if product_card and isinstance(product_card, Tag):
        product = {}

        product_anchor = product_card.find("a", class_="title")
        product_price = product_card.find("h4", class_="price")
        product_description = product_card.find("p", class_="description")
        product_rating = product_card.find("p", attrs={"data-rating": True})
        product_reviews = product_card.find("p", class_="review-count")
        product_url = product_card.find("a", class_="title")

        product["title"] = product_anchor.get_text() if product_anchor else ""
        product["price"] = product_price.get_text() if product_price else ""
        product["description"] = (
            product_description.get_text() if product_description else ""
        )
        product["rating"] = (
            int(f"{product_rating.get('data-rating')}")
            if isinstance(product_rating, Tag)
            else -1
        )
        product["reviews"] = (
            int(product_reviews.get_text().split(" ")[0]) if product_reviews else -1
        )
        product["url"] = (
            product_anchor.get("href") if isinstance(product_anchor, Tag) else ""
        )

        products.append(product)


for product in products:
    print(product)
