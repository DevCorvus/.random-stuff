import { Application } from './app';

const app = new Application();

(async () => {
    await app.init();
})();
