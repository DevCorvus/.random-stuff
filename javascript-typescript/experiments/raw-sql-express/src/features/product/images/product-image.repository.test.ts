import { afterEach, beforeAll, describe, it, expect } from 'vitest';
import {
    AddProductImageInterface,
    ProductImageRepository,
} from './product-image.repository';
import { PostgresDatabase } from '../../../database/postgres';
import { Product, ProductRepository } from '../product.repository';

describe('ProductImageRepository', () => {
    let product: Product;
    let repository: ProductImageRepository;

    beforeAll(async () => {
        const db = new PostgresDatabase();
        await db.init();

        repository = new ProductImageRepository(db);

        const productRepository = new ProductRepository(db);

        product = await productRepository.add({
            title: 'Something',
            description: 'whatever',
            price: 100,
            stock: 2,
        });

        return async () => {
            await productRepository.reset();
            await db.close();
        };
    });

    describe('before product image', () => {
        afterEach(async () => {
            await repository.reset();
        });

        it('should create product image', async () => {
            const data: AddProductImageInterface = {
                productId: product.id,
                type: 'image/png',
                path: '/path/to/image',
            };

            await expect(repository.add(data)).resolves.toEqual({
                ...data,
                id: expect.any(String),
                createdAt: expect.any(Date),
            });
        });
    });
});
