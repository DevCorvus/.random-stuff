import { afterEach, beforeAll, describe, it, expect, beforeEach } from 'vitest';
import { PostgresDatabase } from '../../database/postgres';
import {
    AddProductInterface,
    Product,
    ProductRepository,
} from './product.repository';

const newProductMock: AddProductInterface = {
    title: 'Shoes',
    description: 'Just shoes',
    price: 20 * 100,
    stock: 4,
};

describe('ProductRepository', () => {
    let repository: ProductRepository;

    beforeAll(async () => {
        const db = new PostgresDatabase();
        await db.init();

        repository = new ProductRepository(db);

        return async () => {
            await db.close();
        };
    });

    describe('before product', () => {
        afterEach(async () => {
            await repository.reset();
        });

        it('should create product', async () => {
            await expect(
                repository.add(newProductMock)
            ).resolves.toEqual({
                ...newProductMock,
                id: expect.any(String),
                createdAt: expect.any(Date),
                updatedAt: expect.any(Date),
            });
        });
    });

    describe('after product created', () => {
        let product: Product;

        beforeEach(async () => {
            product = await repository.add(newProductMock);

            return async () => {
                await repository.reset();
            };
        });

        it('should get product by id', async () => {
            await expect(
                repository.findById(product.id)
            ).resolves.toEqual({
                ...newProductMock,
                id: expect.any(String),
                createdAt: expect.any(Date),
                updatedAt: expect.any(Date),
            });
        });
    });
});
