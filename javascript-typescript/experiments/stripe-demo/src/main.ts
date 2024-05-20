import express, { Response, Request } from "express";
import Stripe from "stripe";
import dotenv from "dotenv";

dotenv.config();

const PORT = 3000;
const DOMAIN = "http://localhost:3000";

const STRIPE_API_KEY = process.env.STRIPE_API_KEY;
const STRIPE_WEBHOOK_SECRET = process.env.STRIPE_WEBHOOK_SECRET;

if (!STRIPE_API_KEY) throw new Error("Missing Stripe API Key");
if (!STRIPE_WEBHOOK_SECRET) throw new Error("Missing Stripe Webhook Secret");

const stripe = new Stripe(STRIPE_API_KEY);

const app = express();

app.use(express.static("public"));
// app.use(express.json());

app.post("/checkout", async (_req: Request, res: Response) => {
    const session = await stripe.checkout.sessions.create({
        line_items: [
            {
                price_data: {
                    currency: "usd",
                    unit_amount: 500,
                    product_data: {
                        name: "Huevos Fritos",
                        images: [
                            "https://images.unsplash.com/photo-1620572860868-45824e869129?q=80&w=1170&auto=format&fit=crop&ixlib=rb-4.0.3&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D",
                        ],
                    },
                },
                quantity: 1,
            },
        ],
        mode: "payment",
        success_url: DOMAIN + "/success.html",
        cancel_url: DOMAIN + "/cancel.html",
    });

    if (!session.url) return res.redirect("/error.html");

    res.redirect(session.url);
});

// It's important for this one to not be parsed as json
app.post(
    "/webhook",
    express.raw({ type: "application/json" }),
    async (req: Request, res: Response) => {
        const sig = req.headers["stripe-signature"]!;

        try {
            const event = stripe.webhooks.constructEvent(
                req.body,
                sig,
                STRIPE_WEBHOOK_SECRET,
            );

            // Handle events based on their type
            console.log(event.type);

            res.end();
        } catch (err) {
            if (err instanceof Error) {
                const errMsg = "Webhook error: " + err.message;

                console.error(errMsg);

                res.status(400).send(errMsg);
                return;
            }
        }
    },
);

app.listen(PORT, () => {
    console.log("Server listening on port " + PORT);
});
