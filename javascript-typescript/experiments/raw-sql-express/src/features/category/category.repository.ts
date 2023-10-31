import { DatabaseInterface } from '../../database/types';

export interface Category {
    id: number;
    title: string;
    description: string;
    createdAt: Date;
    updatedAt: Date;
}

export interface AddCategoryInterface {
    title: string;
    description: string;
}

interface CategoryRepositoryInterface {
    add(data: AddCategoryInterface): Promise<Category>;
    reset(): Promise<void>;
}

export class CategoryRepository implements CategoryRepositoryInterface {
    constructor(private db: DatabaseInterface) {}

    async add(data: AddCategoryInterface): Promise<Category> {
        const query =
            'INSERT INTO categories(title, description) VALUES($1, $2) RETURNING *';
        const values = [data.title, data.description];

        const result = await this.db.query(query, values);

        const category = result.rows[0];

        return {
            id: category.id,
            title: category.title,
            description: category.description,
            createdAt: category.created_at,
            updatedAt: category.updated_at,
        };
    }

    async reset(): Promise<void> {
        await this.db.query('DELETE FROM categories');
    }
}
