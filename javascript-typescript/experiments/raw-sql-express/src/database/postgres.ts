import { ClientBase, Pool, PoolClient, QueryResult } from 'pg';
import fs from 'fs/promises';
import path from 'path';

const DATABASE_URL =
    'postgresql://devcorvus@localhost:5432/raw_sql_express?schema=public';

export class PostgresDatabase {
    private pool: Pool;

    constructor() {
        this.pool = new Pool({
            connectionString: DATABASE_URL,
        });

        this.pool.on('error', (err) => {
            console.error('Unexpected error', err);
            process.exit(-1);
        });
    }

    async init() {
        const initSqlPath = path.join(__dirname, 'sql', 'init.sql');
        const query = await fs.readFile(initSqlPath, { encoding: 'utf8' });

        await this.query(query);
    }

    async query(query: string, params?: any[]) {
        return this.pool.query(query, params);
    }

    async transaction(
        cb: (client: {
            query: (query: string, params?: any[]) => Promise<void>;
        }) => Promise<void>
    ) {
        const client = await this.getClient();

        try {
            await client.query('BEGIN');
            await cb({ query: client.query });
            await client.query('COMMIT');
        } catch {
            await client.query('ROLLBACK');
        } finally {
            client.release();
        }
    }

    async getClient() {
        return this.pool.connect();
    }

    async close() {
        await this.pool.end();
    }
}
