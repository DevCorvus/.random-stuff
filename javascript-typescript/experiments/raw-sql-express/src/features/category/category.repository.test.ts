import { afterEach, beforeAll, describe, it, expect } from 'vitest';
import {
    AddCategoryInterface,
    CategoryRepository,
} from './category.repository';
import { PostgresDatabase } from '../../database/postgres';

const data: AddCategoryInterface = {
    title: 'Cloth',
    description: 'just clothes',
};

describe('ProductImageRepository', () => {
    let repository: CategoryRepository;

    beforeAll(async () => {
        const db = new PostgresDatabase();
        await db.init();

        repository = new CategoryRepository(db);

        return async () => {
            await db.close();
        };
    });

    describe('before category', () => {
        afterEach(async () => {
            await repository.reset();
        });

        it('should create category', async () => {
            await expect(repository.add(data)).resolves.toEqual({
                ...data,
                id: expect.any(Number),
                createdAt: expect.any(Date),
                updatedAt: expect.any(Date),
            });
        });
    });
});
