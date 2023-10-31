import { beforeAll, describe, expect, it } from 'vitest';
import { UnitOfWork } from '../../database/uow';
import { PostgresDatabase } from '../../database/postgres';
import {
    CreateUpdateProductInterface,
    ProductService,
} from './product.service';

describe('ProductService', () => {
    let service: ProductService;

    beforeAll(async () => {
        const db = new PostgresDatabase();
        await db.init();

        const uow = new UnitOfWork(db);

        service = new ProductService(uow);

        return async () => {
            await db.close();
        };
    });

    it('should create product', async () => {
        const data: CreateUpdateProductInterface = {
            title: 'Shoes',
            description: 'just shoes',
            price: 20 * 100,
            stock: 4,
            images: [
                { path: '/path/to/image1', type: 'image/png' },
                { path: '/path/to/image1', type: 'image/png' },
            ],
            categories: [{ title: 'Cloth', description: 'Vetements' }],
        };

        await expect(service.create(data)).resolves.toEqual({
            ...data,
            id: expect.any(String),
            createdAt: expect.any(Date),
            updatedAt: expect.any(Date),
            images: [
                {
                    id: expect.any(String),
                    productId: expect.any(String),
                    path: data.images[0].path,
                    type: data.images[0].type,
                    createdAt: expect.any(Date),
                },
                {
                    id: expect.any(String),
                    productId: expect.any(String),
                    path: data.images[1].path,
                    type: data.images[1].type,
                    createdAt: expect.any(Date),
                },
            ],
            categories: [
                {
                    id: expect.any(Number),
                    title: data.categories[0].title,
                    description: data.categories[0].description,
                    createdAt: expect.any(Date),
                    updatedAt: expect.any(Date),
                },
            ],
        });
    });
});
