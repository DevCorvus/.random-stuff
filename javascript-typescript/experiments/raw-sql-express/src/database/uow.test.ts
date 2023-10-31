import { afterEach, beforeAll, describe, expect, it } from 'vitest';
import { PostgresDatabase } from './postgres';
import { UnitOfWork } from './uow';
import {
    AddUserInterface,
    UserRepository,
} from '../features/user/user.repository';

export const newUserMock: AddUserInterface = {
    name: 'fulano',
    email: 'fulano@example.com',
    password: 'fulanopass',
    countryId: 1,
    roleId: 1,
};

export const anotherNewUserMock: AddUserInterface = {
    name: 'fulana',
    email: 'fulana@example.com',
    password: 'fulanapass',
    countryId: 2,
    roleId: 2,
};

describe('UnitOfWork', () => {
    let uow: UnitOfWork;
    let userRepository: UserRepository;

    beforeAll(async () => {
        const db = new PostgresDatabase();

        uow = new UnitOfWork(db);

        userRepository = new UserRepository(db);

        return async () => {
            await db.close();
        };
    });

    describe('before users', () => {
        afterEach(async () => {
            await userRepository.reset();
        });

        it('should commit two users', async () => {
            await expect(
                uow.transaction(async (repo) => {
                    await repo.user.add(newUserMock);
                    await repo.user.add(anotherNewUserMock);
                })
            ).resolves.toBeTruthy();

            await expect(
                userRepository.findByEmail(newUserMock.email)
            ).resolves.not.toBeNull();

            await expect(
                userRepository.findByEmail(anotherNewUserMock.email)
            ).resolves.not.toBeNull();
        });

        it('should rollback two users with the same email', async () => {
            await expect(
                uow.transaction(async (repo) => {
                    await repo.user.add(newUserMock);
                    await repo.user.add(newUserMock);
                })
            ).resolves.toBeTruthy();

            await expect(
                userRepository.findByEmail(newUserMock.email)
            ).resolves.toBeNull();
        });
    });
});
