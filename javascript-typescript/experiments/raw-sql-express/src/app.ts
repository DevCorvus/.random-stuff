import express, { Request, Response } from 'express';

const PORT = 8080;

export class Application {
    async init() {
        const app = express();

        app.get('/', (req: Request, res: Response) => {
            res.send('Hello World!');
        });

        app.listen(PORT, () => {
            console.log('Server started at :' + PORT);
        });
    }
}
