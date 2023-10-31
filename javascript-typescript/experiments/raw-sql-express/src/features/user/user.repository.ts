import { DatabaseInterface } from '../../database/types';

export interface User {
    id: string;
    name: string;
    email: string;
    password: string;
    countryId: number;
    roleId: number;
    createdAt: string;
    updatedAt: string;
}

export interface AddUserInterface {
    name: string;
    email: string;
    password: string;
    countryId: number;
    roleId: number;
}

interface UserRepositoryInterface {
    add(data: AddUserInterface): Promise<User | null>;
    findById(id: string): Promise<User | null>;
    findByEmail(email: string): Promise<User | null>;
    updatePassword(id: string, newPassword: string): Promise<void>;
    reset(): Promise<void>;
}

export class UserRepository implements UserRepositoryInterface {
    constructor(private db: DatabaseInterface) {}

    async add({
        name,
        email,
        password,
        countryId,
        roleId,
    }: AddUserInterface): Promise<User | null> {
        const query =
            'INSERT INTO users(name, email, password, country_id, role_id) VALUES($1, $2, $3, $4, $5) RETURNING *';
        const values = [name, email, password, countryId, roleId];

        try {
            const result = await this.db.query(query, values);
            const newUser = result.rows[0];
            return this.format(newUser);
        } catch {
            return null;
        }
    }

    async findById(id: string): Promise<User | null> {
        const query =
            'SELECT id, name, email, password, country_id, role_id, created_at, updated_at FROM users WHERE id = $1';
        const values = [id];

        const result = await this.db.query(query, values);

        if (result.rowCount === 0) {
            return null;
        } else {
            const user = result.rows[0];
            return this.format(user);
        }
    }

    async findByEmail(email: string): Promise<User | null> {
        const query =
            'SELECT id, name, email, password, country_id, role_id, created_at, updated_at FROM users WHERE email = $1';
        const values = [email];

        const result = await this.db.query(query, values);

        if (result.rowCount === 0) {
            return null;
        } else {
            const user = result.rows[0];
            return this.format(user);
        }
    }

    async updatePassword(id: string, newPassword: string): Promise<void> {
        const query = 'UPDATE users SET password = $2 WHERE id = $1';
        const values = [id, newPassword];

        await this.db.query(query, values);
    }

    async reset() {
        const query = 'DELETE FROM users';
        await this.db.query(query);
    }

    private format(data: any): User {
        return {
            id: data.id,
            name: data.name,
            email: data.email,
            password: data.password,
            countryId: data.country_id,
            roleId: data.role_id,
            createdAt: data.created_at,
            updatedAt: data.updated_at,
        };
    }
}
