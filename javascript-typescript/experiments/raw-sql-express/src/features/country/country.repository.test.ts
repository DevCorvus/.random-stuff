import { it, describe, beforeAll, expect } from 'vitest';
import { CountryRepository } from './country.repository';
import { PostgresDatabase } from '../../database/postgres';

describe('CountryRepository', () => {
    let repository: CountryRepository;

    beforeAll(async () => {
        const db = new PostgresDatabase();
        await db.init();

        repository = new CountryRepository(db);

        return async () => {
            await db.close();
        };
    });

    it('should get country id by code', async () => {
        expect({ id: await repository.getIdByCode('VE') }).toEqual({
            id: expect.any(Number),
        });
    });

    it('should not found country id by code', async () => {
        await expect(repository.getIdByCode('XX')).resolves.toBeNull();
    });
});
