import { afterEach, beforeAll, beforeEach, describe, expect, it } from 'vitest';
import { AddUserInterface, User, UserRepository } from './user.repository';
import { PostgresDatabase } from '../../database/postgres';

export const newUserMock: AddUserInterface = {
    name: 'fulano',
    email: 'fulano@example.com',
    password: 'fulanopass',
    countryId: 1,
    roleId: 1,
};

describe('UserRepository', () => {
    let repository: UserRepository;

    beforeAll(async () => {
        const db = new PostgresDatabase();
        await db.init();

        repository = new UserRepository(db);

        return async () => {
            await db.close();
        };
    });
    describe('before user', () => {
        afterEach(async () => {
            await repository.reset();
        });

        it('should create user', async () => {
            await expect(repository.add(newUserMock)).resolves.toEqual({
                ...newUserMock,
                id: expect.any(String),
                createdAt: expect.any(Date),
                updatedAt: expect.any(Date),
            });
        });

        it('should not create user', async () => {
            await expect(
                repository.add({} as AddUserInterface)
            ).resolves.toBeNull();
        });
    });

    describe('after user created', () => {
        let user: User;

        beforeEach(async () => {
            await repository.add(newUserMock);
            user = (await repository.findByEmail(newUserMock.email)) as User;

            return async () => {
                await repository.reset();
            };
        });

        it('should get user by id', async () => {
            await expect(repository.findById(user.id)).resolves.toEqual({
                ...newUserMock,
                id: expect.any(String),
                createdAt: expect.any(Date),
                updatedAt: expect.any(Date),
            });
        });

        it('should get user by email', async () => {
            await expect(
                repository.findByEmail(newUserMock.email)
            ).resolves.toEqual({
                ...newUserMock,
                id: expect.any(String),
                createdAt: expect.any(Date),
                updatedAt: expect.any(Date),
            });
        });

        it('should not found user by email', async () => {
            await expect(repository.findByEmail('@')).resolves.toBeNull();
        });

        it('should update user password', async () => {
            await expect(
                repository.updatePassword(user.id, 'newfulanopass')
            ).resolves.toBeUndefined();
        });
    });
});
