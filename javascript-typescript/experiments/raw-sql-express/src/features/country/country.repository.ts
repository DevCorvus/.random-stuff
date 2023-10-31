import { DatabaseInterface } from '../../database/types';

export interface Country {
    id: string;
    name: string;
    code: string;
}

interface CountryRepositoryInterface {
    getIdByCode(code: string): Promise<string | null>;
}

export class CountryRepository implements CountryRepositoryInterface {
    constructor(private db: DatabaseInterface) {}

    async getIdByCode(code: string): Promise<string | null> {
        const query = 'SELECT id FROM countries WHERE code = $1';
        const values = [code];

        const result = await this.db.query(query, values);

        if (result.rowCount === 0) {
            return null;
        }

        return result.rows[0].id;
    }
}
